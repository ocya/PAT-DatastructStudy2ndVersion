#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MaxSize 1000

int main( int argc, const char *argv[]){
    int Stack[MaxSize];
    int Top = -1;
    int M, N, K;
    int Tmp;
    int Current;/* 当前栈顶元素 */
    bool flag; /* 判断该序列是否合法*/
    scanf( "%d %d %d\n", &M, &N, &K );
    for( int i = 0 ; i < K ; i++ ){/* 判断 K 次 */
        Top = -1; /* 每开始一轮新的判断时，重置堆栈和标记位 */
        Current = 1;
        flag = true;
        for( int j = 1; j <= N ; j++ ){
            scanf( "%d", &Tmp ); /* 读取序列 */
            while( Current <= Tmp ) /* 当栈顶元素小于等于读取的 Tm p值时，持续压栈 */
                Stack[++Top] = Current++;
            /* 压栈完成判断是否堆栈溢出 */
            /* 弹出当前栈顶元素，判断是否和读取的 Tmp 相等 */
            /* 二者有任一条件不满足，视为非法序列 */
            if( Top == M || Stack[Top--] != Tmp ) flag = false;

        }
        getchar();
        if( flag ) printf( "YES\n");
        else printf( "NO\n");
    }
    
}

