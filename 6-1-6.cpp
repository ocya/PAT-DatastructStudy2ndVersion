#include <iostream>
#include <vector>


#define MaxVertexNum 101
#define INFINITY 65536

typedef int Vertex;
typedef int WeightType;

using namespace std;

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

MGraph BuildMGraph();
void Floyd( MGraph Graph );
vector< vector<WeightType> > Distance( MaxVertexNum, vector<WeightType>( MaxVertexNum, INFINITY ));

int main( int argc, const char *argv[] ){

    MGraph Graph = BuildMGraph();
    Floyd( Graph );
    Vertex V, W;
    WeightType MaxWeight;
    WeightType MinWeight = INFINITY;
    Vertex S;
    for( V = 0; V < Graph->Nv; V++ ){
        MaxWeight = 0;
        for( W = 0; W < Graph->Nv; W++ ){
            if( MaxWeight < Distance[V][W] && V != W ){
                MaxWeight = Distance[V][W];
            }
        }
        if( MaxWeight == INFINITY ){
            cout << 0;
            return 0;
        }
        if( MaxWeight < MinWeight ){
            MinWeight = MaxWeight;
            S = V;
        }
    }

    cout << S+1 << ' ' << MinWeight;
    return 0;
}

void Floyd( MGraph Graph ){
    Vertex V, W, K;

    for( V = 0; V < Graph->Nv; V++ )
        for( W = 0; W < Graph->Nv; W++ )
            Distance[V][W] = Graph->G[V][W];
        

    for( K = 0; K < Graph->Nv; K++ )
        for( V = 0; V < Graph->Nv; V++ )
            for( W = 0; W < Graph->Nv; W++ ){
                if( Distance[V][W] > Distance[V][K] + Distance[K][W] )
                    Distance[V][W] = Distance[V][K] + Distance[K][W];
            }
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
