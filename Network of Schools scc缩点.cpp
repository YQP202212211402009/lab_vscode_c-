#include  <map>
#include  <set>
#include  <cmath>
#include  <queue>
#include  <cstdio>
#include  <vector>
#include  <climits>
#include  <cstring>
#include  <cstdlib>
#include  <iostream>
#include  <algorithm>
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define int long long
#define endl "\n"
using namespace std;
const int maxn=10010;
vector<int>g[maxn];
int dfn[maxn],low[maxn],tot;//时间戳，能抵达的最小的点，tot用来表示戳
int stk[maxn],instk[maxn],top;//手写栈，判断某个数是否在栈中，top表示栈顶
int scc[maxn],siz[maxn],cnt;//scc表示第几个数在第几个强联通里面，siz表示大小，cnt表示强连通个数
int din[maxn],dout[maxn];//入度出度
//low用来和dfn判断，看是否为强连通的根，所以必须要更新low不然会提前出栈，出栈就表示这个数已经列在一个强连通里面了
void tarjan(int x)//tarjan算法强调四个点，入，下，回，离
{
    //入时盖戳，入栈
    dfn[x]=low[x]=++tot;
    stk[++top]=x; instk[x]=1;
    for(int i=0;i<g[x].size();i++)//遍历x的相邻节点
    {
        int y=g[x][i];
        if(!dfn[y])//第一种情况，还没有访问过y
        {
            tarjan(y);
            low[x]=min(low[x],low[y]);//回时用lowy更新lowx；
        }
        else if(instk[y])//第二种情况，y访问过了并且y在栈中
        {
            low[x]=min(low[x],dfn[y]);
        }
        //第三种访问过并且出栈，那就不用操作就不写
    }
    //离x时记录scc
    if(dfn[x]==low[x])//若x是根节点
    {
        int y;cnt++;
        do
        {
            y=stk[top--];instk[y]=0; //y出栈
            scc[y]=cnt;siz[cnt]++;//y是第cnt个强连通的，第cnt强连通个数++
        }while(y!=x); //找到根节点就退出
    }
}
void init()
{
    tot=0;cnt=0;top=0;
    memset(dfn,0,sizeof dfn);memset(din,0,sizeof din);memset(dout,0,sizeof dout);
}
signed main()
{
    jiasu;
    init();
    int n; cin>>n;
    for(int i=1;i<=n;i++)
    {
        int k;
        while(cin>>k)
        {
            if(k==0) break;
            g[i].push_back(k);
        }
    }
    for(int i=1;i<=n;i++)//缩点
     if(dfn[i]==0)
      tarjan(i);
    for(int x=1;x<=n;x++)
    {
        for(int i=0;i<g[x].size();i++)//找x的邻点
        {
            int y=g[x][i];
            if(scc[x]!=scc[y])//如果x和y不在一个环里面
            {
                dout[scc[x]]++;
                din[scc[y]]++;
            }
        }
    }
    int a=0,b=0;
    for(int i=1;i<=cnt;i++)
    {
        if(!din[i]) a++; //入度为0的环
        if(!dout[i]) b++;//出度为0的环
    }
    cout<<a<<endl;
    if(cnt==1) cout<<0<<endl;
    else cout<<max(a,b)<<endl;
    return 0;
}