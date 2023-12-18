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
int n,m,s,t;
map<string,int>mp;
int cnt=0;
const int maxn=10010;
const int maxm=200020;
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
map<int,int>ot,in;
signed main()
{
    memset(h,0,sizeof h);
    s=0;
    int n; cin>>n;
    while(n--)
    {
        string s; cin>>s;
        if(!mp.count(s))
         mp[s]=++cnt;//从1
        ot[mp[s]]++;
    }
    cin>>n;
    int ans=n;
    while(n--)
    {
        string s;
        cin>>s>>s;
        if(!mp.count(s))
         mp[s]=++cnt;
        in[mp[s]]++;
    }
    cin>>n;
    while(n--)
    {
        string a,b;
        cin>>a>>b;
        if(!mp.count(a))
         mp[a]=++cnt;
        if(!mp.count(b))
         mp[b]=++cnt;
        add(mp[a],mp[b],1e9);add(mp[b],mp[a],0);
    }
    t=++cnt;
    map<int,int>::iterator it;
    for(it=in.begin();it!=in.end();it++)
     add(s,it->first,it->second),add(it->first,s,0);
    for(it=ot.begin();it!=ot.end();it++)
     add(it->first,t,it->second),add(t,it->first,0);
    cout<<ans-dinic()<<endl;
    return 0;
}