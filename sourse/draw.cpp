#include "draw.h"
#include "windowsCtrl.h"
#include "gameLogic.h"
#include <stdio.h>
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <GL/glut.h>

//有关开始界面的变量
#define START_MENU_TITLE_HEIGHT 11
int startMenuOptionIndex = 0;
const char startMenuTitle[START_MENU_TITLE_HEIGHT][76] = { "五五五五五五五五五五五　　　子子子子子子子子　　　　　　棋　　棋　　　棋  ",
                                                           "　　　　五　　　　　　　　　　　　　　　　子　　　　　　棋　棋棋棋棋棋棋棋",
                                                           "　　　　五　　　　　　　　　　　　　　　子　　　　　棋棋棋棋　棋　　　棋  ", 
                                                           "　　　　五　　　　　　　　　　　　　　子　　　　　　　　棋　　棋棋棋棋棋  ", 
                                                           "　五五五五五五五五　　　　　　　　　子　　　　　　　　　棋　　棋　　　棋  ", 
                                                           "　　　五　　　　五　　　　子子子子子子子子子子子　　　棋棋棋　棋棋棋棋棋  ", 
                                                           "　　　五　　　　五　　　　　　　　　子　　　　　　　　棋棋　　棋　　　棋  ", 
                                                           "　　　五　　　　五　　　　　　　　　子　　　　　　　棋　棋　棋棋棋棋棋棋棋", 
                                                           "　　　五　　　　五　　　　　　　　　子　　　　　　　　　棋                ", 
                                                           "　　　五　　　　五　　　　　　　　　子　　　　　　　　　棋　　棋　　　棋  ", 
                                                           "五五五五五五五五五五五　　　　　子子子　　　　　　　　　棋　棋　　　　　棋"};
const char startOption[2][15] = { "   开始游戏   ", 
								  "-> 开始游戏   "};
const char helpOption[2][15] = { "   查看帮助   ", 
								 "-> 查看帮助   "};
const char exitOption[2][15] = { "   退出游戏   ", 
								 "-> 退出游戏   "};

//有关帮助页面的变量
#define HELP_PAGE_TITLE_HEIGHT 6
int helpPageOptionIndex = 0;
const char helpTitle[HELP_PAGE_TITLE_HEIGHT][63] = { "五子棋帮助",
													 "1.五子棋是一种双人对弈的纯策略型棋类游戏，是中国传统棋类之一；", 
													 "2.五子棋是在15*15的棋盘上进行的，双方轮流下子，黑棋先行；     ", 
													 "3.每次落子后，可以按下鼠标右键选择悔棋；                      ", 
													 "4.当一方在横、竖、斜方向上连成五子时，游戏结束；              ", 
													 "5.游戏结束后，按r键重新开始，按q键返回游戏设置界面。          "};
const char helpPageOption[HELP_PAGE_OPTION_NUM][39] = { "-> 返回开始菜单          制作人员     ",
														"   返回开始菜单       -> 制作人员     "};

//有关游戏设置页面的变量
int gameSettingOptionIndex = 0;
int gameModeOptionIndex = 0;
int colorTakenOptionIndex = 0;
int difficultOptionIndex = 0;
const char gameModeOption[2][2][40] = { {"   游戏模式： -> 双人博弈      人机对战",
										 "  游戏模式：    双人博弈   -> 人机对战"},
										{"· 游戏模式： -> 双人博弈      人机对战",
										 "· 游戏模式：    双人博弈   -> 人机对战"} };
const char colorTakenOption[2][2][40] = { {"  执棋颜色： -> 黑棋          白棋    ",
										   "  执棋颜色：    黑棋       -> 白棋    "},
										  {"· 执棋颜色： -> 黑棋          白棋    ",
										   "· 执棋颜色：    黑棋       -> 白棋    "} };
const char difficultOption[2][2][40] = { {"  游戏难度： -> 菜鸟          大师    ",
										  "  游戏难度：    菜鸟       -> 大师    "},
										 {"· 游戏难度： -> 菜鸟          大师    ",
										  "· 游戏难度：    菜鸟       -> 大师    "} };
const char blanketOption[40] = { "                                       " };
const char tips[3][32] = { "-----按回车键开始游戏吧！ -----",
						   "-----按Esc键返回开始界面！-----" };

