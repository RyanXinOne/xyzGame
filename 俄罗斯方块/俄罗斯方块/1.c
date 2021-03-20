#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>

enum { false0, one, two, three, four, false5 }status;         //方块状态
enum { I = 1, Lleft, Lright, O, Zleft, Zright, T }Box;       //方块选择
int grid[12][22];             //单元方格状态数组
int colour;                  //光标颜色
typedef struct {        //玩家信息
	char name[11];
	unsigned score;
	char date[7];
	char time[7];
}player;
void gamecircle();

//光标
void pos(int x, int y)
{
	COORD POS;
	POS.X = x + 10;
	POS.Y = 23 - y;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, POS);
}

void HideCursor()                      //隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void DisplayCursor()                 //显示光标
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 1 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

int color(short x)	//自定义函根据参数改变颜色 
{
	if (x >= 0 && x <= 15)//参数在0-15的范围颜色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//只有一个参数，改变字体颜色 
	else//默认的颜色白色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	return x;
}

void pause()    //暂停游戏
{
	while (1)
	{
		Sleep(300);
		if (GetAsyncKeyState('P'))
		{
			break;
		}
	}
}

//欢迎
void welcome()
{
	pos(5, 13);
	printf("欢迎来到俄罗斯方块v0.9");
	pos(15, 12);
	printf("作者：xyz\n\n");
	printf("请按P键继续...");
	pause();
}

void swapinfo(player* x, player* y)      //交换分数信息以供排名
{
	player temp = *x;
	*x = *y;
	*y = temp;
}

//结束
void endGame(int score)
{
	player user;
	player prescore;
	FILE* fp;
	player grp[20];
	int n, n1;
	int i, j;
	int is = 0;
	int num = 0;
	int n0 = 0;
	int con;
	int c;

	pos(30, 18);
	color(-1);
	printf("您的最终得分：%d\n", score);
	pos(30, 16);
	DisplayCursor();
	printf("您的大名(英文输入)：");
	scanf("%s", &user.name);

	fp = fopen("2.bin", "a");

	time_t current = time(NULL);
	struct tm* timer = localtime(&current);

	fprintf(fp, "%s %u %d%02d%02d %02d%02d%02d\n", user.name, score, timer->tm_year - 100, timer->tm_mon + 1, timer->tm_mday, timer->tm_hour, timer->tm_min, timer->tm_sec);
	fclose(fp);

	//按得分排名重新写入rank文件
	fp = fopen("2.bin", "r");
	n = 0;
	while (fscanf(fp, "%s%u%s%s", &grp[n].name, &grp[n].score, &grp[n].date, &grp[n].time) == 4)
		n++;
	fclose(fp);

	prescore = grp[n - 1];

	for (i = 0; i < n - 1; i++) {
		for (j = n - 1; j > i; j--)
			if (grp[j - 1].score <= grp[j].score)
				swapinfo(&grp[j - 1], &grp[j]);
	}

	fp = fopen("2.bin", "w");
	n1 = 0;
	while (n1 != n)
	{
		fprintf(fp, "%s %u %s %s\n", grp[n1].name, grp[n1].score, grp[n1].date, grp[n1].time);
		n1++;
		if (n1 >= 10) break;
	}
	fclose(fp);

	pos(30, 14);
	system("pause");
	system("cls");

	//显示排行榜
	pos(29, 19);
	printf("排行榜");
	pos(10, 17);
	printf("名次      大名      得分      日期      时间");
	fp = fopen("2.bin", "r");
	n = 0;
	while (fscanf(fp, "%s%u%s%s", &grp[n].name, &grp[n].score, &grp[n].date, &grp[n].time) == 4)
	{
		if (n0 == 0)
		{
			if (prescore.score == grp[n].score)
			{
				is = 1;
				num = n + 1;
				n0++;
			}
		}
		pos(10, 16 - n);
		printf("%-10d%-10.10s%-10u%-10s%-10s", n + 1, grp[n].name, grp[n].score, grp[n].date, grp[n].time);
		n++;
	}
	fclose(fp);

	putchar('\n');
	putchar('\n');
	if (is == 1)
		printf("恭喜你，当前排名第%d！！\n", num);
	else
		puts("很可惜，这次没有上榜，和蛇蛇继续努力吧！");

	putchar('\n');
	printf("要继续游戏吗？继续----\'0\'，退出----\'9\'：");
	scanf("%d", &con);

	if (con == 0)
		gamecircle();
	else
		exit(0);
}

//打印边框
void printboundray()
{
	int i;
	color(15);
	for (i = 0; i <= 22; i += 2)
	{
		pos(i, 21);
		printf("■");
		pos(i, 0);
		printf("■");
	}

	for (i = 0; i <= 21; i++)
	{
		pos(0, 21 - i);
		printf("■");
		pos(22, 21 - i);
		printf("■");
	}
}

