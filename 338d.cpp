#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double db;
#define N 10010
ll n,m,a[N],b[N],L,G;
int k;

ll gcd(ll a,ll b){
	if(!b)	return a;	else	return gcd(b,a % b);
}

ll exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){
		x = 1;
		y = 0;
		return a;
	}
	ll d = exgcd(b,a % b,y,x);
	y -= a / b * x;
	return d;
}

ll solve(){
	ll tmp,mo = a[1],re = b[1];
	for(int i = 2;i <= k;i ++){
		ll x,y,d = exgcd(mo,a[i],x,y),c = b[i] - re;
		if(c % d)	return -1;
		tmp = a[i] / d;
		x = (x * (c / d) % tmp + tmp) % tmp;
		re += mo * x;
		mo = mo / d * a[i];
	}
	if(!re)	re = mo;
	return re;
}

int check(ll re){
	if(re <= 0 || re + k - 1 > m)	return 0;
	for(ll i = re;i <= re + k - 1;i ++)	if(gcd(i,L) != a[i - re + 1])	return 0;
	return 1;
}

int main(){
	scanf("%I64d%I64d%d",&n,&m,&k);
	for(int i = 1;i <= k;i ++){
		scanf("%I64d",&a[i]);
		G = gcd(L,a[i]);
		if(!L)	L = a[i];
		else{
			db t = (db)L / (db)G * (db)a[i];
			if(t > (db)n){
				printf("NO\n");
				return 0;
			}
			L = 1LL * L / G * a[i];
		}
	}
	for(int i = 1;i <= k;i ++)	b[i] = (1 - i);
	ll t = solve();
	if(t != -1)	printf("%s\n", check(t) ? "YES" : "NO");
	else		printf("NO\n");
	return 0;
}

				
