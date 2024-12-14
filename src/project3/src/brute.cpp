#include<bits/stdc++.h>
using namespace std;
map<long long,long long>ma,ma_inv;//表示物品编号与物品编号的映射
long long  m,n,total_num=0;
long long a[1010],b[1010];//表示不能共存的两个物品的编号
long long price[1010];//price[i]表示第i个物品的价格
long long ans_index[1010],tot=0;
void pri_index(long long x){//按格式输出x
    if(x<100){
        printf("0");
    }
    if(x<10){
        printf("0");
    }
    printf("%d",x);
}
int main(){
        freopen("input.in","r",stdin);
    freopen("output2.out","w",stdout);
    cin>>m>>n;
    for(long long i=1;i<=m;i++){//读入不能共存的两个物品的编号
        long long x,y;
        cin>>x>>y;
        if(ma.count(x)==0){//如果物品x没有出现过，则将其编号映射到一个新的编号
            total_num++;
            ma[x]=total_num;
            
            ma_inv[total_num]=x;
        }
        if(ma.count(y)==0){//如果物品y没有出现过，则将其编号映射到一个新的编号
            total_num++;
            ma[y]=total_num;
            ma_inv[total_num]=y;
        }
        a[i]=ma[x];
        b[i]=ma[y];
    }
    for(long long i=1;i<=n;i++){
        long long x,y;
        cin>>x>>y;
        if(ma.count(x)==0){//如果物品x没有出现过，则将其编号映射到一个新的编号
            total_num++;
            ma[x]=total_num;
            ma_inv[total_num]=x;
        }
        price[ma[x]]=y;//读入物品的价格
    }
    long long status=(1ll<<n)-1ll;//状态压缩每个物品有取或者不取两种状态
    long long ans=0,ans_price=0x3f3f3f3f3f3f3f3fll;//初始化
    long long ans_count=0;
    for(long long i=status;i>=0;i--){//枚举所有状态
        long long flag=1,cnt=0;
        long long pri=0;
        for(long long j=1;j<=m;j++){//判断状态i是否有取或不取状态冲突
            if((i&(1ll<<(a[j]-1ll)))&&(i&(1ll<<(b[j]-1ll)))){
                flag=0;
                break;
            }
        }
        if(!flag){
            continue;
        }
        for(long long j=1;j<=n;j++){//统计状态i中取的物品数量
            if(i&(1ll<<(j-1ll))){
                cnt++;
                pri+=price[j];
            }
        }
        if(cnt>ans_count||(cnt==ans_count&&pri<ans_price)){
            //更新答案，如果取到的物品数量大于当前答案，或者取到的物品数量相同且价格小于当前答案
            ans_count=cnt;
            ans_price=pri;
            ans=i;
        }
    }
    ans_price=0;
    for(long long i=1;i<=n;i++){//取出取到的物品编号
        if(ans&(1<<(i-1))){
            ans_index[++tot]=ma_inv[i];
            ans_price+=price[i];
        }
    }
    sort(ans_index+1,ans_index+1+tot);//排序输出答案
    cout<<ans_count<<endl;
    for(long long i=1;i<tot;i++){
        pri_index(ans_index[i]);
        cout<<" ";
    }
    pri_index(ans_index[tot]);
    cout<<endl;
    cout<<ans_price<<endl;
    return 0;
}