//有关棋盘的变量
cv::Mat boardImage;           // 棋盘图片
cv::Mat blackChessImage;      // 黑棋图片
cv::Mat whiteChessImage;      // 白棋图片
cv::Mat blackChessLastImage;  // 标记黑棋图片
cv::Mat whiteChessLastImage;  // 标记白棋图片
GLuint boardTexture;          // 棋盘材质
GLuint blackChessTexture;     // 黑棋材质
GLuint whiteChessTexture;     // 白棋材质
GLuint blackChessLastTexture; // 标记黑棋材质
GLuint whiteChessLastTexture; // 标记白棋材质

void drawStartMenuPage()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	// 打印开始界面标题
	for (int i = 0; i < START_MENU_TITLE_HEIGHT; i++)
	{
		centerPrint(hOutput, START_MENU_TITLE_POS_Y + i, startMenuTitle[i]);
	}
	// 打印开始界面选项
	centerPrint(hOutput, START_MENU_OPTION_START_POS_Y, startOption[startMenuOptionIndex == 0]);
	centerPrint(hOutput, START_MENU_OPTION_HELP_POS_Y, helpOption[startMenuOptionIndex == 1]);
	centerPrint(hOutput, START_MENU_OPTION_EXIT_POS_Y, exitOption[startMenuOptionIndex == 2]);
}

void setStartMenuOptionIndex(int dir)
{
	// 设置开始页面选项的索引
	startMenuOptionIndex = (startMenuOptionIndex + dir) >= 0 ? (startMenuOptionIndex + dir) % START_MENU_OPTION_NUM : START_MENU_OPTION_NUM - 1;
}

int getStartMenuOptionIndex()
{
	// 返回开始界面选项的索引
	return startMenuOptionIndex;
}

void drawHelpPage()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	// 打印帮助界面标题
	for (int i = 0; i < HELP_PAGE_TITLE_HEIGHT; i++)
	{
		centerPrint(hOutput, HELP_TITLE_POS_Y + i * 2, helpTitle[i]);
	}
	// 打印帮助页面选项
	centerPrint(hOutput, HELP_PAGE_OPTION_POS_Y, helpPageOption[helpPageOptionIndex]);
}

void setHelpOptionIndex(int dir)
{	
	// 设置帮助页面选项索引
	if (helpPageOptionIndex + dir >= 0 && helpPageOptionIndex + dir <= 1)
		helpPageOptionIndex = helpPageOptionIndex + dir;
	else
		printf("\a"); // 超限警告
}

int getHelpOptionIndex()
{
	// 返回帮助页面选项索引
	return helpPageOptionIndex;
}

void drawGameSettingPage()
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	// 打印游戏设置页面标题
	centerPrint(hOutput, START_MENU_TITLE_POS_Y, "游戏设置");
	// 打印游戏设置页面第一个选项
	centerPrint(hOutput, GAME_GAME_MODE_OPTION_POS_Y, gameModeOption[gameSettingOptionIndex == 0][gameModeOptionIndex]);
	// 人机对弈模式才会显示下述选项
	if (gameModeOptionIndex == 1)
	{
		centerPrint(hOutput, GAME_COLOR_TAKEN_OPTION_POS_Y, colorTakenOption[gameSettingOptionIndex == 1][colorTakenOptionIndex]);
		centerPrint(hOutput, GAME_DIFFICULT_OPTION_POS_Y, difficultOption[gameSettingOptionIndex == 2][difficultOptionIndex]);
	}
	else
	{
		centerPrint(hOutput, GAME_COLOR_TAKEN_OPTION_POS_Y, blanketOption);
		centerPrint(hOutput, GAME_DIFFICULT_OPTION_POS_Y, blanketOption);
	}
	// 打印游戏设置页面提示
	for (int i = 0; i < GAME_SETTING_PAGE_TIPS_NUM; i++)
	{
		centerPrint(hOutput, GAME_SETTING_PAGE_TIPS_POS_Y + i * 2, tips[i]);
	}
}

void setGameSettingOptionIndex(int dir)
{
	// 设置一级选项索引
	if (gameModeOptionIndex == 0 || (gameSettingOptionIndex + dir < 0 && gameSettingOptionIndex + dir >= GAME_SETTING_OPTION_NUM)) printf("\a");  // 超限警告
	else
	{
		gameSettingOptionIndex = (gameSettingOptionIndex + dir) >= 0 ? ((gameSettingOptionIndex + dir) % GAME_SETTING_OPTION_NUM) : GAME_SETTING_OPTION_NUM - 1;
	}
}

