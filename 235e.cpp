#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <unordered_map>
using namespace std;
#define N 2001
#define mo (1<<30)
int fl[N]={0},prime[N]={0},A,B,C;
unordered_map < long long , int > H[600];
int dp(int a,int b,int c,int p){
    if(!p)  return 1;
    long long ha=1ll*N*N*a+1ll*N*b+c,tmp;
    if(tmp=H[p][ha])    return tmp;
    int ret=0,i,j,k,x,y,z,pp=prime[p];
    for(i=1,x=0;i<=a;i*=pp,++x)
        for(j=1,y=0;j<=b;j*=pp,++y)
            for(k=1,z=0;k<=c;k*=pp,++z)
                ret+=dp(a/i,b/j,c/k,p-1)*(x+y+z+1);
    return H[p][ha]=ret;
}
int main(){
    scanf("%d%d%d",&A,&B,&C);
    for(int i=2;i<N;++i){
        if(!fl[i])  prime[++prime[0]]=i;
        for(int j=1;j<=prime[0] && prime[j]*i<N;++j){
            fl[prime[j]*i]=1;
            if(i%prime[j]==0)   break;
        }
    }
    printf("%d\n",(dp(A,B,C,prime[0])%mo+mo)%mo);
    return 0;
}