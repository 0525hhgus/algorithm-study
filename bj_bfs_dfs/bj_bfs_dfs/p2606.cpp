#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include<algorithm>
#include <string.h>

using namespace std;

vector< vector<int> > adjacent; //인접 리스트의 표현
vector<bool> visited(adjacent.size(), false);

int vircount = - 1;

void dfs(int here) {
	//printf("s %d ", here);
	visited[here] = true;
	vircount++;

	for (unsigned int i = 0; i < adjacent[here].size(); i++) {
		if (!visited[adjacent[here][i]])
			dfs(adjacent[here][i]);
	}

}

int main() {


	int node = 0;
	int edge = 0;
	int start_node = 1;

	//scanf("%d %d %d", &node, &edge, &start_node);

	cin >> node;
	cin >> edge;

	node++;

	adjacent = vector< vector<int> >(node);
	visited = vector<bool>(node);

	int num1;
	int num2;

	for (unsigned int i = 0; i < (unsigned)edge; i++) {
		cin >> num1 >> num2;

		adjacent[num2].push_back(num1);
		adjacent[num1].push_back(num2);
	}

	for (unsigned int i = 0; i < adjacent.size(); i++) {
		sort(adjacent[i].begin(), adjacent[i].end());
	}

	dfs(start_node);


	cout << vircount;

	return 0;
}