void setGameSettingOptionInnerIndex(int dir)
{
	// 设置二级选项索引
	switch (gameSettingOptionIndex)
	{
		case 0: 
		{
			if (gameModeOptionIndex + dir < 0 || gameModeOptionIndex + dir >= GAME_SETTING_INNER_OPTION_NUM) printf("\a");
			else gameModeOptionIndex = gameModeOptionIndex + dir;
			break;
		}
		case 1:
		{
			if (colorTakenOptionIndex + dir < 0 || colorTakenOptionIndex + dir >= GAME_SETTING_INNER_OPTION_NUM) printf("\a");
			else colorTakenOptionIndex = colorTakenOptionIndex + dir;
			break;
		}
		case 2:
		{
			if (difficultOptionIndex + dir < 0 || difficultOptionIndex + dir >= GAME_SETTING_INNER_OPTION_NUM) printf("\a");
			else difficultOptionIndex = difficultOptionIndex + dir;
			break;
		}
	}
}

int getGameMode()
{
	// 返回游戏模式
	return gameModeOptionIndex;
}

int getColorTaken()
{
	// 返回执子颜色
	return colorTakenOptionIndex;
}

int getDifficult()
{
	// 返回游戏难度
	return difficultOptionIndex;
}

void initTexture()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);  //启用2D材质以及透明色混合


	// 加载棋盘图片及材质
	boardImage = cv::imread(".\\asset\\board.png", cv::IMREAD_UNCHANGED);  // 读取棋盘图片
	cv::cvtColor(boardImage, boardImage, cv::COLOR_BGRA2RGBA);  // 设置图片颜色数据为OpenGl可以识别的格式
	glGenTextures(1, &boardTexture);  // 绑定材质ID
	glBindTexture(GL_TEXTURE_2D, boardTexture);  // 启用材质 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // 设置材质采样模式
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, boardImage.cols, boardImage.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, boardImage.data);  // 生成2D材质

	// 加载黑棋图片及材质
	blackChessImage = cv::imread(".\\asset\\blackChess.png", cv::IMREAD_UNCHANGED);
	cv::cvtColor(blackChessImage, blackChessImage, cv::COLOR_BGRA2RGBA);
	glGenTextures(1, &blackChessTexture);
	glBindTexture(GL_TEXTURE_2D, blackChessTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, blackChessImage.cols, blackChessImage.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, blackChessImage.data);

	// 加载白棋图片及材质
	whiteChessImage = cv::imread(".\\asset\\whiteChess.png", cv::IMREAD_UNCHANGED);
	cv::cvtColor(whiteChessImage, whiteChessImage, cv::COLOR_BGRA2RGBA);
	glGenTextures(1, &whiteChessTexture);
	glBindTexture(GL_TEXTURE_2D, whiteChessTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, whiteChessImage.cols, whiteChessImage.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, whiteChessImage.data);

	// 加载标记黑棋图片及材质
	blackChessLastImage = cv::imread(".\\asset\\blackChessLast.png", cv::IMREAD_UNCHANGED);
	cv::cvtColor(blackChessLastImage, blackChessLastImage, cv::COLOR_BGRA2RGBA);
	glGenTextures(1, &blackChessLastTexture);
	glBindTexture(GL_TEXTURE_2D, blackChessLastTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, blackChessLastImage.cols, blackChessLastImage.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, blackChessLastImage.data);

	// 加载标记白棋图片及材质
	whiteChessLastImage = cv::imread(".\\asset\\whiteChessLast.png", cv::IMREAD_UNCHANGED);
	cv::cvtColor(blackChessLastImage, blackChessLastImage, cv::COLOR_BGRA2RGBA);
	glGenTextures(1, &whiteChessLastTexture);
	glBindTexture(GL_TEXTURE_2D, whiteChessLastTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, whiteChessLastImage.cols, whiteChessLastImage.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, whiteChessLastImage.data);
}

void drawBoard()
{
	glBindTexture(GL_TEXTURE_2D, boardTexture);  // 启用棋盘材质
	glBegin(GL_QUADS);  // 矩形绘制模式
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, -1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(1.0, -1.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, 0.0);  // 指定材质坐标以及绘制坐标
	glEnd();
	glFlush();  // 强制所有绘图指令加载
}

