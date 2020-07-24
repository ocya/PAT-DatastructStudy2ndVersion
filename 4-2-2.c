#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 10

/* 树节点上没有信息，只需记录左右孩子节点 */
typedef struct BNode BinTree;
struct BNode{
    int Left,Right;
};

void LevelTraversal( BinTree T[], int Root );
int main( int argc, const char *argv[]){
    /* 利用结构体数组实现 */
    BinTree T[MaxSize];
    int front, rear;
    int N;
    char L, R;
    int Root = -1;
    scanf( "%d\n", &N );
    int flag[N]; /* 在建树的过程中， 记录被有指针指向的节点 */
    for( int i = 0 ; i < N ; i++ )
        flag[i] = false;
    for( int i = 0 ; i < N ; i++ ){
        scanf( "%c %c", &L, &R );
        getchar();
        if( L == '-' ) T[i].Left = -1;
        else{
            T[i].Left = L - '0';
            flag[ L- '0' ] = true;
        }
        if( R == '-' ) T[i].Right = -1;
        else{
            T[i].Right = R - '0';
            flag[ R - '0' ] = true;
        }
    }
    /* 建树完成后， 没有被任何指针所指向的节点为根节点 */
    for( int i = 0 ; i < N ; i++ )
        if( flag[i] == false ){
            Root = i;
            break;
        }
    LevelTraversal( T, Root );
    return 0;
}

void LevelTraversal( BinTree T[], int Root ){
    if( Root != -1 ){
        int Queue[MaxSize];/* 利用队列实现层序遍历 */
        int front,rear;
        int Tmp;
        bool flag = true;
        front = rear = 0;
        Queue[rear++] = Root;
        while( front != rear ){
            /* 从队列中取出节点，判断是否为叶节点 */
            Tmp = Queue[front++];
            /* 节点左右子树都为空时为叶节点，输出 */
            if( T[Tmp].Left == -1 && T[Tmp].Right == -1 ){
                if( flag ){
                    printf( "%d", Tmp );
                    flag = false;
                }else printf( " %d",Tmp );
            }else{
                /* 将非空节点入队 */
                if( T[Tmp].Left != -1) Queue[rear++] =  T[Tmp].Left;
                if( T[Tmp].Right != -1) Queue[rear++] = T[Tmp].Right;
            }
            
        }
    }
}
