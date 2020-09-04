#include <iostream>
#include <vector>

#define INFINITY 65536
#define MaxVertexNum 500

using namespace std;

typedef int Vertex;
typedef struct Node WeightType;
struct Node{
    int Distance, Price;
};

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

MGraph CreatEmptyMGraph( int VertexNum );
void InsertMGraph( MGraph Graph, Edge E );
void Dijkstra( MGraph Graph, Vertex S);

// vector<vector<int>> Distance( MaxVertexNum, vector<int>( MaxVertexNum, INFINITY ) );
// vector<vector<int>> Price( MaxVertexNum, vector<int>( MaxVertexNum, INFINITY ) );
// vector<bool> isVisited( MaxVertexNum, false );

vector<Node> Cost( MaxVertexNum );
vector<bool> isCollected( MaxVertexNum, false );
int main( int argc, const char *argv[] ){

    int N, M, S, D;
    cin >> N >> M >> S >> D;
    getchar();
    MGraph Graph = CreatEmptyMGraph( N );
    Graph->Ne = M;

    Edge E = new ENode;
    for( int i = 0; i < M ; i++ ){
        scanf( "%d %d %d %d", &( E->V1 ), &( E->V2 ), &( E->Weight.Distance ), &( E->Weight.Price ) );
        InsertMGraph( Graph, E );
    }
    Dijkstra( Graph, S );
    cout << Cost[D].Distance << ' ' << Cost[D].Price << endl;

    return 0;
}

Vertex FindMinCost( MGraph Graph ){
    Vertex MinV;
    Node MinCost;
    MinCost.Distance = MinCost.Price = INFINITY;

    for( Vertex V = 0; V < Graph->Nv; V++ ){
        if( !isCollected[V] ){
            if( ( Cost[V].Distance < MinCost.Distance) ||
                ( Cost[V].Distance == MinCost.Distance && Cost[V].Price < MinCost.Price ) ){
                MinCost = Cost[V];
                MinV = V;
            }
        }
    }
    if( MinCost.Distance == INFINITY ) return -1;
    else return MinV;
}

void Dijkstra( MGraph Graph, Vertex S){

    Vertex V, W;
    for( W = 0; W < Graph->Nv; W++ ){
        Cost[W] = Graph->G[S][W];
    }
        
    isCollected[S] = true;

    while( 1 ){
        V = FindMinCost( Graph );
        if( V == -1 ) break;
        isCollected[V] = true;
        for( W = 0; W < Graph->Nv; W++ ){
            if( Graph->G[V][W].Distance != INFINITY && !isCollected[W] ){
                if( (Cost[V].Distance + Graph->G[V][W].Distance < Cost[W].Distance) ||
                    ( Cost[V].Distance + Graph->G[V][W].Distance == Cost[W].Distance &&
                     Cost[V].Price + Graph->G[V][W].Price < Cost[W].Price ) ){
                        Cost[W].Distance = Cost[V].Distance + Graph->G[V][W].Distance;
                        Cost[W].Price = Cost[V].Price + Graph->G[V][W].Price;                    
                }
            }
        }
    }
        
}

MGraph CreatEmptyMGraph( int VertexNum ){
    MGraph Graph = new GNode;
    Graph->Ne = 0;
    Graph->Nv = VertexNum;

    for( Vertex V = 0; V < VertexNum; V++ )
        for( Vertex W = 0; W < VertexNum; W++ ){
            Graph->G[V][W].Distance = INFINITY;
            Graph->G[V][W].Price = INFINITY;
        }
            
    
    return Graph;
}

void InsertMGraph( MGraph Graph, Edge E ){
    Graph->G[ E->V1 ][ E->V2 ] = E->Weight;
    Graph->G[ E->V2 ][ E->V1 ] = E->Weight;
}