void drawChess()
{
	extern int chessTaken;
	extern int gameMode;
	extern int board[BOARD_SIZE][BOARD_SIZE];
	extern int currentPlayer;
	extern int gameEnd;
	extern int chessNum;
	glBindTexture(GL_TEXTURE_2D, blackChessTexture);  //启用黑棋材质
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == 1)
			{
				double centerX = BOARD_MARGIN + i * BOARD_GRID_SIZE;
				double centerY = BOARD_MARGIN + j * BOARD_GRID_SIZE;  // 计算点位在屏幕上的坐标
				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(-1.0 + (centerX - CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY - CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(0.0, 1.0); glVertex3f(-1.0 + (centerX - CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY + CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(1.0, 1.0); glVertex3f(-1.0 + (centerX + CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY + CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(1.0, 0.0); glVertex3f(-1.0 + (centerX + CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY - CHESS_SIZE) / 512.0 * 2, 0.0);
				glEnd();
			}
		}
	}
	glFlush();

	glBindTexture(GL_TEXTURE_2D, whiteChessTexture);  // 启用白棋材质
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == 2)
			{
				double centerX = BOARD_MARGIN + i * BOARD_GRID_SIZE;
				double centerY = BOARD_MARGIN + j * BOARD_GRID_SIZE;
				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(-1.0 + (centerX - CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY - CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(0.0, 1.0); glVertex3f(-1.0 + (centerX - CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY + CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(1.0, 1.0); glVertex3f(-1.0 + (centerX + CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY + CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(1.0, 0.0); glVertex3f(-1.0 + (centerX + CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY - CHESS_SIZE) / 512.0 * 2, 0.0);
				glEnd();
			}
		}
	}
	glFlush();

	if (chessNum > 0)
	{
		Move lastMove = getLastMove();  // 获得最后一步棋的坐标
		if(board[lastMove.x][lastMove.y] == BLACK_CHESS)
			glBindTexture(GL_TEXTURE_2D, blackChessLastTexture);
		else
			glBindTexture(GL_TEXTURE_2D, whiteChessLastTexture);  // 启用相应棋子的标记材质
		double centerX = BOARD_MARGIN + lastMove.x * BOARD_GRID_SIZE;
		double centerY = BOARD_MARGIN + lastMove.y * BOARD_GRID_SIZE;
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(-1.0 + (centerX - CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY - CHESS_SIZE) / 512.0 * 2, 0.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(-1.0 + (centerX - CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY + CHESS_SIZE) / 512.0 * 2, 0.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(-1.0 + (centerX + CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY + CHESS_SIZE) / 512.0 * 2, 0.0);
		glTexCoord2f(1.0, 0.0); glVertex3f(-1.0 + (centerX + CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY - CHESS_SIZE) / 512.0 * 2, 0.0);
		glEnd();
	}
	glFlush();

	if (gameMode != 0 && !chessTaken || gameEnd) return;  // 只有游戏没结束或人机对弈时轮到玩家下棋才绘制透明棋子
	switch (currentPlayer)
	{
		case BLACK_CHESS:
		{
			glBindTexture(GL_TEXTURE_2D, blackChessTexture);
			break;
		}
		case WHITE_CHESS:
		{
			glBindTexture(GL_TEXTURE_2D, whiteChessTexture);  // 加载相应颜色的棋子材质
			break;
		}
	}
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == -1)
			{
				GLfloat trueColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
				GLfloat falseColor[] = { 1.0f, 1.0f, 1.0f, 0.5f };  // 设置半透明色
				glColor4fv(falseColor);
				double centerX = BOARD_MARGIN + i * BOARD_GRID_SIZE;
				double centerY = BOARD_MARGIN + j * BOARD_GRID_SIZE;
				glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0); glVertex3f(-1.0 + (centerX - CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY - CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(0.0, 1.0); glVertex3f(-1.0 + (centerX - CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY + CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(1.0, 1.0); glVertex3f(-1.0 + (centerX + CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY + CHESS_SIZE) / 512.0 * 2, 0.0);
				glTexCoord2f(1.0, 0.0); glVertex3f(-1.0 + (centerX + CHESS_SIZE) / 512.0 * 2, 1.0 - (centerY - CHESS_SIZE) / 512.0 * 2, 0.0);
				glEnd();
				glFlush();
				glColor4fv(trueColor);  // 恢复原有的颜色
				return;
			}	
		}
}

void drawGamePage()
{
	drawBoard();        // 绘制棋盘
	drawChess();        // 绘制棋子
	glutSwapBuffers();  // 交换缓冲区使绘制内容显示到屏幕上
}