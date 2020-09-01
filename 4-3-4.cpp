#include <iostream>
#include <vector>
#include <deque>


using namespace std;

struct Node{
    int K1, K2;
    int LeftChild, RightChild;
};

bool is_BST( vector<Node> &Tree, int Root, int &Min, int &Max );
bool isBST( vector<Node> &Tree, int Root );
bool isHeap( vector<Node> &Tree, int Root );
void PreOrderTraversal( vector<Node> &Tree, int Root );
void LevelOrderTraversal( vector<Node> &Tree, int Root );
int main( int argc, const char *argv[] ){

    
    vector<Node> Tree;
    int N;
    cin >> N;
    Tree.resize( N );
    vector<bool> isVisited( N, false )  ;
    for( int i = 0 ; i < N ; i++ ){
        cin >> Tree[i].K1 >> Tree[i].K2 >> Tree[i].LeftChild >> Tree[i].RightChild;
        if( Tree[i].LeftChild != -1 ) isVisited[ Tree[i].LeftChild ] = true;
        if( Tree[i].RightChild != -1 ) isVisited[ Tree[i].RightChild ] = true;
    }

    int root = -1;
    for( int i = 0 ; i < N ; i++ ){
        if( isVisited[i] == false ){
            root = i;
            break;
        }
    }
    // LevelOrderTraversal( Tree, root );
    // PreOrderTraversal( Tree, root );
    // if( isBST( Tree, root ) ) cout << "BST" << endl;
    // else cout << "Not BST" << endl;
    // if( isHeap( Tree, root ) ) cout << "Heap" << endl;
    // else cout << "Not Heap" << endl;
    cout << ( isBST( Tree, root ) && isHeap( Tree, root ) ? "YES" : "NO" ) << endl; 

    return 0;
}

// K2 is the value of heap

bool isHeap( vector<Node> &Tree, int Root ){
    if( Root != -1 ){
        int Left, Right;
        Left = Tree[Root].LeftChild;
        Right = Tree[Root].RightChild;
        if( Left == -1 && Right == -1 ) return true;
        if( Left != -1 && Right != -1 ){
            if( Tree[Root].K2 < Tree[Left].K2 && Tree[Root].K2 < Tree[Right].K2 ) 
                return (isHeap( Tree, Left ) && isHeap( Tree, Right ));
            else 
                return false;
        }
        if( Left != -1 ){
            if( Tree[Root].K2 < Tree[Left].K2 ) 
                return isHeap( Tree, Left );
            else 
                return false;
        }
        if( Right != -1 ){
            if( Tree[Root].K2 < Tree[Right].K2 ) 
                return isHeap( Tree, Right );
            else 
                return false;
        }
    }
    return false;

}


// K1 is the value of BST
bool isBST( vector<Node> &Tree, int Root){
   int Min, Max;
   Min = Max = -1;
   return is_BST( Tree, Root, Min, Max );
}

bool is_BST( vector<Node> &Tree, int Root, int &Min, int &Max ){
    int lmin, lmax, rmin, rmax;
    bool flag_left, flag_right;
    if( Root == -1 ) return true;
    int left, right;
    left =  Tree[Root].LeftChild;
    right = Tree[Root].RightChild;
    if( left == -1 && right == -1 ){
        Min = Max = Tree[Root].K1;
        return true;
    }
    flag_left = flag_right = false;
    if((left != -1 &&
        is_BST( Tree, left, lmin, lmax)&&
        Tree[Root].K1 >lmax ) ||
        left == -1 ){
            flag_left = true;
    }else return false;

    if((right != -1 &&
        is_BST( Tree, right, rmin, rmax ) &&
        Tree[Root].K1 < rmin ) ||
        right == -1 ){
            flag_right = true;
        }else return false;
    if( flag_right && flag_left ){
        if( left != -1 ) Min = lmin;
        else Min = Tree[Root].K1;
        if( right != -1 ) Max = rmax;
        else Max = Tree[Root].K1;
        return true;
    }
    return false;
}

void PreOrderTraversal( vector<Node> &Tree, int Root ){
    if( Root != -1 ){
        int Left, Right;
        Left = Tree[Root].LeftChild;
        Right = Tree[Root].RightChild;         
        cout << Tree[Root].K1 << "  " << Tree[Root].K2 << endl;
        if( Left != -1 ) PreOrderTraversal( Tree, Left );
        if( Right != -1 ) PreOrderTraversal( Tree, Right );
        
    }
}

void LevelOrderTraversal( vector<Node> &Tree, int Root ){
    deque<Node> Queue;
    if( Root != -1 ){
        cout << Tree[Root].K1 << "  " << Tree[Root].K2 << endl;
        Queue.push_back( Tree[Root] );
        while( !Queue.empty() ){
            Node Tmp = Queue[0]; Queue.pop_front();
            if( Tmp.LeftChild != -1 ){
                cout << Tree[Tmp.LeftChild].K1 << "  " << Tree[Tmp.LeftChild].K2 << endl;
                Queue.push_back( Tree[Tmp.LeftChild] );                
            }
            if( Tmp.RightChild != -1 ){
                cout << Tree[Tmp.RightChild].K1 << "  " << Tree[Tmp.RightChild].K2 << endl;
                Queue.push_back( Tree[Tmp.RightChild] );                
            }            
        }
    }
}
