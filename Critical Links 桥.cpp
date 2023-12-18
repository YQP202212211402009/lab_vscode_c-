#include<bits/stdc++.h>
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
//#define int long long
#define endl "\n"
using namespace std;
const int maxn=10010;
const int maxm=10050;
int h[maxn],ne[maxm],to[maxm],idx;
void add(int a,int b)//链式前向星 为了可以处理重边，所以要把边一对一对存入判断，不然dfs的时候直接判断f就行
{
    to[idx]=b;ne[idx]=h[a];h[a]=idx++;
}
int dfn[maxn],low[maxn],tot,cnt;//时间戳，能抵达的最小的点，tot用来表示戳
//割边 无向图里面割掉一个边可以使连通块增加，这个边就是割边也称桥
struct brige
{
    int x,y;
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
                bri[cnt++]={x,y};
            }
        }
        else if(i!=(in_edge^1))//判断是否是回边
        {
            low[x]=min(low[x],dfn[y]);//不是回边那可以
        }
    }
}
int gra[maxn][maxn];
void init()
{
    memset(gra,0,sizeof gra);
    cnt=0;
    tot=0;idx=2;//从2,3开始因为0用来做边界了
    memset(h,0,sizeof h);
    memset(dfn,0,sizeof dfn);
}
int cmp(brige a,brige b)
{
    if(a.x!=b.x)
     return a.x<b.x;
    else
     return a.y<b.y;
}
signed main()
{
    jiasu;
    int n;
    while(cin>>n)
    {
        init();
        for(int i=0;i<n;i++)
        {
            int x,k; cin>>x;
            char ch; cin>>ch>>k>>ch;
            for(int j=0;j<k;j++)
            {
                int y; cin>>y;
                if(gra[x][y]==0 && gra[y][x]==0)
                {
                    add(x,y);
                    add(y,x);
                    gra[x][y]=1; gra[y][x]=1;
                }
                
            }
        }
        for(int i=0;i<n;i++)
         if(!dfn[i]) tarjan(i,0);
        cout<<cnt<<" critical links"<<endl;
        for(int i=0;i<cnt;i++)
         if(bri[i].x>bri[i].y) swap(bri[i].x,bri[i].y);
        sort(bri,bri+cnt,cmp);
        for(int i=0;i<cnt;i++)
        {
            cout<<bri[i].x<<" - "<<bri[i].y<<endl;
        }
        cout<<endl;
    }
    return 0;
}