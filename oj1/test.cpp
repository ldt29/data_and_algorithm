#include<stdio.h>
#include<stdlib.h>

struct Link {
	char num;
	Link* next;
};

Link* iniLink(int N) {
	Link* link = NULL;
	Link* temp = NULL;
	if (!N) {
		link = (Link*)malloc(sizeof(Link*));
		link->num = '0';
		temp = (Link*)malloc(sizeof(Link*));
		link->next = temp;
		temp->next = NULL;
		temp->num = '1';
		return link;
	}
	while (N > 9) {
		int i = 9;
		while (i > 1) {
			if (!(N % i)) {
				N = N / i;
				break;
			}
			i--;
		}
		if (i == 1) {
			link = (Link*)malloc(sizeof(Link*));
			link->num = '1';
			temp = (Link*)malloc(sizeof(Link*));
			link->next = temp;
			temp->next = NULL;
			temp->num = '-';
			return link;
		}
		Link* p = (Link*)malloc(sizeof(Link*));
		p->num = i + '0';
		p->next = NULL;
		if (link == NULL)
		{
			temp = p;
			link = temp;
		}
		else {
			temp->next = p;
			temp = p;
		}
	}
	Link* q = (Link*)malloc(sizeof(Link*));
	q->next = NULL;
	q->num = N + '0';
	if (link == NULL) {
		link = q;
	}
	else {
		temp->next = q;
	}
	return link;
}

void display(Link* link) {
	while (link!=NULL)
	{
		putchar(link->num);
		link = link->next;
	}
}

Link* reverse(Link* link) {
	Link* temp1 = link;
	Link* temp2 = link;
	char str[100];
	int i = 0;
	while (temp1 != NULL) {
		str[i] = temp1->num;
		temp1 = temp1->next;
		i++;
	}
	while (i--) {
		temp2->num = str[i];
		temp2 = temp2->next;
	}
	return link;
}

int main(){
	int N;
	scanf("%d", &N);
	Link* link=NULL;
	link = iniLink(N);
	link = reverse(link);
	display(link);
 }