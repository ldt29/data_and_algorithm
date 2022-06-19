#include<stdio.h> 
#include<stdlib.h>

struct NODE
{
	NODE* next;
	NODE* pre;
};

class LinkList
{
private:
	NODE* head;
	NODE* end;
	int ReverseNum;//翻转次数
	NODE* node;
public:
	LinkList(int N)
	{
		head = NULL;
		end = NULL;
		ReverseNum = 0;
		node = (NODE*)malloc(sizeof(NODE) * (N + 1));
	}

	void Insert(int goods, int pregoods, int LorR)
	{
		node[goods].next = NULL;
		node[goods].pre = NULL;
		if (pregoods == -1)
		{
			head = &node[goods];
			end = &node[goods];
		}
		else
		{
			if ((ReverseNum + LorR) % 2)
			{
				node[goods].next = node[pregoods].next;
				node[pregoods].next = &node[goods];
				node[goods].pre = &node[pregoods];
				if (node[goods].next == NULL)end = &node[goods];
				else node[goods].next->pre = &node[goods];
			}
			else
			{
				node[goods].pre = node[pregoods].pre;
				node[pregoods].pre = &node[goods];
				node[goods].next = &node[pregoods];
				if (node[goods].pre == NULL)head = &node[goods];
				else node[goods].pre->next = &node[goods];
			}
		}
	}

	void Delete(int pregoods)
	{
		if (node[pregoods].pre == NULL && node[pregoods].next == NULL)
		{
			head = NULL;
			end = NULL;
		}
		else {
			if (node[pregoods].pre == NULL)
			{
				head = node[pregoods].next;
				node[pregoods].next->pre = NULL;
			}
			else node[pregoods].pre->next = node[pregoods].next;
			if (node[pregoods].next == NULL)
			{
				end = node[pregoods].pre;
				node[pregoods].pre->next = NULL;
			}
			else node[pregoods].next->pre = node[pregoods].pre;
		}
		NODE* temp = &node[pregoods];
	}

	void Swap(int goods1, int goods2)
	{
		if (node[goods1].next == &node[goods2])
		{
			node[goods2].pre = node[goods1].pre;
			node[goods1].next = node[goods2].next;
			node[goods2].next = &node[goods1];
			node[goods1].pre = &node[goods2];
		}
		else if (node[goods2].next == &node[goods1])
		{
			node[goods1].pre = node[goods2].pre;
			node[goods2].next = node[goods1].next;
			node[goods2].pre = &node[goods1];
			node[goods1].next = &node[goods2];
		}
		else {
			NODE* temp1;
			temp1 = node[goods2].next;
			node[goods2].next = node[goods1].next;
			node[goods1].next = temp1;
			temp1 = node[goods2].pre;
			node[goods2].pre = node[goods1].pre;
			node[goods1].pre = temp1;
		}
		if (node[goods1].pre == NULL)head = &node[goods1];
		else node[goods1].pre->next = &node[goods1];
		if (node[goods2].next == NULL)end = &node[goods2];
		else node[goods2].next->pre = &node[goods2];
		if (node[goods2].pre == NULL)head = &node[goods2];
		else node[goods2].pre->next = &node[goods2];
		if (node[goods1].next == NULL)end = &node[goods1];
		else node[goods1].next->pre = &node[goods1];
	}

	void Reverse()
	{
		if (head == end) ReverseNum--;
		ReverseNum++;
	}

	void Display()
	{
		if (ReverseNum % 2) 
		{
			while (end != NULL)
			{
				printf("%d ", end - node);
				end = end->pre;
			}
		}
		else 
		{
			while (head != NULL)
			{
				printf("%d ", head - node);
				head = head->next;
			}
		}
		printf("-1");
	}
};

int main() {
	int N, M, K, L;
	scanf("%d%d%d%d", &N, &M, &K, &L);
	LinkList list(N);
	int pregoods, goods, LorR;
	int first;
	while (N + M + K + L) {
		scanf("%d", &first);
		if (first == 1) {
			scanf("%d%d%d", &goods, &pregoods, &LorR);
			list.Insert(goods, pregoods, LorR);
			N--;
		}
		else if (!first) {
			scanf("%d", &pregoods);
			list.Delete(pregoods);
			M--;
		}
		else if (first == -1) {
			scanf("%d%d", &pregoods, &goods);
			list.Swap(pregoods, goods);
			K--;
		}
		else if (first == -2) {
			list.Reverse();
			L--;
		}
	}
	list.Display();
	return 0;

}