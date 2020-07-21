#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* 采用链表实现 */
typedef struct DataNode *LinkList;
struct DataNode{
    int Coefficient;
    int Exponential;
    LinkList Next;
};

int main( int argc, const char *argv[]){
    /* 定义链表头结点 */
    LinkList L = ( LinkList )malloc(sizeof(struct DataNode ));
    LinkList Tail = L;
    LinkList Node;
    bool Space = true;
    int C,E;
    while( 1 ){
        scanf( "%d %d", &C, &E );
        if( E == 0 ) break; /* 当读取到系数为 0 时，结束循环不作处理 */
        C = C * E;
        E -= 1;
        /* 在链表中插入求导后的链表结果 */
        Node = ( LinkList )malloc(sizeof(struct DataNode));
        Node->Coefficient = C;
        Node->Exponential = E;
        Node->Next = NULL;
        Tail->Next = Node;
        Tail = Tail->Next;
    }
    /* 链表为空，则表示输入为 常数项 或 0多项式 */
    if( L->Next == NULL ) printf( "0 0" );
    /* 依次输出保存在链表中的求导结果 */
    for( Tail = L->Next ; Tail ; Tail = Tail->Next ){
        if( Space ){
            Space = false;
             printf( "%d %d", Tail->Coefficient, Tail->Exponential );
        }else printf( " %d %d",Tail->Coefficient, Tail->Exponential );
    }


    return 0;
}

