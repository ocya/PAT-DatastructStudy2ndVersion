#include <iostream>
#include <stack>
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

vector<bool> isVisited( MaxVertexNum, false );
stack<int> VisitOrder;

void NonRecursionDFS( MGraph Graph, Vertex V );
void DFS( MGraph Graph, Vertex V );
void InsertMGraph( MGraph Graph, Edge E );
MGraph CreatEmptyMGraph( int VertexNum );
int main( int argc, const char *argv[] ){

    int N, M, S;
    cin >> N >> M >> S;
    MGraph Graph = CreatEmptyMGraph( N );
    Graph->Ne = M;

    Edge E = new ENode;
    for( int i = 0 ; i < M ; i++ ){
        scanf( "%d %d", &(E->V1), &(E->V2) );
        InsertMGraph( Graph, E );
    }
    NonRecursionDFS( Graph, S );
    for( int i = 1 ; i <= Graph->Nv ; i++ ){
        if( !isVisited[i] ){
            cout << " 0";
            break;
        }
    }
    // DFS( Graph, S );
    // int Count = VisitOrder.size();
    // VisitOrder.pop();
    // for( int i = 0 ; i < Count - 1; i++ ){
    //     if( i != 0 ) printf( " " );
    //     printf( "%d", VisitOrder.top() );
    //     VisitOrder.pop();
    // }
    // if( Count != Graph->Nv ) cout << " 0";
    


    return 0;
}

void NonRecursionDFS( MGraph Graph, Vertex V ){
    stack<Vertex> Path;
    isVisited[V] = true;
    Path.push( V );
    cout << V;
    while( !Path.empty() ){
        V = Path.top();
        Vertex W;
        for( W = 1; W <= Graph->Nv; W++ ){
            if( Graph->G[V][W] != INFINITY && !isVisited[W] ){
                printf( " %d", W );
                isVisited[W] = true;
                Path.push( W );
                break;
            }
        }
        if( W == Graph->Nv + 1 ){
            Path.pop();
            if( !Path.empty() )
                printf( " %d", Path.top() );
        }

    }


}

void DFS( MGraph Graph, Vertex V ){

    isVisited[V] = true;
    printf( "%d ", V );
    VisitOrder.push( V );
    for( Vertex W = 1; W <= Graph->Nv; W++ ){
        if( Graph->G[V][W] != INFINITY && !isVisited[W] )
            DFS( Graph, W );
    }
}

void InsertMGraph( MGraph Graph, Edge E ){
    Graph->G[E->V1][E->V2] = 1;
    Graph->G[E->V2][E->V1] = 1;
}

MGraph CreatEmptyMGraph( int VertexNum ){
    MGraph Graph = new GNode;
    Graph->Ne = 0;
    Graph->Nv = VertexNum;

    for( Vertex V = 1; V <= VertexNum; V++ )
        for( Vertex W = 1; W <= VertexNum; W++ )
            Graph->G[V][W] = INFINITY;

    return Graph;
}

