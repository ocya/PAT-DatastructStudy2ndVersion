/*

进阶实验2-3.3 两个有序链表序列的交集 (20分)

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct LNode *PtrToLNode;
struct LNode{
    int Data;
    PtrToLNode Next;
};
typedef PtrToLNode List;

void BuildList( List L );
int main( int argc, const char *argv[]){
    bool flag = true; /* 输出格式控制，消除结尾多余空格 */
    int Tmp; /* 第二个链表数据 */
    PtrToLNode P1,P2,Tail,NewNode;
    List L1,L2;
    L1 = (List)malloc(sizeof(struct LNode)); 
    Tail = L2 = (List)malloc(sizeof(struct LNode));

    
    BuildList( L1 ); /* 同BuildList函数构造 */
    getchar(); /* 读取缓冲区中的 ‘ \n ’ 控制符 */
    while(1){ /* 对于第二列数据，不需要构建链表，对读入的每一个数据和 L1 做比对 */
        scanf("%d",&Tmp);
        if( Tmp == -1 ) break; /* ‘链表’结尾，跳出循环 */
        for( P1 = L1->Next ; P1 ; P1 = P1->Next){ /* 遍历第一个链表，由于序列为增序，确保遍历指针不会回溯 */
            if( P1->Data == Tmp ){ /* 将交集元素插入到 L2 链表中 */
                NewNode = (PtrToLNode)malloc(sizeof(struct LNode)); 
                NewNode->Data = Tmp;
                Tail->Next = NewNode;
                Tail = Tail->Next;
                L1 = P1; /* 增序序列，则将表头指针移动到当前的交集元素所在位置，新的交集元素必然在该位置的后面 */
                break; /* 重要一步 */
            }else if( P1->Data > Tmp ) break; /* 当且仅当 P1->Data 小于 Tmp 时才 向后移动 P1 指针 */
        }
    }
    Tail->Next = NULL; /* 尾指针处理 */
    if( L2->Next == NULL ) printf("NULL");
    for( P2 = L2->Next ; P2 ; P2 = P2->Next ){
        if( flag ){
            flag = false;
            printf("%d",P2->Data);
        }else
            printf(" %d",P2->Data);
    }
    return 0;
}

void BuildList( List L ){
    PtrToLNode Tail,NewNode;
    Tail = L ;
    while( 1 ){
        NewNode = (PtrToLNode)malloc(sizeof(struct LNode));
        scanf("%d",&(NewNode->Data));
        if( NewNode->Data == -1 ) break;
        Tail->Next = NewNode;
        Tail = Tail->Next;   
    }
    Tail->Next = NULL; 
}

