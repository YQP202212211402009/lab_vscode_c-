#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
//网络流重点：容量，流量，增广路，残留网
//dinic算法，可以一次累加多条增广路的流量
//bfs对点分层，找增广路
//dfs多路增广
//1.搜索顺序优化(分层限制搜索深度)
//2.当前弧优化(剪枝)
//3.剩余流量优化(剪枝)
//4.残枝优化(剪枝)
//最小割：对于一个网络 切一刀，把s和t分开使网络断流，从s到t出边容量最少得就是最小割，最小割==最大流
//求边数:当然我们完全可以换种思路用一次最大流搞定，只需建图时将边权w=w*a+1（w为本来的边权，a为大于1000的数），
// 这样我们能求得最大流ans，则最小割的值为ansa，割的边数为ans%a。这很容易理解，但是还是解释一下：
//因为最小割的边集中有w1+w2+w3…+wn=ans（这个ans为本来的最小割），所以必然有w1*a+w2*a+w3*a…+wn*a=ans*a，
//于是必然有w1*a+1+w2*a+1+w3*a+1…+wn*a+1=ans*a+k(k为最小割的边数，k<=m<=1000)，这样就很明显了，
//因为边数m不大于1000，所以k的最大值为1000，我们只要使设定的a的值大于1000，那么按上述方法建图，跑出的最大流除
//以a就是最小割的值ans，最大流模a就是最小割的边数k。
int n,m,s,t;
const int maxn=10010;
const int maxm=200020;
const int mod=2023;
int h[maxn],to[maxm],ne[maxm],w[maxm],idx=2;
int cur[maxn],d[maxn];
void add(int a,int b,int c)
{
    to[idx]=b;w[idx]=c;ne[idx]=h[a];h[a]=idx++;
}
int bfs()
{
    memset(d,0,sizeof d);
    queue<int>q;
    q.push(s);d[s]=1;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=h[u];i;i=ne[i])
        {
            int v=to[i];
            if(d[v]==0 && w[i])
            {
                d[v]=d[u]+1;
                q.push(v);
                if(v==t) return 1;
            }
        }
    }
    return 0;
}
int dfs(int u,int mf)//函数有两个return，一个是到终点的，一个是后续返回的
{
    //入
    if(u==t) return mf;//已经抵达终点，直接返回mf,mf就是到这个点最大的流量
    int sum=0;
    for(int i=cur[u];i;i=ne[i])//i从cur开始走，剪枝，要是一个点有多个邻边，之前走到哪里就从哪里继续
    //因为如果能走到走到这条边那么说明前面的边已经走完了
    {
        //下
        cur[u]=i;//当前弧优化
        int v=to[i];
        if(d[v]==d[u]+1 && w[i])//严格要求，v要是u下一层的点并且有容量
        {
            int f=dfs(v,min(mf,w[i]));
            //回
            w[i]-=f;
            w[i^1]+=f;
            mf-=f;
            sum+=f;
            if(mf==0) break;//剪枝
        }
    }
    //离
    if(sum==0) d[u]=0;//剪枝，到不了终点，那就把这个点抹了，没用
    return sum;
}
int dinic()
{
    int flow=0;
    while(bfs())//bfs分层
    {
        memcpy(cur,h,sizeof h);//重置cur
        flow+=dfs(s,1e9);
    }
    return flow;
}
signed main()
{
    memset(h,0,sizeof h);
    cin>>n>>m;
    s=1,t=n;
    while(m--)
    {
        int a,b,c; cin>>a>>b>>c;
        add(a,b,c*mod+1);add(b,a,0);
    }
    int ans=dinic();
    cout<<ans/mod<<" "<<ans%mod;
    return 0;
}