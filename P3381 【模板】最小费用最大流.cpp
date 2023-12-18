#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
//网络流重点：容量，流量，增广路，残留网
//bfs找增广路，EK求最大流 复杂度O（n*m*m）
//EK算法，一次累加一条增广路
//算最小费用用spfa代替dfs，d本来代表的是距离，现在用来代表单位价格，因为所有流量都要*每个地方的单位价格所以单位价格直接
//全部加起来最后乘就可以了
int n,m,s,t;
const int maxn=10010;
const int maxm=200020;
int h[maxn],to[maxm],ne[maxm],w[maxm],cost[maxm],idx=2;
int mf[maxn],pre[maxn],d[maxn],vis[maxn];//mf用来存到某个点的最大流 pre用来存到某个点的边
int flow,cc;
void add(int a,int b,int c,int d)
{
    to[idx]=b;w[idx]=c;cost[idx]=d;ne[idx]=h[a];h[a]=idx++;
}
int spfa()
{
    memset(vis,0,sizeof vis);
    memset(mf,0,sizeof mf);
    memset(d,inf,sizeof d);
    queue<int>q;
    q.push(s);mf[s]=1e9;d[s]=0,vis[s]=1;//原点的
    while(!q.empty())
    {
        int u=q.front();q.pop();vis[u]=0;//spfa算法，出队列vis就变成0，可以多次进队
        for(int i=h[u];i;i=ne[i])
        {
            int v=to[i],c=w[i],w=cost[i];
            if(d[u]+w<d[v] && c)//小于并且有容量
            {
                d[v]=d[u]+w;
                mf[v]=min(mf[u],c);
                pre[v]=i;
                if(!vis[v])
                {
                    q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
    if(mf[t]) return 1;
    else return 0;
}
void EK()
{
    flow=0;
    cc=0;
    while(spfa())//只要找得到就一直找下去
    {
        int v=t;//逆序
        while(v!=s)
        {
            int i=pre[v];//找到边
            w[i]-=mf[t];//正边剩下来的流量=容量-这条增广路用掉的
            w[i^1]+=mf[t];//建立残留网，这个是反边，用来反悔用
            v=to[i^1];//v=反边的终点，往前走回溯
        }
        flow+=mf[t];//总流量+这条增广路的流量
        cc+=mf[t]*d[t];
    }
}
signed main()
{
    memset(h,0,sizeof h);
    cin>>n>>m>>s>>t;
    while(m--)
    {
        int a,b,c,d; cin>>a>>b>>c>>d;
        add(a,b,c,d);add(b,a,0,-d);
    }
    EK();
    cout<<flow<<" "<<cc<<endl;
    return 0;
}