//I型方块
void boxI(int x, int y)
{
	if (status == one || status == three)
	{
		pos(x, y + 1);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x, y - 1);
		printf("■");
		pos(x, y - 2);
		printf("■");
	}
	else if (status == two || status == four)
	{
		pos(x - 2, y);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x + 2, y);
		printf("■");
		pos(x + 4, y);
		printf("■");
	}
}

void ClboxI(int x, int y)
{
	if (status == one || status == three)
	{
		pos(x, y + 1);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x, y - 1);
		printf("  ");
		pos(x, y - 2);
		printf("  ");
	}
	else if (status == two || status == four)
	{
		pos(x - 2, y);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x + 2, y);
		printf("  ");
		pos(x + 4, y);
		printf("  ");
	}
}

//L左型方块
void boxLleft(int x, int y)
{
	if (status == one)
	{
		pos(x, y + 1);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x, y - 1);
		printf("■");
		pos(x - 2, y - 1);
		printf("■");
	}
	else if (status == two)
	{
		pos(x - 2, y + 1);
		printf("■");
		pos(x - 2, y);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x + 2, y);
		printf("■");
	}
	else if (status == three)
	{
		pos(x + 2, y + 1);
		printf("■");
		pos(x, y + 1);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x, y - 1);
		printf("■");
	}
	else if (status == four)
	{
		pos(x - 2, y);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x + 2, y);
		printf("■");
		pos(x + 2, y - 1);
		printf("■");
	}
}

void ClboxLleft(int x, int y)
{
	if (status == one)
	{
		pos(x, y + 1);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x, y - 1);
		printf("  ");
		pos(x - 2, y - 1);
		printf("  ");
	}
	else if (status == two)
	{
		pos(x - 2, y + 1);
		printf("  ");
		pos(x - 2, y);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x + 2, y);
		printf("  ");
	}
	else if (status == three)
	{
		pos(x + 2, y + 1);
		printf("  ");
		pos(x, y + 1);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x, y - 1);
		printf("  ");
	}
	else if (status == four)
	{
		pos(x - 2, y);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x + 2, y);
		printf("  ");
		pos(x + 2, y - 1);
		printf("  ");
	}
}

//L右型方块
void boxLright(int x, int y)
{
	if (status == one)
	{
		pos(x, y + 1);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x, y - 1);
		printf("■");
		pos(x + 2, y - 1);
		printf("■");
	}
	else if (status == two)
	{
		pos(x - 2, y);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x + 2, y);
		printf("■");
		pos(x - 2, y - 1);
		printf("■");
	}
	else if (status == three)
	{
		pos(x - 2, y + 1);
		printf("■");
		pos(x, y + 1);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x, y - 1);
		printf("■");
	}
	else if (status == four)
	{
		pos(x + 2, y + 1);
		printf("■");
		pos(x + 2, y);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x - 2, y);
		printf("■");
	}
}

void ClboxLright(int x, int y)
{
	if (status == one)
	{
		pos(x, y + 1);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x, y - 1);
		printf("  ");
		pos(x + 2, y - 1);
		printf("  ");
	}
	else if (status == two)
	{
		pos(x - 2, y);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x + 2, y);
		printf("  ");
		pos(x - 2, y - 1);
		printf("  ");
	}
	else if (status == three)
	{
		pos(x - 2, y + 1);
		printf("  ");
		pos(x, y + 1);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x, y - 1);
		printf("  ");
	}
	else if (status == four)
	{
		pos(x + 2, y + 1);
		printf("  ");
		pos(x + 2, y);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x - 2, y);
		printf("  ");
	}
}

//O型方块
void boxO(int x, int y)
{
	if (status == one || status == two || status == three || status == four)
	{
		pos(x, y + 1);
		printf("■");
		pos(x + 2, y + 1);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x + 2, y);
		printf("■");
	}
}

void ClboxO(int x, int y)
{
	if (status == one || status == two || status == three || status == four)
	{
		pos(x, y + 1);
		printf("  ");
		pos(x + 2, y + 1);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x + 2, y);
		printf("  ");
	}
}

//Z左型方块
void boxZleft(int x, int y)
{
	if (status == one || status == three)
	{
		pos(x - 2, y + 1);
		printf("■");
		pos(x, y + 1);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x + 2, y);
		printf("■");
	}
	else if (status == two || status == four)
	{
		pos(x + 2, y + 1);
		printf("■");
		pos(x + 2, y);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x, y - 1);
		printf("■");
	}
}

void ClboxZleft(int x, int y)
{
	if (status == one || status == three)
	{
		pos(x - 2, y + 1);
		printf("  ");
		pos(x, y + 1);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x + 2, y);
		printf("  ");
	}
	else if (status == two || status == four)
	{
		pos(x + 2, y + 1);
		printf("  ");
		pos(x + 2, y);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x, y - 1);
		printf("  ");
	}
}

//Z右型方块
void boxZright(int x, int y)
{
	if (status == one || status == three)
	{
		pos(x + 2, y + 1);
		printf("■");
		pos(x, y + 1);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x - 2, y);
		printf("■");
	}
	else if (status == two || status == four)
	{
		pos(x, y + 1);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x + 2, y);
		printf("■");
		pos(x + 2, y - 1);
		printf("■");
	}
}

