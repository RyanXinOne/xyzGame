#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <windows.h>
#include<time.h>
#include<stdlib.h>
#define TIE 2
#define EXIT 0

int aiOppo(const int x[3][3], const int y[3][3], int* chan);
int aiin(const int x[3][3], const int y[3][3], int* chan);


void pos(int x, int y)                    //设置光标位置
{
	COORD POS;
	POS.X = x;
	POS.Y = y;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, POS);
}

void frame()
{
	int i;

	pos(0, 3);
	printf("-----------");
	pos(0, 7);
	printf("-----------");

	for (i = 0; i <= 10; i++)
	{
		pos(3, i);
		printf("|");
		pos(7, i);
		printf("|");
	}
	pos(3, 3);
	printf("+");
	pos(7, 3);
	printf("+");
	pos(3, 7);
	printf("+");
	pos(7, 7);
	printf("+");
}

int aiOppo(const int x[3][3], const int y[3][3], int* chan)
{
	int i, j;
	int p, q;
	int a[3][3];
	int b[3][3];
	int tie;

	for (i = 0; i <= 2; i++)
	{
		for (j = 0; j <= 2; j++)
		{
			a[i][j] = x[i][j];
			b[i][j] = y[i][j];
		}
	}

	for (j = 0; j <= 2; j++)
	{
		for (i = 0; i <= 2; i++)
		{
			if (a[i][j] == 1 || b[i][j] == 1)
				continue;
			else
			{
				a[i][j] = 1;

				for (q = 0; q <= 2; q++)                                             //胜利判断
				{
					if (a[0][q] == 1 && a[1][q] == 1 && a[2][q] == 1)
						(*chan)--;
				}
				for (q = 0; q <= 2; q++)
				{
					if (a[q][0] == 1 && a[q][1] == 1 && a[q][2] == 1)
						(*chan)--;
				}

				if (a[0][0] == 1 && a[1][1] == 1 && a[2][2] == 1)
					(*chan)--;

				if (a[2][0] == 1 && a[1][1] == 1 && a[0][2] == 1)
					(*chan)--;

				tie = 0;                           //平局判断
				for (q = 0; q <= 2; q++)
				{
					for (p = 0; p <= 2; p++)
					{
						if (a[p][q] == 1 || b[p][q] == 1)
							tie++;
					}
				}
				if (tie == 9)
				{
					return TIE;
				}

				aiin(b, a, chan);

				a[i][j] = 0;
			}
		}
	}
	return EXIT;
}

int aiin(const int x[3][3], const int y[3][3], int* chan)
{
	int i, j;
	int p, q;
	int a[3][3];
	int b[3][3];
	int tie;

	for (i = 0; i <= 2; i++)
	{
		for (j = 0; j <= 2; j++)
		{
			a[i][j] = x[i][j];
			b[i][j] = y[i][j];
		}
	}

	for (j = 0; j <= 2; j++)
	{
		for (i = 0; i <= 2; i++)
		{
			if (a[i][j] == 1 || b[i][j] == 1)
				continue;
			else
			{
				a[i][j] = 1;

				for (q = 0; q <= 2; q++)                                             //胜利判断
				{
					if (a[0][q] == 1 && a[1][q] == 1 && a[2][q] == 1)
					{
						(*chan)++;
					}
				}
				for (q = 0; q <= 2; q++)
				{
					if (a[q][0] == 1 && a[q][1] == 1 && a[q][2] == 1)
					{
						(*chan)++;
					}
				}

				if (a[0][0] == 1 && a[1][1] == 1 && a[2][2] == 1)
				{
					(*chan)++;
				}

				if (a[2][0] == 1 && a[1][1] == 1 && a[0][2] == 1)
				{
					(*chan)++;
				}

				tie = 0;                           //平局判断
				for (q = 0; q <= 2; q++)
				{
					for (p = 0; p <= 2; p++)
					{
						if (a[p][q] == 1 || b[p][q] == 1)
							tie++;
					}
				}
				if (tie == 9)
				{
					return TIE;
				}

				aiOppo(b, a, chan);

				a[i][j] = 0;
			}
		}
	}

	return EXIT;
}

