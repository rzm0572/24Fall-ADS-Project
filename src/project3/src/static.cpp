#include<bits/stdc++.h>
#include<time.h>
using namespace std;
void pri_index(int x){
    if(x<100){
        printf("0");
    }
    if(x<10){
        printf("0");
    }
    printf("%d",x);
}
int main(){
    srand(time(0));
    freopen("input.in","w",stdout);
    int n=30,m=rand()%((n-15)*(n-16)/2);
    printf("%d %d\n",m,n);
    for(int i=1;i<=m;i++){
        int u=rand()%n+1,v=rand()%n+1;//生成随机数并保证u!=v
        if(u==v){
            i--;
            continue;
        }
        pri_index(u);
        printf(" ");
        pri_index(v);
        printf("\n");
    }
    for(int i=n;i>=1;i--){
        pri_index(i);
        printf(" %d\n",rand()%10000);//随机生成价格
    }
    return 0;
}