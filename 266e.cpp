#include <bits/stdc++.h>
using namespace std;

#define mo 1000000007
#define N 100010

int n,m,a[N],p[6][N],s[6][N],c[6][6];

int pow(int a,int b,int c){
	int ret = 1;
	while(b){
		if(b & 1)	ret = 1LL * ret * a % mo;
		b >>= 1;
		a = 1LL * a * a % mo;
	}
	return ret;
}

struct segtree{
	int seg[N << 2],cov[N << 2],K;
	#define ls (x << 1)
	#define rs (x << 1 | 1)
	void upd(int x){
		seg[x] = seg[ls] + seg[rs];
		if(seg[x] >= mo)	seg[x] -= mo;
	}
	void build(int l,int r,int x){
		if(l == r){
			seg[x] = 1LL * a[l] * p[K][l] % mo;
			return;
		}
		int mid = (l + r) >> 1;
		build(l,mid,ls);
		build(mid + 1,r,rs);
		upd(x);
	}
	void init(int _k){
		memset(seg,0,sizeof(seg));
		memset(cov,-1,sizeof(cov));
		K = _k;
		build(1,n,1);
	}
	void down(int l,int r,int x){
		if(cov[x] != -1){
			int mid = (l + r) >> 1;
			cov[ls] = cov[x];
			cov[rs] = cov[x];
			seg[ls] = 1LL * (s[K][mid] - s[K][l - 1] + mo) * cov[x] % mo;
			seg[rs] = 1LL * (s[K][r] - s[K][mid] + mo) * cov[x] % mo;
			cov[x] = -1;
		}
	}
	void modify(int ql,int qr,int v,int l,int r,int x){
		if(ql <= l && r <= qr){
			seg[x] = 1LL * (s[K][r] - s[K][l - 1] + mo) * v % mo;
			cov[x] = v;
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
		if(ql <= mid){
			ret += ask(ql,qr,l,mid,ls);
			if(ret >= mo)	ret -= mo;
		}
		if(mid < qr){
			ret += ask(ql,qr,mid + 1,r,rs);
			if(ret >= mo)	ret -= mo;
		}
		return ret;
	}
}t[6];

int main(){
	for(int i = 0;i <= 5;i ++)	c[i][i] = c[i][0] = 1;
	for(int i = 1;i <= 5;i ++)
		for(int j = 1;j < i;j ++)	c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i ++)	scanf("%d",&a[i]), p[0][i] = 1,s[0][i] = i;
	for(int i = 1;i <= 5;i ++)	for(int j = 1;j <= n;j ++){
		p[i][j] = 1LL * p[i - 1][j] * j % mo;
		s[i][j] = s[i][j - 1] + p[i][j];
		if(s[i][j] >= mo)	s[i][j] -= mo;
	}
	for(int i = 0;i <= 5;i ++)	t[i].init(i);
	char op[2];
	int x,y,k;
	while(m --){
		scanf("%s",op);
		if(op[0] == '?'){
			scanf("%d%d%d",&x,&y,&k);
			int ans = 0;
			for(int j = 0;j <= k;j ++)	ans = (1LL * pow(1 - x,k - j,mo) * c[k][j] % mo * t[j].ask(x,y,1,n,1) + ans) % mo;
			printf("%d\n",(ans + mo) % mo);
		}else{
			scanf("%d%d%d",&x,&y,&k);
			for(int j = 0;j <= 5;j ++)	t[j].modify(x,y,k,1,n,1);
		}
	}
	return 0;
}

			
	
	
	
