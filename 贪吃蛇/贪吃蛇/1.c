#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>

#define U 1
#define D 2
#define L 3
#define R 4

int status;
unsigned sleeptime;
unsigned score;
unsigned add;
int ipause;

typedef struct {        //玩家信息
	char name[11];
	unsigned score;
	char date[7];
	char time[7];
}player;

player prescore;

void pos(int x, int y)                    //设置光标位置
{
	COORD POS;
	POS.X = x;
	POS.Y = y;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, POS);
}

typedef struct SNAKE{                   //蛇身结构体
	int x;
	int y;
	struct SNAKE *next;
}snake;

snake *head;
snake *food;

void gamecircle();

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

void pause()    //暂停游戏
{
	if (ipause)
	{
		while (1)
		{
			Sleep(300);
			if (GetAsyncKeyState(VK_SPACE))
				break;
		}
	}
}

void window()                    //设置控制台
{
	system("mode con cols=150 lines=40");
}

void welcome()
{
	pos(15, 10);
	printf("欢迎来到贪吃蛇v0.9");
	pos(25, 11);
	printf("作者：xyz\n\n");
	system("pause");
	system("cls");

	pos(15, 10);
	printf("请通过方向键\"↑↓←→\"控制蛇蛇，按住\"CTRL\"键可以冲刺哦！");
	pos(15, 11);
	printf("字母\"Q\"键加速，字母\"W\"键减速，按下空格键暂停游戏。");
	pos(15, 13);
	printf("现在就开始吧！\n\n");

	system("pause");
}

void printboundary()                  //打印游戏边框
{
	int i;

	system("cls");

	for (i = 0; i < 100; i += 2)
	{
		pos(i, 0);
		printf("■");
		pos(i, 34);
		printf("■");
	}
	for (i = 0; i < 35; i++)
	{
		pos(0, i);
		printf("■");
		pos(98, i);
		printf("■");
	}
	putchar('\n');
}

void printsnake()                     //打印初始蛇
{
	int i;
	snake *tail;
	tail = (snake*)malloc(sizeof(snake));

    tail->x = 24;
	tail->y = 15;
	tail->next = NULL;

	for (i = 1; i <= 4; i++)
	{
		head = (snake*)malloc(sizeof(snake));
		head->x = 24 + 2 * i;
		head->y = 15;
		head->next = tail;
		tail = head;
	}

	while (tail != NULL)
	{
		pos(tail->x, tail->y);
		printf("■");
		tail = tail->next;
	}
}

int checkfood()                   //检查食物是否与蛇身重合
{
	snake *check;
	check = head;

	while (check != NULL)
	{
		if ((check->x == food->x) && (check->y == food->y))
			return 1;
		else check = check->next;
	}
	return 0;
}

void printfood()                   //打印食物
{
	srand((unsigned)time(NULL));

	do
	{
		food = (snake*)malloc(sizeof(snake));
		do  food->x = rand() % (95) + 2; 
		while (food->x % 2 != 0);

		food->y = rand() % (33) + 1;
	} while (checkfood());
	
	pos(food->x, food->y);
	printf("■");
}

void swapinfo(player *x, player *y)      //交换分数信息以供排名
{
	player temp = *x;
	*x = *y;
	*y = temp;
}

void rank()              //按得分排名重新写入rank文件
{
	FILE *fp;
	player grp[20];
	int n,n1;
	int i,j;

	fp = fopen("1.bin", "r");
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

	fp = fopen("1.bin", "w");
	n1 = 0;
	while (n1 != n)
	{
		fprintf(fp, "%s %u %s %s\n", grp[n1].name, grp[n1].score, grp[n1].date, grp[n1].time);
		n1++;
		if (n1 >= 10) break;
	}
	fclose(fp);
}

void displayrank();

int EndGame()                    //结束游戏
{
	FILE *fp;
	player user;

	free(head);
	pos(110, 8);
	printf("蛇蛇不甘此生，选择了死亡......");
	pos(110, 10);
	printf("您的得分：%d", score);
	pos(110, 12);

	DisplayCursor();
	printf("您的大名(英文输入)：");
	scanf("%s", &user.name);

	fp = fopen("1.bin", "a");

	time_t current = time(NULL);
	struct tm *timer = localtime(&current);

	fprintf(fp, "%s %u %d%02d%02d %02d%02d%02d\n", user.name, score, timer->tm_year - 100, timer->tm_mon + 1, timer->tm_mday, timer->tm_hour, timer->tm_min, timer->tm_sec);
	fclose(fp);

	rank();

	pos(110, 14);
	system("pause");
	system("cls");

	displayrank();
}

