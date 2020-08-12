#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool isMirror;
vector<int> Pre;
vector<int> Post;

void GetPost( int Root, int Tail ){
    if( Root > Tail ) return;
    int i = Root + 1, j = Tail;
    if( !isMirror ){
        while( i <= Tail && Pre[Root] > Pre[i] ) i++;
        while( j > Root && Pre[Root] <= Pre[j] ) j--;
    }else{
        while( i <= Tail && Pre[Root] <= Pre[i] ) i++;
        while( j > Root && Pre[Root] > Pre[j] ) j--;        
    }
    if( i - j != 1 ) return;
    GetPost( Root + 1, j );
    GetPost( i, Tail );
    Post.push_back( Pre[Root] );
}

int main( int argc, const char *argv[] ){

    int N;
    cin >> N;
    Pre.resize( N );
    for( int i = 0 ; i < N ; i++ ){
        cin >> Pre[i];
    }
    GetPost( 0, N-1 );
    if( Post.size() != N ){
         isMirror = true;
         Post.clear();
         GetPost( 0, N-1 );
    }
    
    if( Post.size() != N ){
        cout << "NO";
    } else{
        cout << "YES" << endl;
        cout << Post[0];
        for( int i = 1 ; i < N ; i++ )
            cout << ' ' << Post[i];
    } 

    return 0;
}
