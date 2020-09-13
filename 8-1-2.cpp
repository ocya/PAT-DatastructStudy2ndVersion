#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <stack>

#define MaxVertexNum 201
#define Infinity 65536

using namespace std;

typedef int Vertex;
typedef int WeightType;

typedef struct GNode *MGraph;
struct GNode{
    int Nv, Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
    int Amamy[MaxVertexNum];
};
map<string,int> VertexIdx;
map<int,string> VertexName;
string Start,Dest;
vector<bool> isCollected( MaxVertexNum, false );
vector<Vertex> Path( MaxVertexNum, -1 );
vector<WeightType> Distance( MaxVertexNum, Infinity );
vector<int> DefeatCount( MaxVertexNum, 0 );
vector<int> PathCount( MaxVertexNum, 0 );
vector<int> SaveCount( MaxVertexNum, 0 );
MGraph BuildGraph();
void Dijkstra( MGraph Graph );
int main( int argc, const char *argv[] ){

    MGraph Graph = BuildGraph();
    Dijkstra( Graph );
    Vertex V, W, S, D;
    V = VertexIdx[Start]; W = VertexIdx[Dest];
    stack<Vertex> Ans;
    S = V, D = W;
    cout << VertexName[S];
    while( D != S ){
        Ans.push( D );
        D = Path[D];
    }
    
    while( !Ans.empty() ){
        cout << "->" << VertexName[ Ans.top() ]; 
        Ans.pop();
    }
    cout << endl;
    cout << PathCount[W] << ' ' << Distance[W] << ' ' << DefeatCount[W];
    

    return 0;
}

MGraph BuildGraph(){
    int N, K;
    MGraph Graph = new GNode;
    cin >> N >> K >> Start >> Dest;
    Graph->Nv = N;
    Graph->Ne = K;
    Graph->Amamy[0] = 0;
    VertexName[0] = Start;
    VertexIdx[Start] = 0;
    string Name;
    int Count;
    // Initialize the vertex infomation
    for( int i = 1; i < N; i++ ){
        cin >> Name >> Count;
        VertexIdx[Name] = i;
        VertexName[i] = Name;
        Graph->Amamy[i] = Count;

    }
    
    // Initialize the Edge infomation
    Vertex V, W;
    for( V = 0; V < Graph->Nv; V++ )
        for( W = 0; W < Graph->Nv; W++ )
            Graph->G[V][W] = Infinity;
        

    // Insert Edge
    string SecondName;
    int Distance;
    for( int i = 0; i < K; i++ ){
        cin >> Name >> SecondName >> Distance;
        V = VertexIdx[Name]; W = VertexIdx[SecondName];
        Graph->G[V][W] = Graph->G[W][V] = Distance;
    }
    
    return Graph;
}

Vertex FindMinDistVertex( MGraph Graph ){
    Vertex V, MinV;
    WeightType MinDist = Infinity;
    for( V = 0; V < Graph->Nv; V++ ){
        if( !isCollected[V] && MinDist > Distance[V] ){
            MinV = V;
            MinDist = Distance[V];
        }
    }
    if( MinDist == Infinity ) MinV = -1;
    return MinV;
    
}

void Dijkstra( MGraph Graph ){
    Vertex V, W;

    //Initialize the distance equal to graph weight;
    V = 0;
    for( W = 0; W < Graph->Nv; W++ ){
        Distance[W] = Graph->G[V][W];
        if( Graph->G[V][W] != Infinity ){
            PathCount[W] = 1;
            Path[W] = V;
            DefeatCount[W] = Graph->Amamy[W];
            // SaveCount[W] = 1;
        }
    }

    SaveCount[V] = 0;    
    PathCount[V] = 1;
    Distance[V] = 0;
    isCollected[V] = true;
    while( 1 ){
        V = FindMinDistVertex( Graph );
        if( V == -1 ) break;
        isCollected[V] = true;
        for( W = 0; W < Graph->Nv; W++ ){
            if( Graph->G[V][W] != Infinity && !isCollected[W] ){
                if( Distance[W] > Distance[V] + Graph->G[V][W] ){
                    Distance[W] = Distance[V] + Graph->G[V][W];
                    Path[W] = V;
                    PathCount[W] = PathCount[V];
                    SaveCount[W] = SaveCount[V] + 1;
                    DefeatCount[W] = DefeatCount[V] + Graph->Amamy[W]; 
                }else if( Distance[W] == Distance[V] + Graph->G[V][W] ){
                    PathCount[W] += PathCount[V];
                    if( SaveCount[W] < SaveCount[V] + 1 ){
                        SaveCount[W] = SaveCount[V] + 1;
                        DefeatCount[W] = DefeatCount[V] + Graph->Amamy[W];
                        Path[W] = V;
                    }else if( SaveCount[W] == SaveCount[V] + 1){
                        if( DefeatCount[W] < DefeatCount[V] + Graph->Amamy[W] ){
                            DefeatCount[W] = DefeatCount[V] + Graph->Amamy[W];
                            Path[W] = V;
                        }                        
                    }
                }
            }
        }
        
    }
}


/*

10 12 PAT DBY
DBY 100
PTA 20
PDS 90
PMS 40
TAP 50
ATP 200
LNN 80
LAO 30
LON 70
PAT PTA 10
PAT PMS 10
PAT ATP 20
PAT LNN 10
LNN LAO 10
LAO LON 10
LON DBY 10
PMS TAP 10
TAP DBY 10
DBY PDS 10
PDS PTA 10
DBY ATP 10

*/
