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
#define inf 1000000000

int n,H,h[N],l[N],r[N],f[N];
vector < pair< int,int > > v;
set < pair<int,int> > s;
set < int > g[N];
set < pair<int,int> > :: iterator it,pre,suc;

void upd(int x,int y){
	f[x] = max(f[x], min(f[y], min(r[x],r[y]) - max(l[x],l[y])));
}

int main(){
//	freopen("data.in","r",stdin);
	read(n,H);
	rep(i,1,n)	read(h[i],l[i],r[i]),v.pb(mp(l[i],i)),v.pb(mp(r[i],-i));
	sort(v.begin(),v.end());
	h[++ n] = 0;	l[n] = -inf - 10;	r[n] = inf + 10;
	h[++ n] = H;	l[n] = -inf - 20;	r[n] = inf + 20;
	s.insert(mp(h[n - 1],n - 1));
	s.insert(mp(h[n],n));
	for(int o = 0;o < v.size();o ++){
		int i = v[o].se;
		if(i > 0){
			pre = suc = it = s.insert(mp(h[i],i)).fi;
			-- pre;
			++ suc;
			if(g[pre -> se].find(suc -> se) != g[pre -> se].end())	g[pre -> se].erase(suc -> se);
			g[pre -> se].insert(i);
			g[i].insert(suc -> se);
		}else	s.erase(mp(h[-i],-i));
	}
	v.clear();
	rep(i,1,n)	v.pb(mp(h[i],i));
	sort(v.begin(),v.end());
	f[n - 1] = 2 * inf;
	for(int o = 0;o < v.size() - 1;o ++){
		int i = v[o].se;
		for(set <int> :: iterator j = g[i].begin();j != g[i].end();j ++)	upd(*j,i);
	}
	out(f[n]);
	return 0;
}

				
