#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10000
typedef int ElementType;
typedef int SetType[MAXN+1]; /*定义集合类型, 元素下标从 1 到 N */

void Union( SetType S, int Root1,int Root2 );
int FindRoot( SetType S, ElementType X );

int main( int argc, const char *argv[]){

    int N;
    int Count;
    char Order;
    int Computer1,Computer2;
    int Root1,Root2;
    scanf( "%d\n", &N );
    SetType S;
    for( int i = 1 ; i <= N ; i++ )
        S[i] = -1;
    while( 1 ){
        scanf( "%c", &Order );
        if( Order == 'S' ) break;
        scanf( "%d %d", &Computer1, &Computer2 );
        getchar();
        Root1 = FindRoot( S, Computer1 );
        Root2 = FindRoot( S, Computer2 );
        if( Order == 'C' ){
            if( Root1 == Root2 ) printf( "yes" );
            else printf( "no" );
            printf( "\n");
        }else 
            Union( S, Root1, Root2 );   
    }
    Count = 0;
    for( int i = 1 ; i <= N ; i++ ){
        if( S[i] < 0 ) Count++;
    }
    if( Count == 1 ) printf( "The network is connected.");
    else printf( "There are %d components", Count );
    printf( "\n");  
    return 0;
}
/* 给定集合和两个根节点，合并 */
/* 已经明确 Root1  不等于 Root2 */
void Union( SetType S, int Root1,int Root2 ){
    if( S[Root1] > S[Root2] ){
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }else{ /* 注意这里不能再加判断 if( S[Root1] < S[Root2] ), 因为二者可能相等  */
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
}

/* 在查询元素的根节点时，压缩 */
int FindRoot( SetType S, ElementType X ){
    if( S[X] < 0 ) return X;
    else return S[X] = FindRoot( S, S[X] );
}
