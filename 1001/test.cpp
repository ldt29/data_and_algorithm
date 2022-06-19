#include<stdio.h>
#include<stdlib.h>

typedef struct Link {
	char num;
	struct Link* next;
};
//生成链表
struct Link* iniLink(char* str) {
	struct Link* p = NULL;
	struct Link* temp = (struct Link*)malloc(sizeof(struct Link));
	temp->num = str[0];
	temp->next = NULL;
	p = temp;
	int i = 1;
	while (str[i] != '\0') {
		struct Link* a = (struct Link*)malloc(sizeof(struct Link));
		a->num = str[i];
		a->next = NULL;
		temp->next = a;
		temp = a;
		i++;
	}
	return p;
}
//逆序链表
struct Link* revLink(struct Link* Link){
	char str[100] = {"\0"};
	int i = 0;
	struct Link* p = Link;
	while (Link!= NULL) {
		str[i] = Link->num;
		Link = Link->next;
		i++;
	}
	struct Link* temp = p;
	while (i>0) {
		temp->num = str[i - 1];
		temp = temp->next;
		i--;
	}
	return p;
}
//链表加法
struct Link* sumLink(struct Link* Link1, struct Link* Link2) {
	Link1 = revLink(Link1);
	Link2 = revLink(Link2);
	struct Link* p = Link1;
	int Flag = 0;
	int flag = 0;
	while (Link1!=NULL&&Link2!=NULL)
	{
		int num1 = Link1->num - '0';
		int num2 = Link2->num - '0';
		Link1->num = (num1 + num2+flag) % 10 + '0';
		flag = (num1 + num2+flag) / 10;
		struct Link* a1 = Link1;
		Link1 = Link1->next;
		Link2 = Link2->next;
		if (Link2== NULL&&Link1!=NULL) {
			if (flag) { 
				if ((Link1->num - '0'+1) / 10)
				{
					Flag = 1;
				}
				Link1->num = (Link1->num - '0' + 1) % 10 + '0';
			}
		}
		if(Link1==NULL&&Link2!=NULL)
		{
			if (flag) {
				if ((Link2->num - '0'+1) / 10)
				{
					Flag = 1;
				}
				Link2->num = (Link2->num - '0' + 1) % 10 + '0';
			}
			a1->next = Link2;
		}
		if(Link1==NULL&&Link2==NULL)
		{
			if (flag) {
				struct Link* a = (struct Link*)malloc(sizeof(struct Link*));
				a->num = '1';
				a->next = NULL;
				a1->next = a;
			}
		}
	}
	if (Flag)
	{
		if (Link1 != NULL) {
			struct Link* b1 = Link1;
			Link1 = Link1->next;
			while (Link1!=NULL)
			{
				if (Flag) {
					Flag = 0;
					if ((Link1->num - '0'+1) / 10)Flag = 1;
					Link1->num = (Link1->num - '0' + 1) % 10 + '0';
				}
				b1 = Link1;
				Link1 = Link1->next;
			}
			if (Flag) {
				struct Link* a = (struct Link*)malloc(sizeof(struct Link*));
				a->num = '1';
				a->next = NULL;
				b1->next = a;
			}
		}
		else
		{
			struct Link* c1=Link2;
			Link2 = Link2->next;
			while (Link2 != NULL)
			{
				if (Flag) {
					Flag = 0;
					if ((Link2->num - '0' + 1) / 10)Flag = 1;
					Link2->num = (Link2->num - '0' + 1) % 10 + '0';
					c1 = Link2;
					Link2 = Link2->next;
				}
			}
			if (Flag) {
				struct Link* a = (struct Link*)malloc(sizeof(struct Link*));
				a->num = '1';
				a->next = NULL;
				c1->next = a;
			}

		}
	}
	p = revLink(p);
	return p;
}
//打印链表
void desLink(struct Link* Link) {
	while (Link != NULL) {
		putchar(Link->num);
		Link = Link->next;
	}
}
int main() {
	char str1[100] = { "\0" };
	char str2[100] = { "\0" };
	scanf("%s", str1);
	struct Link* Link1 = iniLink(str1);
	scanf("%s", str2);
	struct Link* Link2 = iniLink(str2);
	Link1=sumLink(Link1, Link2);
	desLink(Link1);
	return 0;
}