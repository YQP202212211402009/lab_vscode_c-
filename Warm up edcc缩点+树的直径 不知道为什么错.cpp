#include<bits/stdc++.h>
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
//#define int long long
#define endl "\n"
using namespace std;
const int maxn=200005;
const int maxm=1000005;
//边双连通分量：无向图中极大的不包含割边的连通块
int h[maxn],to[maxm],ne[maxm],idx;//链式前向星
int dfn[maxn],low[maxn],tot;//时间戳，能抵达的最小的点，tot用来表示戳
int st[maxn],top;//和scc不同的是因为不用判断是否在栈中
int dcc[maxn],cnt;//scc表示第几个数在第几个强联通里面，siz表示大小，cnt表示强连通个数
vector<int>g[maxn];
//low用来和dfn判断，看是否为强连通的根，所以必须要更新low不然会提前出栈，出栈就表示这个数已经列在一个强连通里面了
//dcc和scc不同的是dcc缩的是无向图
//vdcc缩点后建图，所有边都是桥，我们要找最长的一条就是树的直径，用两次dfs
//首先从任意节点 y 开始进行第一次 DFS，到达距离其最远的节点，记为 z，
//然后再从 z 开始做第二次 DFS，到达距离 z 最远的节点，记为 z'，则即为树的直径。
//最终答案就是桥数-树的直径+1
int n,m,ma,p;
void tarjan(int x,int in_edg)//tarjan算法强调四个点，入，下，回，离
{
    //入时盖戳，入栈
    dfn[x]=low[x]=++tot;
    st[top++]=x;
    for(int i=h[x];i;i=ne[i])//遍历x的相邻节点
    {
        int y=to[i];
        if(!dfn[y])//第一种情况，还没有访问过y
        {
            tarjan(y,i);
            low[x]=min(low[x],low[y]);//回时用lowy更新lowx；
        }
        else if(i!=(in_edg^1))//不是反边
        {
            low[x]=min(low[x],dfn[y]);
        }
    }
    //离x时记录dcc
    if(dfn[x]==low[x])//若x是根节点
    {
        int y;
        do
        {
            y=st[--top];//y出栈
            dcc[y]=cnt;//y是第cnt个强连通的
        }while(y!=x); //找到根节点就退出
        cnt++;
    }
}
void add(int a,int b)
{
    to[idx]=b;ne[idx]=h[a];h[a]=idx++;
}
void init()
{
    tot=0;cnt=0;idx=2,top=0;//从2开始
    memset(dfn,0,sizeof dfn);memset(h,0,sizeof h);memset(dcc,0,sizeof dcc);
    for(int i=0;i<=n;i++) g[i].clear();
}
void dfs(int u,int step,int f)
{
    if(step>ma) ma=step,p=u;
    for(auto v:g[u])
    {
        if(v!=f)
         dfs(v,step+1,u);
    }
}
signed main()
{
    jiasu;
    while(cin>>n>>m)
    {
        if(n==0 && m==0) break;
        init();
        while(m--)
        {
            int a,b;cin>>a>>b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        tarjan(1,0);
        for(int i=1;i<=n;i++)
        {
            for(int j=h[i];j;j=ne[j])
            {
                int y=to[j];
                if(dcc[i]!=dcc[y])
                {
                    g[dcc[i]].push_back(dcc[y]);
                }
            }
        }
        //到这里建完图
        ma=-1;
        dfs(0,0,-1);
        dfs(p,0,-1);
        cout<<cnt-ma-1<<endl;
    }
    return 0;
}