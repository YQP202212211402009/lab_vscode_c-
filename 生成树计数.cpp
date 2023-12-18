#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
const int maxn=20;
const int mod=1000000000;
double eps=1e-8;
int a[maxn][maxn],A[maxn][maxn],num[maxn][maxn];
char g[maxn][maxn];
int gauss(int n)
{
	//n--;
	memcpy(A,a,sizeof a);
    int res = 1;
    for(int i = 1; i <= n; ++i)
	{
        for(int j = i + 1; j <= n; ++j)
		{
            while(A[j][i])
			{
                int t = A[i][i] / A[j][i];
                for(int k = i; k <= n; ++k)
                 A[i][k] = (A[i][k] - A[j][k] * t) % mod;
                for(int k = i; k <= n; ++k)
                 swap(A[i][k],A[j][k]);
                res = -res; 
            }
        }
        if(!A[i][i]) return 0;
        res = res * A[i][i] % mod;
    }
    return (res + mod) % mod;
}
signed main()
{
	jiasu;
	int n,m;
    int tot=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>g[i][j];
            if(g[i][j]=='.')
            {
                num[i][j]=++tot;
            }
        }
    }
    memset(a,0,sizeof a);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(i<n && g[i][j]=='.' && g[i+1][j]=='.')
            {
                int x=num[i][j],y=num[i+1][j];
                a[x][x]++;a[y][y]++;a[x][y]=a[y][x]=-1;
            }
            if(j<m && g[i][j]=='.' && g[i][j+1]=='.')
            {
                int x=num[i][j],y=num[i][j+1];
                a[x][x]++;a[y][y]++;a[x][y]=a[y][x]=-1;
            }
        }
    }
    cout<<gauss(tot)<<endl;
	return 0;
}