void ClboxZright(int x, int y)
{
	if (status == one || status == three)
	{
		pos(x + 2, y + 1);
		printf("  ");
		pos(x, y + 1);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x - 2, y);
		printf("  ");
	}
	else if (status == two || status == four)
	{
		pos(x, y + 1);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x + 2, y);
		printf("  ");
		pos(x + 2, y - 1);
		printf("  ");
	}
}

//T型方块
void boxT(int x, int y)
{
	if (status == one)
	{
		pos(x - 2, y + 1);
		printf("■");
		pos(x, y + 1);
		printf("■");
		pos(x + 2, y + 1);
		printf("■");
		pos(x, y);
		printf("■");
	}
	else if (status == two)
	{
		pos(x, y + 1);
		printf("■");
		pos(x - 2, y);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x, y - 1);
		printf("■");
	}
	else if (status == three)
	{
		pos(x, y + 1);
		printf("■");
		pos(x - 2, y);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x + 2, y);
		printf("■");
	}
	else if (status == four)
	{
		pos(x, y + 1);
		printf("■");
		pos(x, y);
		printf("■");
		pos(x + 2, y);
		printf("■");
		pos(x, y - 1);
		printf("■");
	}
}

void ClboxT(int x, int y)
{
	if (status == one)
	{
		pos(x - 2, y + 1);
		printf("  ");
		pos(x, y + 1);
		printf("  ");
		pos(x + 2, y + 1);
		printf("  ");
		pos(x, y);
		printf("  ");
	}
	else if (status == two)
	{
		pos(x, y + 1);
		printf("  ");
		pos(x - 2, y);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x, y - 1);
		printf("  ");
	}
	else if (status == three)
	{
		pos(x, y + 1);
		printf("  ");
		pos(x - 2, y);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x + 2, y);
		printf("  ");
	}
	else if (status == four)
	{
		pos(x, y + 1);
		printf("  ");
		pos(x, y);
		printf("  ");
		pos(x + 2, y);
		printf("  ");
		pos(x, y - 1);
		printf("  ");
	}
}

//随机出现方块
void randBox(int x, int y)
{
	srand((unsigned)time(NULL));
	Box = rand() % (7) + 1;
	status = rand() % (4) + 1;

	if (Box == I)
	{
		colour = color(-1);
		boxI(x, y);
	}
	else if (Box == Lleft)
	{
		colour = color(12);
		boxLleft(x, y);
	}
	else if (Box == Lright)
	{
		colour = color(13);
		boxLright(x, y);
	}
	else if (Box == O)
	{
		colour = color(14);
		boxO(x, y);
	}
	else if (Box == Zleft)
	{
		colour = color(11);
		boxZleft(x, y);
	}
	else if (Box == Zright)
	{
		colour = color(10);
		boxZright(x, y);
	}
	else if (Box == T)
	{
		colour = color(9);
		boxT(x, y);
	}
}

