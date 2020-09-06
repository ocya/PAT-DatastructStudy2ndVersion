#include <iostream>
#include <vector>
#include <map>

#define MaxVertexNum 201
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

MGraph BuildMGraph();
void CheckHamiltonianPath( MGraph Graph );
int main( int argc, const char *argv[] ){

    Vertex V;
    MGraph Graph = BuildMGraph();
    CheckHamiltonianPath( Graph );

    
    return 0;
}


bool isConnected( MGraph Graph, vector<Vertex> Path ){
    Vertex V, W;
    for( int i = 0; i < Path.size() - 1; i++ ){
        V = Path[i], W = Path[i+1];
        if( Graph->G[V][W] == INFINITY ) return false;
    }
    return true;
}

void CheckHamiltonianPath( MGraph Graph ){
    int K;
    cin >> K;
    int VCount;
    vector<Vertex> Path;
    vector<bool> isVisited, Temp;
    Temp.assign( Graph->Nv, true );
    for( int i = 0; i < K; i++ ){
        cin >> VCount;
        isVisited.assign( Graph->Nv, false );
        Path.resize( VCount );
        Vertex V;
        for( int j = 0; j < VCount; j++ ){
            cin >> V;
            Path[j] = V - 1;
            isVisited[ Path[j] ] = true;
        }    

        if( VCount != Graph->Nv + 1 || Path[0] != Path[VCount-1] || isVisited != Temp ) cout << "NO\n";
        else{
            if( isConnected( Graph, Path ) ) cout << "YES\n";
            else cout << "NO\n";
        }

    }
}

MGraph CreatEmptyMGraph( int VertexNum ){
    MGraph Graph = new GNode;
    Graph->Ne = 0;
    Graph->Nv = VertexNum;

    Vertex V, W;
    for( V = 0; V < VertexNum; V++ )
        for( W = 0; W < VertexNum; W++ )
            Graph->G[V][W] = INFINITY;

    return Graph;
}

void InsetMGraph( MGraph Graph, Edge E ){
    Graph->G[ E->V1 ][ E->V2 ] = E->Weight;
    Graph->G[ E->V2 ][ E->V1 ] = E->Weight;
}

MGraph BuildMGraph(){
    int N, M;
    cin >> N >> M;
    MGraph Graph = CreatEmptyMGraph( N );
    Graph->Ne = M;

    Edge E = new ENode;
    for( int i = 0; i < M; i++ ){
        cin >> E->V1 >> E->V2;
        E->V1 -= 1;
        E->V2 -= 1;
        E->Weight = 1;
        InsetMGraph( Graph, E );
    }

    return Graph;
}

