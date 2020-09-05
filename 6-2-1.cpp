#include <iostream>
#include <vector>
#include <stack>
#include <queue>

#define MaxVertexNum 11
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
void NonRecursionDFS( MGraph Graph, Vertex S );
void BFS( MGraph Graph, Vertex S );
vector<bool> isVisited( MaxVertexNum, false );
int main( int argc, const char *argv[] ){

    Vertex V;
    MGraph Graph = BuildMGraph();
    
    for( V = 0; V < Graph->Nv; V++ )
        NonRecursionDFS( Graph, V ); 
    isVisited.assign( MaxVertexNum, false );
    for( V = 0; V < Graph->Nv; V++ )
        BFS( Graph, V ); 
    
    return 0;
}

void BFS( MGraph Graph, Vertex S ){
    queue<Vertex> Q;
    if( !isVisited[S] ){
        isVisited[S] = true;
        Q.push( S );
        cout << "{ " << S;

        Vertex V, W;
        while( !Q.empty() ){
            V = Q.front(); Q.pop();
            for( W = 0; W < Graph->Nv; W++ ){
                if( !isVisited[W] && Graph->G[V][W] != INFINITY ){
                    isVisited[W] = true;
                    Q.push( W );
                    cout << ' ' << W;
                }
            }
        }
        cout << " }" << endl;
    }
}

void NonRecursionDFS( MGraph Graph, Vertex S ){
    stack<Vertex> St;
    if( !isVisited[S] ){
        isVisited[S] = true;
        St.push( S );
        cout << "{ " << S;

        Vertex V, W;
        while( !St.empty() ){
            V = St.top();
            for( W = 0; W < Graph->Nv; W++ ){
                if( !isVisited[W] && Graph->G[V][W] != INFINITY ){
                    isVisited[W] = true;
                    St.push( W );
                    cout << ' ' << W;
                    break;
                }
            }
            if( W == Graph->Nv )
                St.pop();
        }
        cout << " }" << endl;
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
        E->Weight = 1;
        InsetMGraph( Graph, E );
    }

    return Graph;
}

