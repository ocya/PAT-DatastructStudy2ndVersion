//有一个测试点未通过
#include <iostream>
#include <vector>
#include <cmath>
#include <stack>

#define Infinity 65536
#define MaxVertexNum 101
#define Diameter 15
#define Boundary 50

using namespace std;

typedef int Vertex;
typedef int WeightType;


struct Position{
    int X, Y;
};

typedef struct ENode *Edge;
struct ENode{
    Vertex V1, V2;
};

typedef struct GNode *MGraph;
struct GNode{
    int Nv, Ne;
    int JumpDistance;
    WeightType G[MaxVertexNum][MaxVertexNum];
    Position P[MaxVertexNum];
};

MGraph BuildMGraph();
void Floyd( MGraph Graph );
bool isSafe( MGraph Graph, Vertex V );
bool isFirstJump( MGraph Graph, Vertex V );
WeightType Distance[MaxVertexNum][MaxVertexNum];
Vertex Path[MaxVertexNum][MaxVertexNum];
int main( int argc, const char *argv[] ){

    MGraph Graph = BuildMGraph();
    Floyd( Graph );
    vector<bool> First( MaxVertexNum, false ), Safe( MaxVertexNum, false );
    Vertex V, W, S, D;

    for( V = 0; V < Graph->Nv; V++ ){
        if( isFirstJump( Graph, V ) ) First[V] = true;
        if( isSafe( Graph, V ) )  Safe[V] = true;
    }
    WeightType MinDist = Infinity;
    int FirstJumpDistNew, FirstJumpDistOld;
    for( V = 0; V < Graph->Nv; V++ )
        for( W = 0; W < Graph->Nv; W++ ){
            if( First[V] && Safe[W] && Distance[V][W] != Infinity ){
                if( MinDist > Distance[V][W] ){
                    MinDist = Distance[V][W];
                    S = V;
                    D = W;
                    FirstJumpDistOld = pow( Graph->P[S].X, 2 ) + pow( Graph->P[S].Y, 2 );
                }else if( MinDist == Distance[V][W] ){
                    FirstJumpDistNew = pow( Graph->P[V].X, 2 ) + pow( Graph->P[V].Y, 2 );
                    if( FirstJumpDistNew < FirstJumpDistOld ){
                        FirstJumpDistOld = FirstJumpDistNew;
                        S = V; D = W;
                    }
                    
                }
            }
        }
    if( MinDist == Infinity ) cout << 0;
    else if( S == D ) cout << 1;
    else{
        stack<Vertex> Ans;
        Ans.push( D );
        while( Path[S][D] != -1 ){
            D = Path[S][D];
            Ans.push( D );
        }
        Ans.push( S );
        cout << Ans.size() + 1 << endl;
        while( !Ans.empty() ){
            cout << Graph->P[ Ans.top() ].X << ' ' << Graph->P[ Ans.top() ].Y << endl;
            Ans.pop();
        }
    }


    return 0;
}



void Floyd( MGraph Graph ){

    Vertex K, V, W;
    for( V = 0; V < Graph->Nv; V++ )
        for( W = 0; W < Graph->Nv; W++ ){
            Distance[V][W] = Graph->G[V][W];
            Path[V][W] = -1;
        }
            
        
    for( K = 0; K < Graph->Nv; K++ )
        for( V = 0; V < Graph->Nv; V++ )
            for( W = 0; W < Graph->Nv; W++ ){
                if( Distance[V][W] > Distance[V][K] + Distance[K][W] ){
                    Distance[V][W] = Distance[V][K] + Distance[K][W];
                    Path[V][W] = K;
                }
            }
}

bool isSafe( MGraph Graph, Vertex V ){
    int X, Y;
    X = abs( Graph->P[V].X ); Y = abs( Graph->P[V].Y );
    if( X + Graph->JumpDistance >= Boundary || Y + Graph->JumpDistance >= Boundary ) return true;
    else return false;
}

bool isFirstJump( MGraph Graph, Vertex V ){
    int Distance;
    Distance = pow( Graph->P[V].X, 2 ) + pow( Graph->P[V].Y, 2 );
    Distance = sqrt( Distance );
    if( Graph->JumpDistance + Diameter / 2 >= Distance ) return true;
    else return false;
}

MGraph BuildMGraph(){
    int N, D;
    cin >> N >> D;
    MGraph Graph = new GNode;
    Graph->Nv = N;
    Graph->JumpDistance = D;

    Vertex V, W;
    for( int i = 0; i < N; i++ )
        cin >> Graph->P[i].X >> Graph->P[i].Y;
    
    for( V = 0; V < Graph->Nv; V++ )
        for( W = 0; W < Graph->Nv; W++ ){
            Graph->G[V][W] = Infinity;
        }
    
    
    int X1, X2, Y1, Y2;
    int Distance;
    Edge E = new ENode;
    for( V = 0; V < Graph->Nv; V++ ){
        X1 = Graph->P[V].X; Y1 = Graph->P[V].Y;
        for( W = 0; W < Graph->Nv; W++ ){
            X2 = Graph->P[W].X; Y2 = Graph->P[W].Y;
            Distance = pow( (X1 - X2), 2 ) + pow( (Y1 - Y2), 2);
            if( Distance <= pow( Graph->JumpDistance, 2) ){
                Graph->G[V][W] = Graph->G[V][W] = 1;
            }
        }
    }

    return Graph;
}

