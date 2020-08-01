#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MsgLength 11
#define MaxN 100001
#define NegInfinity -65536

typedef struct Node ElementType;
struct Node{
    char Name[MsgLength];
    int Priority;
};

typedef struct HNode *Heap;
struct HNode{
    int Capacity;
    int CurrentSize;
    ElementType *Data;
};
Heap CreatEmptyHeap( int N );
void InsertMinHeap( Heap H, ElementType X );
ElementType DeleteMinHeap( Heap H );
void PercDown( Heap H, int P );
int main( int argc, const char *argv[]){

    int N;
    char Command[4];
    ElementType TmpData;
    Heap H;
    scanf( "%d\n", &N );
    H = CreatEmptyHeap( N );
    for( int i = 0 ; i < N ; i++ ){
        scanf( "%s", Command );
        if( Command[0] == 'P' ){
            scanf( " %s %d", TmpData.Name, &TmpData.Priority );
            InsertMinHeap( H, TmpData );
        }else{
            TmpData = DeleteMinHeap( H );
            if( TmpData.Priority == -1 ) printf( "EMPTY QUEUE!\n");
            else printf( "%s\n", TmpData.Name );
        }
        getchar();
    }

    return 0;
}

Heap CreatEmptyHeap( int N ){
    Heap H = (Heap)malloc(sizeof(struct HNode));
    H->Capacity = MaxN;
    H->CurrentSize = 0;/* 注意!!! */
    H->Data = (ElementType*)malloc(sizeof(ElementType)*( N + 1) ); /* 注意 */
    H->Data[0].Priority = NegInfinity;

    return H;
}

void InsertMinHeap( Heap H, ElementType X ){
    int P;
    for( P = ++H->CurrentSize ; H->Data[P/2].Priority > X.Priority ; P /= 2 )
        H->Data[P] = H->Data[P/2];
    H->Data[P] = X;
}

ElementType DeleteMinHeap( Heap H ){
    ElementType Item;
    if( H->CurrentSize > 0 ){
         Item = H->Data[1];
        H->Data[1] = H->Data[H->CurrentSize--];
        PercDown( H, 1 );
    }else Item.Priority = -1;
    
    return Item;
}

void PercDown( Heap H, int P ){
    int Parent, Child;
    ElementType Item = H->Data[P];
    for( Parent = P ; Parent*2 <= H->CurrentSize ; Parent = Child ){
        Child = Parent*2;
        if( Child != H->CurrentSize && H->Data[Child].Priority > H->Data[Child+1].Priority )
            Child++;
        if( H->Data[Child].Priority > Item.Priority ) break;
        else H->Data[Parent] = H->Data[Child];
    }
    H->Data[Parent] = Item;
}

