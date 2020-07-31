#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define MaxSize 10000
#define NegInfinity -65536


typedef int ElementType;

typedef struct HNode *Heap;
struct HNode{
    int Capacity;
    int CurrentSize;
    ElementType *Data;
};

/* 堆相关的操作函数 */
ElementType DeleteMinHeap( Heap H );
void InsertMinHeap( Heap H, ElementType X );
Heap CreatEmptyHeap( int N );
void BuildHeap( Heap H );
void PercDown( Heap H, int P );
int main( int argc, const char *argv[]){

    int N;
    int Sum = 0;
    ElementType A, B, Tmp;
    scanf( "%d\n", &N );
    Heap H = CreatEmptyHeap( N );
    for( int i = 1 ; i <= N ; i++ )
        scanf( "%d", &H->Data[i] );
    BuildHeap( H );

    /* Huffman算法，每次选最短的两块合并，合并后进行费用累加 */
    while( 1 ){
        A = DeleteMinHeap( H );
        if( H->CurrentSize == 0 ) break;
        B = DeleteMinHeap( H );
        Tmp = A + B;
        Sum += Tmp;
        InsertMinHeap( H, Tmp );   
    }
    
    printf( "%d\n", Sum );


    return 0;
}

ElementType DeleteMinHeap( Heap H ){
    ElementType Item = H->Data[1];
    H->Data[1] = H->Data[H->CurrentSize--];
    PercDown( H, 1 );
    return Item;
}

void InsertMinHeap( Heap H, ElementType X ){
    int P;
    for( P = ++H->CurrentSize ; H->Data[P/2] > X ; P /= 2 )
        H->Data[P] = H->Data[P/2];
    H->Data[P] = X;
}

Heap CreatEmptyHeap( int N ){
    Heap H = (Heap)malloc(sizeof(struct HNode));
    H->Capacity = MaxSize;
    H->CurrentSize = N;
    H->Data = (ElementType*)malloc(sizeof(ElementType)*(H->Capacity + 1 ));
    H->Data[0] = NegInfinity;
    return H;
}

void BuildHeap( Heap H ){
    for( int P = H->CurrentSize/2 ; P > 0 ; P-- )
        PercDown( H, P );
}

void PercDown( Heap H, int P ){
    int Parent, Child;
    ElementType Item = H->Data[P];
    for( Parent = P; Parent*2 <= H->CurrentSize ; Parent = Child ){
        Child = Parent*2;
        if( Child != H->CurrentSize && H->Data[Child] > H->Data[Child+1] )
            Child++;
        if( H->Data[Child] > Item ) break;
        else H->Data[Parent] = H->Data[Child];
    }
    H->Data[Parent] = Item;
}

