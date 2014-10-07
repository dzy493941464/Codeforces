#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <deque>

using namespace std;

#define pr pair <int,int>
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define rep(i,j,k) for(int i = (j);i <= (k);i ++)
#define repd(i,j,k,d) for(int i = (j);i <= (k);i += (d))
#define rrep(i,j,k) for(int i = (j);i >= (k);i --)
#define rrepd(i,j,k,d) for(int i = (j);i >= (k);i -= (d))
#define mo 1000000007
#define cl(x,d) memset(x,(d),sizeof(x))
#define repg(i,u) for(int i = h[u];~i;i = n1[i])
typedef long long ll;

void read(int &x){
    char ch = getchar();    int f = 1;  while((ch != '-') && (ch < '0' || ch > '9'))    ch = getchar();
    if(ch == '-')   f = -1, x = 0;  else     x = ch - 48;
    ch = getchar(); while(ch >= '0' && ch <= '9')   x = x * 10 + ch - 48, ch = getchar();   x *= f;
}
void read(ll &x){
    char ch = getchar();    int f = 1;  while((ch != '-') && (ch < '0' || ch > '9'))    ch = getchar();
    if(ch == '-')   f = -1, x = 0;  else     x = ch - 48;
    ch = getchar(); while(ch >= '0' && ch <= '9')   x = x * 10LL + ch - 48, ch = getchar(); x *= f;
}
void _print(const int &x){  if(x < 10)  putchar(48 + x);    else    _print(x / 10), _print(x % 10);}
void _print(const ll &x){   if(x < 10)  putchar(48 + x);    else    _print(x / 10), _print(x % 10);}
void print(const int &x){   if(x < 0)   putchar('-'), _print(-x);   else    _print(x);}
void print(const ll &x){    if(x < 0)   putchar('-'), _print(-x);   else    _print(x);}
void println(const int &x){ print(x);   putchar('\n');}
void println(const ll &x){  print(x);   putchar('\n');}

int vis[100010],ans[100010],tot=0,n;
void dfs(int x){
	vis[x]=1;
	if(!vis[x*2%n])dfs(x*2%n);
	if(!vis[(x*2+1)%n])dfs((x*2+1)%n);
	ans[++tot]=x;
}
int main(){
	read(n);
	if(n&1){print(-1);return 0;}
	dfs(0);rrep(i,tot,1)print(ans[i]),putchar(' ');
	print(0);
	return 0;
}
