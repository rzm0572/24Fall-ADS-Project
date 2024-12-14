#include<bits/stdc++.h>
#include<Windows.h>
using namespace std;
int main(){
    int n=10000;
    system("g++ static.cpp -o make_static");//编译数据生成器
    system("brute.cpp -o brute");//编译暴力解法
    system("g++ fruit.cpp -o fruit");//编译解法
    for(int i=1;i<=n;i++){//循环n次
        system("make_static.exe");//生成数据
        system("brute.exe");//暴力解法
        system("fruit.exe");//解法1
        if(system("fc output1.out output2.out")){//比较两个输出文件
                 cout<<"Wrong Answer"<<endl;//输出错误信息
            return 0;
        }
        // if(i%100==0){
            cout<<i<<" cases checked"<<endl;//输出已检查的测试用例数
        // }
    }
    return 0;
}