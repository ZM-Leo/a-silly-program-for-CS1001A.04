#include<stdio.h>
#include<math.h>
#include<graphics.h>
#include<time.h>
#include<stdlib.h>
#define G 0.1
#define dt 0.01
#define M 0.01
#define K 80
struct ball
{
	double x, y;
	double vx, vy;
	double ax, ay;
	int e;
	int color[3];
	int ifin;
};
int randnum()
{
	srand((unsigned)time(NULL));
	return rand() % 14;
}
//输入小球
void inputball(struct ball* b, int num)
{
	switch (num)
	{
		case 0:
			b->e = -7;
			b->color[0] = 255;
			b->color[1] = 215;
			b->color[2] = 0;
			break;
		case 1:
			b->e = -6;
			b->color[0] = 0;
			b->color[1] = 0;
			b->color[2] = 255;
			break;
		case 2:
			b->e = -5;
			b->color[0] = 255;
			b->color[1] = 0;
			b->color[2] = 0;
			break;
		case 3:
			b->e = -4;
			b->color[0] = 160;
			b->color[1] = 32;
			b->color[2] = 240;
			break;
		case 4:
			b->e = -3;
			b->color[0] = 255;
			b->color[1] = 127;
			b->color[2] = 0;
			break;
		case 5:
			b->e = -2;
			b->color[0] = 50;
			b->color[1] = 205;
			b->color[2] = 50;
			break;
		case 6:
			b->e = -1;
			b->color[0] = 160;
			b->color[1] = 82;
			b->color[2] = 45;
			break;
		case 7:
			b->e = 1;
			b->color[0] = 160;
			b->color[1] = 82;
			b->color[2] = 45;
			break;
		case 8:
			b->e = 2;
			b->color[0] = 50;
			b->color[1] = 205;
			b->color[2] = 50;
			break;
		case 9:
			b->e = 3;
			b->color[0] = 255;
			b->color[1] = 127;
			b->color[2] = 0;
			break;
		case 10:
			b->e = 4;
			b->color[0] = 160;
			b->color[1] = 32;
			b->color[2] = 240;
			break;
		case 11:
			b->e = 5;
			b->color[0] = 255;
			b->color[1] = 0;
			b->color[2] = 0;
			break;
		case 12:
			b->e = 6;
			b->color[0] = 0;
			b->color[1] = 0;
			b->color[2] = 255;
			break;
		case 13:
			b->e = 7;
			b->color[0] = 255;
			b->color[1] = 215;
			b->color[2] = 0;
			break;
	}
	b->x = 20;
	b->y = 700;
	b->vx = 0;
	b->vy = 0;
	b->ax = 0;
	b->ay = G;
	b->ifin = 1;
}
//画小球
void drawball(struct ball* b)
{
	setcolor(RGB(b->color[0], b->color[1], b->color[2]));
	setfillcolor(RGB(b->color[0], b->color[1], b->color[2]));
	solidcircle(b->x, b->y, 20);
	setcolor(WHITE);
	setfillcolor(WHITE);
	solidcircle(b->x, b->y, 10);
	char s[10];
	sprintf_s(s, "%d", b->e);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(10, 0, "黑体");
	outtextxy(b->x - 5, b->y - 5, s);
}
void drawarrow(int x1, int y1, int x2, int y2)
{
	setcolor(BLACK);
	setfillcolor(BLACK);
	line(x1, y1, x2, y2);
	double distance = sqrt((y1 - y2) * (y1 - y2) + (x1 - x2) * (x1 - x2));
	double tmpx = double(x1 + (x2 - x1) * (1 - (12 * sqrt(3) / 2) / distance));
	double tmpy = double(y1 + (y2 - y1) * (1 - (12 * sqrt(3) / 2) / distance));
	if (y1 == y2)
	{
		line(x2, y2, int(tmpx), int(tmpy + 6));
		line(x2, y2, int(tmpx), int(tmpy - 6));
	}
	else
	{
		double k = (double(x2) - double(x1)) / (double(y1) - double(y2));
		double increX = 6 / sqrt(k * k + 1);
		double increY = 6 * k / sqrt(k * k + 1);
		line(x2, y2, int(tmpx + increX), int(tmpy + increY));
		line(x2, y2, int(tmpx - increX), int(tmpy - increY));
	}
}
//判断小球是否出界
void whatin(struct ball* b[])
{
	for (int i = 0; i < 100; i++)
	{
		if (b[i]->ifin == 2)
		{
			if (b[i]->x < 20 || b[i]->x > 1060 || b[i]->y < 20 || b[i]->y > 700)
			{
				b[i]->ifin = 0;
			}
		}
	}
}
//小球运动
void moveball(struct ball* b)
{
	b->vx += b->ax * dt;
	b->vy += b->ay * dt;
	b->x += b->vx * dt;
	b->y += b->vy * dt;
}
//两小球的相互作用
void aball(struct ball* b1, struct ball* b2)
{
	double d = sqrt((b1->x - b2->x) * (b1->x - b2->x) + (b1->y - b2->y) * (b1->y - b2->y));
	if (b1->y == b2->y)
	{
		if (b1->x > b2->x)
		{
			b1->ax += (K * b1->e * b2->e / (d * d)) / M;
			b2->ax += -(K * b1->e * b2->e / (d * d)) / M;
		}
		else
		{
			b1->ax += -(K * b1->e * b2->e / (d * d)) / M;
			b2->ax += (K * b1->e * b2->e / (d * d)) / M;
		}
		return;
	}
	if (b1->x == b2->x)
	{
		if (b1->y > b2->y)
		{
			b1->ay += (K * b1->e * b2->e / (d * d)) / M;
			b2->ay += -(K * b1->e * b2->e / (d * d)) / M;
		}
		else
		{
			b1->ay += -(K * b1->e * b2->e / (d * d)) / M;
			b2->ay += (K * b1->e * b2->e / (d * d)) / M;
		}
		return;
	}
	double tantheta = (b1->y - b2->y) / (b1->x - b2->x);
	if (tantheta < 0)
	{
		tantheta = -tantheta;
	}
	double sintheta = tantheta / sqrt(tantheta * tantheta + 1);
	double costheta = 1 / sqrt(tantheta * tantheta + 1);
	if (b1->x > b2->x && b1->y < b2->y)
	{
		b1->ax += (K * b1->e * b2->e / (d * d)) * costheta / M;
		b1->ay += -(K * b1->e * b2->e / (d * d)) * sintheta / M;
		b2->ax += -(K * b1->e * b2->e / (d * d)) * costheta / M;
		b2->ay += (K * b1->e * b2->e / (d * d)) * sintheta / M;
	}
	else if (b1->x < b2->x && b1->y < b2->y)
	{
		b1->ax += -(K * b1->e * b2->e / (d * d)) * costheta / M;
		b1->ay += -(K * b1->e * b2->e / (d * d)) * sintheta / M;
		b2->ax += (K * b1->e * b2->e / (d * d)) * costheta / M;
		b2->ay += (K * b1->e * b2->e / (d * d)) * sintheta / M;
	}
	else if (b1->x < b2->x && b1->y > b2->y)
	{
		b1->ax += -(K * b1->e * b2->e / (d * d)) * costheta / M;
		b1->ay += (K * b1->e * b2->e / (d * d)) * sintheta / M;
		b2->ax += (K * b1->e * b2->e / (d * d)) * costheta / M;
		b2->ay += -(K * b1->e * b2->e / (d * d)) * sintheta / M;
	}
	else
	{
		b1->ax += (K * b1->e * b2->e / (d * d)) * costheta / M;
		b1->ay += (K * b1->e * b2->e / (d * d)) * sintheta / M;
		b2->ax += -(K * b1->e * b2->e / (d * d)) * costheta / M;
		b2->ay += -(K * b1->e * b2->e / (d * d)) * sintheta / M;
	}	
}
//所有小球的相互作用
void aballs(struct ball* b[], struct ball* pbal)
{
	for (int i = 0; i < 100; i++)
	{
		if (b[i]->ifin == 2)
		{
			b[i]->ax = 0;
			b[i]->ay = G;
		}
	}
	pbal->ax = 0;
	pbal->ay = G;
	for (int i = 0; i < 100; i++)
	{
		if (b[i]->ifin == 2)
		{
			for (int j = i + 1; j < 100; j++)
			{
				if (b[j]->ifin == 2)
				{
					aball(b[i], b[j]);
				}
			}
			aball(b[i], pbal);
		}
	}
}
//小球的碰撞
void collision(struct ball* b1, struct ball* b2)
{
	if (pow(b1->x - b2->x, 2) + pow(b1->y - b2->y, 2) <= 400)
	{
		double v1x = b1->vx;
		double v1y = b1->vy;
		double v2x = b2->vx;
		double v2y = b2->vy;
		if (pow(b1->x - b2->x, 2) + pow(b1->y - b2->y, 2) <= 100)
		{
			b1->ifin = 0;
			b2->ifin = 0;
			return;
		}
		if (b1->x == b2->x)
		{
			b1->vx = -v1x;
			b2->vx = -v2x;
			return;
		}
		if (b1->y == b2->y)
		{
			b1->vy= -v1y;
			b2->vy = -v2y;
			return;
		}
		double tantheta = (b1->y - b2->y) / (b1->x - b2->x);
		if (tantheta < 0)
		{
			tantheta = -tantheta;
		}
		double costheta = 1 / sqrt(1 + tantheta * tantheta);
		double sintheta = tantheta / sqrt(1 + tantheta *tantheta);
		if ((b1->x < b2->x && b1->y < b2->y) || (b1->x > b2->x && b1->y >b2->y))
		{
			double v1t = v1x * sintheta - v1y * costheta;
			double v2n = v1x * costheta + v1y * sintheta;
			double v2t = v2x * sintheta - v2y * costheta;
			double v1n = v2x * costheta + v2y * sintheta;
			b1->vx = v1t * sintheta + v1n * costheta;
			b1->vy = -v1t * costheta + v1n * sintheta;
			b2->vx = v2t * sintheta + v2n * costheta;
			b2->vy = -v2t * costheta + v2n * sintheta;
		}
		else
		{
			double v1t = v1x * sintheta + v1y * costheta;
			double v2n = -v1x * costheta + v1y * sintheta;
			double v2t = v2x * sintheta + v2y * costheta;
			double v1n = -v2x * costheta + v2y * sintheta;
			b1->vx = v1t * sintheta - v1n * costheta;
			b1->vy = v1t * costheta + v1n * sintheta;
			b2->vx = v2t * sintheta - v2n * costheta;
			b2->vy = v2t * costheta + v2n * sintheta;
		}
	}
}
void time(clock_t Start_time)
{
	clock_t End_time;
	int time_1;
	char str[10];
	End_time = clock();
	time_1 = (int)((End_time - Start_time) / 1000);
	settextstyle(20, 0, "宋体");
	setcolor(BLACK);//
	sprintf_s(str, " %d s", time_1);
	outtextxy(10, 10, str);
}
//随机模式下的画图
void draw(struct ball* b[], struct ball* pbal, int tag, struct ExMessage msg, clock_t Start_time)
{
	whatin(b);
	BeginBatchDraw();
	cleardevice();
	time(Start_time);
	for (int i = 0; i <= tag; i++)
	{
		if (b[i]->ifin == 2)
		{
			moveball(b[i]);
			drawball(b[i]);
		}
	}
	drawball(b[tag]);
	moveball(pbal);
	drawball(pbal);
	drawarrow(20, 700, msg.x, msg.y);
	EndBatchDraw();
}
int button()
{
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(255, 228, 255));
	fillroundrect(430, 260, 665, 350, 10, 10);
	fillroundrect(430, 370, 665, 460, 10, 10);
	settextcolor(BLACK);
	settextstyle(50, 0, "黑体");
	outtextxy(450, 270, "随机模式");
	outtextxy(450, 380, "手动模式");
	ExMessage msg;
	while (true)
	{
		msg = getmessage(EX_MOUSE);
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			if (msg.x > 430 && msg.x < 665 && msg.y>260 && msg.y < 350)
			{
				BeginBatchDraw();
				setfillcolor(RED);
				fillroundrect(430, 260, 665, 350, 10, 10);
				settextstyle(50, 0, "黑体");
				outtextxy(450, 270, "随机模式");
				EndBatchDraw();
			}
			else if (msg.x > 430 && msg.x < 665 && msg.y>370 && msg.y < 460)
			{
				BeginBatchDraw();
				setfillcolor(RED);
				fillroundrect(430, 370, 665, 460, 10, 10);
				settextstyle(50, 0, "黑体");
				outtextxy(450, 380, "手动模式");
				EndBatchDraw();
			}
			else
			{
				BeginBatchDraw();
				setfillcolor(RGB(255, 228, 255));
				fillroundrect(430, 260, 665, 350, 10, 10);
				fillroundrect(430, 370, 665, 460, 10, 10);
				settextcolor(BLACK);
				settextstyle(50, 0, "黑体");
				outtextxy(450, 270, "随机模式");
				outtextxy(450, 380, "手动模式");
				EndBatchDraw();
			}
			break;
		case WM_LBUTTONDOWN:
			if (msg.x > 430 && msg.x < 665 && msg.y>260 && msg.y < 350)
			{
				cleardevice();
				return 1;
			}
			else if (msg.x > 430 && msg.x < 665 && msg.y> 370 && msg.y < 460)
			{
				cleardevice();
				return 2;
			}
			else
			{
				return 0;
			}
			break;
		}
	}
}
void count()
{
	char s[4] = { '3','2','1' };
	for (int i = 0; i < 3; i++)
	{
		clearrectangle(0, 0, 1080, 680);
		settextcolor(BLACK);
		settextstyle(100, 0, "黑体");
		outtextxy(500, 300, s[i]);
		Sleep(500);
	}
}
void end(clock_t Start_time)
{
	cleardevice();
	settextcolor(BLACK);
	settextstyle(100, 0, "黑体");
	outtextxy(300, 300, "GAME OVER");
	clock_t End_time;
	int time_1;
	char str[100];
	End_time = clock();
	time_1 = (int)((End_time - Start_time) / 1000);
	settextstyle(20, 0, "宋体");
	setcolor(BLACK);
	sprintf_s(str, " %d s", time_1);
	outtextxy(450, 400, str);
}
int where(ExMessage msg)
{
	if (msg.message == WM_LBUTTONDOWN)
	{
		if ((msg.x - 20) * (msg.x - 20) + (msg.y - 700) * (msg.y - 700) <= 400)
		{
			return 0;
		}
		else if ((msg.x - 100) * (msg.x - 100) + (msg.y - 700) * (msg.y - 700) <= 400)
		{
			return 1;
		}
		else if ((msg.x - 180) * (msg.x - 180) + (msg.y - 700) * (msg.y - 700) <= 400)
		{
			return 2;
		}
		else if ((msg.x - 260) * (msg.x - 260) + (msg.y - 700) * (msg.y - 700) <= 400)
		{
			return 3;
		}
		else if ((msg.x - 340) * (msg.x - 340) + (msg.y - 700) * (msg.y - 700) <= 400)
		{
			return 4;
		}
		else if ((msg.x - 420) * (msg.x - 420) + (msg.y - 700) * (msg.y - 700) <= 400)
		{
			return 5;
		}
		else if ((msg.x - 500) * (msg.x - 500) + (msg.y - 700) * (msg.y - 700) <= 400)
		{
			return 6;
		}
		else if ((msg.x - 580) * (msg.x - 580) + (msg.y - 700) * (msg.y - 700) <= 400)
		{
			return 7;
		}
		else if ((msg.x - 660) * (msg.x - 660) + (msg.y - 700) * (msg.y - 700) <= 400)
		{
			return 8;
		}
		else if ((msg.x - 740) * (msg.x - 740) + (msg.y - 700) * (msg.y - 700) <= 400)
		{
			return 9;
		}
		else if ((msg.x - 820) * (msg.x - 820) + (msg.y - 700) * (msg.y - 700) <= 400)
		{
			return 10;
		}
		else if ((msg.x - 900) * (msg.x - 900) + (msg.y - 700) * (msg.y - 700) <= 400)
		{
			return 11;
		}
		else if ((msg.x - 980) * (msg.x - 980) + (msg.y - 700) * (msg.y - 700) <= 400)
		{
			return 12;
		}
		else if ((msg.x - 1060) * (msg.x - 1060) + (msg.y - 700) * (msg.y - 700) <= 400)
		{
			return 13;
		}
	}
	return -1;
}
//手动模式下的画图1
void draw1(struct ball* b[], struct ball* pbal, struct ball ab1[], int flag, struct ExMessage msg, clock_t Start_time)
{
	whatin(b);
	BeginBatchDraw();
	cleardevice();
	time(Start_time);
	for (int i = 0; i < 100; i++)
	{
		if (b[i]->ifin == 2)
		{
			moveball(b[i]);
			drawball(b[i]);
		}
	}
	for (int i = 0; i < 14; i++)
	{
		drawball(&ab1[i]);
	}
	moveball(pbal);
	drawball(pbal);
	drawarrow(80 * flag + 20, 700, msg.x, msg.y);
	EndBatchDraw();
}
//手动模式下的画图2
void draw2(struct ball* b[], struct ball* pbal, struct ball ab1[], struct ExMessage, clock_t Start_time)
{
	whatin(b);
	BeginBatchDraw();
	cleardevice();
	time(Start_time);
	for (int i = 0; i < 100; i++)
	{
		if (b[i]->ifin == 2)
		{
			moveball(b[i]);
			drawball(b[i]);
		}
	}
	for (int i = 0; i < 14; i++)
	{
		drawball(&ab1[i]);
	}
	moveball(pbal);
	drawball(pbal);
	EndBatchDraw();
}
int main() 
{
	struct ball b[100], bal;
	struct ball* pb[100];
	struct ball* pbal = &bal;
	for (int i = 0; i < 100; i++)
	{
		pb[i] = &b[i];
	}
	bal.x = 540;
	bal.y = 20;
	bal.vx = 0;
	bal.vy = 0;
	bal.ax = 0;
	bal.ay = G;
	bal.e = 1;
	bal.color[0] = 0;
	bal.color[1] = 0;
	bal.color[2] = 0;
	bal.ifin = 2;
	initgraph(1080, 720);
	setbkcolor(WHITE);
	cleardevice();
	while (true)
	{
		int m = button();
		switch (m)
		{
		case 1:
		{
			count();
			clock_t Start_time;
			Start_time = clock();
			ExMessage msg;
			getmessage(&msg);
			for (int i = 0; i < 100; i++)
			{
				int num = randnum();
				inputball(pb[i], num);
				drawball(pb[i]);
				pb[i]->ifin = 1;
				while (true)
				{
					for (int j = 0; j < 100; j++)
					{
						if (pb[j]->ifin == 2)
						{
							collision(pb[i], pbal);
						}
					}
					for (int j = 0; j < 100; j++)
					{
						if (pb[j]->ifin == 2)
						{
							for (int k = j + 1; k < 100; k++)
							{
								if (pb[k]->ifin == 2)
								{
									collision(pb[j], pb[k]);
								}
							}
						}
					}
					aballs(pb, pbal);
					draw(pb, pbal, i, msg, Start_time);
					if (peekmessage(&msg, EX_MOUSE, 1));
					{
						if (msg.message == WM_LBUTTONDOWN)
						{
							while (true)
							{
								getmessage(&msg);
								if (msg.message == WM_LBUTTONUP)
								{
									pb[i]->ifin = 2;
									pb[i]->vx = (msg.x - 20) / 50;
									pb[i]->vy = (msg.y - 700) / 50;
									goto A;
								}
							}
						}
					}
					if (pbal->x < 20 || pbal->x > 1060 || pbal->y < 20 || pbal->y > 700)
					{
						end(Start_time);
						Sleep(10000);
						closegraph();
					}
				}
			A:
				;
			}
			break;
		}
		case 2:
		{
			struct ball ab[14];
			int a[14] = { 20,100,180,260,340,420,500,580,660,740,820,900,980,1060 };
			struct ball ab1[14];
			int c[14];
			for (int i = 0; i < 14; i++)
			{
				inputball(&ab[i], i);
				ab[i].x = a[i];
				ab[i].y = 20;
				drawball(&ab[i]);
			}
			ExMessage msg;
			int flag;
			for (int i = 0; i < 14; i++)
			{
				while (true)
				{
					msg = getmessage();
					if (msg.message == WM_LBUTTONDOWN)
					{
						if ((msg.x - 20) * (msg.x - 20) + (msg.y - 20) * (msg.y - 20) <= 400)
						{
							ab[0].x = a[i];
							ab[0].y = 700;
							ab1[i] = ab[0];
							c[i] = 0;
							drawball(&ab[0]);
							break;
						}
						else if ((msg.x - 100) * (msg.x - 100) + (msg.y - 20) * (msg.y - 20) <= 400)
						{
							ab[1].x = a[i];
							ab[1].y = 700;
							ab1[i] = ab[1];
							c[i] = 1;
							drawball(&ab[1]);
							break;
						}
						else if ((msg.x - 180) * (msg.x - 180) + (msg.y - 20) * (msg.y - 20) <= 400)
						{
							ab[2].x = a[i];
							ab[2].y = 700;
							ab1[i] = ab[2];
							c[i] = 2;
							drawball(&ab[2]);
							break;
						}
						else if ((msg.x - 260) * (msg.x - 260) + (msg.y - 20) * (msg.y - 20) <= 400)
						{
							ab[3].x = a[i];
							ab[3].y = 700;
							ab1[i] = ab[3];
							c[i] = 3;
							drawball(&ab[3]);
							break;
						}
						else if ((msg.x - 340) * (msg.x - 340) + (msg.y - 20) * (msg.y - 20) <= 400)
						{
							ab[4].x = a[i];
							ab[4].y = 700;
							ab1[i] = ab[4];
							c[i] = 4;
							drawball(&ab[4]);
							break;
						}
						else if ((msg.x - 420) * (msg.x - 420) + (msg.y - 20) * (msg.y - 20) <= 400)
						{
							ab[5].x = a[i];
							ab[5].y = 700;
							ab1[i] = ab[5];
							c[i] = 5;
							drawball(&ab[5]);
							break;
						}
						else if ((msg.x - 500) * (msg.x - 500) + (msg.y - 20) * (msg.y - 20) <= 400)
						{
							ab[6].x = a[i];
							ab[6].y = 700;
							ab1[i] = ab[6];
							c[i] = 6;
							drawball(&ab[6]);
							break;
						}
						else if ((msg.x - 580) * (msg.x - 580) + (msg.y - 20) * (msg.y - 20) <= 400)
						{
							ab[7].x = a[i];
							ab[7].y = 700;
							ab1[i] = ab[7];
							c[i] = 7;
							drawball(&ab[7]);
							break;
						}
						else if ((msg.x - 660) * (msg.x - 660) + (msg.y - 20) * (msg.y - 20) <= 400)
						{
							ab[8].x = a[i];
							ab[8].y = 700;
							ab1[i] = ab[8];
							c[i] = 8;
							drawball(&ab[8]);
							break;
						}
						else if ((msg.x - 740) * (msg.x - 740) + (msg.y - 20) * (msg.y - 20) <= 400)
						{
							ab[9].x = a[i];
							ab[9].y = 700;
							ab1[i] = ab[9];
							c[i] = 9;
							drawball(&ab[9]);
							break;
						}
						else if ((msg.x - 820) * (msg.x - 820) + (msg.y - 20) * (msg.y - 20) <= 400)
						{
							ab[10].x = a[i];
							ab[10].y = 700;
							ab1[i] = ab[10];
							c[i] = 10;
							drawball(&ab[10]);
							break;
						}
						else if ((msg.x - 900) * (msg.x - 900) + (msg.y - 20) * (msg.y - 20) <= 400)
						{
							ab[11].x = a[i];
							ab[11].y = 700;
							ab1[i] = ab[11];
							c[i] = 11;
							drawball(&ab[11]);
							break;
						}
						else if ((msg.x - 980) * (msg.x - 980) + (msg.y - 20) * (msg.y - 20) <= 400)
						{
							ab[12].x = a[i];
							ab[12].y = 700;
							ab1[i] = ab[12];
							c[i] = 12;
							drawball(&ab[12]);
							break;
						}
						else if ((msg.x - 1060) * (msg.x - 1060) + (msg.y - 20) * (msg.y - 20) <= 400)
						{
							ab[13].x = a[i];
							ab[13].y = 700;
							ab1[i] = ab[13];
							c[i] = 13;
							drawball(&ab[13]);
							break;
						}
					}
				}
			}
			count();
			cleardevice();
			for (int i = 0; i < 14; i++)
			{
				drawball(&ab1[i]);
			}
			clock_t Start_time;
			Start_time = clock();
			for (int i = 0; i < 100; i++)
			{
				while (true)
				{
					peekmessage(&msg, EX_MOUSE, 1);
					flag = where(msg);
					if (flag != -1)
					{
						b[i] = ab1[flag];
						while (true)
						{
							peekmessage(&msg, EX_MOUSE, 1);
							for (int j = 0; j < 100; j++)
							{
								if (pb[j]->ifin == 2)
								{
									collision(pb[i], pbal);
								}
							}
							for (int j = 0; j < 100; j++)
							{
								if (pb[j]->ifin == 2)
								{
									for (int k = j + 1; k < 100; k++)
									{
										if (pb[k]->ifin == 2)
										{
											collision(pb[j], pb[k]);
										}
									}
								}
							}
							aballs(pb, pbal);
							draw1(pb, pbal, ab1, flag, msg, Start_time);
							if (msg.message == WM_LBUTTONUP)
							{
								pb[i]->ifin = 2;
								pb[i]->vx = (msg.x - a[flag]) / 40;
								pb[i]->vy = (msg.y - 700) / 40;
								goto B;
							}
							if (pbal->x < 20 || pbal->x > 1060 || pbal->y < 20 || pbal->y > 700)
							{
								end(Start_time);
								Sleep(10000);
								closegraph();
							}
						}
					}
					else
					{
						for (int j = 0; j < 100; j++)
						{
							if (pb[j]->ifin == 2)
							{
								collision(pb[i], pbal);
							}
						}
						for (int j = 0; j < 100; j++)
						{
							if (pb[j]->ifin == 2)
							{
								for (int k = j + 1; k < 100; k++)
								{
									if (pb[k]->ifin == 2)
									{
										collision(pb[j], pb[k]);
									}
								}
							}
						}
						aballs(pb, pbal);
						draw2(pb, pbal, ab1, msg, Start_time);
						if (pbal->x < 20 || pbal->x > 1060 || pbal->y < 20 || pbal->y > 700)
						{
							end(Start_time);
							Sleep(10000);
							closegraph();
						}

					}
				}
			B:
				;
			}
		}
		}
	}
	return 0;
}