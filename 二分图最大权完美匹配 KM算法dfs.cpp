#include<bits/stdc++.h>
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define int long long
#define endl "\n"
using namespace std;
//如果最大匹配有N条边，那么就成这个匹配为完美匹配。
//可行顶标：给每个节点分配权值la[x],lb[y],对所有边满足la[x]+lb[y]>=w;
//相等子图:包含所有点只满足有la[x]+lb[y]==w[x,y]的边
//如果相等子图是完美匹配，那么这个图就是最大权完美匹配
//dfs 时间复杂度O(n^4)
const int maxn=510;
const int maxm=maxn*maxn;
#define inf 0x3f3f3f3f3f3f3f3f
int n,m;
int match[maxn];
int va[maxn],vb[maxn];//标记是否在交替路中,匈牙利算法里只用标记右边的点，这是为了修改权值，左边也要修改
int la[maxn],lb[maxn];
int w[maxn][maxn],d[maxn];//维护更新的delta值
int dfs(int x)
{
    va[x]=1;
    for(int y=1;y<=n;y++)
    {
        if(!vb[y])
        {
            if(la[x]+lb[y]==w[x][y])//相等子图
            {
                vb[y]=1;
                if(!match[y] || dfs(match[y]))
                {
                    match[y]=x;
                    return 1;
                }
            }
            else
             d[y]=min(d[y],la[x]+lb[y]-w[x][y]);//不是相等子图就记录差值
        }
    }
    return 0;
}
int EM()
{
    //左顶标取出边的最大值
    for(int i=1;i<=n;i++) la[i]=-inf;
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      la[i]=max(la[i],w[i][j]);
    memset(lb,0,sizeof lb);//右顶标一开始都是0
    memset(match,0,sizeof match);
    for(int i=1;i<=n;i++)
    {
        while(1)//直到左顶标匹配，就算你这次不匹配但是可以改变顶标的值反正一定会匹配的
        {
            memset(va,0,sizeof va);
            memset(vb,0,sizeof vb);
            memset(d,inf,sizeof d);
            if(dfs(i)) break;//如果找到就break不然就改值
            int delta=inf;
            for(int j=1;j<=n;j++)
             if(!vb[j]) delta=min(delta,d[j]);//不在交替路,不是相等子图
            for(int j=1;j<=n;j++)
            {
                if(va[j]) la[j]-=delta;
                if(vb[j]) lb[j]+=delta;//在交替路中才修改
            }
        }
    }
    int res=0;
    for(int i=1;i<=n;i++)
     res+=w[match[i]][i];
    return res;
}
signed main()
{
    jiasu;
    while(cin>>n)
    {
        for(int i=1;i<=n;i++)
         for(int j=1;j<=n;j++)
          w[i][j]=-inf;
        for(int i=1;i<=n;i++)
         for(int j=1;j<=n;j++)
          cin>>w[i][j];
        cout<<EM()<<endl;
    }
    return 0;
}