//方块下落
int move(int x, int y)
{
	if (Box == I)
	{
		if (status == one || status == three)
		{
			if (grid[x / 2][y - 3] != 0)                 //检查下一格是否有方格
			{
				grid[x / 2][y + 1] = colour;                     //更新方格记录
				grid[x / 2][y] = colour;
				grid[x / 2][y - 1] = colour;
				grid[x / 2][y - 2] = colour;
				return 0;
			}
		}
		else if (status == two || status == four)
		{
			if (grid[x / 2 - 1][y - 1] != 0 || grid[x / 2][y - 1] != 0 || grid[x / 2 + 1][y - 1] != 0 || grid[x / 2 + 2][y - 1] != 0)
			{
				grid[x / 2 - 1][y] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2 + 1][y] = colour;
				grid[x / 2 + 2][y] = colour;
				return 0;
			}
		}
		ClboxI(x, y);
		boxI(x, y - 1);
		return 1;
	}
	else if (Box == Lleft)
	{
		if (status == one)
		{
			if (grid[x / 2 - 1][y - 2] != 0 || grid[x / 2][y - 2] != 0)
			{
				grid[x / 2][y + 1] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2][y - 1] = colour;
				grid[x / 2 - 1][y - 1] = colour;
				return 0;
			}
		}
		else if (status == two)
		{
			if (grid[x / 2 - 1][y - 1] != 0 || grid[x / 2][y - 1] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				grid[x / 2 - 1][y + 1] = colour;
				grid[x / 2 - 1][y] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2 + 1][y] = colour;
				return 0;
			}
		}
		else if (status == three)
		{
			if (grid[x / 2 + 1][y] != 0 || grid[x / 2][y - 2] != 0)
			{
				grid[x / 2 + 1][y + 1] = colour;
				grid[x / 2][y + 1] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2][y - 1] = colour;
				return 0;
			}
		}
		else if (status == four)
		{
			if (grid[x / 2 - 1][y - 1] != 0 || grid[x / 2][y - 1] != 0 || grid[x / 2 + 1][y - 2] != 0)
			{
				grid[x / 2 - 1][y] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2 + 1][y] = colour;
				grid[x / 2 + 1][y - 1] = colour;
				return 0;
			}
		}
		ClboxLleft(x, y);
		boxLleft(x, y - 1);
		return 1;
	}
	else if (Box == Lright)
	{
		if (status == one)
		{
			if (grid[x / 2][y - 2] != 0 || grid[x / 2 + 1][y - 2] != 0)
			{
				grid[x / 2][y + 1] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2][y - 1] = colour;
				grid[x / 2 + 1][y - 1] = colour;
				return 0;
			}
		}
		else if (status == two)
		{
			if (grid[x / 2 - 1][y - 2] != 0 || grid[x / 2][y - 1] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				grid[x / 2 - 1][y] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2 + 1][y] = colour;
				grid[x / 2 - 1][y - 1] = colour;
				return 0;
			}
		}
		else if (status == three)
		{
			if (grid[x / 2 - 1][y] != 0 || grid[x / 2][y - 2] != 0)
			{
				grid[x / 2 - 1][y + 1] = colour;
				grid[x / 2][y + 1] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2][y - 1] = colour;
				return 0;
			}
		}
		else if (status == four)
		{
			if (grid[x / 2 - 1][y - 1] != 0 || grid[x / 2][y - 1] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				grid[x / 2 + 1][y + 1] = colour;
				grid[x / 2 + 1][y] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2 - 1][y] = colour;
				return 0;
			}
		}
		ClboxLright(x, y);
		boxLright(x, y - 1);
		return 1;
	}
	else if (Box == O)
	{
		if (status == one || status == two || status == three || status == four)
		{
			if (grid[x / 2][y - 1] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				grid[x / 2][y + 1] = colour;
				grid[x / 2 + 1][y + 1] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2 + 1][y] = colour;
				return 0;
			}
		}
		ClboxO(x, y);
		boxO(x, y - 1);
		return 1;
	}
	else if (Box == Zleft)
	{
		if (status == one || status == three)
		{
			if (grid[x / 2 - 1][y] != 0 || grid[x / 2][y - 1] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				grid[x / 2 - 1][y + 1] = colour;
				grid[x / 2][y + 1] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2 + 1][y] = colour;
				return 0;
			}
		}
		else if (status == two || status == four)
		{
			if (grid[x / 2][y - 2] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				grid[x / 2 + 1][y + 1] = colour;
				grid[x / 2 + 1][y] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2][y - 1] = colour;
				return 0;
			}
		}
		ClboxZleft(x, y);
		boxZleft(x, y - 1);
		return 1;
	}
	else if (Box == Zright)
	{
		if (status == one || status == three)
		{
			if (grid[x / 2 - 1][y - 1] != 0 || grid[x / 2][y - 1] != 0 || grid[x / 2 + 1][y] != 0)
			{
				grid[x / 2 + 1][y + 1] = colour;
				grid[x / 2][y + 1] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2 - 1][y] = colour;
				return 0;
			}
		}
		else if (status == two || status == four)
		{
			if (grid[x / 2][y - 1] != 0 || grid[x / 2 + 1][y - 2] != 0)
			{
				grid[x / 2][y + 1] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2 + 1][y] = colour;
				grid[x / 2 + 1][y - 1] = colour;
				return 0;
			}
		}
		ClboxZright(x, y);
		boxZright(x, y - 1);
		return 1;
	}
	else if (Box == T)
	{
		if (status == one)
		{
			if (grid[x / 2 - 1][y] != 0 || grid[x / 2][y - 1] != 0 || grid[x / 2 + 1][y] != 0)
			{
				grid[x / 2 - 1][y + 1] = colour;
				grid[x / 2][y + 1] = colour;
				grid[x / 2 + 1][y + 1] = colour;
				grid[x / 2][y] = colour;
				return 0;
			}
		}
		else if (status == two)
		{
			if (grid[x / 2 - 1][y - 1] != 0 || grid[x / 2][y - 2] != 0)
			{
				grid[x / 2][y + 1] = colour;
				grid[x / 2 - 1][y] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2][y - 1] = colour;
				return 0;
			}
		}
		else if (status == three)
		{
			if (grid[x / 2 - 1][y - 1] != 0 || grid[x / 2][y - 1] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				grid[x / 2][y + 1] = colour;
				grid[x / 2 - 1][y] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2 + 1][y] = colour;
				return 0;
			}
		}
		else if (status == four)
		{
			if (grid[x / 2][y - 2] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				grid[x / 2][y + 1] = colour;
				grid[x / 2][y] = colour;
				grid[x / 2 + 1][y] = colour;
				grid[x / 2][y - 1] = colour;
				return 0;
			}
		}
		ClboxT(x, y);
		boxT(x, y - 1);
		return 1;
	}
}

