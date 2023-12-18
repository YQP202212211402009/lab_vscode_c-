#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
//网络流重点：容量，流量，增广路，残留网
//bfs找增广路，EK求最大流 复杂度O（n*m*m）
//EK算法，一次累加一条增广路
int n,m,s,t;
const int maxn=10010;
const int maxm=200020;
int h[maxn],to[maxm],ne[maxm],w[maxm],idx=2;
int mf[maxn],pre[maxn];//mf用来存到某个点的最大流 pre用来存到某个点的边
void add(int a,int b,int c)
{
    to[idx]=b;w[idx]=c;ne[idx]=h[a];h[a]=idx++;
}
int bfs()
{
    memset(mf,0,sizeof mf);
    queue<int>q;
    q.push(s);mf[s]=1e9;//原点的
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=h[u];i;i=ne[i])
        {
            int v=to[i];
            if(mf[v]==0 && w[i])//要求这个点还没访问过并且，还有容量
            {
                mf[v]=min(mf[u],w[i]);//流量就是父亲的限制和自己限制的最小值
                q.push(v);
                pre[v]=i;
                if(v==t) return 1;//已经找到终点，终点也不会再更新了，直接返回就可以
            }
        }
    }
    return 0;
}
int EK()
{
    int flow=0;
    while(bfs())//只要找得到就一直找下去
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
    }
    return flow;
}
signed main()
{
    memset(h,0,sizeof h);
    cin>>n>>m>>s>>t;
    while(m--)
    {
        int a,b,c; cin>>a>>b>>c;
        add(a,b,c);add(b,a,0);
    }
    cout<<EK()<<endl;
    return 0;
}