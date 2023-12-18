#include<bits/stdc++.h>
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define int long long
#define endl "\n"
using namespace std;
const int maxn=5050;
const int maxm=200005;
//边双连通分量：无向图中极大的不包含割边的连通块
int h[maxn],to[maxm],ne[maxm],idx;//链式前向星
int dfn[maxn],low[maxn],tot;//时间戳，能抵达的最小的点，tot用来表示戳
stack<int>st;//和scc不同的是因为不用判断是否在栈中
int dcc[maxn],cnt;//scc表示第几个数在第几个强联通里面，siz表示大小，cnt表示强连通个数
int bri[maxn],d[maxn];//bri用来判断是否为桥，d用来存缩点后图的度
//low用来和dfn判断，看是否为强连通的根，所以必须要更新low不然会提前出栈，出栈就表示这个数已经列在一个强连通里面了
//dcc和scc不同的是dcc缩的是无向图
void tarjan(int x,int in_edg)//tarjan算法强调四个点，入，下，回，离
{
    //入时盖戳，入栈
    dfn[x]=low[x]=++tot;
    st.push(x);
    for(int i=h[x];i;i=ne[i])//遍历x的相邻节点
    {
        int y=to[i];
        if(!dfn[y])//第一种情况，还没有访问过y
        {
            tarjan(y,i);
            low[x]=min(low[x],low[y]);//回时用lowy更新lowx；
            if(low[y]>dfn[x]) bri[i]=bri[i^1]=1;//一条边两个方向
        }
        else if(i!=(in_edg^1))//不是反边
        {
            low[x]=min(low[x],dfn[y]);
        }
    }
    //离x时记录dcc
    if(dfn[x]==low[x])//若x是根节点
    {
        int y;
        do
        {
            y=st.top();st.pop(); //y出栈
            dcc[y]=cnt;//y是第cnt个强连通的
        }while(y!=x); //找到根节点就退出
        cnt++;
    }
}
void add(int a,int b)
{
    to[idx]=b;ne[idx]=h[a];h[a]=idx++;
}
void init()
{
    tot=0;cnt=0;idx=2;//从2开始
    memset(dfn,0,sizeof dfn);memset(bri,0,sizeof bri);
}
signed main()
{
    jiasu;
    init();
    int n,m; cin>>n>>m;
    while(m--)
    {
        int a,b; cin>>a>>b;
        add(a,b);add(b,a);
    }
    tarjan(1,0);//不用循环是因为是连通图
    for(int i=2;i<idx;i++)//每条边每个方向都找过来
    {
        if(bri[i])
         d[dcc[to[i]]]++;//这条边如果是割边那这条边终点++，因为两个方向都存了所以都会加的
    }
    int sum=0;
    for(int i=0;i<cnt;i++)
     if(d[i]==1) sum++; //找叶子结点的个数
    cout<<(sum+1)/2<<endl; //(sum+1)/2就是答案
    return 0;
}