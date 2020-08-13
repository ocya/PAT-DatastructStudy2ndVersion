#include <iostream>
#include <string>
#include <vector>

#define NegInfinnity -65536

using namespace std;

typedef int ElementType;

typedef struct HNode *Heap;
struct HNode{
    int Size;
    int MaxSize;
    ElementType* Data;
};

Heap CreatEmptyHeap( int N );
void InsertMinHeap( Heap H, ElementType X );
bool isRoot( Heap H, ElementType X );
bool isSibiling( Heap H, int Idx1, int Idx2 );
bool isParent( Heap H, int Idx1, int Idx2 );
bool isChild( Heap H, int Idx1, int Idx2 );
int FindIdx( Heap H, ElementType X );
int main( int argc, const char *argv[] ){

    int N, M;
    string S;
    cin >> N >> M;
    Heap H = CreatEmptyHeap( N );
    int Data;
    for( int i = 0 ; i < N ; i++ ){
        cin >> Data;
        InsertMinHeap( H, Data );
    }
    getchar();
    ElementType X1, X2;
    int Idx1, Idx2;
    bool isRight;
    for( int i = 0 ; i < M ; i++ ){
        getline( cin, S );
        X1 = stoi( S.substr( 0, S.find_first_of( ' ' ) ));
        Idx1 = FindIdx( H, X1 );
        S = S.substr( S.find_first_of( ' ' )+1 );
        S = S.substr( S.find_first_of( ' ' )+1 );
        // cout << S.substr( S.find_last_of( ' ' )) << endl;
        if( S.substr( S.find_last_of( ' ' )+1 ) == "root" ){
            if( isRoot( H, X1 ) ) isRight = true;
            else isRight = false;        
        }else if( S.substr( S.find_last_of( ' ' )+1 ) == "siblings" ){                  
            X2 = stoi( S.substr( 0, S.find_first_of( ' ' ) ));
            Idx2 = FindIdx( H, X2 );
            if( isSibiling( H, Idx1, Idx2 ) ) isRight = true;
            else isRight = false;
        }else{
            X2 = stoi( S.substr( S.find_last_of( ' ' )+1 ));
            Idx2 = FindIdx( H, X2 );
            if( S[0] == 't' ){
                if( isParent( H, Idx1, Idx2 ) ) isRight = true;
                else isRight = false;
            }else{
                if( isChild( H, Idx1, Idx2 ) ) isRight = true;
                else isRight = false;
            }
        }
        if( isRight ) cout << 'T' << endl;
        else cout << 'F' << endl;
    }

    

    return  0;
}
bool isRoot( Heap H, ElementType X ){
    if( X == H->Data[1] ) return true;
    else return false;
}

bool isSibiling( Heap H, int Idx1, int Idx2 ){
    if( Idx1/2 == Idx2/2 ) return true;
    else return false;
}

bool isParent( Heap H, int Idx1, int Idx2 ){
    if( Idx2/2 == Idx1 ) return true;
    else return false;
}

bool isChild( Heap H, int Idx1, int Idx2 ){
    return isParent( H, Idx2, Idx1 );
}

int FindIdx( Heap H, ElementType X ){
    int Idx;
    for( int i = 1; i <= H->Size ; i++ )
        if( H->Data[i] == X ){
            Idx = i;
            break;
        }
    return Idx;
}

Heap CreatEmptyHeap( int N ){
    Heap H = ( Heap )malloc( sizeof ( struct HNode ) );
    H->MaxSize = N + 1;
    H->Size = 0;
    H->Data = ( ElementType *)malloc( sizeof( ElementType )* ( H->MaxSize ) );
    H->Data[0] = NegInfinnity;

    return H;
}

void InsertMinHeap( Heap H, ElementType X ){
    int P;
    for( P = ++H->Size ; H->Data[P/2] > X ; P /= 2 )
        H->Data[P] = H->Data[P/2];
    H->Data[P] = X;
}
