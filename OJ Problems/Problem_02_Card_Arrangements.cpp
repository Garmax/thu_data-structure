// OJ Problem #2
// Card Arrangements

#include<iostream>
#include<algorithm>
using namespace std;

int card[100001], cardMaxCap[100001];
int op[1000001][3];
int* stack[100001];

int main() {
	ios::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++)
		card[i] = 1;
	
	for (int j = 0; j<m; j++) {
		cin >> op[j][0] >> op[j][1] >> op[j][2];
		if (op[j][0] == 1) {
			int x = op[j][1], y = op[j][2];
			cardMaxCap[x] = max(card[x], cardMaxCap[x]);
			card[x]--;
			card[y]++;
			cardMaxCap[y] = max(card[y], cardMaxCap[y]);
		}
	}
	
	for (int l = 1; l <= n; l++) {
		card[l] = 1;
		stack[l] = new int[cardMaxCap[l] + 1];
		stack[l][1] = l;
	}
	
	for (int q = 0; q<m; q++) {
		int x = op[q][1], y = op[q][2];
		if (op[q][0] == 1) {
		    int k=stack[x][card[x]];
		    card[x]--;
		    card[y]++;
			stack[y][card[y]] = k;
			cout << k << '\n';
		}
		else {
			cout << stack[x][y] << '\n';
		}
	}
	
	for (int h = 1; h <= n; h++) {
		delete[] stack[h];
	}
	return 0;
}