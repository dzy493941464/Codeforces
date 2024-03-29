#include <bits/stdc++.h>
using namespace std;

#define N 200010
struct que{
	int op,x,y;
}q[N];
int n,bin[N],cnt;
int F[N],cur,ml[N],mr[N],tot,seq[N],vis[N];

int gf(int x){
	return (F[x] == x) ? x : (F[x] = gf(F[x]));
}
vector <int> s[N << 2];

#define ls (x << 1)
#define rs (x << 1 | 1)

void find(int pos,int l,int r,int x){
	while(!s[x].empty()){
		int y = s[x].back();
		s[x].pop_back();
		if(!vis[y])	vis[y] = 1, seq[++ tot] = y;
	}
	if(l == r)	return;
	int mid = (l + r) >> 1;
	if(pos <= mid)	find(pos,l,mid,ls);
	else		find(pos,mid + 1,r,rs);
}
void cover(int ql,int qr,int v,int l,int r,int x){
	if(ql <= l && r <= qr){
		s[x].push_back(v);
		return;
	}
	int mid = (l + r) >> 1;
	if(ql <= mid)	cover(ql,qr,v,l,mid,ls);
	if(mid < qr)	cover(ql,qr,v,mid + 1,r,rs);
}
void add(int l,int r){
	tot = 0;
	find(l,1,cnt,1);
	find(r,1,cnt,1);
	int L = l,R = r;
	++ cur;
	F[cur] = cur;
	for(int i = 1;i <= tot;i ++){
		L = min(L, ml[seq[i]]);
		R = max(R, mr[seq[i]]);
		F[gf(seq[i])] = cur;
	}
	ml[cur] = L;
	mr[cur] = R;
	if(L + 1 <= R - 1)	cover(L + 1,R - 1,cur,1,cnt,1);
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++){
		scanf("%d%d%d",&q[i].op,&q[i].x,&q[i].y);
		if(q[i].op)	bin[++ cnt] = q[i].x, bin[++ cnt] = q[i].y;
	}
	sort(bin + 1,bin + cnt + 1);
	cnt = unique(bin + 1,bin + cnt + 1) - bin - 1;
	for(int i = 1;i <= n;i ++){
		if(q[i].op == 1)	q[i].x = lower_bound(bin + 1,bin + cnt + 1,q[i].x) - bin, q[i].y = lower_bound(bin + 1,bin + cnt + 1,q[i].y) - bin;
		if(q[i].op == 1)	add(q[i].x,q[i].y);
		else{
			int x = gf(q[i].x), y = gf(q[i].y);
			if(x == y || mr[x] > ml[y] && mr[x] < mr[y] || mr[y] > ml[x] && ml[y] < ml[x])	printf("YES\n");
			else	printf("NO\n");
		}
	}
	return 0;
}

