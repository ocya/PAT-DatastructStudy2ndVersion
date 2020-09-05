#include <iostream>
#include <vector>


#define MaxVertexNum 101
#define INFINITY 65536

using namespace std;

typedef int Vertex;
typedef int WeightType;

typedef struct ENode *Edge;
struct ENode{
    Vertex V1, V2;
    WeightType Weight;
};

typedef struct GNode *MGraph;
struct GNode{
    int Nv, Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
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

typedef struct LGNode *LGraph;
struct LGNode{
    int Nv, Ne;
    AdjList G;
};

MGraph BuildMGraph();
int Prim( MGraph Graph, LGraph MST );
int main( int argc, const char *argv[] ){

    MGraph Graph = BuildMGraph();
    LGraph MST;
    WeightType TotalWeight = Prim( Graph, MST );
    cout << TotalWeight;


    return 0;
}

Vertex FindMinDistVertex( MGraph Graph, WeightType Distance[] ){
    WeightType MinDist = INFINITY;
    Vertex MinV;
    
    for( Vertex V = 0; V < Graph->Nv; V++ ){
        if( Distance[V] != 0 && Distance[V] < MinDist ){
            MinDist = Distance[V];
            MinV = V;
        }
    }
    if( MinDist == INFINITY ) MinV = -1;
    return MinV;
}

void InsertLGraph( LGraph MST, Edge E ){
    PtrToAdjVNode NewNode = new AdjVNode;
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    NewNode->Next = MST->G[E->V1].FirstEdge;
    MST->G[E->V1].FirstEdge = NewNode;
    
}

LGraph CreatEmptyLGraph( int VertexNum ){

    LGraph Graph = new LGNode;
    Graph->Ne = 0;
    Graph->Nv = VertexNum;

    return Graph;
}

int Prim( MGraph Graph, LGraph MST ){
    WeightType Distance[MaxVertexNum];
    Vertex Parent[MaxVertexNum];
    Vertex V, W, TotalWeight, VCount;

    for( V = 0; V < Graph->Nv; V++ ){
        Distance[V] = Graph->G[0][V];
        Parent[V] = 0;
    }
    Distance[0] = 0;
    Parent[0] = -1;
    VCount = 1;

    MST = CreatEmptyLGraph( Graph->Nv );
    TotalWeight = 0;
    Edge E = new ENode;
    while( 1 ){
        V = FindMinDistVertex( Graph, Distance );
        if( V == -1 ) break;

        E->V1 = Parent[V];
        E->V2 = V;
        E->Weight = Distance[V];
        InsertLGraph( MST, E );

        TotalWeight += Distance[V];
        Distance[V] = 0;
        VCount++;

        for( W = 0; W < Graph->Nv; W++ ){
            if( Distance[W] != 0 && Graph->G[V][W] != INFINITY ){
                if( Graph->G[V][W] < Distance[W] ){
                    Distance[W] = Graph->G[V][W];
                    Parent[W] = V;
                }
            }
        }
    }
    if( VCount != Graph->Nv )
        TotalWeight = -1;
    return TotalWeight;
    
}

MGraph CreatEmptyMGraph( int VertexNum ){
    MGraph Graph = new GNode;
    Graph->Ne = 0;
    Graph->Nv = VertexNum;

    Vertex V, W;
    for( V = 0;  V < Graph->Nv; V++ )
        for( W = 0; W < Graph->Nv; W++ )
            Graph->G[V][W] = INFINITY;
    
    return Graph;
}

void InsertMGraph( MGraph Graph, Edge E ){
    Graph->G[ E->V1 ][ E->V2 ] = E->Weight;
    Graph->G[ E->V2 ][ E->V1 ] = E->Weight;
}

MGraph BuildMGraph(){
    int N, M;
    cin >> N >> M;
    getchar();
    MGraph Graph = CreatEmptyMGraph( N );
    
    Edge E = new ENode;
    for( int i = 0; i < M; i++ ){
        scanf( "%d %d %d", &( E->V1 ), &( E->V2 ), &( E->Weight ));
        E->V1 -= 1;
        E->V2 -= 1;
        InsertMGraph( Graph, E );
    }
    return Graph;
}
