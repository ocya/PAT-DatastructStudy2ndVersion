#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MaxSize 1000

int main( int argc, const char *argv[]){

    int N;
    int AQueue[MaxSize],BQueue[MaxSize];
    int Tmp;
    int Afornt,Arear,BFront,Brear;
    bool SwitchFlag = false; /* 控制窗口切换 */
    bool SpaceControlFlag = true; /* 结尾空格控制字符 */
    int ACnt; /* 记录A窗口处理的人数 */
    Afornt = Arear = BFront = Brear = 0;
    scanf( "%d", &N );
    for( int i = 0 ; i < N ; i++ ){
        scanf( "%d", &Tmp );/* 分别保存A,B窗口待处理的顾客编号 */
        if( Tmp % 2 == 0 ) BQueue[Brear++] = Tmp;
        else AQueue[Arear++] = Tmp; 
    }
    ACnt = 0;
    while (1){
        
         if( ACnt == 2 || Afornt == Arear ){
             SwitchFlag = true;/* 当 A 处理两个或者 A 为空，切换到 B */
             ACnt = 0;/* 切换到 B 时将记录的 A 窗口处理人数清零 */
         } 
         if( SwitchFlag ){/* 对 B 进行处理 */
             SwitchFlag = false; /* 重置切换标记位 */
             if( BFront != Brear ){ /* 输出前需要判断 B 是否空 */
                if( SpaceControlFlag ){
                    printf( "%d", BQueue[BFront++] );
                    SpaceControlFlag = false;
                }else printf( " %d", BQueue[BFront++] );
             }
         }else{/* 对 A 进行处理 */
             while( ACnt != 2 ){/* A 可以连续输出两个 */
                 if( Afornt != Arear ){/* 输出前判断 A 是否空 */
                     ACnt++;
                     if( SpaceControlFlag ){
                        printf( "%d", AQueue[Afornt++] );
                        SpaceControlFlag = false;
                     }else printf( " %d", AQueue[Afornt++] );
                 }else break; /* 若 A 空，则停止输出 A  */
             }
         }
         /* A, B 都为空队列时，停止循环 */
         if( Afornt == Arear && BFront == Brear ) break;
    }
        
    return 0;
}

