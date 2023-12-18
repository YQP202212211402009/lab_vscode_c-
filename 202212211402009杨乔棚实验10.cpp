#include<bits/stdc++.h>
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define int long long
#define endl "\n"
using namespace std;
const int maxn=10005;
int g[maxn][maxn];
int vis[maxn];
int n,q;
void dfs(int u)
{
    vis[u]=1;
    cout<<u<<" ";
    for(int i=1;i<=n;i++)
    {
        if(vis[i]) continue;
        if(g[u][i])
        {
            dfs(i);
        }
    }
}
void bfs(int u)
{
    memset(vis,0,sizeof vis);
    queue<int>q;
    q.push(u);vis[u]=1;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        cout<<u<<" ";
        for(int i=1;i<=n;i++)
        {
            if(vis[i]) continue;
            if(g[u][i])
            {
                vis[i]=1;
                q.push(i);
            }
        }
    }
}
signed main()
{
    jiasu;
    memset(g,0,sizeof g);
    memset(vis,0,sizeof vis);
    cout<<"输入顶点个数和边数"<<endl;
    cin>>n>>q;
    cout<<"输入每条边相连的两个点"<<endl;
    while(q--)
    {
        int a,b; cin>>a>>b;
        g[a][b]=g[b][a]=1;
    }
    int root;
    cout<<"输入搜索的根节点"<<endl;
    cin>>root;
    cout<<"dfs:";
    dfs(root);
    cout<<endl;
    cout<<"bfs:";
    bfs(root);
    return 0;
}