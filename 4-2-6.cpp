#include <iostream>
#include <string>


using namespace std;

typedef struct Node *PtrToNode;
struct Node{
    string Info;
    bool isDirectory;
    PtrToNode LeftChild, NextSibiling;
};
typedef PtrToNode Tree;


PtrToNode CreatNewNode( string Info, bool isDirectory );
PtrToNode Insert( PtrToNode Root, string Info, bool isDirectory );
void PreOrderTravesal( Tree T, int Layer );
int main( int argc, const char *argv[] ){

    int n;
    PtrToNode Pos;
    string stemp;
    cin >> n;
    getchar();
    Tree root = CreatNewNode( "root", true );

    int bgn, end;
    for( int i = 0; i < n ; i++ ){
        getline( cin, stemp ); 
        Pos = root; bgn = end = 0;
        for( int j = 0 ; j < stemp.length() ; j++ ){
            if( stemp[j] == '\\' ){
                end = j;
                Pos = Insert( Pos, stemp.substr( bgn, end - bgn ), true );
                bgn = end + 1;
            }
        }
        if( stemp[bgn] != '\0' ){
            Insert( Pos, stemp.substr( bgn ), false );
        }
        
    }
    PreOrderTravesal( root, 0 );

    return 0;
}

PtrToNode CreatNewNode( string Info, bool isDirectory ){
    PtrToNode T = new Node; 
    T->Info = Info;
    T->isDirectory = isDirectory;
    T->LeftChild = T->NextSibiling = nullptr;
    return T;
}


PtrToNode Insert( PtrToNode Root, string Info, bool isDirectory ){
    if( Root->LeftChild == nullptr ){
        Root->LeftChild = CreatNewNode( Info, isDirectory );
        return Root->LeftChild;
    }
    PtrToNode FrontPtr = Root, TailPtr = Root->LeftChild;
    while( ( TailPtr ) && (( TailPtr->isDirectory == isDirectory && TailPtr->Info < Info ) || ( TailPtr->isDirectory && !isDirectory ))){
        FrontPtr = TailPtr;
        TailPtr = TailPtr->NextSibiling;
    }
    if( TailPtr == nullptr ){
        FrontPtr->NextSibiling = CreatNewNode( Info, isDirectory );
        return FrontPtr->NextSibiling;
    }else if( TailPtr->Info == Info ){
        return TailPtr;
    }else{
        PtrToNode NewNode = CreatNewNode( Info, isDirectory );
        if( Root == FrontPtr ){
            NewNode->NextSibiling = TailPtr;
            FrontPtr->LeftChild = NewNode;
        }else{
            NewNode->NextSibiling = TailPtr;
            FrontPtr->NextSibiling = NewNode;
        }
        return NewNode;
    }
}

void PreOrderTravesal( Tree T, int Layer ){
    if( T ){
        for( int i = 0 ; i < Layer ; i++ ){
            cout << "  ";
        }
        cout << T->Info << endl;
        PreOrderTravesal( T->LeftChild, Layer+1 );
        PreOrderTravesal( T->NextSibiling, Layer );
    }
}
