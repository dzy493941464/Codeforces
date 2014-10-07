#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define clr(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for(int i = (a);i <= (b);i ++)
#define dwn(i,a,b) for(int i = (a);i >= (b);i --)
#define reu(i,a) for(int i = h[a];~i;i = n1[i])

typedef long long ll;
typedef long double db;

template <class T> inline void read(T &x){
	char ch = getchar();	int f = 1;	while((ch != '-') && (ch < '0' || ch > '9'))	ch = getchar();
	if(ch == '-')	f = 0, x = 0;	else	x = ch - 48;
	ch = getchar(); while(ch >= '0' && ch <= '9')	x = x * 10 + ch - 48, ch = getchar();
	if(!f)	x = -x;
}
template <class T> inline void read(T &x,T &y){read(x);read(y);}
template <class T> inline void read(T &x,T &y,T &z){read(x);read(y);read(z);}
template <class T> inline void read(T &x,T &y,T &z,T &o){read(x);read(y);read(z);read(o);}

int _t[20];
template <class T> inline void out(T x,int ln = 1){
	if(!x)	putchar('0');
	else{
		if(x < 0)	putchar('-'),x = -x;
		for(_t[0] = 0;x;x /= 10)	_t[++ _t[0]] = x % 10;
		dwn(i,_t[0],1)	putchar(_t[i] + 48);
	}
	if(ln)	putchar('\n');
}

/*...........................................................................................................*/

#define N 100010

struct segnode{
	int same;
	ll sum,tag,col;
}t[N << 2];
#define ls (x << 1)
#define rs (x << 1 | 1)
void upd(int x){
	t[x].sum = t[ls].sum + t[rs].sum;
	if(t[ls].same && t[rs].same && t[ls].col == t[rs].col)	t[x].same = 1, t[x].col = t[ls].col;
	else	t[x].same = 0;
}

void build(int l,int r,int x){
	if(l == r){
		t[x].col = l;
		t[x].same = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(l,mid,ls);
	build(mid + 1,r,rs);
	upd(x);
}

void color(int l,int r,int x,ll v,ll tt){
	t[x].same = 1;
	t[x].sum += 1LL * tt * (r - l + 1);
	t[x].col = v;
	t[x].tag += tt;
}

void down(int l,int r,int x){
	if(t[x].tag){
		int mid = (l + r) >> 1;
		color(l,mid,ls,t[x].col,t[x].tag);
		color(mid + 1,r,rs,t[x].col,t[x].tag);
		t[x].tag = 0;
	}
}

void modify(int ql,int qr,ll v,int l,int r,int x){
	if(ql <= l && r <= qr && t[x].same){
		color(l,r,x,v,abs(t[x].col - v));
		return;
	}
	int mid = (l + r) >> 1;
	down(l,r,x);
	if(ql <= mid)	modify(ql,qr,v,l,mid,ls);
	if(mid < qr)	modify(ql,qr,v,mid + 1,r,rs);
	upd(x);
}

ll ask(int ql,int qr,int l,int r,int x){
	if(ql <= l && r <= qr)	return t[x].sum;
	int mid = (l + r) >> 1;
	ll ret = 0;
	down(l,r,x);
	if(ql <= mid)	ret += ask(ql,qr,l,mid,ls);
	if(mid < qr)	ret += ask(ql,qr,mid + 1,r,rs);
	return ret;
}

int main(){
	int n,m;
	read(n,m);
	build(1,n,1);
	int x,y,z;
	rep(i,1,m){
		read(x);
		if(x == 1)	read(x,y,z),	modify(x,y,z,1,n,1);
		else		read(x,y),	out(ask(x,y,1,n,1));
	}
	return 0;
}

