#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAXN = 1100;

vector<int> G[MAXN];
int inDegree[MAXN] = {0};
int tempInd[MAXN];
bool isTopologicalOrder(vector<int> query){
    for(int i=0; i<query.size(); i++){
        int u = query[i];
        if(tempInd[u] != 0){
            return false;
        }
        for(int j=0; j<G[u].size(); j++){ //u所有邻接点的入度减一
            tempInd[G[u][j]]--;
        }
    }
    return true;
}

int main(){
    int N, M; //N: 顶点数； M: 有向边数
    scanf("%d%d", &N, &M);
    for(int i=0; i<M; i++){
        int i1, i2; // 有向边i1->i2录入图G中 
        scanf("%d%d", &i1, &i2);
        G[i1].push_back(i2);
        inDegree[i2]++;
    }
    int K;
    scanf("%d", &K);
    vector<vector<int>> query(K); // 储存查询的二维数组,K行N列
    for(int i=0; i<K; i++){
        for(int j=0; j<N; j++){
            int jj;
            scanf("%d", &jj);
            query[i].push_back(jj);
        }
    }
    int num = 0; // 累计有多少个不是拓扑排序的查询？
    for(int i=0; i<K; i++){
        memcpy(tempInd, inDegree, sizeof(inDegree));
        if(!isTopologicalOrder(query[i])){
            if(num==0){ // 第一个答案不输出空格
                printf("%d", i);
            }else{
                printf(" %d", i);
            }
            num++;
        }
    }
    
    system("pause");
    return 0;
}
