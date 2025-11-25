// Problem: G. Famous Choreographer
// Contest: Codeforces - Codeforces Round 1043 (Div. 3)
// URL: https://codeforces.com/contest/2132/problem/G
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <vector>

using namespace std;

const int mod = 923135259;

const int base1 = 269, base2 = 271;

long long final_ans;

void solve(int n, int m, const vector<vector<char>> &a){
	vector<vector<int>> H_LtoR(n + 2, vector<int>(m + 2, 0));
	vector<vector<int>> H_RtoL(n + 2, vector<int>(m + 2, 0));
	vector<vector<int>> H_UtoD(n + 2, vector<int>(m + 2, 0));
	vector<vector<int>> H_DtoU(n + 2, vector<int>(m + 2, 0));
	vector<int> b1(max(n, m) + 1, 0);
	vector<int> b2(max(n, m) + 1, 0);
	b1[0] = b2[0] = 1;
	for(int i = 1; i <= max(n, m); i++){
		b1[i] = 1ll * b1[i - 1] * base1 % mod;
		b2[i] = 1ll * b2[i - 1] * base2 % mod;
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++)
			H_LtoR[i][j] = (1ll * H_LtoR[i][j - 1] * base1 % mod + a[i][j]) % mod;
		for(int j = m; j >= 1; j--)
			H_RtoL[i][j] = (1ll * H_RtoL[i][j + 1] * base1 % mod + a[i][j]) % mod;
	}
	for(int j = 1; j <= m; j++){
		for(int i = 1; i <= n; i++)
			H_UtoD[i][j] = (1ll * H_UtoD[i - 1][j] * base2 % mod + H_LtoR[i][j]) % mod;
		for(int i = n; i >= 1; i--){
			int tmp = ((H_RtoL[i][1] - 1ll * H_RtoL[i][j + 1] * b1[j] % mod) % mod + mod) % mod;
			H_DtoU[i][j] = (1ll * H_DtoU[i + 1][j] * base2 % mod + tmp) % mod;
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			int ans1 = H_UtoD[i][j];
			int ans2 = ((H_DtoU[1][j] - 1ll * b2[i] * H_DtoU[i + 1][j] % mod) % mod  + mod) % mod;
			if(ans1 == ans2) final_ans = min(final_ans, 1ll * (2 * n - i) * (2 * m - j) - 1ll * n * m);
		}
	}
}

void solve(){
	int n, m;
	cin >> n >> m;
	final_ans = 1e18;
	vector<vector<char>> a(n + 2, vector<char>(m + 2, 0));
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin >> a[i][j];
	solve(n, m, a);
	vector<vector<char>> b(m + 2, vector<char>(n + 2, 0));
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			b[m - j + 1][i] = a[i][j];
	solve(m, n, b);
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= n; j++)
			a[n - j + 1][i] = b[i][j];
	solve(n, m, a);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			b[m - j + 1][i] = a[i][j];
	solve(m, n, b);
	cout << final_ans << '\n';
}

int main(){
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}
