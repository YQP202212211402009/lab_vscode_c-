// Problem: 小天的贪吃蛇
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/72041/E
// Memory Limit: 262144 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>

using namespace std;

#define fi first
#define sc second
#define endl '\n'
#define pb push_back
#define mem0(a) memset(a,0,sizeof(a))
#define mem1(a) memset(a,-1,sizeof(a))
#define meminf(a) memset(a,0x3f,sizeof(a))
#define debug(x) cout<<"----Line#"<<x<<"----"<<endl
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;
typedef pair<char, char> PCC;
typedef pair<int, string> PIS;
const int INF = 0x3f3f3f3f;
const double eps = 1e-6;
const ll mod = 1e9 + 7;
ll gcd(ll a,ll b) {return b?gcd(b,a%b):a;}

const int N = 1e5 + 10;
int n, m, q;
string col, row;
map<PII, int> mp1, mp2;
set<int> s1[26], s2[26];

void solve () {
    cin >> n >> m;
    vector s(n + 1, vector<char> (m + 1));
    for (int i = 1; i <= n; i ++) {
    	for (int j = 1; j <= m; j ++) {
    		cin >> s[i][j];
    	}
    }
    for (int i = 1, v = 1; i <= n; i ++)
    	if (i & 1) 
    		for (int j = 1; j <= m; j ++) 
    			mp1[{i, j}] = v ++;
    	else 
    		for (int j = m; j >= 1; j --)
    			mp1[{i, j}] = v ++;
    			
    for (int j = 1, v = 1; j <= m; j ++) 
    	if (j & 1) 
    		for (int i = 1; i <= n; i ++) 
    			mp2[{i, j}] = v ++;
     	else 
    		for (int i = n; i >= 1; i --) 
    			mp2[{i, j}] = v ++;
	
    for (int i = 1; i <= n; i ++) 
    	for (int j = 1; j <= m; j ++) {
    		int ch = s[i][j] - 'a';
    		s1[ch].insert(mp1[{i, j}]);
    		s2[ch].insert(mp2[{i, j}]);
    	}
 	cin >> q;
    while (q --) {
    	int op, x, y; cin >> op >> x >> y;
    	if (op == 1) {
    		char c; cin >> c;
    		char ch = s[x][y];
    		s1[ch - 'a'].erase(mp1[{x, y}]);
    		s2[ch - 'a'].erase(mp2[{x, y}]);
    		s1[c - 'a'].insert(mp1[{x, y}]);
    		s2[c - 'a'].insert(mp2[{x, y}]);
    		s[x][y] = c;
    	} else if (op == 2) {
    		char ch = s[x][y];
    		int ans = INF;
    		for (char c = 'a'; c <= 'z'; c ++) {
    			if (c == ch) continue;
    			else {
    				auto pos = s1[c - 'a'].lower_bound(mp1[{x, y}]);
    				if (pos == s1[c - 'a'].end()) {
    					ans = min(ans, n * m - mp1[{x, y}] + 1);
    				} else {
    					ans = min(ans, *pos - mp1[{x, y}]);
    				}
    			}
    		}
    		cout << ans << endl;
    	} else {
    		char ch = s[x][y];
    		int ans = INF;
    		for (char c = 'a'; c <= 'z'; c ++) {
    			if (c == ch) continue;
    			else {
    				auto pos = s2[c - 'a'].lower_bound(mp2[{x, y}]);
    				if (pos == s2[c - 'a'].end()) {
    					ans = min(ans, n * m - mp2[{x, y}] + 1);
    				} else {
    					ans = min(ans, *pos - mp2[{x, y}]);
    				}
    			}
    		}
    		cout << ans << endl;
    	}
    }
    return ;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T = 1;
    //cin >> T;
    while (T --) {
        solve ();
    }
    return 0;
}
