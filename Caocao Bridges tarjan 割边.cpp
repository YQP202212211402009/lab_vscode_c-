#include<bits/stdc++.h>
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define int long long
#define endl "\n"
using namespace std;
const int maxn=2000;
const int maxm=maxn*maxn;
int h[maxn],ne[maxm],to[maxm],val[maxm],idx;
void add(int a,int b,int c)//链式前向星 为了可以处理重边，所以要把边一对一对存入判断，不然dfs的时候直接判断f就行
{
    to[idx]=b;val[idx]=c;ne[idx]=h[a];h[a]=idx++;
}
int dfn[maxn],low[maxn],tot,cnt;//时间戳，能抵达的最小的点，tot用来表示戳
//割边 无向图里面割掉一个边可以使连通块增加，这个边就是割边也称桥
struct brige
{
    int x,y,w;
}bri[maxm];
void tarjan(int x,int in_edge)//tarjan算法强调四个点，入，下，回，离
{
    //入时盖戳
    dfn[x]=low[x]=++tot;
    for(int i=h[x];i;i=ne[i])
    {
        int y=to[i];
        if(!dfn[y])//没有访问过
        {
            tarjan(y,i);
            //回的时候判断
            low[x]=min(low[x],low[y]);
            if(low[y]>dfn[x])//注意这里没有等于，因为不让判断回边
            {
                bri[cnt++]={x,y,val[i]};
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
    memset(h,0,sizeof h);memset(dfn,0,sizeof dfn);memset(low,0,sizeof low);
}
int cmp(brige a,brige b)
{
    return a.w<b.w;
}
signed main()
{
    jiasu;
    int n,m;
    while(cin>>n>>m)
    {
        if(n==0 && m==0) break;
        init();
        while(m--)
        {
            int a,b,c; cin>>a>>b>>c;
            add(a,b,c); add(b,a,c);
        }
        tarjan(1,0);
        int flag=1;
        for(int i=2;i<=n;i++)
         if(!dfn[i]) flag=0;
        if(flag==0)
        {
            cout<<0<<endl;
            continue;
        }
        if(cnt==0) cout<<-1<<endl;
        else
        {
            sort(bri,bri+cnt,cmp);
            if(bri[0].w)
             cout<<bri[0].w<<endl;
            else
             cout<<1<<endl;
        }
    }
    return 0;
}