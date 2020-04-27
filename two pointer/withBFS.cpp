#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> height;
int N, si, sj, result = 987654321;
int map[50][50];
int tired[50][50];
int visit[50][50] = { 0 };
int queue[100000][2];
int front, rear;
int pop[2];
int di[8] = {1, 1, 1, 0, 0, -1, -1, -1};
int dj[8] = {1, 0, -1, 1, -1, 1, 0, -1};

int main(){
	int find = 0;
    char ch;
    scanf("%d ", &N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            scanf("%1c ", &ch);
            switch(ch){
                case 'K':
                    map[i][j] = 1;
                    find++;
                    break;
                case 'P':
                    map[i][j] = 2;
                    si = i;
                    sj = j;
                    break;
                case '.':
                    map[i][j] = 0;
                    break;
            }
        }
    }
    int last = -1;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            scanf("%d", &tired[i][j]);
            if(map[i][j] != 0){
                if(tired[i][j] > last){
                    last = tired[i][j];
                }
            }
            height.push_back(tired[i][j]);
        }
    }
    sort(height.begin(), height.end());
	  height.erase(unique(height.begin(), height.end()), height.end());
    for(int i = 0; i < height.size(); i++){
        if(last == height[i]){
            last = i;
            break;
        }
    }
    int low = 0, high = last;
    while(low < height.size()){
        memset(visit, 0, sizeof(visit));
        int stack = 0;
        front = 0;
        rear = 0;
        if(height[low] <= tired[si][sj] && tired[si][sj] <= height[high]){
            queue[rear][0] = si;
            queue[rear][1] = sj;
            rear++;
        }
        while(front < rear){
            pop[0] = queue[front][0];
            pop[1] = queue[front][1];
            front++;
            if(visit[pop[0]][pop[1]]){
                continue;
            }
            if(map[pop[0]][pop[1]] == 1){
                stack++;
            }
            visit[pop[0]][pop[1]] = 1;
            for(int k = 0; k < 8; k++){
                int ni = pop[0] + di[k];
                int nj = pop[1] + dj[k];
                if(ni < 0 || ni >= N || nj < 0 || nj >= N){
                    continue;
                }
                if(visit[ni][nj] || tired[ni][nj] > height[high] || tired[ni][nj] < height[low]){
                    continue;
                }
                queue[rear][0] = ni;
                queue[rear][1] = nj;
                rear++;
            }
        }
        if(find == stack){
            result = min(result, height[high] - height[low]);
            low++;
        }
        else if(high + 1 < height.size()){
            high++;
        }
        else{
            break;
        }
    }
    printf("%d", result);
    return 0;
}
