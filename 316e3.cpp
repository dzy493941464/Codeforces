#include <bits/stdc++.h>
using namespace std;

#define N 200010
#define mo 1000000000
struct m4{
	int a[4];
}p[N],O;

int a[N],n,m,f[N],tag[N << 2];

struct m2{
	int a[2];
	void add(int l,int r,int x){
		a[1] = (1LL * f[r - l + 1] * x + a[1]) % mo;
		a[0] = (1LL * f[r - l] * x + a[0]) % mo;
	}
}seg[N << 2];
#define ls (x << 1)
#define rs (x << 1 | 1)

m4 operator * (m4 a,m4 b){
	m4 c;
	c.a[0] = (1LL * a.a[0] * b.a[0] + 1LL * a.a[1] * b.a[2]) % mo;
	c.a[1] = (1LL * a.a[0] * b.a[1] + 1LL * a.a[1] * b.a[3]) % mo;
	c.a[2] = (1LL * a.a[2] * b.a[0] + 1LL * a.a[3] * b.a[2]) % mo;
	c.a[3] = (1LL * a.a[2] * b.a[1] + 1LL * a.a[3] * b.a[3]) % mo;
	return c;
}

m2 operator * (m2 a,m4 b){
	m2 c;
	c.a[0] = (1LL * a.a[0] * b.a[0] + 1LL * a.a[1] * b.a[2]) % mo;
	c.a[1] = (1LL * a.a[0] * b.a[1] + 1LL * a.a[1] * b.a[3]) % mo;
	return c;
}

m2 operator + (m2 a,m2 b){
	m2 c;
	c.a[0] = a.a[0] + b.a[0];
	if(c.a[0] >= mo)	c.a[0] -= mo;
	c.a[1] = a.a[1] + b.a[1];
	if(c.a[1] >= mo)	c.a[1] -= mo;
	return c;
}

void upd(int l,int r,int x){
	seg[x] = seg[ls] + (seg[rs] * p[((l + r) >> 1) - l + 1]);
}
void build(int l,int r,int x){
	if(l == r){
		seg[x].a[0] = 0;
		seg[x].a[1] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l,mid,ls);
	build(mid + 1,r,rs);
	upd(l,r,x);
}
void down(int l,int r,int x){
	if(tag[x]){
		int mid = (l + r) >> 1;
		seg[ls].add(l,mid,tag[x]);
		seg[rs].add(mid + 1,r,tag[x]);
		tag[ls] += tag[x];
		tag[rs] += tag[x];
		if(tag[ls] >= mo)	tag[ls] -= mo;
		if(tag[rs] >= mo)	tag[rs] -= mo;
		tag[x] = 0;
	}
}
void modify(int pos,int v,int l,int r,int x){
	if(l == r){
		seg[x].a[0] = 0;
		seg[x].a[1] = v;
		return;
	}
	down(l,r,x);
	int mid = (l + r) >> 1;
	if(pos <= mid)	modify(pos,v,l,mid,ls);
	else		modify(pos,v,mid + 1,r,rs);
	upd(l,r,x);
}
void add(int ql,int qr,int v,int l,int r,int x){
	if(ql <= l && r <= qr){
		seg[x].add(l,r,v);
		tag[x] += v;
		if(tag[x] >= mo)	tag[x] -= mo;
		return;
	}
	down(l,r,x);
	int mid = (l + r) >> 1;
	if(ql <= mid)	add(ql,qr,v,l,mid,ls);
	if(mid < qr)	add(ql,qr,v,mid + 1,r,rs);
	upd(l,r,x);
}
m2 ask(int ql,int qr,int l,int r,int x){
	if(ql <= l && r <= qr)	return seg[x] * p[l - ql];
	int mid = (l + r) >> 1;
	down(l,r,x);
	m2 ret;
	ret.a[0] = ret.a[1] = 0;
	if(ql <= mid)	ret = ret + ask(ql,qr,l,mid,ls);
	if(mid < qr)	ret = ret + ask(ql,qr,mid + 1,r,rs);
	return ret;
}
int main(){
	scanf("%d%d",&n,&m);
	p[0].a[0] = p[0].a[3] = 1;
	O.a[1] = O.a[2] = O.a[3] = 1;
	f[1] = f[2] = 1;
	for(int i = 1;i <= n;i ++){
		scanf("%d",&a[i]);
		p[i] = p[i - 1] * O;
	}
	for(int i = 3;i <= n + 5;i ++){
		f[i] = f[i - 1] + f[i - 2];
		if(f[i] >= mo)	f[i] -= mo;
	}
	for(int i = 1;i <= n + 5;i ++){
		f[i] += f[i - 1];
		if(f[i] >= mo)	f[i] -= mo;
	}
	build(1,n,1);
	int op,x,y,v;
	for(int i = 1;i <= m;i ++){
		scanf("%d",&op);
		if(op == 1){
			scanf("%d%d",&x,&v);
			modify(x,v,1,n,1);
		}else	if(op == 2){
			scanf("%d%d",&x,&y);
			printf("%d\n",ask(x,y,1,n,1).a[1]);
		}else{
			scanf("%d%d%d",&x,&y,&v);
			add(x,y,v,1,n,1);
		}
	}
	return 0;
}