int aiout(const int x[3][3], const int y[3][3])
{
	int i, j;
	int p, q;
	int a[3][3];
	int b[3][3];
	int chance[10] = { 0 };
	int chan;
	int POS;
	int tie;
	int ran[9] = { 0 };
	int range;
	int output;
	int z;

	for (i = 0; i <= 2; i++)
	{
		for (j = 0; j <= 2; j++)
		{
			a[i][j] = x[i][j];
			b[i][j] = y[i][j];
		}
	}

	for (j = 0; j <= 2; j++)
	{
		for (i = 0; i <= 2; i++)
		{
			if (a[i][j] == 1 || b[i][j] == 1)
				continue;
			else
			{
				a[i][j] = 1;


				for (q = 0; q <= 2; q++)                                             //ai胜利判断
				{
					if (a[0][q] == 1 && a[1][q] == 1 && a[2][q] == 1)
					{
						return j * 3 + i + 1;
					}
				}
				for (q = 0; q <= 2; q++)
				{
					if (a[q][0] == 1 && a[q][1] == 1 && a[q][2] == 1)
					{
						return j * 3 + i + 1;
					}
				}

				if (a[0][0] == 1 && a[1][1] == 1 && a[2][2] == 1)
				{
					return j * 3 + i + 1;
				}

				if (a[2][0] == 1 && a[1][1] == 1 && a[0][2] == 1)
				{
					return j * 3 + i + 1;
				}

				a[i][j] = 0;
			}
		}
	}

	for (j = 0; j <= 2; j++)
	{
		for (i = 0; i <= 2; i++)
		{
			if (a[i][j] == 1 || b[i][j] == 1)
				continue;
			else
			{
				b[i][j] = 1;

				for (q = 0; q <= 2; q++)                                             //对手胜利判断
				{
					if (b[0][q] == 1 && b[1][q] == 1 && b[2][q] == 1)
					{
						return j * 3 + i + 1;
					}
				}
				for (q = 0; q <= 2; q++)
				{
					if (b[q][0] == 1 && b[q][1] == 1 && b[q][2] == 1)
					{
						return j * 3 + i + 1;
					}
				}

				if (b[0][0] == 1 && b[1][1] == 1 && b[2][2] == 1)
				{
					return j * 3 + i + 1;
				}

				if (b[2][0] == 1 && b[1][1] == 1 && b[0][2] == 1)
				{
					return j * 3 + i + 1;
				}

				b[i][j] = 0;

			}
		}
	}


	for (j = 0; j <= 2; j++)
	{
		for (i = 0; i <= 2; i++)
		{
			if (a[i][j] == 1 || b[i][j] == 1)
				continue;
			else
			{
				a[i][j] = 1;

				tie = 0;                           //平局判断
				for (q = 0; q <= 2; q++)
				{
					for (p = 0; p <= 2; p++)
					{
						if (a[p][q] == 1 || b[p][q] == 1)
							tie++;
					}
				}
				if (tie == 9)
				{
					return j * 3 + i + 1;
				}

				chan = 0;
				aiOppo(b, a, &chan);
				chance[j * 3 + i + 1] = chan;

				a[i][j] = 0;
			}
		}
	}

	chance[0] = INT_MIN;
	POS = 0;                             //找出胜率最大位置
	for (j = 0; j <= 2; j++)
	{
		for (i = 0; i <= 2; i++)
		{
			if (a[i][j] == 1 || b[i][j] == 1)
				continue;
			if (chance[POS] < chance[j * 3 + i + 1])
				POS = j * 3 + i + 1;
		}
	}

	z = 0;                             //若胜率相同，则随机选择一个位置
	for (j = 0; j <= 2; j++)
	{
		for (i = 0; i <= 2; i++)
		{
			if (a[i][j] == 1 || b[i][j] == 1)
				continue;
			if (chance[POS] == chance[j * 3 + i + 1])
			{
				ran[z] = j * 3 + i + 1;
				z++;
			}
		}
	}


	for (i = 0; i <= 8; i++)
	{
		if (ran[i] == 0)
		{
			range = i - 1;
			break;
		}
	}

	srand((unsigned)time(NULL));
	output = rand() % (range + 1);

	return ran[output];
}