int lmove(int x, int y)                                    //方块左移
{
	if (Box == I)
	{
		if (status == one || status == three)
		{
			if (grid[x / 2 - 1][y + 1] != 0 || grid[x / 2 - 1][y] != 0 || grid[x / 2 - 1][y - 1] != 0 || grid[x / 2 - 1][y - 2] != 0)                 //检查左方是否有方格
			{
				return 0;
			}
		}
		else if (status == two || status == four)
		{
			if (grid[x / 2 - 2][y] != 0)
			{
				return 0;
			}
		}
		ClboxI(x, y);
		boxI(x - 2, y);
		return 1;
	}
	else if (Box == Lleft)
	{
		if (status == one)
		{
			if (grid[x / 2 - 1][y + 1] != 0 || grid[x / 2 - 1][y] != 0 || grid[x / 2 - 2][y - 1] != 0)
			{
				return 0;
			}
		}
		else if (status == two)
		{
			if (grid[x / 2 - 2][y + 1] != 0 || grid[x / 2 - 2][y] != 0)
			{
				return 0;
			}
		}
		else if (status == three)
		{
			if (grid[x / 2 - 1][y + 1] != 0 || grid[x / 2 - 1][y] != 0 || grid[x / 2 - 1][y - 1] != 0)
			{
				return 0;
			}
		}
		else if (status == four)
		{
			if (grid[x / 2 - 2][y] != 0 || grid[x / 2][y - 1] != 0)
			{
				return 0;
			}
		}
		ClboxLleft(x, y);
		boxLleft(x - 2, y);
		return 1;
	}
	else if (Box == Lright)
	{
		if (status == one)
		{
			if (grid[x / 2 - 1][y + 1] != 0 || grid[x / 2 - 1][y] != 0 || grid[x / 2 - 1][y - 1] != 0)
			{
				return 0;
			}
		}
		else if (status == two)
		{
			if (grid[x / 2 - 2][y] != 0 || grid[x / 2 - 2][y - 1] != 0)
			{
				return 0;
			}
		}
		else if (status == three)
		{
			if (grid[x / 2 - 2][y + 1] != 0 || grid[x / 2 - 1][y] != 0 || grid[x / 2 - 1][y - 1] != 0)
			{
				return 0;
			}
		}
		else if (status == four)
		{
			if (grid[x / 2][y + 1] != 0 || grid[x / 2 - 2][y] != 0)
			{
				return 0;
			}
		}
		ClboxLright(x, y);
		boxLright(x - 2, y);
		return 1;
	}
	else if (Box == O)
	{
		if (status == one || status == two || status == three || status == four)
		{
			if (grid[x / 2 - 1][y + 1] != 0 || grid[x / 2 - 1][y] != 0)
			{
				return 0;
			}
		}
		ClboxO(x, y);
		boxO(x - 2, y);
		return 1;
	}
	else if (Box == Zleft)
	{
		if (status == one || status == three)
		{
			if (grid[x / 2 - 2][y + 1] != 0 || grid[x / 2 - 1][y] != 0)
			{
				return 0;
			}
		}
		else if (status == two || status == four)
		{
			if (grid[x / 2][y + 1] != 0 || grid[x / 2 - 1][y] != 0 || grid[x / 2 - 1][y - 1] != 0)
			{
				return 0;
			}
		}
		ClboxZleft(x, y);
		boxZleft(x - 2, y);
		return 1;
	}
	else if (Box == Zright)
	{
		if (status == one || status == three)
		{
			if (grid[x / 2 - 1][y + 1] != 0 || grid[x / 2 - 2][y] != 0)
			{
				return 0;
			}
		}
		else if (status == two || status == four)
		{
			if (grid[x / 2 - 1][y + 1] != 0 || grid[x / 2 - 1][y] != 0 || grid[x / 2][y - 1] != 0)
			{
				return 0;
			}
		}
		ClboxZright(x, y);
		boxZright(x - 2, y);
		return 1;
	}
	else if (Box == T)
	{
		if (status == one)
		{
			if (grid[x / 2 - 2][y + 1] != 0 || grid[x / 2 - 1][y] != 0)
			{
				return 0;
			}
		}
		else if (status == two)
		{
			if (grid[x / 2 - 1][y + 1] != 0 || grid[x / 2 - 2][y] != 0 || grid[x / 2 - 1][y - 1] != 0)
			{
				return 0;
			}
		}
		else if (status == three)
		{
			if (grid[x / 2 - 1][y + 1] != 0 || grid[x / 2 - 2][y] != 0)
			{
				return 0;
			}
		}
		else if (status == four)
		{
			if (grid[x / 2 - 1][y + 1] != 0 || grid[x / 2 - 1][y] != 0 || grid[x / 2 - 1][y - 1] != 0)
			{
				return 0;
			}
		}
		ClboxT(x, y);
		boxT(x - 2, y);
		return 1;
	}
}

