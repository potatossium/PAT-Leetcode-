#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>

using namespace std;

const int MAXN = 100;
const int INF = 1000000000;
int G[MAXN][MAXN] = {0};
int weight[MAXN] = {0}; // weight[AAA]点权
bool vis[MAXN] = {false};
int numPerson = 0;
int n, k;

map<int, string> intToString; // 1 TO AAA
map<string, int> stringToInt; // AAA to 1
map<string, int> gang; // AAA to numofGang

void DFS(int nowVisit, int &head, int &numMember, int &totalValue){
    if(weight[head]<weight[nowVisit]) head = nowVisit;
    numMember++;
    vis[nowVisit] = true;
    
    for(int i=0; i<numPerson; i++){
        if(G[nowVisit][i]>0){
            totalValue += G[nowVisit][i];
            G[nowVisit][i] = G[i][nowVisit] = 0;
            if(vis[i]==false){
                DFS(i, head, numMember, totalValue);
            }
        }
    }
    
}

void DFSTrave(){
    for(int i=0; i<numPerson; i++){
        if(vis[i]==false){
            int head = i, numMember = 0, totalValue = 0;
            DFS(i, head, numMember, totalValue);
            if(numMember>2 && totalValue>k){
                gang[intToString[head]] = numMember;
            }
        }
    }
}

int change(string str){
    if(stringToInt.find(str)!=stringToInt.end()){
        return stringToInt[str];
    }else{
        stringToInt[str] = numPerson;
        intToString[numPerson] = str;
        return(numPerson++);
    }
}

int main(){
    cin >> n >> k;
    
    for(int i=0; i<n; i++){
        int w;
        string str1, str2;
        cin >> str1 >> str2 >> w;
        int id1 = change(str1);
        int id2 = change(str2);
        G[id1][id2] += w;
        G[id2][id1] += w;
        weight[id1] += w;
        weight[id2] += w;
    }
    DFSTrave();
    cout << gang.size() << endl;
    map<string, int>::iterator it;
    for(it = gang.begin(); it != gang.end(); it++){
        cout << it->first << " " << it->second <<endl;
    }
    return 0;
}
