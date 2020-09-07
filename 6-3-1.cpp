#include <iostream>
#include <vector>
#include <queue>


#define MaxVertexNum 501
#define Infinity 65536

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

int FindConnectedSetCount( MGraph Graph );
MGraph BuildMGraph();
void DeleteMGraph( MGraph Graph, Vertex V );
vector<bool> isVisited( MaxVertexNum, false );
vector<bool> isDeleted( MaxVertexNum, false );
int main( int argc, const char *argv[] ){

    MGraph Graph = BuildMGraph();
    int K;
    cin >> K;
    Vertex CityNumber;
    int OldCount, NewCount;
    OldCount = FindConnectedSetCount( Graph );

    for( int i = 0; i < K; i++ ){
        cin >> CityNumber;
        DeleteMGraph( Graph, CityNumber );
        isVisited.assign( MaxVertexNum, false );
        NewCount = FindConnectedSetCount( Graph );
        
        if( NewCount <= OldCount ) 
            cout << "City " << CityNumber << " is lost." << endl;
        else 
            cout << "Red Alert: City " << CityNumber << " is lost!" << endl;
        OldCount = NewCount;
        
    }
    if( K == Graph->Nv ) cout << "Game Over." << endl;

    return 0;
}



void DFS( MGraph Graph, Vertex S ){
    
    isVisited[S] = true;

    for( Vertex W = 0; W < Graph->Nv; W++ ){
        if( Graph->G[S][W] != Infinity && !isVisited[W] ){
            DFS( Graph, W );
        }
    }
}

int FindConnectedSetCount( MGraph Graph ){
    int Count = 0;
    for( Vertex V = 0; V < Graph->Nv; V++ ){
        if( !isDeleted[V] && !isVisited[V] ){
            DFS( Graph, V );
            Count++;
        }
    }

    return Count;
}

void DeleteMGraph( MGraph Graph, Vertex V ){
    isDeleted[V]= true; 
    for( Vertex W = 0; W < Graph->Nv; W++ ){
        Graph->G[V][W] = Graph->G[W][V] = Infinity;
    }
}

void InsertMGraph( MGraph Graph, Edge E ){
    Graph->G[ E->V1 ][ E->V2 ] = E->Weight;
    Graph->G[ E->V2 ][ E->V1 ] = E->Weight;
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
        E->Weight = 1;
        InsertMGraph( Graph, E );
    }

    return Graph;
}
