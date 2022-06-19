#include<stdio.h>
#include<vector>
#include<queue>
#include<string.h>
#include<iostream>
#include<stack>

#define Max 1<<16;

using namespace std;
int N, M, S, D;

inline int read()
{
	int x = 0, k = 1; char c = getchar();
	while (c < '0' || c>'9') { if (c == '-')k = -1; c = getchar(); }
	while (c >= '0' && c <= '9')x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x * k;
}
struct Edge 
{
	int node;
	int value;
	int color;
	Edge* next;
};

struct Head {
	Edge* last = NULL;
	Edge* top = NULL;
}head[30000];

void BuildGraph(int a,int b,int c) 
{
	Edge* temp1 = new(Edge);
	temp1->node = b;
	temp1->value = c;
	temp1->next = NULL;
	temp1->color = 0;
	if(!head[a].top)
		head[a].top = temp1;
	else	
		head[a].last->next = temp1;
	head[a].last = temp1;
	Edge* temp2 = new(Edge);
	temp2->node = a;
	temp2->value = c;
	temp2->next = NULL;
	temp2->color = 0;
	if (!head[b].top )
		head[b].top = temp2;
	else
		head[b].last->next = temp2;
	head[b].last = temp2;
}

struct Link 
{
	int node;
	int value;
	Link* parent;
}link[30000];

inline bool operator <(Link a, Link b)
{
	return (a.value > b.value);
}

priority_queue<Link> edge;

int flag[3][30000] = {0};

void Dijkstra(int ans,int num)
{
	
	for (int i = 0; i < ans; i++)
	{
		link[i].node = i;
		link[i].value = Max;
		link[i].parent = NULL;
		edge.push(link[i]);
	}
	for (int i = ans+1; i < N; i++)
	{
		link[i].node = i;
		link[i].value = Max;
		link[i].parent = NULL;
		edge.push(link[i]);
	}
	link[ans].node = ans;
	link[ans].value = 0;
	link[ans].parent = NULL;
	edge.push(link[ans]);
	while (!edge.empty())
	{
		ans= edge.top().node;
		edge.pop();
		if (flag[num][ans])continue;
		flag[num][ans] = 1;
		Edge* temp = head[ans].top;
		while (temp != NULL)
		{
			if ((!temp->color)&&(!flag[num][temp->node])&&(link[ans].value+temp->value<link[temp->node].value))
			{
				link[temp->node].value = link[ans].value;
				link[temp->node].value += temp->value;
				link[temp->node].parent = &link[ans];
				edge.push(link[temp->node]);
			}
			temp = temp->next;
		}
	}
}

void mark(int S) {
	if (link[S].parent == NULL)return;
	stack<int> bug;
	Edge* temp = head[S].top;
	while(temp)
	{
		if (temp->value + link[temp->node].value == link[S].value)
		{
			temp->color++;
			Edge* temp2 = head[temp->node].top;
			while (temp2) {
				if (S == temp2->node)
				{
					temp2->color++;
					break;
				}
				temp2 = temp2->next;
			}
			bug.push(temp->node);
		}
		temp = temp->next;
	}
	while (bug.size()) 
	{
		int b = bug.top();
		mark(b);
		bug.pop();
	}
}

int main()
{
	N = read();
	M = read();
	int a, b, c;
	for (int i = 0; i < M; i++)
	{
		a = read();
		b = read();
		c = read();
		BuildGraph(a, b, c);
	}
	S = read();
	D = read();
	Dijkstra(D, 1);
	Link* out = &link[S];
	printf("start\n");
	while (out)
	{
		printf("%d\n", out->node);
		out = out->parent;
	}
	printf("end\n");
	printf("%d\n", link[S].value);
	mark(S);
	Dijkstra(D, 2);
	out = &link[S];
	printf("start\n");
	while (out)
	{
		printf("%d\n", out->node);
		out = out->parent;
	}
	printf("end\n");
	printf("%d\n", link[S].value);
	return 0;
}
