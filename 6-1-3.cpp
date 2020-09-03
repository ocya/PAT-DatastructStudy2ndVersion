#include <iostream>
#include <vector>

#define MaxVertexNum 1001
#define INFINITY 65536

using namespace std;

typedef int Vertex;
typedef int WeightType;

typedef struct ENode *Edge;
struct ENode{
    Vertex V1, V2;
};

typedef struct GNode *MGraph;
struct GNode{
    int Nv, Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
};

MGraph BuildMGraph();
MGraph CreatEmptyMGraph( int VertexNum );
void InsertMGraph( MGraph Graph, Edge E );
void DFS( MGraph Graph, Vertex V );
bool ConnectedCheck( MGraph Graph );
bool DegreeCheck( MGraph Graph );

vector<bool> isVisited( MaxVertexNum, false );

int main( int argc, const char *argv[] ){

    MGraph Graph = BuildMGraph();
    bool isConnected = ConnectedCheck( Graph );
    bool isOddDegree = DegreeCheck( Graph );
    if( isConnected && isOddDegree ) cout << 1;
    else cout << 0;
    return 0;
}

bool DegreeCheck( MGraph Graph ){
    Vertex V, W;
    int Degree;
    for( V = 1; V <= Graph->Nv; V++ ){
        Degree = 0;
        for( W = 1; W <= Graph->Nv; W++ ){
            if( Graph->G[V][W] != INFINITY )
                Degree++;
        }
        if( Degree % 2 != 0 ) return false;
    }
    return true;
}

bool ConnectedCheck( MGraph Graph ){
    DFS( Graph, 1 );
    for( int i = 1; i <= Graph->Nv; i++ ){
        if( isVisited[i] == false ) return false;
    } 
    return true;
}

void DFS( MGraph Graph, Vertex V ){
    isVisited[V] = true;
    for( Vertex W = 1 ; W <= Graph->Nv; W++ ){
        if( Graph->G[V][W] != INFINITY && isVisited[W] == false ){
            DFS( Graph, W );
        }
    }
}

MGraph BuildMGraph(){
    int N, M;
    cin >> N >> M;
    MGraph Graph = CreatEmptyMGraph( N );
    Graph->Ne = M;

    Edge E = new ENode;
    for( int i = 0 ; i < M ; i++ ){
        scanf( "%d %d", &(E->V1), &(E->V2) );
        InsertMGraph( Graph, E );
    }
    return Graph;
}

MGraph CreatEmptyMGraph( int VertexNum ){
    MGraph Graph = new GNode;
    Graph->Ne = 0;
    Graph->Nv = VertexNum;
    
    Vertex V, W;
    for( V = 1; V <= VertexNum;  V++ )
        for( W = 1; W <= VertexNum; W++ )
            Graph->G[V][W] = INFINITY;

    return Graph;
}

void InsertMGraph( MGraph Graph, Edge E ){
    Graph->G[E->V1][E->V2] = 1;
    Graph->G[E->V2][E->V1] = 1;
}
