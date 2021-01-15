#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include<algorithm>
#include <queue>
#include <string.h>

using namespace std;

vector< vector<int> > adjacent; //인접 리스트의 표현
vector<bool> visited(adjacent.size(), false);
vector< vector<int> > adjacent_test;

int n = 0;
int m = 0;
int ans = 0;

int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };


void bfs(int here) {
	queue<int> qsearch;

	visited[here] = true;
	qsearch.push(here);

	while (!qsearch.empty()) {

		int node = qsearch.front();

		printf("%d ", node);
		qsearch.pop();

		for (unsigned int i = 0; i < adjacent[node].size(); i++) {
			int next = adjacent[node][i];

			if (!visited[next]) {
				visited[next] = true;
				qsearch.push(next);
			}
		}
	}
}

void virusSpread() {
	//SpreadLab은 3개의 벽으로 막은 후 바이러스가 퍼졌을 때의 연구소의 상황을 저장하는곳.
	vector< vector<int> > adjacent_spread;
	adjacent_spread.resize(m, vector<int>(n));

	copy(adjacent_test.begin(), adjacent_test.end(), adjacent_spread.begin());

	queue<pair<int, int>> q;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (adjacent_spread[i][j] == 2)
				q.push(make_pair(i, j));

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			//연구소 범위 안에 감염되지 않은 영역만 오염시킬 수 있다.
			if (0 <= nx && nx < n && 0 <= ny && ny < m) {
				if (adjacent_spread[nx][ny] == 0) {
					adjacent_spread[nx][ny] = 2;
					q.push(make_pair(nx, ny));
				}
			}
		}
	}
	//연구소에 오염되지 않은 부분 체크.
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (adjacent_spread[i][j] == 0)
				cnt += 1;
		}
	}
	ans = max(ans, cnt);
}

int wallcount = 0;

void makeWall(int wallcount) {

	if (wallcount == 3) {
		virusSpread();
		return;
	}
	
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (adjacent_test[i][j] == 0) {
				adjacent_test[i][j] = 1;
				makeWall(wallcount + 1);
				adjacent_test[i][j] = 0;
			}
		}
	}

}

int main() {

	// scanf("%d %d %d", &node, &edge, &start_node);
	
	cin >> n >> m;

	adjacent = vector< vector<int> >(m);
	visited = vector<bool>(m);
	
	int num;

	for (unsigned int i = 0; i < (unsigned)m; i++) {
		for (unsigned int j = 0; j < (unsigned)n; j++) {
			cin >> num;
			adjacent[i].push_back(num);
		}
	}


	adjacent_test.resize(m, vector<int>(n));

	copy(adjacent.begin(), adjacent.end(), adjacent_test.begin());

	makeWall(0);

	/*
	for (unsigned int i = 0; i < (unsigned)m; i++) {
		for (unsigned int j = 0; j < (unsigned)n; j++) {
			cout << adjacent[i][j] << " ";
		}
		cout << "\n";
	}
	*/

	cout << ans;

	// bfs(1);

	return 0;
}

