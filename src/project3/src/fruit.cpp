#include <bits/stdc++.h>
using namespace std;
int pai1[1010],pai2[1010];//记录水果相克情况
int Map[1010],Map_inv[1010];//记录编号与水果名称的映射关系
int price[1010];//记录水果价格
int vis[1010];//记录被多少已经选中的水果相克
int chos[1010];//记录是否已经选择了某个水果
struct Edge{//边结构
    int v,Next;
}edge[2000010];
int head[1010],tot=0;//邻接表储存相克关系
void add_edge(int u,int v){//添加边
    edge[++tot].v=v;
    edge[tot].Next=head[u];
    head[u]=tot;
}
int n,m;//n为水果种类数，m为相克关系数
int ans=0;//记录最优解数量
long long num=0x3f3f3f3f3f3f3f3f;//记录最优解总价
int logans[1010];//记录最优解的选择情况
void dfs(int dep,long long sum,int cho){//深度优先搜索
    if(dep>n){//搜索到底了
        if(cho>ans||(cho==ans&&sum<num)){//如果选择的水果数量大于当前最优解数量或者数量相同且总价更小
            ans=cho;//更新最优解数量
            num=sum;//更新最优解总价
            for(int i=1;i<=n;i++){//更新最优解选择情况
                logans[i]=chos[i];
            }
        }
        return ;
    }
    if(n-dep+1+cho<ans){//剪枝，如果选择的水果数量不可能大于当前最优解数量，则不继续搜索
        return ;
    }
    if(n-dep+1+cho==ans&&sum>num){//剪枝，如果选择的水果数量最多等于当前最优解数量且总价更大，则不继续搜索
        return ;
    }
    dfs(dep+1,sum,cho);//不选当前水果
    if(vis[dep]){//如果当前水果已经被选过，则不再选
        return ;
    }
    int flag=1;
    for(int i=head[dep];i;i=edge[i].Next){//遍历当前水果相克的水果
        int v=edge[i].v;
        if(chos[v]){
            flag=0;
        }
        vis[v]++;//暂时标记当前水果已经被选过，且可以重复标记来避免消除前面的标记
    }
    if(flag){
        chos[dep]=1;//选择当前水果
        dfs(dep+1,sum+price[dep]*1ll,cho+1);
        chos[dep]=0;//取消选择当前水果
    }
    for(int i=head[dep];i;i=edge[i].Next){//恢复标记
        int v=edge[i].v;
        vis[v]--;
    }
}
int pri[1010],cnt=0;
void pri_index(int x){//按格式输出编号
    if(x<100){
        printf("0");
    }
    if(x<10){
        printf("0");
    }
    printf("%d",x);
}
int main() {
    freopen("input.in","r",stdin);
    freopen("output1.out","w",stdout);
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++){//读取相克关系
        scanf("%d %d",&pai1[i],&pai2[i]);
    }
    for(int i=1;i<=n;i++){//初始化水果编号与名称的映射关系
        int x,y;
        scanf("%d %d",&x,&y);
        Map[x]=i;//编号与名称的映射关系
        Map_inv[i]=x;//名称与编号的映射关系
        price[i]=y;//记录水果价格
    }
    for(int i=1;i<=m;i++){//用无向图记录相克关系
        add_edge(Map[pai1[i]],Map[pai2[i]]);
        add_edge(Map[pai2[i]],Map[pai1[i]]);
    }
    dfs(1,0,0);//搜索最优解
    for(int i=1;i<=n;i++){//输出最优解选择情况
        if(logans[i]){
            pri[++cnt]=Map_inv[i];  
        }
    }
    sort(pri+1,pri+cnt+1);//排序输出结果
    //输出结果
    printf("%d\n",ans);
    for(int i=1;i<cnt;i++){//输出结果
        pri_index(pri[i]);
        printf(" ");
    }
    pri_index(pri[cnt]);//输出最后一个结果
    printf("\n");
    printf("%lld\n",num);
    return 0;
}