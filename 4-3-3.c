#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MaxN 1001
int GetLeftLength( int len );
void BuildCBT( int Data[],int CBTree[], int Left, int Right, int Root );
int Increment( const void *a, const void *b );
int main( int argc, const char *argv[]){

    int N;
    /* 利用数组表达完全二叉搜索树 */
    int Data[MaxN];
    int CBTree[MaxN];
    bool flag = true;
    scanf( "%d", &N );

    /* 下标从1开始 */
    for( int i = 1 ; i <= N ; i++ )
        scanf( "%d", &Data[i] );
    qsort( Data+1, N, sizeof(Data[0]), Increment );
    /* 递归的建树*/
    BuildCBT( Data, CBTree, 1, N, 1 );
    for( int i = 1 ; i <= N ; i++ ){
        if( flag ){
            printf( "%d", CBTree[i] );
            flag = false;
        }else printf( " %d", CBTree[i] );

    }
    return 0;
}

int Increment( const void *a, const void *b ){
    return *(const int *)a - *(const int *)b;
}


int GetLeftLength( int Len ){

    int Level = 1;
    int Tmp = Len;
    int LastLevelCount;
    int LeftLength;
    int LeftSubTree;
    while( pow( 2, Level ) - 1 < Len )
        Level++;
    LastLevelCount = Len - pow( 2, Level-1 ) + 1;
    LeftSubTree = pow( 2, Level-2 ) - 1;
    LeftLength = ( LastLevelCount <= pow( 2, Level-2 ) ) ? ( LeftSubTree + LastLevelCount ) : ( LeftSubTree + pow( 2, Level-2) );

    return LeftLength;
    
}

void BuildCBT( int Data[],int CBTree[], int Left, int Right, int Root ){
    int Len = Right - Left + 1;
    if( Len == 0 ) return ;
    int LeftLength = GetLeftLength( Len );
    int RightLength = Len - LeftLength - 1;
    CBTree[Root] = Data[Left + LeftLength];
    BuildCBT( Data, CBTree, Left, Left + LeftLength - 1, Root*2 );
    BuildCBT( Data, CBTree, Left + LeftLength + 1, Right, Root*2 + 1 );
}
