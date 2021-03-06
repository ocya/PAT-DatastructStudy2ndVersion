/* BST 实现 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MaxLength 31

typedef struct BNode *PtrToBNode;
struct BNode{
    char Name[MaxLength];
    int Count;
    PtrToBNode Left, Right;
};
typedef PtrToBNode Tree;

int N;
void LMRTraversal( Tree T );
Tree InsertBSTree( Tree T, char Data[] );
int main( int argc, const char *argv[]){
    
    Tree T = NULL ;
    char Data[MaxLength];
    scanf( "%d\n", &N );
    for( int i = 0 ; i < N ; i++ ){
        gets( Data );
        T = InsertBSTree( T, Data );
    }
    LMRTraversal( T );
    return 0;
}

Tree InsertBSTree( Tree T, char Data[] ){
    if( T == NULL ){
        PtrToBNode NewNode;
        NewNode = ( Tree )malloc(sizeof(struct BNode));
        NewNode->Count = 1;
        strcpy( NewNode->Name, Data );
        NewNode->Left = NewNode->Right = NULL;
        T = NewNode;
    }else{
        if( strcmp( T->Name, Data ) == 0 ) T->Count += 1;
        else if( strcmp( T->Name, Data ) > 0 ) T->Left = InsertBSTree( T->Left, Data );
        else T->Right = InsertBSTree( T->Right, Data );
    }
    return T;
}

void LMRTraversal( Tree T ){
    if( T != NULL ){
        LMRTraversal( T->Left );
        printf( "%s %.4f%%\n", T->Name, (float)T->Count * 100 / N );
        LMRTraversal( T->Right );
    }
}

/* 链表实现 */
/* 最大 N 测试点超时 */


// #include <stdio.h>
// #include <stdbool.h>
// #include <stdlib.h>
// #include <string.h>

// #define MaxLength 31

// typedef struct LNode *PtrToLNode;
// struct LNode{
//     char Name[MaxLength];
//     int Count;
//     PtrToLNode Next;
// };
// typedef PtrToLNode LinkList;

// void InsertLinkList( LinkList L, char Tmp[] );



// int main( int argc, const char *argv[]){
//     int N;
//     char Tmp[MaxLength];
//     LinkList L = ( LinkList )malloc(sizeof(struct LNode));
//     L->Next = NULL; /* 非常重要的一步，未初始化导致出现 bug  */
//     PtrToLNode Tail;
//     scanf( "%d\n", &N );
//     for( int i = 0 ; i < N ; i++ ){
//         gets( Tmp ); /* gets( ) 函数会读取缓冲区中的 '\n'，因此后面不能再用 getschar( ) ，重要 */
//         InsertLinkList( L, Tmp );
//     } 
//     for( Tail = L->Next ; Tail ; Tail = Tail->Next )
//         printf( "%s %.4f%%\n", Tail->Name, (float)Tail->Count*100/N );
       
// }

// void InsertLinkList( LinkList L, char Tmp[] ){
//     PtrToLNode P1,P2;
//     PtrToLNode NewNode;
//     P1 = L;
//     P2 = P1->Next;

//     for(  ; P2 != NULL ; P2 = P2->Next ){
//         if( strcmp( P2->Name, Tmp ) == 0 ){/* 遇到匹配的字符串，数量加一 */
//             P2->Count += 1;
//             break;
//         }else if( strcmp( P2->Name, Tmp ) > 0 ){/* 指针所在位置的字符串大于目标字符串，且前面没有匹配的字符串，则在此处插入新的节点 */
//             NewNode = (PtrToLNode)malloc(sizeof(struct LNode));
//             strcpy( NewNode->Name, Tmp );
//             NewNode->Count = 1;
//             NewNode->Next = P2;
//             P1->Next = NewNode;
//             break;
//         }
//         P1 = P2;
//     }
//     if( P2 == NULL ){ /* 当遍历到最后，没有匹配字符串，且目标字符串比所有链表中的字符串都要大，则在链表尾部插入新的节点 */
//         NewNode = (PtrToLNode)malloc(sizeof(struct LNode));
//         strcpy( NewNode->Name, Tmp );
//         NewNode->Count = 1;
//         NewNode->Next = NULL;
//         P1->Next = NewNode;
//     }   

// }
