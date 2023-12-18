#include<bits/stdc++.h>
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define int long long
#define endl "\n"
using namespace std;
const int maxn=20000;
vector<int>g[maxn];
int n;
int dfn[maxn],low[maxn],tot;//时间戳，能抵达的最小的点，tot用来表示戳
int cut[maxn],root;
//割点：对于一个 无向图 ，如果这个点被割了，连通块的个数增加了，那么这个点就是割点
void tarjan(int x)//tarjan算法强调四个点，入，下，回，离
{
    //入时盖戳
    dfn[x]=low[x]=++tot;
    int child=0;
    for(auto y:g[x])//遍历x的相邻节点
    {
        if(!dfn[y])//还没有访问过y
        {
            tarjan(y);
            //回
            low[x]=min(low[x],low[y]);//回时用lowy更新lowx
            if(low[y]>=dfn[x])
            {
                child++;//子树个数
                if(x!=root || child>1)//如果x是根那么child要>=2
                 cut[x]=1;//x是割点
            }
        }
        else //y已访问
        {
            low[x]=min(low[x],dfn[y]);
        }
    }
}
void init()
{
    tot=0;
    memset(dfn,0,sizeof dfn);memset(cut,0,sizeof cut);memset(low,0,sizeof low);
    for(int i=1;i<=n;i++) g[i].clear();
}
signed main()
{
    //jiasu;
    while(cin>>n)
    {
        if(n==0) break;
        init();
        int u,v;
        while(scanf("%d",&u) , u)
        {
            while(getchar() != '\n')
            {
                scanf("%d",&v);
                g[u].push_back(v);
                g[v].push_back(u);
            }
        }
        for(root=1;root<=n;root++) //注意这里root不要int!!!!!!!!!!!!!!
         if(!dfn[root]) tarjan(root);
        int ans=0;
        for(int i=1;i<=n;i++)
         if(cut[i]) ans++;
        cout<<ans<<endl;
    }
    return 0;
}