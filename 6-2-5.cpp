#include <iostream>
#include <vector>
#include <stack>

#define MaxVertexNum 500
#define Infinity 65536

using namespace std;

typedef int Vertex;
typedef int WeightType;
typedef int DataType;

typedef struct ENode *Edge;
struct ENode{
    Vertex V1, V2;
    WeightType Weight;
};

typedef struct GNode *MGraph;
struct GNode{
    int Nv, Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
    DataType Value[MaxVertexNum];
};

MGraph BuildMGraph();
Vertex S, D;
vector<bool> isCollected( MaxVertexNum, false );
vector<WeightType> Distance( MaxVertexNum, Infinity );
vector<Vertex> Path( MaxVertexNum, -1 );
vector<int> Count( MaxVertexNum, 0 );
vector<DataType> Team( MaxVertexNum, 0 );
void Dijkstra( MGraph Graph, Vertex S );
int main( int argc, const char *argv[] ){
    
    MGraph Graph = BuildMGraph();
    Dijkstra( Graph, S );
    cout << Count[D] << ' ' << Team[D] << endl;

    cout << S;
    stack<Vertex> Ans;
    for( Vertex V = D; V != S; V = Path[V] )
        Ans.push( V );

    while( !Ans.empty() ){
        cout << ' ' << Ans.top(); 
        Ans.pop();
    }

    return 0;
}

Vertex FindMinDistVertex( MGraph Graph ){
    Vertex V, MinV;
    WeightType MinDist = Infinity;

    for( V = 0; V < Graph->Nv; V++ ){
        if( !isCollected[V] && Distance[V] < MinDist ){
            MinDist = Distance[V];
            MinV = V;
        }
    }
    if( MinDist == Infinity ) MinV = -1;
    return MinV;
}

void Dijkstra( MGraph Graph, Vertex S ){
    
    Vertex V, W;
    Team[S] = Graph->Value[S];
    for( V = 0; V < Graph->Nv; V++ ){
        Distance[V] = Graph->G[S][V];
        if( Distance[V] != Infinity ){
            Path[V] = S;
            Team[V] = Team[S] + Graph->Value[V];
            Count[V] = 1;
        }
            
    }
    Count[S] = 1;
    Distance[S] = 0;
    isCollected[S] = true;

    while( 1 ){
        V = FindMinDistVertex( Graph );
        if( V == -1 ) break;

        isCollected[V] = true;

        for( W = 0; W < Graph->Nv; W++ ){
            if( !isCollected[W] && Graph->G[V][W] != Infinity ){
                if( Distance[W] > Distance[V] + Graph->G[V][W] ){
                    Distance[W] = Distance[V] + Graph->G[V][W];
                    Path[W] = V;
                    Count[W] = Count[V];
                    Team[W] = Team[V] + Graph->Value[W];
                }else if( Distance[W] == Distance[V] + Graph->G[V][W] ){
                    Count[W] += Count[V];
                    if( Team[W] < Team[V] + Graph->Value[W]){
                        Team[W] = Team[V] + Graph->Value[W];
                        Path[W] = V;
                        Count[W] = Count[V] + 1;
                    } 
                }
            }
        }
    }


}

MGraph CreatEmptyMGraph( int VertexNum ){
    MGraph Graph = new GNode;
    Graph->Ne = 0;
    Graph->Nv = VertexNum;
    for( Vertex V = 0; V < VertexNum; V++ ){
        Graph->Value[V] = 0;
        for( Vertex W = 0;  W < VertexNum; W++ )
            Graph->G[V][W] = Infinity;
    } 

    return Graph;  
}

void InsertMGraph( MGraph Graph, Edge E ){
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildMGraph(){
    int N, M;
    cin >> N >> M >> S >> D;
    MGraph Graph = CreatEmptyMGraph( N );

    
    for( int i = 0; i < N; i++ )
        cin >> Graph->Value[i];
    
    Edge E = new ENode;
    for( int i = 0; i < M; i++ ){
        cin >> E->V1 >> E->V2 >> E->Weight;
        InsertMGraph( Graph, E );
    }

    return Graph;
}
