#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MaxN 10000
typedef int ElementType;
typedef ElementType SetType[MaxN+1];

void Union( SetType S, int RootA, int RootB );
int FindRoot( SetType S, ElementType X );
int main( int argc, const char *argv[]){

    SetType S;
    int N, K, Q;
    int A, B;
    int RootA,RootB;
    int Id = 1;
    int Cnt = 0;
    scanf( "%d\n", &N );

    for( int i = 1 ; i <= MaxN ; i++ )
        S[i] = -1;

    for( int i = 0 ; i < N ; i++ ){
        scanf( "%d %d", &K, &A );
        if( Id < A ) Id = A;
        for( int j = 1 ; j < K ; j++ ){
            scanf( "%d", &B );
            if( Id < B ) Id = B;
            RootA = FindRoot( S, A ); /* 重要！！！ 把A的根查找放在循环里面， 因为每一层合并可能导致A的根发生变化 */
            RootB = FindRoot( S, B );
            if( RootA != RootB ) Union( S, RootA, RootB );
        }
        getchar();
    }
    
    /* 统计家族个数 */
    for( int i = 1 ; i <= Id ; i++ )
        if( S[i] < 0 ) Cnt++;
    printf( "%d %d\n", Id, Cnt );
   
    scanf( "%d", &Q );
    for( int i = 0 ; i < Q ; i++ ){
        scanf( "%d %d", &A, &B );
        RootA = FindRoot( S, A );
        RootB = FindRoot( S, B );
        if( RootA == RootB ) printf( "Y\n");
        else printf( "N\n" );
        getchar();
    }
    
    return 0;
}

/* 路径压缩 */
int FindRoot( SetType S, ElementType X ){
    if( S[X] < 0 ) return X;
    else return S[X] = FindRoot( S, S[X] );
}

/* 按秩大小归并，确保小集合并入大集合 */
void Union( SetType S, int RootA, int RootB ){
    if( S[RootA] > S[RootB] ){
         S[RootB] += S[RootA];
         S[RootA] = RootB;
    }else{
        S[RootA] += S[RootB];
        S[RootB] = RootA;
    }
}

/*

5
3 7 9 8
3 1 3 5
4 2 4 6 10
1 11
7 12 6 3 11 9 13 14
5
11 12
1 3
4 8
5 7
14 2

*/