int rmove(int x, int y)                                    //方块左移
{
	if (Box == I)
	{
		if (status == one || status == three)
		{
			if (grid[x / 2 + 1][y + 1] != 0 || grid[x / 2 + 1][y] != 0 || grid[x / 2 + 1][y - 1] != 0 || grid[x / 2 + 1][y - 2] != 0)                 //检查右方是否有方格
			{
				return 0;
			}
		}
		else if (status == two || status == four)
		{
			if (grid[x / 2 + 3][y] != 0)
			{
				return 0;
			}
		}
		ClboxI(x, y);
		boxI(x + 2, y);
		return 1;
	}
	else if (Box == Lleft)
	{
		if (status == one)
		{
			if (grid[x / 2 + 1][y + 1] != 0 || grid[x / 2 + 1][y] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				return 0;
			}
		}
		else if (status == two)
		{
			if (grid[x / 2][y + 1] != 0 || grid[x / 2 + 2][y] != 0)
			{
				return 0;
			}
		}
		else if (status == three)
		{
			if (grid[x / 2 + 2][y + 1] != 0 || grid[x / 2 + 1][y] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				return 0;
			}
		}
		else if (status == four)
		{
			if (grid[x / 2 + 2][y] != 0 || grid[x / 2 + 2][y - 1] != 0)
			{
				return 0;
			}
		}
		ClboxLleft(x, y);
		boxLleft(x + 2, y);
		return 1;
	}
	else if (Box == Lright)
	{
		if (status == one)
		{
			if (grid[x / 2 + 1][y + 1] != 0 || grid[x / 2 + 1][y] != 0 || grid[x / 2 + 2][y - 1] != 0)
			{
				return 0;
			}
		}
		else if (status == two)
		{
			if (grid[x / 2 + 2][y] != 0 || grid[x / 2][y - 1] != 0)
			{
				return 0;
			}
		}
		else if (status == three)
		{
			if (grid[x / 2 + 1][y + 1] != 0 || grid[x / 2 + 1][y] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				return 0;
			}
		}
		else if (status == four)
		{
			if (grid[x / 2 + 2][y + 1] != 0 || grid[x / 2 + 2][y] != 0)
			{
				return 0;
			}
		}
		ClboxLright(x, y);
		boxLright(x + 2, y);
		return 1;
	}
	else if (Box == O)
	{
		if (status == one || status == two || status == three || status == four)
		{
			if (grid[x / 2 + 2][y + 1] != 0 || grid[x / 2 + 2][y] != 0)
			{
				return 0;
			}
		}
		ClboxO(x, y);
		boxO(x + 2, y);
		return 1;
	}
	else if (Box == Zleft)
	{
		if (status == one || status == three)
		{
			if (grid[x / 2 + 1][y + 1] != 0 || grid[x / 2 + 2][y] != 0)
			{
				return 0;
			}
		}
		else if (status == two || status == four)
		{
			if (grid[x / 2 + 2][y + 1] != 0 || grid[x / 2 + 2][y] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				return 0;
			}
		}
		ClboxZleft(x, y);
		boxZleft(x + 2, y);
		return 1;
	}
	else if (Box == Zright)
	{
		if (status == one || status == three)
		{
			if (grid[x / 2 + 2][y + 1] != 0 || grid[x / 2 + 1][y] != 0)
			{
				return 0;
			}
		}
		else if (status == two || status == four)
		{
			if (grid[x / 2 + 1][y + 1] != 0 || grid[x / 2 + 2][y] != 0 || grid[x / 2 + 2][y - 1] != 0)
			{
				return 0;
			}
		}
		ClboxZright(x, y);
		boxZright(x + 2, y);
		return 1;
	}
	else if (Box == T)
	{
		if (status == one)
		{
			if (grid[x / 2 + 2][y + 1] != 0 || grid[x / 2 + 1][y] != 0)
			{
				return 0;
			}
		}
		else if (status == two)
		{
			if (grid[x / 2 + 1][y + 1] != 0 || grid[x / 2 + 1][y] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				return 0;
			}
		}
		else if (status == three)
		{
			if (grid[x / 2 + 1][y + 1] != 0 || grid[x / 2 + 2][y] != 0)
			{
				return 0;
			}
		}
		else if (status == four)
		{
			if (grid[x / 2 + 1][y + 1] != 0 || grid[x / 2 + 2][y] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				return 0;
			}
		}
		ClboxT(x, y);
		boxT(x + 2, y);
		return 1;
	}
}

