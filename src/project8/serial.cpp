#include<bits/stdc++.h>
#include<time.h>
#include<chrono>
using namespace std;
struct Node{ // Trie树节点
    Node *sons[26];// 26个子节点
    int num;// 节点中出现的单词个数
    Node(){// 初始化节点
        for(int i=0;i<26;i++){// 初始化子节点
            sons[i]=nullptr;// 子节点为空
        }
        num=0;// 节点中出现的单词个数为0
    }
}root;
int n,m=0;// n为单词个数，m为单词最长长度
vector<pair<int,string> > sort_list;// 按照单词出现次数排序的单词列表，pair的第一个元素为单词出现次数，第二个元素为单词
void dfs(Node *p,string s){// 遍历Trie树
    if(p->num!=0){// 如果节点中出现的单词个数不为0，说明该节点是一个单词的结尾
        sort_list.push_back(make_pair(p->num,s));// 将该单词加入排序列表
    }
    for(int i=0;i<26;i++){// 遍历子节点
        if(p->sons[i]!=nullptr){// 如果子节点不为空
            dfs(p->sons[i],s+char(i+'a'));// 递归遍历子节点
        }
    }
}
bool cmp(pair<int,string> a,pair<int,string> b){// 按照单词出现次数排序
    if(a.first!=b.first){// 如果出现次数不同
        return a.first>b.first;// 按照出现次数从大到小排序
    }
    return a.second<b.second;// 按照单词字典序排序
}
int main(){
    string ch;
    cin>>ch;// 输入文件名
    
    freopen(("./"+ch+"/1.txt").c_str(),"r",stdin);// 打开文件
    cin>>n;// 输入单词个数
    for(int i=1;i<=n;i++){// 输入单词
        string s;
        cin>>s;
        Node *p=&root;
        for(int j=0;j<s.size();j++){// 建立Trie树
            int index=s[j]-'a';
            if(p->sons[index]==nullptr){// 如果子节点为空，则创建子节点
                p->sons[index]=new Node();
            }
            p=p->sons[index];// 移动到子节点
        }
        p->num++;// 单词出现次数+1
        m=max(m,p->num);
    }
    dfs(&root,"");// 遍历Trie树，将单词加入排序列表
    sort(sort_list.begin(),sort_list.end(),cmp);// 按照单词出现次数排序
    FILE *file_out=fopen(("./"+ch+"/ans1.txt").c_str(),"w");// 打开输出文件
    for(int i=0;i<sort_list.size();i++){// 输出排序后的单词
        fprintf(file_out,"%s %d\n",sort_list[i].second.c_str(),sort_list[i].first);
    }
    return 0;
}