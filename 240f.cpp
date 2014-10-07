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
int n,m;
char str[N];
int an[N];
struct segtree{
	int seg[N << 2],cov[N << 2],K;
	#define ls (x << 1)
	#define rs (x << 1 | 1)
	void upd(int x){
		seg[x] = seg[ls] + seg[rs];
	}
	void down(int l,int r,int x){
		if(cov[x] != -1){
			int mid = (l + r) >> 1;
			cov[ls] = cov[x];
			cov[rs] = cov[x];
			seg[ls] = cov[x] * (mid - l + 1);
			seg[rs] = cov[x] * (r - mid);
			cov[x] = -1;
		}
	}
	void build(int l,int r,int x){
		if(l == r){
			seg[x] = (str[l] - 'a' == K);
			return;
		}
		int mid = (l + r) >> 1;
		build(l,mid,ls);
		build(mid + 1,r,rs);
		upd(x);
	}
	void modify(int ql,int qr,int v,int l,int r,int x){
		if(ql <= l && r <= qr){
			cov[x] = v;
			seg[x] = v * (r - l + 1);
			return;
		}
		int mid = (l + r) >> 1;
		down(l,r,x);
		if(ql <= mid)	modify(ql,qr,v,l,mid,ls);
		if(mid < qr)	modify(ql,qr,v,mid + 1,r,rs);
		upd(x);
	}
	int ask(int ql,int qr,int l,int r,int x){
		if(ql <= l && r <= qr)	return seg[x];
		int mid = (l + r) >> 1,ret = 0;
		down(l,r,x);
		if(ql <= mid)	ret += ask(ql,qr,l,mid,ls);
		if(mid < qr)	ret += ask(ql,qr,mid + 1,r,rs);
		return ret;
	}
	void travel(int l,int r,int x){
		if(l == r){
			if(seg[x])	an[l] = K;
			return;
		}
		down(l,r,x);
		int mid = (l + r) >> 1;
		travel(l,mid,ls);
		travel(mid + 1,r,rs);
	}
	void init(int __){
		K = __;
		memset(cov,-1,sizeof(cov));
		build(1,n,1);
	}
}t[26];

int c[26];
void solve(int x,int y){
	int kk = 0;
	rep(i,0,25)	c[i] = t[i].ask(x,y,1,n,1), kk += c[i] & 1;
	int dx = x,dy = y;
	if((y - x) & 1){
		if(kk)	return;
		rep(i,0,25){
			if(c[i]){
				t[i].modify(x,y,0,1,n,1);
				t[i].modify(dx,dx + c[i] / 2 - 1,1,1,n,1);
				t[i].modify(dy - c[i] / 2 + 1,dy,1,1,n,1);
				dx += c[i] / 2;
				dy -= c[i] / 2;
			}
		}
	}else{
		if(kk != 1)	return;
		int pos;
		rep(i,0,25){
			if(c[i] & 1){
				pos = i;
				c[i] --;
				if(!c[i])	t[i].modify(x,y,0,1,n,1);
			}
			if(c[i]){
				t[i].modify(x,y,0,1,n,1);
				t[i].modify(dx,dx + c[i] / 2 - 1,1,1,n,1);
				t[i].modify(dy - c[i] / 2 + 1,dy,1,1,n,1);
				dx += c[i] / 2;
				dy -= c[i] / 2;
			}
		}
		t[pos].modify(dx,dy,1,1,n,1);
	}
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read(n,m);
	scanf("%s",str + 1);
	rep(i,0,25)	t[i].init(i);
	int x,y;
	while(m --){
		read(x,y);
		solve(x,y);
		clr(an,0);
	}
	rep(i,0,25)	t[i].travel(1,n,1);
	rep(i,1,n)	putchar(an[i] + 'a');
	return 0;
}

	
	
