#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 10

struct BNode{
    char Data;
    int Left,Right;
};

bool Check( struct BNode T1[], struct BNode T2[], int Root1, int Root2 );
int BuildTree( struct BNode T[]);
int main( int argc, const char *argv[]){
    /* 这里用结构体数组实现数 */
    struct BNode T1[MaxSize], T2[MaxSize];
    int Root1, Root2;
    Root1 = BuildTree( T1 );
    Root2 = BuildTree( T2 );
    if( Check( T1, T2, Root1, Root2 ) )
        printf( "Yes\n" );
    else
        printf( "No\n" );
    
    return 0;
}

bool Check( struct BNode T1[], struct BNode T2[], int Root1, int Root2 ){
    if( Root1 == -1 && Root2 == -1 ) return true;
    if(( Root1 == -1 && Root2 != -1 ) || ( Root1 != -1 && Root2 == -1 ) ) return false;
    if( T1[Root1].Data == T2[Root2].Data ){ /* 当根节点相等时，检查左右子树是否同构，考虑两种情形，左右都交换 或者 左右都不交换 */
        return (Check( T1, T2, T1[Root1].Left, T2[Root2].Left) && Check( T1, T2, T1[Root1].Right, T2[Root2].Right)) || \
        ( Check( T1, T2, T1[Root1].Right, T2[Root2].Left ) && Check( T1, T2, T1[Root1].Left, T2[Root2].Right ) );
    }else return false;
}

int BuildTree( struct BNode T[]){
    int N;
    char Data;
    char L, R;
    int Left,Right;
    int Root = -1; /* 初始化 Root 为 -1 ，即等价于 NULL */
    scanf( "%d\n", &N );
    bool flag[N];
    for( int i = 0 ; i < N ; i++ )
        flag[i] = false; /* 统一初始化为 false, 当有指针指向某节点时，标记位置位 true */
    for( int i = 0 ; i < N ; i++ ){
        scanf( "%c %c %c", &Data, &L, &R );
        getchar();
        T[i].Data = Data;
        if( L != '-' ){
            Left = L - '0';
            T[i].Left = Left;
            flag[Left] = true; /* 在构建树的过程中，标记是否有指针指向该节点 */
        }else T[i].Left = -1;
        if( R != '-' ){
            Right = R - '0';
            T[i].Right = Right;
            flag[Right] = true;
        }else T[i].Right = -1;
    }
    /* 没有任何指针指向的节点为根节点 */
    for( int i = 0 ; i < N ; i++ )
        if( flag[i] == false ){
            Root = i;
            break;
        }
               
    return Root;
}
