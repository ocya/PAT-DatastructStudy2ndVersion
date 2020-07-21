#include <stdio.h>
#include <stdbool.h>

int Terms[31];/* 全局数组保存递归过程中的分解项 */
int N; 
int Cnt = 0; /* 每四个输出换行符 */
void Search( int Remainder, int Start, int nTerm );

int main( int argc, const char *argv[]){

    scanf( "%d", &N );
    Search( N , 1 , 1 );
    return 0;  
}

/* Remainder 表示剩余值，Start 表示分解项起始值， nTerm 表示分解式的第几项 */
void Search( int Remainder, int Start, int nTerm ){
    if( Remainder == 0 ){/* 递归终止条件 */
        Cnt++;/* 在终止条件中累加分解式的个数 */
        for( int i = 1 ; i < nTerm ; i++ ){
            if( i == 1 ) printf( "%d=%d", N, Terms[i] );
            else printf( "+%d", Terms[i] );
        } 
        if( Cnt % 4 == 0 ) printf( "\n" );       
        else if( Terms[nTerm-1] != N ) printf( ";" );
        /* 最后一个分解式 N=N，结尾不需要分号 */
    }else{
        /*从 Start开始 遍历 nTerm 位置所有可能的分解值 */
        for( int i = Start ; i <= Remainder ; i++ ){
            Terms[nTerm] = i;
            /* 递归分解剩余值，确保分解项不小于Start */
            Search( Remainder - i , i , nTerm+1 );
        }
    }
}
