#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
const int maxn=1010;
int mod,n;
double eps=1e-8;
int a[maxn][maxn],A[maxn][maxn];
int gauss(int n)
{
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
    while(cin>>n>>mod)
    {
        for(int i=1;i<=n;i++)
         for(int j=1;j<=n;j++)
          cin>>a[i][j];
        cout<<gauss(n)<<endl;
    }
	return 0;
}