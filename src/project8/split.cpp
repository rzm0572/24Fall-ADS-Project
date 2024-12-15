#include<bits/stdc++.h>
using namespace std;
string tostring(int num){//将数字转为字符串
    string str="";
    while(num>0){//将数字转为字符串
        str=char(num%10+'0')+str;//将数字的个位数字转为字符并添加到字符串前面
        num/=10;
    }
    return str;
}
int main(){
    freopen("1.txt","r",stdin);//读取数据
    freopen("./1/1.txt","w",stdout);//输出数据
    cout<<100000<<endl;//输出单词总数
    long long n=0,maxnum=0;
    string s;
    int j=1,mo=100000,m=3;
    int nn=1;
    while(cin>>s){//读取文章中的单词
        string str="";//用于存储单词
        for(int i=0;i<s.size();i++){//将单词中的非字母字符全部去掉
            if((s[i]>='a'&&s[i]<='z')||s[i]=='\''){
                if(s[i]!='\''){
                    str+=s[i];
                }
                
            }
            else {
                if(s[i]>='A'&&s[i]<='Z'){//将大写字母转为小写字母
                    str+=s[i]-'A'+'a';
                }
                else{
                    maxnum=max(maxnum,(long long)(str.size()));//记录单词中最长的字母数
                    if(str.size()>0&&str.size()<16){//单词长度小于16才输出
                        cout<<str<<endl;//输出单词
                        n++;
                        str="";
                        if(n>=mo){//输出足够个单词后换文件
                            mo+=100000;
                            n=0;
                            nn++;
                            freopen(("./"+tostring(nn)+"/1.txt").c_str(),"w",stdout);
                            cout<<mo<<endl;
                        }
                    }

                }
            }
        }
        if(str.size()>0&&str.size()<16){//单词长度小于16才输出
            cout<<str<<endl;
            n++;
            str="";
            if(n>=mo){
                mo+=100000;
                n=0;
                nn++;
                freopen(("./"+tostring(nn)+"/1.txt").c_str(),"w",stdout);
                cout<<mo<<endl;
            }
        }
        
    }

    return 0;
}