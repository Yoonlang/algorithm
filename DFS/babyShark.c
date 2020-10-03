//20.10.03
/*
런타임 에러가 났던 이유
queue에 push 할 때 미리 visit 값을 1로 바꿔줘야 중복 방문이 덜 일어남.
*/
#include <stdio.h>
#include <string.h>

int N;
int di[4] = {-1, 0, 0, 1}; // x 상대좌표
int dj[4] = {0, -1, 1, 0}; // y 상대좌표
int eatingStack = 0;
int sharkSize = 2;
int totalTime = 0;
int map[21][21];
int visit[21][21];
int queue[1000000][4];
int front = 0, rear = 0;
int pop[4];
int sharkX, sharkY;
int gotoX = -1, gotoY = 0, far;

int ins(int a){
	return a > 0 ? a : -1 * a;
}

void findFish(){
    /*
    한 번의 findFish()에서 하나의 먹이를 찾으러 감.
    상어가 있던 위치에서 범위를 넓혀가면서 먹을 수 있는 물고기와 그 거리를 탐색.
    변수 far을 통해 가장 가까운 물고기까지의 거리를 저장한 뒤 합산.
    */
	queue[0][0] = sharkX; // x 위치
	queue[0][1] = sharkY; // y 위치
	queue[0][2] = 0; // 근처 물고기가 발견 된 제일 가까운 거리
	queue[0][3] = 0; // 원래 상어가 있던 자리에서 이동한 거리
	rear++;
	visit[sharkX][sharkY] = 1;
	int limit = 987654321; // 물고기가 발견되면 limit를 제한둬서 더이상 queue가 진행되지 않게
	while(front < rear){
		pop[0] = queue[front][0];
		pop[1] = queue[front][1];
		pop[2] = queue[front][2];
		pop[3] = queue[front][3];
		front++;
		for(int k = 0; k < 4; k++){
            // 상대좌표를 통해 4방향을 일일이 치지않고 한번에 확인할 수 있음.
			int ni = pop[0] + di[k]; // 상대좌표를 통해 다음 갈 곳
			int nj = pop[1] + dj[k];
			if(pop[2] >= limit){
				break;
			}
			if(ni < 0 || ni >= N || nj < 0 || nj >= N){
                // 상대좌표이기 때문에 벽뚫 방지
				continue;
			}
			if(map[ni][nj] > sharkSize || visit[ni][nj] == 1){
				continue;
			}
			if(map[ni][nj] == sharkSize || map[ni][nj] == 0){
				queue[rear][0] = ni;
				queue[rear][1] = nj;
				queue[rear][2] = pop[2] + 1;
				queue[rear][3] = pop[3] + 1;
				rear++;
			}
			else{
				if(gotoX == -1){
					gotoX = ni;
					gotoY = nj;
					limit = pop[2] + 1;
					far = pop[3] + 1;
				}
				else{
					if(gotoX > ni){
						gotoX = ni;
						gotoY = nj;
						far = pop[3] + 1;
					}
					else if(gotoX == ni){
						if(gotoY > nj){
							gotoX = ni;
							gotoY = nj;
							far = pop[3] + 1;
						}
					}
				}
			}
            visit[ni][nj] = 1;
		}
	}
}

int main(){
	scanf("%d", &N);
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			scanf("%d", &map[i][j]);
			if(map[i][j] == 9){
				sharkX = i;
				sharkY = j;
			}
		}
	}
	while(1){
		memset(visit, 0, sizeof(visit));
		findFish();
		if(gotoX == -1){
			break;
		}
        
        //초기화
		totalTime += far;
		map[gotoX][gotoY] = 9;
		map[sharkX][sharkY] = 0;
		sharkX = gotoX;
		sharkY = gotoY;
		gotoX = -1;
		gotoY = 0;
		front = 0;
		rear = 0;
		far = 0;
        
        //물고기 먹으면서 커지기
		eatingStack++;
		if(eatingStack == sharkSize){
			sharkSize++;
			eatingStack = 0;
		}
	}
	printf("%d", totalTime);
	return 0;
}