#include<bits/stdc++.h>
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define int long long
#define endl "\n"
using namespace std;
const int maxn=5050;
const int maxm=200005;
//边点连通分量：无向图中极大点双连通子图
vector<int>g[maxn],ne[maxn];//一开始的图和缩点后的图
int dfn[maxn],low[maxn],tot;//时间戳，能抵达的最小的点，tot用来表示戳
stack<int>st;//和scc不同的是因为不用判断是否在栈中
vector<int>dcc[maxn];//用来存每个双连通里面的点
int cut[maxn],root,cnt,num,id[maxn];//cut用来表示是否为割点，割点和双连通的判断并不相同，id用来表示割点的新点
//low用来和dfn判断，看是否为强连通的根，所以必须要更新low不然会提前出栈，出栈就表示这个数已经列在一个强连通里面了
//dcc和scc不同的是dcc缩的是无向图
void tarjan(int x)//tarjan算法强调四个点，入，下，回，离
{
    //入时盖戳，入栈
    dfn[x]=low[x]=++tot;
    st.push(x);
    if(!g[x].size())//单个点也算双连通但并不是割点，单个点也进不去循环所以要单独判断
    {
        dcc[cnt++].push_back(x);
        return ;
    }
    int child=0;
    for(auto y:g[x])//遍历x的相邻节点
    {
        if(!dfn[y])//第一种情况，还没有访问过y
        {
            tarjan(y);
            low[x]=min(low[x],low[y]);//回时用lowy更新lowx；
            //回时判断是否为割点，判断是否为双连通
            if(low[y]>=dfn[x])//双连通的判断
            {
                child++;
                if(x!=root || child>1)//割点的判断
                {
                    cut[x]=1;
                }
                while(1)
                {
                    int z=st.top();st.pop();
                    dcc[cnt].push_back(z);
                    if(z==y) break;
                }
                dcc[cnt++].push_back(x);//!!!!!!!特别的，要把那个割点也放进去，割点要分裂成好几个
            }
        }
        else//门槛很低，只要访问过就行
         low[x]=min(low[x],dfn[y]);
    }
}
void init()
{
    tot=0;cnt=0;//从2开始
    memset(dfn,0,sizeof dfn);
}
signed main()
{
    jiasu;
    init();
    int n,m;cin>>n>>m;
    while(m--)
    {
        int a,b;cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for(root=1;root<=n;root++)
     if(!dfn[root]) tarjan(root);
    //给每个割点一个编号，从cnt开始
    num=cnt;
    for(int i=1;i<=n;i++)
     if(cut[i]) id[i]=num++;//num和id的用处
    //建新图，让双连通和割点建边
    for(int i=0;i<cnt;i++)//遍历双连通
    {
        for(int j=0;j<dcc[i].size();j++)
        {
            int x=dcc[i][j];
            if(cut[x])//找到割点，体现了 上面特地吧割点放进去的重要性
            {
                ne[i].push_back(id[x]);//id[x]太庙了
                ne[id[x]].push_back(i);//双向
            }
        }
    }
    return 0;
}