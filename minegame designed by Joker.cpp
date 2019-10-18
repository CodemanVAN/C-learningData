#include <stdio.h>
#include<time.h>
#include <stdlib.h>
#include<graphics.h>
#include<Windows.h>
#include<cstdio>
#define ROW 15
#define COL 15
#define NUM 25
#define SIZE 50
IMAGE img[14];
int arry[ROW + 2][COL + 2];// 当数组定义在全局时，数组and变量内容不初始化时全为0，局部就是随机；
void gamestart()
{
	initgraph(ROW * SIZE, COL * SIZE);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < ROW + 2; i++)
	{
		for (int k = 0; k < COL + 2; k++)
			arry[i][k] = 0;
	}
	
		loadimage(&img[0], L"./res/0.jpg",SIZE,SIZE);
		loadimage(&img[1], L"./res/1.jpg", SIZE, SIZE);
		loadimage(&img[2], L"./res/2.jpg", SIZE, SIZE);
		loadimage(&img[3], L"./res/3.jpg", SIZE, SIZE);
		loadimage(&img[4], L"./res/4.jpg", SIZE, SIZE);
		loadimage(&img[5], L"./res/5.jpg", SIZE, SIZE);
		loadimage(&img[6], L"./res/6.jpg", SIZE, SIZE);
		loadimage(&img[7], L"./res/7.jpg", SIZE, SIZE);
		loadimage(&img[8], L"./res/8.jpg", SIZE, SIZE);
		loadimage(&img[9], L"./res/9.jpg", SIZE, SIZE);
		loadimage(&img[10], L"./res/10.jpg", SIZE, SIZE);
		loadimage(&img[11], L"./res/11.jpg", SIZE, SIZE);
		loadimage(&img[12], L"./res/12.jpg", SIZE, SIZE);
		loadimage(&img[13], L"./res/13.jpg", SIZE, SIZE);
		//loadimage(&img[14], L"./res/14.jpg", SIZE, SIZE);
	
	for (int j = 0; j < NUM;)
	{
		int c = rand() % ROW + 1;
		int x = rand() % COL + 1;
		if (arry[c][x] == 0)
		{
			arry[c][x] = -1;
			j++;
		}
	}
	for (int i = 1; i < ROW + 1; i++)
	{
		for (int k = 1; k < COL + 1; k++)
		{
			if (arry[i][k] == 0)
			{
				for (int m = i - 1; m <= i + 1; m++)
				{
					for (int l = k - 1; l <= k + 1; l++)
					{ 
						if (arry[m][l] == -1)
						{
							arry[i][k]++;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < ROW + 2; i++)
	{
		for (int k = 0; k < COL + 2; k++)
			arry[i][k] += 20;
	}
}
void round(int n, int m)
{
	for (int i =n-1; i <= n+1; i++)
			{
				for (int k = m-1; k <=m+1; k++)
				{
					if (arry[i][k] == 20)
					{
						arry[i][k] -= 20;
						round(i+1,k+1);
					}
				}
			}

		
	
}
void drawmap()
{
	system("cls");
	for (int p = 1; p < ROW + 1; p++)
	{
		for (int d = 1; d < COL + 1; d++)
		{
			if (arry[p][d] == -1)
			{
				putimage((d - 1) * SIZE, (p - 1) * SIZE, &img[13]);
			}
			else if (arry[p][d] >= 0 && arry[p][d] <= 8) {
				putimage((d - 1) * SIZE, (p - 1) * SIZE, &img[arry[p][d]]);
			}
			else if (arry[p][d] >= 19 && arry[p][d] <= 28) 
			{
				putimage((d - 1) * SIZE, (p - 1) * SIZE, &img[9]);
			}		
			else if (arry[p][d] > 28)
			{
				putimage((d - 1) * SIZE, (p - 1) * SIZE, &img[10]);
			}
			printf("%2d ", arry[p][d]);
		}
		printf("\n");
	}

}
int playgame() 
{
	MOUSEMSG msg = { 0 };
	msg = GetMouseMsg();
	int n;
	if (msg.uMsg == WM_LBUTTONDOWN)
	{
		n = arry[msg.y / SIZE + 1][msg.x / SIZE + 1];
		if(n>=19&&n<=28)
		{
			arry[msg.y / SIZE + 1][msg.x / SIZE + 1] -= 20;
			if (arry[msg.y / SIZE + 1][msg.x / SIZE + 1] == 0) {
				round(msg.y / SIZE + 1, msg.x / SIZE + 1);
			}
		}
	}
	else if (msg.uMsg == WM_RBUTTONDOWN)
	{
		n = arry[msg.y / SIZE + 1][msg.x / SIZE + 1];
		if (n >= 19 && n <= 28)
		{
			arry[msg.y / SIZE + 1][msg.x / SIZE + 1] += 30;
		}
		if (n >= 30)
		{
			arry[msg.y / SIZE + 1][msg.x / SIZE + 1] -= 30;
		}
	}
	return arry[msg.y / SIZE + 1][msg.x / SIZE + 1];
}
void safe()
{
	MOUSEMSG msg = { 0 };
	msg = GetMouseMsg();
	int n;
	if (msg.uMsg == WM_LBUTTONDOWN)
	{
		n = arry[msg.y / SIZE + 1][msg.x / SIZE + 1];
		if (n == 19)
		{
			for (int i = 0; i < ROW + 2; i++)
			{
				for (int k = 0; k < COL + 2; k++)
					if (arry[i][k] == 20)
					{
						int n = arry[i][k];
						arry[i][k] = arry[msg.y / SIZE + 1][msg.x / SIZE + 1];
						arry[msg.y / SIZE + 1][msg.x / SIZE + 1] = n;
					}
			}
		}
	}
}

int main()
{

	gamestart();
	safe();
	while (1) 
	{
		drawmap();
		int m=playgame();
		if (m == -1)
		{
			drawmap();
			getchar();
			exit(0);
		}
	}
	getchar();
	return 0;
}
