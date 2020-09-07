#include <iostream>
#include <vector>
#include <queue>


#define MaxVertexNum 101
#define Infinity 65536

using namespace std;

typedef int Vertex;
typedef int WeightType;

typedef struct ENode *Edge;
struct ENode{
    Vertex V1, V2;
    WeightType Weight;
};

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
    Vertex AdjV;
    WeightType Weight;
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge = nullptr;
}AdjList[MaxVertexNum];

typedef struct GNode *LGraph;
struct GNode{
    int Nv, Ne;
    AdjList G;
};

LGraph BuildGraph();
bool TopSort( LGraph Graph );

vector<WeightType> LatiestFinishTime( MaxVertexNum, 0 );
int main( int argc, const char *argv[] ){
    LGraph Graph = BuildGraph();

    if( TopSort( Graph ) ){
        WeightType TotalTime = 0;
        for( int i = 0; i < Graph->Nv; i++ )
            if( TotalTime < LatiestFinishTime[i] )
                TotalTime = LatiestFinishTime[i];
        cout << TotalTime;
             
    }else cout << "Impossible";

    return 0;
}

bool TopSort( LGraph Graph ){

    vector<int> InDegree( MaxVertexNum, 0 );
    Vertex V;
    PtrToAdjVNode W;
    queue<Vertex> Q;

    for( V = 0; V < Graph->Nv; V++ )
        for( W = Graph->G[V].FirstEdge; W ; W = W->Next )
            InDegree[W->AdjV] += 1;


    for( V = 0; V < Graph->Nv; V++ ){
        if( InDegree[V] == 0 )
            Q.push( V );
    }

    int Count = 0;
    while( !Q.empty() ){
        V = Q.front(); Q.pop();
        Count++;
        for( W = Graph->G[V].FirstEdge; W; W = W->Next ){
            if( LatiestFinishTime[W->AdjV] < LatiestFinishTime[V] + W->Weight )
                LatiestFinishTime[W->AdjV] = LatiestFinishTime[V] + W->Weight;
            if( --InDegree[W->AdjV] == 0 )
                Q.push( W->AdjV );
        }
    }

    if( Count == Graph->Nv ) return true;
    else return false;
}

void InsertLGraph( LGraph Graph, Edge E ){
    PtrToAdjVNode NewNode = new AdjVNode;
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
}

LGraph BuildGraph(){
    int N, M;
    cin >> N >> M;
    LGraph Graph = new GNode;
    Graph->Ne = M;
    Graph->Nv = N;

    Edge E = new ENode;
    for( int i = 0; i < M; i++ ){
        cin >> E->V1 >> E->V2 >> E->Weight;
        InsertLGraph( Graph, E );
    }

    return Graph;
}