//方块状态改变
int transform(int x, int y)
{
	status++;
	if (status > 4)
		status = 1;

	if (Box == I)
	{
		if (status == one || status == three)
		{
			if (grid[x / 2][y + 1] != 0 || grid[x / 2][y] != 0 || grid[x / 2][y - 1] != 0 || grid[x / 2][y - 2] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}
		else if (status == two || status == four)
		{
			if (grid[x / 2 - 1][y] != 0 || grid[x / 2][y] != 0 || grid[x / 2 + 1][y] != 0 || grid[x / 2 + 2][y] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}

		status--;
		if (status < 1)
			status = 4;
		ClboxI(x, y);

		status++;
		if (status > 4)
			status = 1;
		boxI(x, y);
		return 1;
	}
	else if (Box == Lleft)
	{
		if (status == one)
		{
			if (grid[x / 2][y + 1] != 0 || grid[x / 2][y] != 0 || grid[x / 2][y - 1] != 0 || grid[x / 2 - 1][y - 1] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}
		else if (status == two)
		{
			if (grid[x / 2 - 1][y + 1] != 0 || grid[x / 2 - 1][y] != 0 || grid[x / 2][y] != 0 || grid[x / 2 + 1][y] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}
		else if (status == three)
		{
			if (grid[x / 2 + 1][y + 1] != 0 || grid[x / 2][y + 1] != 0 || grid[x / 2][y] != 0 || grid[x / 2][y - 1] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}
		else if (status == four)
		{
			if (grid[x / 2 - 1][y] != 0 || grid[x / 2][y] != 0 || grid[x / 2 + 1][y] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}

		status--;
		if (status < 1)
			status = 4;
		ClboxLleft(x, y);

		status++;
		if (status > 4)
			status = 1;
		boxLleft(x, y);
		return 1;
	}
	else if (Box == Lright)
	{
		if (status == one)
		{
			if (grid[x / 2][y + 1] != 0 || grid[x / 2][y] != 0 || grid[x / 2][y - 1] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}
		else if (status == two)
		{
			if (grid[x / 2 - 1][y] != 0 || grid[x / 2][y] != 0 || grid[x / 2 + 1][y] != 0 || grid[x / 2 - 1][y - 1] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}
		else if (status == three)
		{
			if (grid[x / 2 - 1][y + 1] != 0 || grid[x / 2][y + 1] != 0 || grid[x / 2][y] != 0 || grid[x / 2][y - 1] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}
		else if (status == four)
		{
			if (grid[x / 2 + 1][y + 1] != 0 || grid[x / 2 + 1][y] != 0 || grid[x / 2][y] != 0 || grid[x / 2 - 1][y] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}

		status--;
		if (status < 1)
			status = 4;
		ClboxLright(x, y);

		status++;
		if (status > 4)
			status = 1;
		boxLright(x, y);
		return 1;
	}
	else if (Box == O)
	{
		if (status == one || status == two || status == three || status == four)
		{
			if (grid[x / 2][y + 1] != 0 || grid[x / 2 + 1][y + 1] != 0 || grid[x / 2][y] != 0 || grid[x / 2 + 1][y] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}

		status--;
		if (status < 1)
			status = 4;
		ClboxO(x, y);

		status++;
		if (status > 4)
			status = 1;
		boxO(x, y);
		return 1;
	}
	else if (Box == Zleft)
	{
		if (status == one || status == three)
		{
			if (grid[x / 2 - 1][y + 1] != 0 || grid[x / 2][y + 1] != 0 || grid[x / 2][y] != 0 || grid[x / 2 + 1][y] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}
		else if (status == two || status == four)
		{
			if (grid[x / 2 + 1][y + 1] != 0 || grid[x / 2 + 1][y] != 0 || grid[x / 2][y] != 0 || grid[x / 2][y - 1] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}

		status--;
		if (status < 1)
			status = 4;
		ClboxZleft(x, y);

		status++;
		if (status > 4)
			status = 1;
		boxZleft(x, y);
		return 1;
	}
	else if (Box == Zright)
	{
		if (status == one || status == three)
		{
			if (grid[x / 2 + 1][y + 1] != 0 || grid[x / 2][y + 1] != 0 || grid[x / 2][y] != 0 || grid[x / 2 - 1][y] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}
		else if (status == two || status == four)
		{
			if (grid[x / 2][y + 1] != 0 || grid[x / 2][y] != 0 || grid[x / 2 + 1][y] != 0 || grid[x / 2 + 1][y - 1] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}

		status--;
		if (status < 1)
			status = 4;
		ClboxZright(x, y);

		status++;
		if (status > 4)
			status = 1;
		boxZright(x, y);
		return 1;
	}
	else if (Box == T)
	{
		if (status == one)
		{
			if (grid[x / 2 - 1][y + 1] != 0 || grid[x / 2][y + 1] != 0 || grid[x / 2 + 1][y + 1] != 0 || grid[x / 2][y] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}
		else if (status == two)
		{
			if (grid[x / 2][y + 1] != 0 || grid[x / 2 - 1][y] != 0 || grid[x / 2][y] != 0 || grid[x / 2][y - 1] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}
		else if (status == three)
		{
			if (grid[x / 2][y + 1] != 0 || grid[x / 2 - 1][y] != 0 || grid[x / 2][y] != 0 || grid[x / 2 + 1][y] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}
		else if (status == four)
		{
			if (grid[x / 2][y + 1] != 0 || grid[x / 2][y] != 0 || grid[x / 2 + 1][y] != 0 || grid[x / 2][y - 1] != 0)
			{
				status--;
				if (status < 1)
					status = 4;
				return 0;
			}
		}

		status--;
		if (status < 1)
			status = 4;
		ClboxT(x, y);

		status++;
		if (status > 4)
			status = 1;
		boxT(x, y);
		return 1;
	}
}

//核心控制
void core()
{
	int j;
	int a, b;
	int x, y;
	unsigned speed;
	unsigned gamespeed = 6;
	unsigned tmp;
	int interval = 1;
	int score = 0;
	int bonus;
	int level = 1;

	while (1)
	{
		if (level == 1 && score >= 100)             //虽得分加速
		{
			level++;
			if (gamespeed > 1)
				gamespeed--;
		}
		else if (level == 2 && score >= 300)
		{
			level++;
			if (gamespeed > 1)
				gamespeed--;
		}
		else if (level == 3 && score >= 600)
		{
			level++;
			if (gamespeed > 1)
				gamespeed--;
		}
		else if (level == 4 && score >= 1000)
		{
			level++;
			if (gamespeed > 1)
				gamespeed--;
		}
		else if (level == 5 && score >= 1500)
		{
			level++;
			if (gamespeed > 1)
				gamespeed--;
		}
		pos(30, 18);
		color(15);
		printf("得分：%d", score);
		x = 10;
		y = 19;
		if (grid[x / 2][y] != 0)           //判断游戏结束
			endGame(score);
		randBox(x, y);
		speed = gamespeed;
		tmp = speed;
		Sleep(100 * gamespeed);

		while (1)
		{
			if (interval >= speed)
			{
				if (move(x, y) == 0)
					break;
				y--;
			}

			speed = tmp;

			interval++;
			if (interval > speed)
				interval = 1;

			if (GetAsyncKeyState(VK_LEFT))
			{
				while (lmove(x, y) == 1)
				{
					x = x - 2;
					break;
				}
			}
			else if (GetAsyncKeyState(VK_RIGHT))
			{
				while (rmove(x, y) == 1)
				{
					x = x + 2;
					break;
				}
			}
			else if (GetAsyncKeyState(VK_UP))
			{
				transform(x, y);
			}
			else if (GetAsyncKeyState(VK_SPACE))
			{
				speed = 0;
				tmp = speed;
			}
			else if (GetAsyncKeyState(VK_DOWN))
			{
				tmp = speed;
				speed = 1;
			}
			else if (GetAsyncKeyState('P'))
			{
				pause();
			}
			else if (GetAsyncKeyState('Q'))
			{
				if (speed > 1)
				{
					speed--;
					gamespeed--;
					tmp = speed;
				}
			}
			else if (GetAsyncKeyState('W'))
			{
				if (speed < 20)
				{
					speed++;
					gamespeed++;
					tmp = speed;
				}
			}

			if (speed == 0)
				Sleep(0);
			else
				Sleep(100);
		}

		//检查是否可消除，若是，则消除后下移一格
		for (j = 1; j <= 20; j++)
		{
			if (grid[1][j] != 0 && grid[2][j] != 0 && grid[3][j] != 0 && grid[4][j] != 0 && grid[5][j] != 0 && grid[6][j] != 0 && grid[7][j] != 0 && grid[8][j] != 0 && grid[9][j] != 0 && grid[10][j] != 0)
			{
				bonus = 0;
				do {
					score += (21 - gamespeed) * 2;
					score += bonus;
					bonus += 10;
					for (b = j + 1; b <= 20; b++)
					{
						for (a = 1; a <= 10; a++)
						{
							if (grid[a][b] != 0)
							{
								if (grid[a][b] == -1)
									color(-1);
								else if (grid[a][b] == 9)
									color(9);
								else if (grid[a][b] == 10)
									color(10);
								else if (grid[a][b] == 11)
									color(11);
								else if (grid[a][b] == 12)
									color(12);
								else if (grid[a][b] == 13)
									color(13);
								else if (grid[a][b] == 14)
									color(14);
								pos(2 * a, b - 1);
								printf("■");
								grid[a][b - 1] = grid[a][b];
							}
							else if (grid[a][b] == 0)
							{
								pos(2 * a, b - 1);
								printf("  ");
								grid[a][b - 1] = 0;
							}
						}
					}

					for (a = 1; a <= 10; a++)
					{
						pos(2 * a, 20);
						printf("  ");
						grid[a][20] = 0;
					}
				} while (grid[1][j] != 0 && grid[2][j] != 0 && grid[3][j] != 0 && grid[4][j] != 0 && grid[5][j] != 0 && grid[6][j] != 0 && grid[7][j] != 0 && grid[8][j] != 0 && grid[9][j] != 0 && grid[10][j] != 0);
			}
		}
	}
}

//游戏循环
void gamecircle()
{
	HideCursor();
	system("cls");
	printboundray();
	int i, j;
	for (i = 1; i <= 10; i++)
	{
		grid[i][0] = 15;
		grid[i][21] = 15;
	}
	for (j = 1; j <= 20; j++)
	{
		grid[0][j] = 15;
		grid[11][j] = 15;
	}
	for (i = 1; i <= 10; i++)
	{
		for (j = 1; j <= 20; j++)
			grid[i][j] = 0;
	}

	core();
}

void main()
{
	welcome();
	gamecircle();
}