void stdbattle()
{
	int i;
	int player = 1;
	int end = 0;
	int a[3][3] = { 0 };
	int b[3][3] = { 0 };
	int j;
	int tie;

	frame();

	pos(0, 12);
	puts("从左上角开始每个格子分别用数字1-9来表示");
	puts("请选择坐标。");

	while (end == 0)
	{
		player++;
		if (player > 1)
			player = 0;

		pos(0, 14);
		if (player == 0)
		{
			printf("       \r");
			printf("玩家1:");
			scanf("%d", &i);
		}
		else
		{
			printf("       \r");
			printf("玩家2:");
			scanf("%d", &i);
		}

		switch (i)
		{
		case 1:pos(1, 1);
			if (a[0][0] == 0 && b[0][0] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[0][0] = 1;
				}
				else
				{
					printf("X");
					b[0][0] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		case 2:pos(5, 1);
			if (a[1][0] == 0 && b[1][0] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[1][0] = 1;
				}
				else
				{
					printf("X");
					b[1][0] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		case 3:pos(9, 1);
			if (a[2][0] == 0 && b[2][0] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[2][0] = 1;
				}
				else
				{
					printf("X");
					b[2][0] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		case 4:pos(1, 5);
			if (a[0][1] == 0 && b[0][1] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[0][1] = 1;
				}
				else
				{
					printf("X");
					b[0][1] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		case 5:pos(5, 5);
			if (a[1][1] == 0 && b[1][1] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[1][1] = 1;
				}
				else
				{
					printf("X");
					b[1][1] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		case 6:pos(9, 5);
			if (a[2][1] == 0 && b[2][1] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[2][1] = 1;
				}
				else
				{
					printf("X");
					b[2][1] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		case 7:pos(1, 9);
			if (a[0][2] == 0 && b[0][2] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[0][2] = 1;
				}
				else
				{
					printf("X");
					b[0][2] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		case 8:pos(5, 9);
			if (a[1][2] == 0 && b[1][2] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[1][2] = 1;
				}
				else
				{
					printf("X");
					b[1][2] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		case 9:pos(9, 9);
			if (a[2][2] == 0 && b[2][2] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[2][2] = 1;
				}
				else
				{
					printf("X");
					b[2][2] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		}

		tie = 0;                           //平局判断
		for (j = 0; j <= 2; j++)
		{
			for (i = 0; i <= 2; i++)
			{
				if (a[i][j] == 1 || b[i][j] == 1)
					tie++;
			}
		}
		if (tie == 9)
			end = 2;

		for (j = 0; j <= 2; j++)                                             //胜利判断
		{
			if (a[0][j] == 1 && a[1][j] == 1 && a[2][j] == 1)
				end = 1;
		}
		for (j = 0; j <= 2; j++)
		{
			if (a[j][0] == 1 && a[j][1] == 1 && a[j][2] == 1)
				end = 1;
		}

		if (a[0][0] == 1 && a[1][1] == 1 && a[2][2] == 1)
			end = 1;

		if (a[2][0] == 1 && a[1][1] == 1 && a[0][2] == 1)
			end = 1;

		for (j = 0; j <= 2; j++)
		{
			if (b[0][j] == 1 && b[1][j] == 1 && b[2][j] == 1)
				end = 1;
		}
		for (j = 0; j <= 2; j++)
		{
			if (b[j][0] == 1 && b[j][1] == 1 && b[j][2] == 1)
				end = 1;
		}

		if (b[0][0] == 1 && b[1][1] == 1 && b[2][2] == 1)
			end = 1;

		if (b[2][0] == 1 && b[1][1] == 1 && b[0][2] == 1)
			end = 1;
	}

	if (end == 1)
	{
		pos(0, 14);
		putchar('\n');
		printf("恭喜玩家%d获得了胜利！！！", player + 1);
		putchar('\n');
	}
	else if (end == 2)
	{
		pos(0, 14);
		putchar('\n');
		printf("\a平局！！！");
		putchar('\n');
	}
}

void aibattle()
{
	int i;
	int player = 1;
	int who;
	int end = 0;
	int a[3][3] = { 0 };
	int b[3][3] = { 0 };
	int j;
	int tie;

	frame();

	do {
		pos(0, 12);
		printf("                       \r");
		printf("我先---1，对手先---2：");
		scanf("%d", &who);
	} while (who != 1 && who != 2);

	pos(0, 12);
	puts("从左上角开始每个格子分别用数字1-9来表示");
	puts("请选择坐标。");

	while (end == 0)
	{
		player++;
		if (player > 1)
			player = 0;

		pos(0, 14);
		if (who == 1)
		{
			if (player == 0)
			{
				printf("      \r");
				printf("玩家:");
				scanf("%d", &i);
			}
			else
			{
				i = aiout(b, a);
				printf("      \r");
				printf("电脑:");
				Sleep(500);
				printf("%d", i);
				Sleep(1000);
			}
		}
		else if (who == 2)
		{
			if (player == 0)
			{
				i = aiout(a, b);
				printf("      \r");
				printf("电脑:");
				Sleep(500);
				printf("%d", i);
				Sleep(1000);
			}
			else
			{
				printf("      \r");
				printf("玩家:");
				scanf("%d", &i);
			}
		}

		switch (i)
		{
		case 1:pos(1, 1);
			if (a[0][0] == 0 && b[0][0] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[0][0] = 1;
				}
				else
				{
					printf("X");
					b[0][0] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		case 2:pos(5, 1);
			if (a[1][0] == 0 && b[1][0] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[1][0] = 1;
				}
				else
				{
					printf("X");
					b[1][0] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		case 3:pos(9, 1);
			if (a[2][0] == 0 && b[2][0] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[2][0] = 1;
				}
				else
				{
					printf("X");
					b[2][0] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		case 4:pos(1, 5);
			if (a[0][1] == 0 && b[0][1] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[0][1] = 1;
				}
				else
				{
					printf("X");
					b[0][1] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		case 5:pos(5, 5);
			if (a[1][1] == 0 && b[1][1] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[1][1] = 1;
				}
				else
				{
					printf("X");
					b[1][1] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		case 6:pos(9, 5);
			if (a[2][1] == 0 && b[2][1] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[2][1] = 1;
				}
				else
				{
					printf("X");
					b[2][1] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		case 7:pos(1, 9);
			if (a[0][2] == 0 && b[0][2] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[0][2] = 1;
				}
				else
				{
					printf("X");
					b[0][2] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		case 8:pos(5, 9);
			if (a[1][2] == 0 && b[1][2] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[1][2] = 1;
				}
				else
				{
					printf("X");
					b[1][2] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		case 9:pos(9, 9);
			if (a[2][2] == 0 && b[2][2] == 0)
			{
				if (player == 0)
				{
					printf("○");
					a[2][2] = 1;
				}
				else
				{
					printf("X");
					b[2][2] = 1;
				}
			}
			else
			{
				player++;
				if (player > 1)
					player = 0;
			}
			break;
		}

		tie = 0;                           //平局判断
		for (j = 0; j <= 2; j++)
		{
			for (i = 0; i <= 2; i++)
			{
				if (a[i][j] == 1 || b[i][j] == 1)
					tie++;
			}
		}
		if (tie == 9)
			end = 2;

		for (j = 0; j <= 2; j++)                                             //胜利判断
		{
			if (a[0][j] == 1 && a[1][j] == 1 && a[2][j] == 1)
				end = 1;
		}
		for (j = 0; j <= 2; j++)
		{
			if (a[j][0] == 1 && a[j][1] == 1 && a[j][2] == 1)
				end = 1;
		}

		if (a[0][0] == 1 && a[1][1] == 1 && a[2][2] == 1)
			end = 1;

		if (a[2][0] == 1 && a[1][1] == 1 && a[0][2] == 1)
			end = 1;

		for (j = 0; j <= 2; j++)
		{
			if (b[0][j] == 1 && b[1][j] == 1 && b[2][j] == 1)
				end = 1;
		}
		for (j = 0; j <= 2; j++)
		{
			if (b[j][0] == 1 && b[j][1] == 1 && b[j][2] == 1)
				end = 1;
		}

		if (b[0][0] == 1 && b[1][1] == 1 && b[2][2] == 1)
			end = 1;

		if (b[2][0] == 1 && b[1][1] == 1 && b[0][2] == 1)
			end = 1;
	}

	if (end == 1)
	{
		if (who == 1)
		{
			pos(0, 14);
			putchar('\n');
			if (player == 0)
				printf("恭喜你，你赢了！！！");
			else if (player == 1)
				printf("\a很可惜，你输了！！！");
			putchar('\n');
		}
		else if (who == 2)
		{
			pos(0, 14);
			putchar('\n');
			if (player == 0)
				printf("\a很可惜，你输了！！！");
			else if (player == 1)
				printf("恭喜你，你赢了！！！");
			putchar('\n');
		}
	}
	else if (end == 2)
	{
		pos(0, 14);
		putchar('\n');
		printf("\a平局！！！");
		putchar('\n');
	}
}

void main()
{
	int i;
	int con;

	putchar('\n');
	putchar('\n');
	puts("          井字棋1.0          作者--xyz");
	puts("游戏模式：1---玩家对战；2---AI挑战");
	do
	{
		printf("请选择：");
		scanf("%d", &i);
	} while (i != 1 && i != 2);
	Sleep(500);

	if (i == 1)
	{
		do
		{
			system("cls");
			stdbattle();
			printf("要继续吗？继续---0，退出---9：");
			scanf("%d", &con);
		} while (con == 0);
	}
	else if (i == 2)
	{
		do
		{
			system("cls");
			aibattle();
			printf("要继续吗？继续---0，退出---9：");
			scanf("%d", &con);
		} while (con == 0);
	}

	exit(0);
}