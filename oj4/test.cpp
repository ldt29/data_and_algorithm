#include<queue>
#include<vector>
#include<algorithm>
#include<stdio.h>

#define ll long long
#define re register
const int L = 1 << 20 | 1;
char buffer[L], * S, * T;
#define getchar() ((S==T&&(T=(S=buffer)+fread(buffer,1,L,stdin),S==T))?EOF:*S++)
using namespace std;
ll times;
ll dimused;
ll root;
ll X, Y, k;

struct node
{
	ll x[2];
	ll id;
	friend bool operator < (node& a, node& b)
	{
		return a.x[dimused] < b.x[dimused];
	}
}Node[100010];

struct tree {
	node Node;
	ll Max[2];
	ll Min[2];
	ll left;
	ll right;
}Tree[100010];


struct pq
{
	ll dis;
	ll pos;
};

inline bool operator < (pq a, pq b)
{
	return a.dis > b.dis || (a.dis == b.dis && a.pos < b.pos);
};

priority_queue<pq> pt;

inline ll read()
{
	re ll a = 0; re char c = getchar();
	while (c >= '0' && c <= '9')
	{
		a = (a << 3) + (a << 1) + (c ^ 48);
		c = getchar();
	}
	return a;
}

inline ll dis(ll* a)
{
	re ll x = a[0] - X;
	re ll y = a[1] - Y;
	return x * x + y * y;
}

inline ll maxdis(tree a)
{
	re ll x = max((a.Max[0] - X) * (a.Max[0] - X), (a.Min[0] - X) * (a.Min[0] - X));
	re ll y = max((a.Max[1] - Y) * (a.Max[1] - Y), (a.Min[1] - Y) * (a.Min[1] - Y));
	return x + y;
}

inline void Update(re ll root)
{
	if (!root)return;
	re ll left = Tree[root].left, right = Tree[root].right;
	if (left)
	{
		for (int i = 0; i < 2; i++)
		{
			Tree[root].Max[i] = max(Tree[root].Max[i], Tree[left].Max[i]);
			Tree[root].Min[i] = min(Tree[root].Min[i], Tree[left].Min[i]);
		}
	}
	if (right)
	{
		for (int i = 0; i < 2; i++)
		{
			Tree[root].Max[i] = max(Tree[root].Max[i], Tree[right].Max[i]);
			Tree[root].Min[i] = min(Tree[root].Min[i], Tree[right].Min[i]);
		}
	}
}

inline void CreatKDtree(re ll& root, re ll l, re ll r, re ll dim) {
	if (l > r) return;
	root = ++times; dimused = dim;
	re ll mid = (l + r) >> 1;
	nth_element(Node + l, Node + mid, Node + r + 1);
	Tree[root].Node = Node[mid];
	for (int i = 0; i < 2; i++)
	{
		Tree[root].Min[i] = Tree[root].Max[i] = Tree[root].Node.x[i];
	}
	CreatKDtree(Tree[root].left, l, mid - 1, dim ^ 1);
	CreatKDtree(Tree[root].right, mid + 1, r, dim ^ 1);
	Update(root);
}

inline void query(re ll root)
{
	if (!root) return;
	re ll res = dis(Tree[root].Node.x);
	if (pt.size() < k) 
	{
		pt.push(pq{ res, Tree[root].Node.id });
	}
	else if (pt.size() == k && (res > pt.top().dis || (res == pt.top().dis && Tree[root].Node.id < pt.top().pos)))
	{
		pt.pop();
		pt.push(pq{ res, Tree[root].Node.id });
	}
	re ll left = Tree[root].left;
	re ll right = Tree[root].right;
	re ll dl = 0, dr = 0;
	if (left) dl = maxdis(Tree[left]);
	if (right) dr = maxdis(Tree[right]);
	if (dl > dr)
	{
		if (dl >= pt.top().dis) query(left);
		if (dr >= pt.top().dis) query(right);
	}
	else
	{
		if (dr >= pt.top().dis) query(right);
		if (dl >= pt.top().dis) query(left);
	}
}

int main()
{
	ll N, M;
	N = read();
	M = read();
	for (re int i = 0; i < N; i++)
	{
		Node[i].x[0] = read();
		Node[i].x[1] = read();
		Node[i].id = i;
	}
	CreatKDtree(root, 0, N - 1, 0);
	for (re int i = 0; i < M; i++)
	{
		X = read(), Y = read(), k = read();
		while (pt.size()) pt.pop();
		pt.push(pq{ -1,0 });
		query(root);
		printf("%lld\n", pt.top().pos);
	}
	return 0;
}