#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

    const int MAXN = 510;
    const int INF = 1000000000;

    //int G[MAXN][MAXN] = {INF};
    int G[MAXN][MAXN];          // 邻接矩阵
    int dis[MAXN];              // 保存最小路径
    int teams[MAXN];            // teams[i]第i个城市救援队数量
    bool vis[MAXN] = {false};   // 是否访问过
    int num[MAXN];              // i节点的最短路径数量
    int maxTeams[MAXN];         // i节点最短路径的最大救援数量

    void searching(int C1, int C2, int N){
        
        for(int i=0; i<N; i++){
            int u = -1, MIN = INF;
            for(int j=0; j<N; j++){
                if(vis[j]==false && dis[j]<MIN){
                    u = j;
                    MIN = dis[j];
                }
            }
            if(u==-1) return;
            vis[u] = true;
            printf("%d++%d\n", u, maxTeams[u]);
            //if(u==C2) return;

            for(int v=0; v<N; v++){
                if(vis[v]==false && G[u][v]!=INF){
                    if(dis[u]+G[u][v]<dis[v]){
                        dis[v] = dis[u] + G[u][v];
                        num[v] = num[u];
                        maxTeams[v] = maxTeams[u] + teams[v];
                    }else if(dis[u]+G[u][v]==dis[v]){
                        num[v] += num[u];
                        if(maxTeams[v]<maxTeams[u] + teams[v]){
                            maxTeams[v] = maxTeams[u] + teams[v];
                        }
                    }
                    printf("v:%d--num[v]:%d--maxT[v]%d\n", v, num[v], maxTeams[v]);
                }
            }
        }
    }


int main(){
    int N, M; // N:numof cities, M:numof roads
    int C1, C2; // C1: start, C2: end
    scanf("%d%d%d%d", &N, &M, &C1, &C2);
    for(int i=0; i<N; i++){
        scanf("%d", &teams[i]);
    }
    int cc1, cc2, L;
    fill(G[0], G[0]+MAXN*MAXN, INF);
    for(int i=0; i<M; i++){
        scanf("%d%d%d", &cc1, &cc2, &L);
        G[cc1][cc2] = G[cc2][cc1] = L;
    }

    fill(dis, dis+MAXN, INF);
    memset(num, 0, sizeof(num));
    memset(maxTeams, 0, sizeof(maxTeams));
    dis[C1] = 0;
    num[C1] = 1;
    maxTeams[C1] = teams[C1];
    
    searching(C1, C2, N);
    printf("%d %d", num[C2], maxTeams[C2]);
    system("pause");
    return 0;
}
