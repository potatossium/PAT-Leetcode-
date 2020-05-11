#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

struct Node{
    int id;
    int layer;
};

vector<Node> Adj[1010];
bool inq[1010] = {false};

int BFS(int u, int L){
    int numForward = 0;
    queue<Node> q;
    inq[u] = true;
    Node first;
    first.id = u;
    first.layer = 0;
    q.push(first);
    while(!q.empty()){
        Node topNode = q.front();
        q.pop();
        int uu = topNode.id;
        for(int i=0; i<Adj[uu].size(); i++){
            Adj[uu][i].layer = topNode.layer + 1;
            if(!inq[Adj[uu][i].id] && Adj[uu][i].layer<=L){
                inq[Adj[uu][i].id] = true;
                q.push(Adj[uu][i]);
                numForward++;
            }
        }
    }
    return numForward;
}

int main(){
    int N, L; //N: user number, L: level number
    scanf("%d%d", &N, &L);

    int numFollow, idFollow;
    Node user;
    for(int i=1; i<=N; i++){
        user.id = i;
        scanf("%d", &numFollow);
        for(int j=0; j<numFollow; j++){
            scanf("%d", &idFollow);
            Adj[idFollow].push_back(user);
        }
    }

    int K, queryId; // K: number of query
    scanf("%d", &K);
    for(int i=0; i<K; i++){
        memset(&inq, false, sizeof(inq));
        scanf("%d", &queryId);
        printf("%d\n", BFS(queryId, L));
    }
    return 0;
}
