#include<bits/stdc++.h>
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define int long long
#define endl "\n"
using namespace std;
const int maxn=10005;
int num_function;//记录函数个数 
int space_line,comment_line,code_line;//记录空行，解释，代码行 
int space_infunction,comment_infunction,code_infunction;//记录函数中的各个行数 
int start_pos,end_pos,max_si;//最长函数的开始，结尾，长度 
int now,deep;//目前读取的行数，最大嵌套数 
void init()//初始化 
{
    num_function=0;
    space_line=comment_line=code_line=0;
    start_pos=end_pos,max_si=0;
    space_infunction=comment_infunction=code_infunction=0;
    now=0,deep=0;
}
void dfs(string s,int st,int dee)//dfs搜索当前函数 st表示开始,dee表示当前嵌套个数 
{
    deep=max(deep,dee);//最大深度 
    while(getline(cin,s))
    {
        now++;
        if(now-st+1>max_si)//更新最大长度，开始，结尾 
        {
            max_si=now-st+1;
            start_pos=st;
            end_pos=now;
        }
        if(s.empty()) space_infunction++,space_line++;
        else if(s[0]==s[1] && s[0]=='/') comment_infunction++,comment_line++;
        else code_infunction++,code_line++;
        int pos=s.find("{");//如果找到函数标开始志 
        if(pos!=string::npos)
        {
        	int st;
        	if(s.size()!=1)//这个if用来分 { 是否单独为一行，如果单独为一行那么上面那一句话也是函数内容，所以st为now-1 
        	 st=now;
            else
             st=now-1;
			dfs(s,st,dee+1);
        }
        pos=s.find("}");//找到函数结束标志 
        if(pos!=string::npos)
        {
            num_function++;//函数个数++ 
            return ;
        }
    }
}
signed main()
{
    jiasu;
    init();
    string s;
    while(getline(cin,s))//一直读入直到文件结束，要用ctrl+z表示结束输入 
    {
    	now++;
        if(s.empty()) space_line++;
        else if(s[0]==s[1] && s[0]=='/') comment_line++;
        else code_line++;
        int pos=s.find("{");
        if(pos!=string::npos)
        {
        	int st;
        	if(s.size()!=1)
        	 st=now;
            else
             st=now-1;
			code_infunction+=2;//主函数中和dfs中不同，如果是{单独为一行那code_infunction要+2因为 { 和上一行都算在函数中 
			dfs(s,st,1);
        }
    }
    cout<<"本程序代码 注释 空行的行数为：";
    cout<<code_line<<" "<<comment_line<<" "<<space_line<<endl;
    cout<<"本程序函数中的代码 注释 空行的行数为：";
    cout<<code_infunction<<" "<<comment_infunction<<" "<<space_infunction<<endl;
    double ave_len=(1.0*code_infunction/num_function);
    double rate_comment=(1.0*comment_line/(comment_line+code_line+space_line));
    double rate_space=((1.0*space_line)/(comment_line+code_line+space_line));
    double a=ave_len,b=rate_comment,c=rate_space;
    cout<<"本程序函数个数为："<<num_function<<endl;
    cout<<"本程序函数最大深度为："<<deep<<endl;
    cout<<"本程序函数最大长度为："<<max_si<<endl;
    cout<<"本程序函数最大长度起始 末尾为："<<start_pos<<" "<<end_pos<<endl;
    cout<<"本程序函数平均长度为："<<ave_len<<endl;
    cout<<"本程序注释(占总行数比率)为："<<rate_comment<<endl;
    cout<<"本程序空行(占总行数比率)为："<<rate_space<<endl;
    cout<<"本程序代码风格为：";
    if(a>=10 && a<=15 && b>=0.15 && b<=0.25 && c>=0.15 && c<=0.25)
     cout<<"A"<<endl;
    else if(((a>=8 && a<=9) || (a>=16 && a<=20)) && ((b>=0.1 && b<=0.14) || (b>=0.26 && b<=0.30)) && ((c>=0.1 && b<=0.14) || (c>=0.26 && b<=0.30)))
     cout<<"B"<<endl;
    else if(((a>=5 && a<=7) || (a>=21 && a<=24)) && ((b>=0.05 && b<=0.09) || (b>=0.31 && b<=0.35)) && ((c>=0.05 && b<=0.09) || (c>=0.31 && b<=0.35)))
     cout<<"C"<<endl;
    else if((a<5 || a>24) && (b<0.05 || b>0.35) && ((c<0.05 || c>0.35)))
     cout<<"D"<<endl;
    else
     cout<<"E"<<endl;
    return 0;
}

// 测试用例 
// void a()
// {
//    int b()
//    {
//        char c()
//        {

//        }
//    }
// }