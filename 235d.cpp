#include <bits/stdc++.h>
using namespace std;

#define N 6010
typedef long double db;
int p[N],n1[N],h[N],ee = 0,n;
int pre[N],cir[N],iscir[N],cirtot = 0,tmp[N],id[N],bl[N],d[N];
bool vis[3010][3010];
db ans = 0;
void ae(int x,int y){
	p[ee] = y;	n1[ee] = h[x];	h[x] = ee ++;
}
void dfs(int u,int fa){
	tmp[u] = 1;
	for(int i = h[u];~i;i = n1[i]){
		if(cir[1])	return;
		if(p[i] == fa || tmp[p[i]] == 2)	continue;
		pre[p[i]] = u;
		if(tmp[p[i]] == 1){
			if(!cir[1])	cir[1] = p[i];
			return;
		}
		dfs(p[i],u);
	}
	tmp[u] = 2;
}
void dd(int rt,int u,int fa){
	bl[u] = rt;
	for(int i = h[u];~i;i = n1[i]){
		if(p[i] == fa || iscir[p[i]])	continue;
		d[p[i]] = d[u] + 1;
		dd(rt,p[i],u);
	}
}
void count(int u,int v,int fa,int x,int y){
	int z = d[u]+d[v];
	ans += (db)2*((db)1/(db)(z+x)+(db)1/(db)(z+y)-(db)1/(db)(x+y+z));
	for(int i = h[v];~i;i = n1[i]){
		if(iscir[p[i]] || p[i] == fa)	continue;
		count(u,p[i],v,x,y);
	}
}
void count2(int u,int fa,int v,int x,int y){
	count(u,v,0,x,y);
	for(int i = h[u];~i;i = n1[i]){
		if(iscir[p[i]] || p[i] == fa)	continue;
		count2(p[i],u,v,x,y);
	}
}
void tr(int u,int fa,int dep){
	ans += (db)1/(db)dep;
	for(int i = h[u];~i;i = n1[i]){
		if(p[i] != bl[u] && iscir[p[i]])	continue;
		if(p[i] == fa)	continue;
		tr(p[i],u,dep+1);
	}
}		
int main(){
	scanf("%d",&n);
	int x,y;
	memset(h,-1,sizeof(h));
	for(int i = 1;i <= n;i ++){
		scanf("%d%d",&x,&y);
		++ x;
		++ y;
		ae(y,x);
		ae(x,y);
	}
	dfs(1,0);
	iscir[cir[1]] = 1;
	x = pre[cir[1]];
	while(x != cir[1]){
		cir[++ cirtot] = x;
		iscir[x] = 1;
		x = pre[x];
	}
	for(int i = 1;i <= cirtot;i ++){
		id[cir[i]] = i;
		d[cir[i]] = 1;
		dd(cir[i],cir[i],0);
	}
	for(int i = 1;i <= cirtot;i ++)
		for(int j = i + 1;j <= cirtot;j ++)
			count2(cir[i],0,cir[j],j - i - 1,cirtot - (j - i + 1));
	for(int i = 1;i <= n;i ++)	tr(i,0,1);
	printf("%.10lf\n",(double)ans);
	return 0;
}

