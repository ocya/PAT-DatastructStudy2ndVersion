#include <iostream>
#include <vector>
#include <cmath>

#define MaxVertexNum 101
#define Boundary 50

using namespace std;

typedef int Vertex;

struct Position{
    int X, Y;
};

typedef struct ENode *Edge;
struct ENode{
    Vertex V1, V2;
};

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
    Vertex AdjV;
    PtrToAdjVNode Next;
    Position Pos;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge = nullptr;
    Position Pos;
}AdjList[MaxVertexNum];

typedef struct GNode *LGraph;
struct GNode{
    int Nv, Ne;
    int JumpDistance;
    AdjList G;
};

bool isFisrtJump( LGraph Graph, Vertex S);
bool DFS( LGraph Graph, Vertex S );
LGraph BuildLGraph();
vector<bool> isVisited( MaxVertexNum, false );
int main( int argc, const char *argv[] ){

    LGraph Graph = BuildLGraph();
    Vertex V;
    for( V = 0; V < Graph->Nv; V++ ){
        if( isFisrtJump( Graph, V ) ){
            if( DFS( Graph, V ) ){
                cout << "Yes";
                break;
            } 
        }
    }
    if( V == Graph->Nv ) cout << "No";
    return 0;
}


bool isFisrtJump( LGraph Graph, Vertex S){
    int Distance;
    int X, Y;
    X = Graph->G[S].Pos.X; Y = Graph->G[S].Pos.Y;
    Distance = pow( X, 2 ) + pow( Y,2 );
    if( pow((Graph->JumpDistance + 7.5), 2 ) >=  Distance ) return true;
    else return false;
    
}

bool isSafe( LGraph Graph, Vertex V ){
    int Distance;
    int X, Y;
    X = abs(Graph->G[V].Pos.X); Y = abs(Graph->G[V].Pos.Y);
    if( X + Graph->JumpDistance >= Boundary || Y + Graph->JumpDistance >= Boundary ) return true;
    else return false;

}

bool DFS( LGraph Graph, Vertex S ){

    isVisited[S] = true;
    if( isSafe( Graph, S ) ) return true;
    
    for( PtrToAdjVNode W = Graph->G[S].FirstEdge; W ; W = W->Next ){
        if( !isVisited[W->AdjV] )
            return DFS( Graph, W->AdjV );
    }
    return false;
}

void InsertLGraph( LGraph Graph, Edge E ){
    PtrToAdjVNode NewNode;
    NewNode = new AdjVNode;
    NewNode->AdjV = E->V2;
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;

    NewNode = new AdjVNode;
    NewNode->AdjV = E->V1;
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildLGraph(){
    int N, M;
    cin >> N >> M;

    LGraph Graph = new  GNode;
    Graph->Nv = N;
    Graph->JumpDistance = M;

    for( int i = 0; i < N; i++ )
        cin >> Graph->G[i].Pos.X >> Graph->G[i].Pos.Y;
    
    int Distance;
    Edge E = new ENode;
    int X1, X2, Y1, Y2;
    for( int i = 0; i < N; i++ ){
        X1 = Graph->G[i].Pos.X; Y1 = Graph->G[i].Pos.Y;
        for( int j = i + 1; j < N; j++ ){
            X2 = Graph->G[j].Pos.X; Y2 = Graph->G[j].Pos.Y;
            Distance = pow( (X1 - X2), 2) + pow( (Y1 - Y2), 2 );
            if( Distance <= M * M ){
                E->V1 = i;
                E->V2 = j;
                InsertLGraph( Graph, E );
            }        
        }
    }

    return Graph;
}
