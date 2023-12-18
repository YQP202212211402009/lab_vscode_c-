#include<bits/stdc++.h>
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
//#define int long long
#define endl "\n"
using namespace std;
const int maxn=5e5+5;
const int maxm=maxn*2;
int h[maxn],ne[maxm],to[maxm];
int dfn[maxn],low[maxn];
bool cut[maxn];
int n,m,tot,cnt,ans,k,root;
void init()
{
    memset(cut,0,sizeof(cut));
    memset(h,0,sizeof(h));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    tot=cnt=ans=0;
    k=1;
}
void add(int u,int v)
{
    to[k]=v;ne[k]=h[u];h[u]=k++;
}
void tarjan(int u)
{
    dfn[u]=low[u]=++tot;
    int child=0;
    for(int i=h[u];i;i=ne[i])
	{
        int v=to[i];
        if(!dfn[v])
		{
            tarjan(v);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u])
            {
                child++;//子树个数
                if(u!=root || child>1)//如果x是根那么child要>=2
                 cut[u]=1;//x是割点
            }
        }
        else //y已访问
        {
            low[u]=min(low[u],dfn[v]);
        }
    }
}
signed main()
{
    int n,u,v;
    char c;
    while(scanf("%d",&n),n)
	{
        init();
        while(scanf("%d",&u),u)
		{
            while(scanf("%d%c",&v,&c))
			{
                add(u,v),add(v,u);
                if(c=='\n') break;
            }
        }
        for(root=1;root<=n;root++)
         if(!dfn[root]) tarjan(root);
        for(int i=1;i<=n;i++)
         if(cut[i]) ans++;
        cout<<ans<<endl;
    }
    return 0;
}