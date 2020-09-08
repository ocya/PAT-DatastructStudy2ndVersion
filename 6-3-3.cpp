//最后一个测试点未通过
//应该是超时了
#include <iostream>
#include <vector>
#include <stack>


#define MaxVertexNum 501
#define Infinity 65536

using namespace std;

typedef int Vertex;
struct WeightType{
    int Time, Length;
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


MGraph BuildMGraph();
Vertex S, D;
vector<WeightType> Cost( MaxVertexNum );
vector<Vertex> LengthPath( MaxVertexNum, -1 );
vector<Vertex> TimePath( MaxVertexNum, -1 );
vector<bool> isCollected( MaxVertexNum, false );

void DijkstraTime( MGraph Graph, Vertex S );
void DijkstraLength( MGraph Graph, Vertex S );
int main( int argc, const char *argv[] ){

    MGraph Graph = BuildMGraph();
    cin >> S >> D;
    stack<Vertex> AnsTime, AnsLength;
    WeightType Result;
    DijkstraTime( Graph, S );
    Result.Time = Cost[D].Time;
    for( Vertex V = D; V != S; V = TimePath[V] ){
        AnsTime.push( V );
    }    
    isCollected.assign( MaxVertexNum, false );
    DijkstraLength( Graph, S );
    Result.Length = Cost[D].Length;
    for( Vertex V = D; V != S; V = LengthPath[V] ){
        AnsLength.push( V );
    }
    if( AnsLength == AnsTime ){
        cout << "Time = " << Result.Time << "; Distance = " << Result.Length << ": " << S;
        while( !AnsTime.empty() ){
            cout << " => " << AnsTime.top();
            AnsTime.pop();
        }
    }else{
        cout << "Time = " << Result.Time << ": " << S;
        while( !AnsTime.empty() ){
            cout << " => " << AnsTime.top();
            AnsTime.pop();
        }
        cout << endl;  
        cout << "Distance = " << Result.Length << ": " << S;    
        while( !AnsLength.empty() ){
            cout << " => " << AnsLength.top();
            AnsLength.pop();
        }                  
    }

    return 0;
}


Vertex FindMindTimeVertex( MGraph Graph ){
    Vertex V, MinV;
    WeightType Min;
    Min.Time = Infinity;
    for( V = 0; V < Graph->Nv; V++ ){
        if( Min.Time > Cost[V].Time && !isCollected[V] ){
            Min.Time = Cost[V].Time;
            MinV = V;
        }
    }
    if( Min.Time == Infinity ) MinV = -1;
    return MinV;    
}

void DijkstraTime( MGraph Graph, Vertex S ){

    
    Vertex V, W;
    for( V = 0; V < Graph->Nv; V++ ){
        Cost[V] = Graph->G[S][V];
        if( Graph->G[S][V].Length != Infinity )
            TimePath[V] = S;       
    }
    Cost[S].Time = Cost[S].Length = 0;
    isCollected[S] = true;
    
    while( 1 ){
        V = FindMindTimeVertex( Graph );
        if( V == -1 ) break;

        isCollected[V] = true;
        for( W = 0; W < Graph->Nv; W++ ){
            if( !isCollected[W] && Graph->G[V][W].Length != Infinity ){
                if( Cost[W].Time > Cost[V].Time + Graph->G[V][W].Time ){
                    Cost[W].Length = Cost[V].Length + Graph->G[V][W].Length;
                    Cost[W].Time = Cost[V].Time + Graph->G[V][W].Time;
                    TimePath[W] = V;
                }else if( Cost[W].Time == Cost[V].Time + Graph->G[V][W].Time ){
                    if( Cost[W].Length > Cost[V].Length + Graph->G[V][W].Length ){
                        Cost[W].Length = Cost[V].Length + Graph->G[V][W].Length; 
                        TimePath[W] = V;
                    }
                }
            }
        }
    }
    
}

Vertex FindMindLengthVertex( MGraph Graph ){
    Vertex V, MinV;
    WeightType Min;
    Min.Length = Infinity;
    for( V = 0; V < Graph->Nv; V++ ){
        if( Min.Length > Cost[V].Length && !isCollected[V]){
            Min.Length = Cost[V].Length;
            MinV = V;
        }
    }
    if( Min.Length == Infinity ) MinV = -1;
    return MinV;

}

void DijkstraLength( MGraph Graph, Vertex S ){

    vector<int> NodeCount( MaxVertexNum, Infinity );
    NodeCount[S] = 1;
    Vertex V, W;
    for( V = 0; V < Graph->Nv; V++ ){
        Cost[V] = Graph->G[S][V];
        if( Graph->G[S][V].Length != Infinity )
            LengthPath[V] = S; 
            NodeCount[V] = NodeCount[S] + 1;      
    }
    Cost[S].Length = 0;
    isCollected[S] = true;
    
    while( 1 ){
        V = FindMindLengthVertex( Graph );
        if( V == -1 ) break;

        isCollected[V] = true;
        for( W = 0; W < Graph->Nv; W++ ){
            if( !isCollected[W] && Graph->G[V][W].Length != Infinity ){
                if( Cost[W].Length > Cost[V].Length + Graph->G[V][W].Length ){
                    Cost[W].Length = Cost[V].Length + Graph->G[V][W].Length;
                    LengthPath[W] = V;
                    NodeCount[W] = NodeCount[V] + 1;
                }else if( Cost[W].Length == Cost[V].Length + Graph->G[V][W].Length ){
                    if( NodeCount[W] > NodeCount[V] + 1 ){
                        NodeCount[W] = NodeCount[V] + 1;
                        LengthPath[W] = V;
                    }
                }
            }
        }
    }
    
}

MGraph BuildMGraph(){
    int N, M;
    cin >> N >> M;
    MGraph Graph = new GNode;
    Graph->Nv = N;
    Graph->Ne = M;

    for( Vertex V = 0; V < Graph->Nv; V++ )
        for( Vertex W = 0; W < Graph->Nv; W++ ){
            Graph->G[V][W].Length = Infinity;
            Graph->G[V][W].Time = Infinity;
        }
            
    Edge E = new ENode;
    int OneWay;
    for( int i = 0; i < M; i++ ){
        cin >> E->V1 >> E->V2 >> OneWay >> E->Weight.Length>> E->Weight.Time;
        Graph->G[ E->V1 ][E->V2 ] = E->Weight;
        if( OneWay == 0 )   Graph->G[ E->V2 ][E->V1 ] = E->Weight;
    }

    return Graph;
}
