#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

struct Node{
    int v; //v:邻接边的目标顶点
    int dis; //dis: 边权
    Node(int _v, int _dis) : v(_v), dis(_dis) {} 
};

const int MAXN = 510;
const int INF = 999999999;
vector<Node> G[MAXN];   // 邻接矩阵
int dis[MAXN];          // 储存到每个顶点的最短路径
int num[MAXN];          // 到每个顶点有多少条最短路径
set<int> pre[MAXN];     // 储存顶点的前节点

int teams[MAXN];        // 每个顶点的救援队数量
int maxTeams[MAXN];     // 到每个顶点最短路径的最大救援队数量
void Bellman(int N){
    for(int i=0; i<N-1; i++){
        for(int u=0; u<N; u++){
            for(int j=0; j<G[u].size(); j++){
                int v = G[u][j].v;
                int d = G[u][j].dis;
                if(dis[u]+d<dis[v]){
                    dis[v] = dis[u] + d;
                    num[v] = num[u];
                    maxTeams[v] = maxTeams[u] + teams[v];
                    pre[v].clear();
                    pre[v].insert(u);
                }else if(dis[u]+d==dis[v]){
                    pre[v].insert(u);
                    num[v] = 0;
                    set<int>::iterator it;
                    for(it=pre[v].begin(); it!=pre[v].end(); it++){
                        num[v] += num[*it];
                    }
                    if(maxTeams[v]<maxTeams[u]+teams[v]){
                        maxTeams[v] = maxTeams[u]+teams[v];
                    } 
                }
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
    for(int i=0; i<M; i++){
        scanf("%d%d%d", &cc1, &cc2, &L);
        G[cc2].push_back(Node(cc1, L));
        G[cc1].push_back(Node(cc2, L));
    }
    
    fill(dis, dis+MAXN, INF);
    memset(num, 0, sizeof(num));
    memset(maxTeams, 0, sizeof(maxTeams));
    dis[C1] = 0;
    num[C1] = 1;
    maxTeams[C1] = teams[C1];   // 也可以在Bellman函数内初始化，对于多点测试比较方便
    Bellman(N);
    
    printf("%d %d", num[C2], maxTeams[C2]);
    system("pause");
    return 0;
}
