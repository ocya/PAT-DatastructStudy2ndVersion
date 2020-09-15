//最大N测试点超时
#include <iostream>
#include <vector>
#include <map>

#define MaxVertexNum 1001

using namespace std;

typedef struct GNode *MGraph;
struct GNode{
    int Nv, Ne;
    int G[MaxVertexNum][MaxVertexNum];
};

typedef struct HNode *Heap;
struct HNode{
    int CurrentSize;
    int *Data;
};

MGraph BuildMGraph( int VertexNum );
void TopSort( MGraph Graph );
vector<int> HashTable;
map<int, int> Idx;
int main( int argc, const char *argv[] ){
    int N;
    cin >> N;
    HashTable.resize( N );
    for( int i = 0; i < N; i++ ){
        scanf( "%d", &HashTable[i] );
        Idx[ HashTable[i] ] = i;
    }
        
    MGraph Graph = BuildMGraph( N );
    TopSort( Graph );
}

Heap CreatEmptyHeap( int VertexNum ){
    Heap H = new HNode;
    H->CurrentSize = 0;
    H->Data = ( int *)malloc( sizeof( int )*( VertexNum + 1 ) );
    H->Data[0] = -65535;
    
    return H;
}
MGraph BuildMGraph( int VertexNum ){
    MGraph Graph = new GNode;
    Graph->Nv = VertexNum;
    int V, W;
    for( V = 0; V < VertexNum; V++ )
        for( W = 0; W < VertexNum; W++ )
            Graph->G[V][W] = 0;
    
    for( int i = 0; i < VertexNum; i++ ){
        if( HashTable[i] >= 0 ){
            for( V = HashTable[i]%VertexNum; V != i; V++ ){
                if( V == VertexNum ) V = 0;
                if( HashTable[V] >= 0 )
                    Graph->G[V][i] = 1;
            }
        }
    }  
    return Graph; 
}

void InsertMinHeap( Heap H, int Item ){
    int i;
    for( i = ++H->CurrentSize; H->Data[i/2] > Item; i /= 2 ){
        H->Data[i] = H->Data[i/2];
    }
    H->Data[i] = Item;
}

void PercDwon( Heap H, int Pos ){
    int Item = H->Data[Pos];
    int Parent, Child;
    for( Parent = Pos; Parent*2 <= H->CurrentSize; Parent = Child ){
        Child = Parent * 2;
        if( Child != H->CurrentSize && H->Data[Child] > H->Data[Child+1] )
            Child++;
        if( H->Data[Child] < Item )
            H->Data[Parent] = H->Data[Child];
        else break;
    }
    H->Data[Parent] = Item;
}

int DeleteMinHeap( Heap H ){
    int Item = H->Data[1];
    H->Data[1] = H->Data[ H->CurrentSize-- ];
    PercDwon( H, 1 );

    return Item;
}

void TopSort( MGraph Graph ){
    vector<int> InDegree( Graph->Nv, 0 );
    Heap H = CreatEmptyHeap( Graph->Nv );
    int V, W;
    for( V = 0; V < Graph->Nv; V++ )
        for( W = 0; W < Graph->Nv; W++ ){
            if( Graph->G[V][W] == 1 ) 
                InDegree[W]++;
        }

    for( V = 0; V < Graph->Nv; V++ ){
        if( InDegree[V] == 0 && HashTable[V] >= 0 ) 
            InsertMinHeap( H, HashTable[V] );
    }

    int Key;
    bool isFirst = false;
    while( H->CurrentSize != 0 ){
        Key = DeleteMinHeap( H );
        V = Idx[Key];
        if( !isFirst ){
            isFirst = true;
            printf( "%d", Key );
        }else{
            printf( " %d", Key ); 
        }

        for( W = 0; W < Graph->Nv; W++ ){
            if( Graph->G[V][W] == 1 ){
                InDegree[W]--;
                if( InDegree[W] == 0 && HashTable[W] >=  0 )
                    InsertMinHeap( H, HashTable[W] );
            }
                 
        }
    }


        
}


