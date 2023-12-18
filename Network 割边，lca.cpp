#include<bits/stdc++.h>
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define int long long
#define endl "\n"
using namespace std;
const int maxn=210;
const int maxm=10050;
int h[maxn],ne[maxm],to[maxm],idx;
void add(int a,int b)//链式前向星 为了可以处理重边，所以要把边一对一对存入判断，不然dfs的时候直接判断f就行
{
    to[idx]=b;ne[idx]=h[a];h[a]=idx++;
}
int dfn[maxn],low[maxn],tot,cnt;//时间戳，能抵达的最小的点，tot用来表示戳
//割边 无向图里面割掉一个边可以使连通块增加，这个边就是割边也称桥
int bri[maxn],f[maxn],d[maxn],ans;//d表示深度求lca用的
void tarjan(int x,int in_edge)//tarjan算法强调四个点，入，下，回，离
{
    //入时盖戳
    dfn[x]=low[x]=++tot;
    for(int i=h[x];i;i=ne[i])
    {
        int y=to[i];
        if(!dfn[y])//没有访问过
        {
            //下的时候赋值
            f[y]=x;d[y]=d[x]+1;
            tarjan(y,i);
            //回的时候判断
            low[x]=min(low[x],low[y]);
            if(low[y]>dfn[x])//注意这里没有等于，因为不让判断回边
            {
                bri[y]=1;ans++;
            }
        }
        else if(i!=(in_edge^1))//判断是否是回边
        {
            low[x]=min(low[x],dfn[y]);//不是回边那可以
        }
    }
}
void init()
{
    cnt=0;
    tot=0;idx=2;//从2,3开始因为0用来做边界了
    memset(h,0,sizeof h);memset(dfn,0,sizeof dfn);memset(bri,0,sizeof bri);
    ans=0;
}
void check(int a,int b)//从a到b的lca的路上，那些边如果是割边，那么他们也同样会多一条边，所以沿路的割边全部都要去掉
{
    while(d[a]>d[b])
    {
        if(bri[a]) ans--,bri[a]=0;
        a=f[a];
    }
    while(d[b]>d[a])
    {
        if(bri[b]) ans--,bri[b]=0;
        b=f[b];
    }
    while(a!=b)
    {
        if(bri[a]) ans--,bri[a]=0;
        if(bri[b]) ans--,bri[b]=0;
        a=f[a],b=f[b];
    }
}
signed main()
{
    jiasu;
    int n,m;
    int ca=1;
    while(cin>>n>>m)
    {
        init();
        if(n==0 && m==0) break;
        while(m--)
        {
            int a,b;cin>>a>>b;
            add(a,b);add(b,a);
        }
        for(int i=1;i<=n;i++)
         if(!dfn[i]) tarjan(i,0);
        cout<<"Case "<<ca++<<":"<<endl;
        int q;cin>>q;
        while(q--)
        {
            int a,b;cin>>a>>b;
            check(a,b);
            cout<<ans<<endl;
        }
        cout<<endl;
    }
    return 0;
}