#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

struct node{
    int data;
    node* lc;
    node* rc;
};
node* newNode(int x){
    node* newn = new node;
    newn->data = x;
    newn->lc = newn->rc = NULL;
    return newn;
}

void insert(node* &root, int x){
    if(root==NULL){
        root = newNode(x);
        return;
    }
    if(root->data<=x){
        insert(root->rc, x);
    }else{
        insert(root->lc, x);
    }
}

void preOrder(node* root, vector<int> &preo){
    if(root==NULL) return;
    preo.push_back(root->data);
    preOrder(root->lc, preo);
    preOrder(root->rc, preo);
}
void preOrderMirror(node* root, vector<int> &preom){
    if(root==NULL) return;
    preom.push_back(root->data);
    preOrderMirror(root->rc, preom);
    preOrderMirror(root->lc, preom);
}
void postOrder(node* root, vector<int> &posto){
    if(root==NULL) return;
    postOrder(root->lc, posto);
    postOrder(root->rc, posto);
    posto.push_back(root->data);
}
void postOrderMirror(node* root, vector<int> &postom){
    if(root==NULL) return;
    postOrderMirror(root->rc, postom);
    postOrderMirror(root->lc, postom);
    postom.push_back(root->data);
}

int N;
node* root = NULL;
vector<int> preo, preom, posto, postom;
vector<int> input;

int main(){
    scanf("%d", &N);
    int temp;
    for(int i=0; i<N; i++){
        scanf("%d", &temp);
        input.push_back(temp);
        insert(root, temp);
    }
    preOrder(root, preo);
    preOrderMirror(root, preom);
    if(input==preo){
        postOrder(root, posto);
        printf("YES\n");
        for(int i=0; i<N; i++){
            printf("%d", posto[i]);
            if(i!=(N-1)) printf(" ");
        }

    }else if(input==preom){
        postOrderMirror(root, postom);
        printf("YES\n");
        for(int i=0; i<N; i++){
            printf("%d", postom[i]);
            if(i!=(N-1)) printf(" ");
        }
    }else{
        printf("NO\n");
    }

    system("pause");
    return 0;
}