void displayrank()            //显示排行榜
{
	FILE *fp;
	player grp[20];
	int n;
	int is = 0;
	int num = 0;
	int n0 = 0;
	int con;

	pos(39, 4);
	printf("排行榜");
	pos(20, 6);
	printf("名次      大名      得分      日期      时间");
	fp = fopen("1.bin", "r");
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
		pos(20, n + 7);
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

void move()            //蛇运行
{
	snake *nexthead;
	snake *scan;
	nexthead = (snake*)malloc(sizeof(snake));

	if (status == U)
	{
		nexthead->x = head->x;
		nexthead->y = head->y - 1;
		nexthead->next = head;

		if ((nexthead->x == food->x) && (nexthead->y == food->y)) //头前有食物
		{
			head = nexthead;
			score += add;
			free(food);
			printfood();
		}			
		else                   //无食物
		{
			head = nexthead;
			pos(head->x, head->y);
			printf("■");

			scan = head;

			while (scan->next->next != NULL)
			{
				if ((nexthead->x == scan->next->x) && (nexthead->y == scan->next->y))   //检查是否撞到自己
					EndGame();
				scan = scan->next;
			}

			if ((nexthead->x == scan->x) && (nexthead->y == scan->y))                  //检查是否撞到自己
				EndGame();
			if ((nexthead->x == scan->next->x) && (nexthead->y == scan->next->y))
				EndGame();
			if (nexthead->x == 0 || nexthead->x == 98 || nexthead->y == 0 || nexthead->y == 34)     //检查是否撞到墙
				EndGame();

			pos(scan->next->x, scan->next->y);
			printf("  ");

			free(scan->next);
			scan->next = NULL;
		}
	}
	else if (status == D)
	{
		nexthead->x = head->x;
		nexthead->y = head->y + 1;
		nexthead->next = head;

		if ((nexthead->x == food->x) && (nexthead->y == food->y)) //头前有食物
		{
			head = nexthead;
			score += add;
			free(food);
			printfood();
		}
		else
		{
			head = nexthead;
			pos(head->x, head->y);
			printf("■");

			scan = head;

			while (scan->next->next != NULL)
			{
				if ((nexthead->x == scan->next->x) && (nexthead->y == scan->next->y))
					EndGame();
				scan = scan->next;
			}

			if ((nexthead->x == scan->x) && (nexthead->y == scan->y))
				EndGame();
			if ((nexthead->x == scan->next->x) && (nexthead->y == scan->next->y))
				EndGame();
			if (nexthead->x == 0 || nexthead->x == 98 || nexthead->y == 0 || nexthead->y == 34)
				EndGame();

			pos(scan->next->x, scan->next->y);
			printf("  ");

			free(scan->next);
			scan->next = NULL;
		}
	}
	else if (status == L)
	{
		nexthead->x = head->x - 2;
		nexthead->y = head->y;
		nexthead->next = head;

		if ((nexthead->x == food->x) && (nexthead->y == food->y)) //头前有食物
		{
			head = nexthead;
			score += add;
			free(food);
			printfood();
		}
		else
		{
			head = nexthead;
			pos(head->x, head->y);
			printf("■");

			scan = head;

			while (scan->next->next != NULL)
			{
				if ((nexthead->x == scan->next->x) && (nexthead->y == scan->next->y))
					EndGame();
				scan = scan->next;
			}

			if ((nexthead->x == scan->x) && (nexthead->y == scan->y))
				EndGame();
			if ((nexthead->x == scan->next->x) && (nexthead->y == scan->next->y))
				EndGame();
			if (nexthead->x == 0 || nexthead->x == 98 || nexthead->y == 0 || nexthead->y == 34)
				EndGame();

			pos(scan->next->x, scan->next->y);
			printf("  ");

			free(scan->next);
			scan->next = NULL;
		}
	}
	else if (status == R)
	{
		nexthead->x = head->x + 2;
		nexthead->y = head->y;
		nexthead->next = head;

		if ((nexthead->x == food->x) && (nexthead->y == food->y)) //头前有食物
		{
			head = nexthead;
			score += add;
			free(food);
			printfood();
		}
		else
		{
			head = nexthead;
			pos(head->x, head->y);
			printf("■");

			scan = head;

			while (scan->next->next != NULL)
			{
				if ((nexthead->x == scan->next->x) && (nexthead->y == scan->next->y))
					EndGame();
				scan = scan->next;
			}

			if ((nexthead->x == scan->x) && (nexthead->y == scan->y))
				EndGame();
			if ((nexthead->x == scan->next->x) && (nexthead->y == scan->next->y))
				EndGame();
			if (nexthead->x == 0 || nexthead->x == 98 || nexthead->y == 0 || nexthead->y == 34)
				EndGame();

			pos(scan->next->x, scan->next->y);
			printf("  ");

			free(scan->next);
			scan->next = NULL;
		}
	}
}

void core()                  //用户控制及核心循环
{

	unsigned tmp;

	status = R;
	sleeptime = 300;
	score = 0;
	add = 10;
	ipause = 0;
	HideCursor();

	while (1)
	{ 
		pos(110, 10);
		printf("当前得分：%d", score);

		if (GetAsyncKeyState(VK_UP) && status != D)             //方向控制
			status = U;
		else if (GetAsyncKeyState(VK_DOWN) && status != U)
			status = D;
		else if (GetAsyncKeyState(VK_LEFT) && status != R)
			status = L;
		else if (GetAsyncKeyState(VK_RIGHT) && status != L)
			status = R;
		else if (GetAsyncKeyState(VK_SPACE))     //暂停
			pause();
		else if (GetAsyncKeyState('Q'))                      //加速
		{
			if (sleeptime > 50)
			{
				sleeptime -= 50;
				if (sleeptime < 300)
					add += 2;
			}

		}
		else if (GetAsyncKeyState('W'))                    //减速
		{
			sleeptime += 50;
			if (sleeptime <= 300)
				add -= 2;
		}

		tmp = sleeptime;
		if (GetAsyncKeyState(VK_CONTROL))        //冲刺
		{
			tmp = sleeptime;
			sleeptime = 50;
		}

		ipause = 1;
		Sleep(sleeptime);
		sleeptime = tmp;
		move();
	}
}

void gamecircle()                //游戏主程序
{
	printboundary();
	printsnake();
	printfood();
	core();
}

void main()               //主函数
{
	window();
	welcome();
	gamecircle();
}