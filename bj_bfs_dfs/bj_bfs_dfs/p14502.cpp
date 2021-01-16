#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include<algorithm>
#include <queue>
#include <string.h>

using namespace std;

int m = 0; // 너비
int n = 0; // 높이

int max_space = 0; // 최대 안전(0) 공간

// 방향 배열
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

int lab[8][8]; // 연구소
int temp_lab[8][8]; // 벽을 세울 연구소
int virus_lab[8][8]; // 바이러스가 퍼진 연구소

bool visited[8][8] = { false };

void bfs(int x, int y) {
	queue<pair <int, int>> qsearch; // 좌표상 위치
	qsearch.push(make_pair(x, y));
	visited[x][y] = true;

	while (!qsearch.empty()) {

		x = qsearch.front().first;
		y = qsearch.front().second;
		qsearch.pop();

		for (unsigned int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (nx < 0 || ny < 0 || nx >= m || ny >= n)
				continue;

			//방문하지 않았고 벽이 아닌 경우
			if (visited[nx][ny] == false && virus_lab[nx][ny] == 0) { 
				virus_lab[nx][ny] = 2; // 바이러스를 퍼뜨림
				visited[nx][ny] = true;
				qsearch.push(make_pair(nx, ny)); 
			}
		}
	}
}

void spread_virus() {
	
	// 벽을 세운 배열 복사 및 방문 여부 초기화
	for (unsigned int i = 0; i < (unsigned)m; i++) {
		for (unsigned int j = 0; j < (unsigned)n; j++) {
			virus_lab[i][j] = temp_lab[i][j];
			visited[i][j] = false;
		}
	}

	// 바이러스 퍼뜨림 (bfs)
	for (unsigned int i = 0; i < (unsigned)m; i++) {
		for (unsigned int j = 0; j < (unsigned)n; j++) {
			if (virus_lab[i][j] == 2) {
				bfs(i, j);
			}
		}
	}

	// 안전(0) 구역 크기
	int safe = 0;
	for (unsigned int i = 0; i < (unsigned)m; i++) {
		for (unsigned int j = 0; j < (unsigned)n; j++) {
			if (virus_lab[i][j] == 0) {
				safe++;
			}
		}
	}

	// 최대 안전 구역 저장
	max_space = max(max_space, safe);
}


// 벽을 세우는 함수 (재귀 호출)
void make_wall(int wallcount) {

	// 벽 3개를 세웠을 경우
	if (wallcount == 3) {
		spread_virus();
		return;
	}
	else {
		for (unsigned int i = 0; i < (unsigned)m; i++) {
			for (unsigned int j = 0; j < (unsigned)n; j++) {
				if (temp_lab[i][j] == 0) {
					temp_lab[i][j] = 1;
					make_wall(wallcount + 1);
					temp_lab[i][j] = 0;
				}
			}
		}
	}
}

int main() {

	// 연구소 구조 정보 입력
	scanf("%d %d", &m, &n);
	
	for (unsigned int i = 0; i < (unsigned)m; i++) {
		for (unsigned int j = 0; j < (unsigned)n; j++) {
			scanf("%d", &lab[i][j]);
		}
	}
	
	// 벽을 세울 임시 연구실로 복사
	for (unsigned int i = 0; i < (unsigned)m; i++) {
		for (unsigned int j = 0; j < (unsigned)n; j++) {
			temp_lab[i][j] = lab[i][j];
		}
	}

	// 벽 세우기
	for (unsigned int i = 0; i < (unsigned)m; i++) {
		for (unsigned int j = 0; j < (unsigned)n; j++) {
			if (temp_lab[i][j] == 0) {
				temp_lab[i][j] = 1;
				make_wall(1);
				temp_lab[i][j] = 0;
			}
		}
	}

	printf("%d", max_space);

	return 0;
}

