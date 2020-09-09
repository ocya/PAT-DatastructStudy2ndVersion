#include <iostream>
#include <vector>
#include <queue>
#include <stack>

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
    WeightType Earliest = 0, Latest = Infinity;
}AdjList[MaxVertexNum];

typedef struct GNode *LGraph;
struct GNode{
    int Nv, Ne;
    AdjList G;
};

LGraph BuildLGraph();
WeightType TopSort( LGraph Graph);

int main( int argc, const char *argv[] ){

    LGraph Graph = BuildLGraph();
    WeightType EarliestFinishTime = TopSort( Graph );
    if( EarliestFinishTime == -1 ) cout << 0;
    else{
        cout << EarliestFinishTime << endl; 
        Vertex V; PtrToAdjVNode W;
        for( V = 0; V < Graph->Nv; V++ )
            for( W = Graph->G[V].FirstEdge; W; W = W->Next )
                if(  Graph->G[W->AdjV].Latest - Graph->G[V].Earliest - W->Weight == 0 )
                    cout << V + 1 << "->" << W->AdjV + 1 << endl;   
    }

    return 0;
}



WeightType TopSort( LGraph Graph){
    stack<Vertex> TopOrder;
    vector<int> InDegree( Graph->Nv, 0 );
    Vertex V; PtrToAdjVNode W;
    for( V = 0; V < Graph->Nv; V++ )
        for( W = Graph->G[V].FirstEdge; W; W = W->Next )
            InDegree[ W->AdjV ]++;

    queue<Vertex> Q;
    for( V = 0; V < Graph->Nv; V++ )
        if( InDegree[V] == 0 )
            Q.push( V );

    WeightType EarliestFinishTime = 0;
    Vertex TheLastVertex;
    while( !Q.empty() ){
        V = Q.front(); Q.pop();
        TopOrder.push( V );
        for( W = Graph->G[V].FirstEdge; W; W = W->Next ){
            if( Graph->G[W->AdjV].Earliest < Graph->G[V].Earliest + W->Weight ){
                Graph->G[W->AdjV].Earliest = Graph->G[V].Earliest + W->Weight;
                if( EarliestFinishTime < Graph->G[W->AdjV].Earliest ){
                    EarliestFinishTime = Graph->G[W->AdjV].Earliest;
                    TheLastVertex = W->AdjV;
                } 
            }
            if( --InDegree[ W->AdjV ] == 0 ){
                Q.push( W->AdjV );
            }
        }
    }
    if( TopOrder.size() != Graph->Nv ) return -1;

    Graph->G[TheLastVertex].Latest = EarliestFinishTime;

    while( !TopOrder.empty() ){
        V = TopOrder.top(); TopOrder.pop(); 
        for( W = Graph->G[V].FirstEdge; W; W = W->Next ){
            if( Graph->G[V].Latest > Graph->G[W->AdjV].Latest - W->Weight )
                Graph->G[V].Latest = Graph->G[W->AdjV].Latest - W->Weight;
        }
    }

    return EarliestFinishTime;
}

void InsertLGraph( LGraph Graph, Edge E ){
    PtrToAdjVNode NewNode = new AdjVNode;
    NewNode->Weight = E->Weight;
    NewNode->AdjV = E->V2;
    NewNode->Next = Graph->G[ E->V1 ].FirstEdge;
    Graph->G[ E->V1 ].FirstEdge = NewNode;
}

LGraph BuildLGraph(){
    int N, M;
    cin >> N >> M;
    LGraph Graph = new GNode;
    Graph->Ne = M; Graph->Nv = N;
    Vertex V;
    Edge E = new ENode;
    for( int i = 0; i < M; i++ ){
        cin >> E->V1 >> E->V2 >> E->Weight;
        E->V1 -= 1; E->V2 -= 1;
        InsertLGraph( Graph, E );
    }

    return Graph;
}




/*
9 11
1 2 6
1 3 4
1 4 5
2 5 1
3 5 1
4 6 2
5 7 9
5 8 7
6 8 4
7 9 2
8 9 4

11 14
1 2 4
1 3 3
2 4 5
3 4 3
4 5 1
4 6 6
5 7 5
6 7 2
8 3 7
9 3 7
9 10 6
4 10 2
10 6 5
6 11 4


*/
