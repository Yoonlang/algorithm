#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int, int>> under;
int map[100][100];
int visit[100][100];
int N, M, P, flag = 0;
int di[4] = {1, -1, 0, 0};
int dj[4] = {0, 0, 1, -1};

void Jave(int num, int thro){
    if(num == 0){
        for(int i = 0; i < M; i++){
            if(map[thro][i] == 1){
                map[thro][i] = 0;
                return;
            }
        }
    }
    else if(num == 1){
        for(int i = M - 1; i >= 0; i--){
            if(map[thro][i] == 1){
                map[thro][i] = 0;
                return;
            }
        }
    }
}

void DFS(int i, int j){
    visit[i][j] = 1;
    for(int k = 0; k < 4; k++){
        int ni = i + di[k];
        int nj = j + dj[k];
        if(ni >= N){
            flag = 1;
            continue;
        }
        if(ni < 0 || nj < 0 || nj >= M){
            continue;
        }
        if(visit[ni][nj] == 1 || map[ni][nj] == 0){
            continue;
        }
        DFS(ni, nj);
    }
}

void color(int i, int j){
    map[i][j] = 2;
    for(int k = 0; k < 4; k++){
        int ni = i + di[k];
        int nj = j + dj[k];
        if(ni < 0 || nj < 0 || nj >= M){
            continue;
        }
        if(map[ni][nj] == 0 || map[ni][nj] == 2){
            continue;
        }
        map[ni][nj] = 2;
        color(ni, nj);
    }
}

int deep(){
    for(int i = 1; i < N; i++){
        for(int j = 0; j < under.size(); j++){
            if(map[under[j].first + i][under[j].second] == 1 || under[j].first + i == N){
                return i - 1;
            }
        }
    }
}

void check(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            visit[i][j] = 0;
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(map[i][j] == 1 && visit[i][j] == 0){
                flag = 0;
                DFS(i, j);
                if(flag == 0){
                    color(i, j);
                    under.clear();
                    for(int k = 0; k < M; k++){
                        for(int l = N - 1; l >= 0; l--){
                            if(map[l][k] == 2){
                                under.push_back(make_pair(l, k));
                                break;
                            }
                        }
                    }
                    int ret = deep();
                    for(int l = N - 1; l >= 0; l--){
                    	for(int k = 0; k < M; k++){
                            if(map[l][k] == 2){
                                map[l + ret][k] = 1;
                                map[l][k] = 0;
                            }
                        }
                    }
                    return;
                }
            }
        }
    }
}

int main(){
    char ch;
    int thro;
    scanf("%d %d ", &N, &M);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            scanf("%1c ", &ch);
            if(ch == '.'){
                map[i][j] = 0;
            }
            else{
                map[i][j] = 1;
            }
        }
    }
    scanf("%d", &P);
    for(int i = 0; i < P; i++){
        scanf("%d", &thro);
        thro--;
        Jave(i % 2, N - thro - 1);
        check();
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(map[i][j] == 0){
                printf(".");
            }
            else{
                printf("x");
            }
        }
        puts("");
    }
    return 0;
}
