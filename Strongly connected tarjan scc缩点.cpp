#include<bits/stdc++.h>
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define int long long
#define endl "\n"
using namespace std;
//这个题目要使整个图的边最多但是又是非强连通图，意思就是不能在所有点都可以遍历整个图，我们可以
//认为把图最终变为两个巨大的环然后这两个环中间只有一个方向通行
//一个环为x一个为y 最终边个数就是x*(x-1)+y*(y-1)+x*y-m;
//又因为x+y=n 最终就是n^2-x*y-n-m 那就是x*y要最小 x==y的时候是最大的，x y要差的大,那久直接拿
//缩了点之后最小的环当x就好了
//缩点加边到最后，X 与 Y 一定是 X → Y 或者 Y → X 的，所以作为 X Y 的前提条件是， 入度为 0 或者出度为 0 
const int maxn=200010;
vector<int>g[maxn];//ne表示缩点后的图
int dfn[maxn],low[maxn],tot;//时间戳，能抵达的最小的点，tot用来表示戳
int stk[maxn],instk[maxn],top;//手写栈，判断某个数是否在栈中，top表示栈顶
int scc[maxn],siz[maxn],cnt;//scc表示第几个数在第几个强联通里面，siz表示大小，cnt表示强连通个数
int din[maxn],dout[maxn];
//low用来和dfn判断，看是否为强连通的根，所以必须要更新low不然会提前出栈，出栈就表示这个数已经列在一个强连通里面了
void tarjan(int x)//tarjan算法强调四个点，入，下，回，离
{
    //入时盖戳，入栈
    dfn[x]=low[x]=++tot;
    stk[++top]=x; instk[x]=1;
    for(auto y:g[x])//遍历x的相邻节点
    {
        if(!dfn[y])//第一种情况，还没有访问过y
        {
            tarjan(y);
            low[x]=min(low[x],low[y]);//回时用lowy更新lowx；
        }
        else if(instk[y])//第二种情况，y访问过了并且y在栈中
        {
            low[x]=min(low[x],dfn[y]);
        }
        //第三种访问过并且出栈，那就不用操作就不写
    }
    //离x时记录scc
    if(dfn[x]==low[x])//若x是根节点
    {
        int y;
        do
        {
            y=stk[top--];instk[y]=0; //y出栈
            scc[y]=cnt;siz[cnt]++;//y是第cnt个强连通的，第cnt强连通个数++
        }while(y!=x); //找到根节点就退出
        cnt++;
    }
}
int n,m;
void init()
{
    tot=0;cnt=0;top=0;
    memset(dfn,0,sizeof dfn);memset(siz,0,sizeof siz);memset(instk,0,sizeof instk);memset(low,0,sizeof low);
    memset(scc,0,sizeof scc);memset(din,0,sizeof din);memset(dout,0,sizeof dout);
    for(int i=1;i<=n;i++) g[i].clear();
}
signed main()
{
    jiasu;
    int t;cin>>t;
    for(int ca=1;ca<=t;ca++)
    {
        init();
        cin>>n>>m;
        for(int i=0;i<m;i++)
        {
            int a,b; cin>>a>>b;
            g[a].push_back(b);
        }
        for(int i=1;i<=n;i++)//缩点
         if(dfn[i]==0) tarjan(i);
        cout<<"Case "<<ca<<": ";
        if(cnt==1)
        {  
            cout<<-1<<endl;
        }
        else
        {
            for(int i=1;i<=n;i++)
            {
                for(auto y:g[i])
                {
                    if(scc[i]!=scc[y])// i->y
                    {
                        din[scc[y]]++;
                        dout[scc[i]]++;
                    }
                }
            }
            int ma,mi=INT_MAX;
            for(int i=0;i<cnt;i++)
            {
                if(din[i]==0 || dout[i]==0)
                 mi=min(mi,siz[i]);
            }
            ma=n-mi;
            cout<<ma*(ma-1)+mi*(mi-1)+ma*mi-m<<endl;
        }
    }
    return 0;
}