#include<bits/stdc++.h>
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define int long long
#define endl "\n"
using namespace std;
const int maxn=10005;
const int maxm=maxn*maxn;
//二分图:如果所有点可以分成两个集合并且集合中的点不相邻那就是二分图
//二分图之中只存在偶数环，不存在奇数环
//用dfs找到一个点，把他的邻点都变成和他不一样的颜色，如果找到一样颜色的邻点那么说明找到奇数边了
int h[maxn],to[maxm],ne[maxm],idx=1;
int color[maxn];
void add(int a,int b)
{
    to[idx]=b;ne[idx]=h[a];h[a]=idx++;
}
int dfs(int u,int c)
{
    color[u]=c;
    for(int i=h[u];i;i=ne[i])
    {
        int v=to[i];
        if(color[v]==0)
         if(dfs(v,3-c)) return 1;
        else if(color[v]==c)
         return 1;
    }
    return 0;
}
signed main()
{
    jiasu;
    int n,m;
    cin>>n>>m;
    while(m--)
    {
        int a,b;
        cin>>a>>b;
        add(a,b);
        add(b,a);
    }
    int flag=0;
    for(int i=1;i<=n;i++)
    {
        if(color[i]==0)
        {
            if(dfs(i,1)==1)
            {
                flag=1;
                break;
            }
        }
    }
    if(flag)
     cout<<""<<endl;
    else
     cout<<""<<endl;
    return 0;
}