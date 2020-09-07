#include <iostream>
#include <vector>
#include <queue>


#define MaxVertexNum 10001
#define Infinity 65536

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

bool isConnected( MGraph Graph );
MGraph BuildMGraph();
double Calculate( MGraph Graph, Vertex V );
void Floyd( MGraph Graph );

WeightType Distance[MaxVertexNum][MaxVertexNum];
vector<bool> isVisited( MaxVertexNum, false );
int main( int argc, const char *argv[] ){

    MGraph Graph = BuildMGraph();
    Floyd( Graph );
    bool Flag = isConnected( Graph );


    int K;
    cin >> K;
    Vertex V;
    for( int i = 0; i < K; i++ ){
        cin >> V;
        if( Flag )
            printf( "Cc(%d)=%.2f\n", V, Calculate( Graph, V-1 ));
        else
            printf( "Cc(%d)=0.00\n", V );
        
    }

    return 0;
}

void DFS( MGraph Graph, Vertex S ){
    isVisited[S] = true;
    for( Vertex W = 0; W < Graph->Nv; W++ ){
        if( !isVisited[W] && Graph->G[S][W] != Infinity )
            DFS( Graph, W );
    }
}

bool isConnected( MGraph Graph ){
    DFS( Graph, 0 );
    for( int i = 0; i < Graph->Nv; i++ )
        if( !isVisited[i] ) return false;
    return true;
}

double Calculate( MGraph Graph, Vertex V ){
    Vertex W;
    double Sum = 0;
    for( W = 0; W < Graph->Nv; W++ ){
        if( W != V ){
            Sum += Distance[V][W];
        }
    }

    return (Graph->Nv - 1)/Sum;
}

void Floyd( MGraph Graph ){
    Vertex V, W, K;
    for( V = 0;  V < Graph->Nv; V++ )
        for( W = 0; W < Graph->Nv; W++ ){
            Distance[V][W] = Graph->G[V][W];
        }
    
    for( K = 0; K < Graph->Nv; K++ )
        for( V = 0;  V < Graph->Nv; V++ )
            for( W = 0; W < Graph->Nv; W++ ){
                if( Distance[V][W] > Distance[V][K] + Distance[K][W] )
                    Distance[V][W] = Distance[V][K] + Distance[K][W];
            }
}

MGraph BuildMGraph(){
    int N, M;
    cin >> N >> M;
    MGraph Graph = new GNode;
    Graph->Nv = N;
    Graph->Ne = M;

    for( Vertex V = 0; V < Graph->Nv; V++ )
        for( Vertex W = 0; W < Graph->Nv; W++ )
            Graph->G[V][W] = Infinity;
    Edge E = new ENode;
    for( int i = 0; i < M; i++ ){
        cin >> E->V1 >> E->V2;
        E->V1 -= 1;
        E->V2 -= 1;
        Graph->G[ E->V1 ][ E->V2 ] = 1;
        Graph->G[ E->V2 ][ E->V1 ] = 1;
    }

    return Graph;
}
