#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

struct Node{
    int id;
    int d; //distance
    int c; //cost
};
const int MAXN = 510;
const int INF = 999999999;

vector<Node> G[MAXN];
int Dis[MAXN];
bool vis[MAXN] = {false};

vector<int> pre[MAXN]; //记录前节点（最短路径）

void travel(int C1, int C2, int N){   // Dijkstra算法
    
    for(int i=0; i<N; i++){
        int u = -1, MIN = INF;
        for(int j=0; j<N; j++){
            if(vis[j]==false && Dis[j]<MIN){
                u = j;
                MIN = Dis[j];
            }
        }
        if(u==-1) return;
        vis[u] = true;
        //if(u==C2) return;
        for(int j=0; j<G[u].size(); j++){
            Node x = G[u][j];
            if(vis[x.id]==false){
                if(Dis[x.id]>Dis[u]+x.d){
                    Dis[x.id] = Dis[u] + x.d;
                    pre[x.id].clear();
                    pre[x.id].push_back(u);
                }else if(Dis[x.id]==Dis[u]+x.d){
                    pre[x.id].push_back(u);
                }
            }
        }
    }

}
vector<int> path, tempPath;
int minCost = INF;
void DFS(int C1, int C2){   // 深度搜索
    //int u = C2;
    if(C2==C1){
        tempPath.push_back(C2);
        int ccc = 0; // Cost of this road;
        for(int i=tempPath.size()-1; i>0; i--){
            int i1 = tempPath[i];
            int i2 = tempPath[i-1];
            int jcost;
            for(int j=0; j<G[i1].size(); j++){ // 找cost
                if(G[i1][j].id == i2){
                    jcost = G[i1][j].c;
                    break;
                }
            }
            ccc += jcost;
        }
        if(ccc<minCost){
            minCost = ccc;
            path = tempPath;
        }
        tempPath.pop_back();
        return;
    }
    tempPath.push_back(C2);
    for(int i=0; i<pre[C2].size(); i++){
        DFS(C1, pre[C2][i]);
    }
    tempPath.pop_back();
}

int main(){
    int N, M, S, D; // N总城市数，M道路数量，S起点，D目标点
    scanf("%d%d%d%d", &N, &M, &S, &D);
    for(int i=0; i<M; i++){
        int c1, c2, distance, cost;
        scanf("%d%d%d%d", &c1, &c2, &distance, &cost);
        Node newnode;
        newnode.id = c2;
        newnode.c = cost;
        newnode.d = distance;
        G[c1].push_back(newnode);
        newnode.id = c1;
        G[c2].push_back(newnode);
    }
    fill(Dis, Dis+MAXN, INF);
    Dis[S] = 0;
    travel(S, D, N);
    DFS(S, D);
    for(int i=path.size()-1; i>=0; i--){
        printf("%d ", path[i]);
    }
    printf("%d ", Dis[D]);
    printf("%d", minCost);
    system("pause");
    return 0;
}
