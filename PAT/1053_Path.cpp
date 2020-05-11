#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

static const int MAXN = 50;
struct node{
    int weight;
    vector<int> child;
}Node[MAXN];

bool cmp(int a, int b){
    return Node[a].weight > Node[b].weight;
}

int path[MAXN];
int n, m, s; // number of nodes, number of non-leaf nodes, sum;

void DFS(int index, int numNode, int sum){ 
    path[numNode] = index;
    sum += Node[index].weight;

    if(sum>s) return;
    if(sum==s){
        if(Node[index].child.empty()){
            for(int j=0; j<=numNode; j++){
                printf("%d", Node[path[j]].weight);
                if(j<numNode) printf(" ");
            }
            printf("\n");
        }
        return; //what if without this return ????
    }
    for(int i=0; i<Node[index].child.size(); i++){
        DFS(Node[index].child[i], numNode+1, sum);
    }
}

int main(){
    scanf("%d%d%d", &n,&m,&s);
    for(int i=0; i<n; i++){
        scanf("%d", &Node[i].weight);
    }
    int p, k, l;
    for(int i=0; i<m; i++){
        scanf("%d%d", &p, &k);
        for(int j=0; j<k; j++){
            scanf("%d", &l);
            Node[p].child.push_back(l);
        }
        sort(Node[p].child.begin(), Node[p].child.end(), cmp);
    }
    DFS(0, 0, 0);

    system("pause");
    return 0;
}
