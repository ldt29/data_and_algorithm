#include<stdio.h>
#include<queue>
#include<stack>
#include<vector>
#include<stdlib.h>

using namespace std;
bool flag = 0;
int cnt = 0;//计数器
int Lx;//迷宫的长
int Ly;//迷宫的宽
vector<int> a;
bool Matrix[1000][1000]; //迷宫

//位姿
struct pos
{
	int x;//x轴坐标
	int y;//y轴坐标
	int dir;//朝向
};

struct pos_
{
	pos_* parent;//父亲节点
}node[1000][1000][4];

pos_* sor;
bool operator ==(pos a, pos b) {
	return a.x == b.x && a.y == b.y && a.dir == b.dir;
}

pos cur{ 0,0,0 }; //当前位姿
pos tar{ 0,0,0 }; //目标位姿

queue<pos> queuePos;
stack<pos> stackPos;

void bfs() {
	cur.dir--;
	tar.dir--;
	queuePos.push(cur);
	int x, y, dir;
	pos now;
	pos_* to;
	sor = &node[0][0][0];
	node[cur.x][cur.y][cur.dir].parent = &node[999][999][0];
	while (queuePos.size()) {
		x = queuePos.front().x;
		y = queuePos.front().y;
		dir = queuePos.front().dir;
		queuePos.pop();

		if (!node[x][y][(dir - 1 + 4) % 4].parent) {
			node[x][y][(dir - 1 + 4) % 4].parent = &node[x][y][dir];
			queuePos.push({ x,y,(dir - 1 + 4) % 4 });
		}
		if (pos{ x,y,(dir - 1 + 4) % 4 } == tar) {
			break;
		}

		if (!node[x][y][(dir + 1 + 4) % 4].parent) {
			node[x][y][(dir + 1 + 4) % 4].parent = &node[x][y][dir];
			queuePos.push({ x,y,(dir + 1 + 4) % 4 });
		}
		if (pos{ x,y,(dir + 1 + 4) % 4 } == tar) {
			break;
		}

		if (dir == 0) {
			if (y > 0 && !Matrix[x][y - 1])
			{
				if (node[x][y - 1][0].parent == NULL)
				{
					node[x][y - 1][0].parent = &node[x][y][0];
					queuePos.push({ x,y - 1,0 });
				}
				if (pos{ x,y - 1,0 } == tar)break;
			}
		}
		if (dir == 1) {
			if (x > 0 && !Matrix[x - 1][y])
			{
				if (node[x - 1][y][1].parent == NULL)
				{
					node[x - 1][y][1].parent = &node[x][y][1];
					queuePos.push({ x - 1,y ,1 });
				}
				if (pos{ x - 1,y ,1 } == tar)break;
			}
		}
		if (dir == 2) {
			if (y + 1 < Ly && !Matrix[x][y + 1])
			{
				if (node[x][y + 1][2].parent == NULL)
				{
					node[x][y + 1][2].parent = &node[x][y][2];
					queuePos.push({ x,y + 1 ,2 });
				}
				if (pos{ x,y + 1 ,2 } == tar)break;
			}
		}
		if (dir == 3) {
			if (x + 1 < Lx && !Matrix[x + 1][y])
			{
				if (node[x + 1][y][3].parent == NULL)
				{
					node[x + 1][y][3].parent = &node[x][y][3];
					queuePos.push(pos{ x + 1,y ,3 });
				}
				if (pos{ x + 1,y ,3 } == tar)break;
			}
		}
	}
	to = &node[tar.x][tar.y][tar.dir];
	now = { (to - sor) / 4 / 1000,(to - sor) / 4 % 1000 ,(to - sor) % 4 };
	while (!(now == cur)) {
		stackPos.push(now);
		to = to->parent;
		now = { (to - sor) / 4 / 1000,(to - sor) / 4 % 1000 ,(to - sor) % 4 };
	}
	now = cur;
	while (stackPos.size()) {
		switch ((now.dir - stackPos.top().dir + 4) % 4)
		{
		case 1:a.push_back(1);
			break;
		case 2:a.push_back(2);
			a.push_back(2);
			cnt++;
			break;
		case 3:a.push_back(3);
			break;
		default:
			break;
		}
		if (now.dir == stackPos.top().dir) {
			now = stackPos.top();
			stackPos.pop();
			if (stackPos.size()) {
				if (now.dir == stackPos.top().dir)
					a.push_back(4);
				else
				{
					a.push_back(5);
					cnt++;
					continue;
				}
			}
			else
			{
				a.push_back(5);
				cnt++;
				continue;
			}
		}
		now = stackPos.top();
		stackPos.pop();
		cnt++;
	}
	printf("%d\n", cnt);
	for (int i = 0; i < cnt; i++)
	{
		switch (a[i])
		{
		case 1:printf("R\n");
			break;
		case 2:printf("L\n");
			break;
		case 3:printf("L\n");
			break;
		case 4:printf("F2\n");
			break;
		case 5:printf("F\n");
			break;
		default:
			break;
		}
	}
}

int main()
{
	scanf("%d", &Lx);
	scanf("%d", &Ly);
	for (int i = 0; i < Ly; i++)
	{
		for (int j = 0; j < Lx; j++)
		{
			scanf("%d", &Matrix[j][i]);
			for (int k = 0; k < 4; k++)
			{
				node[j][i][k].parent == NULL;
			}
		}
	}
	scanf("%d", &cur.x);
	scanf("%d", &cur.y);
	scanf("%d", &cur.dir);
	scanf("%d", &tar.x);
	scanf("%d", &tar.y);
	scanf("%d", &tar.dir);
	bfs();
	//printf("N");
}