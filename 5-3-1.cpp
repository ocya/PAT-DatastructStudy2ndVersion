#include <iostream>
#include <string>
#include <map>


using namespace std;

int main( int argc, const char *argv[] ){

    int N, K;
    map<string, int> HashMap;
    cin >> N >> K;
    getchar();

    char Id[19];
    int Distance;
    for( int i = 0 ; i < N ; i++ ){
        scanf( "%s %d", Id, &Distance );
        if( Distance < K ) Distance = K;
        HashMap[Id] += Distance;
    }
    
    int M;
    cin >> M;
    getchar();

    for( int i = 0 ; i < M ; i++ ){
        scanf( "%s", Id );
        getchar();
        if( HashMap[Id] != 0 ){
            printf( "%d\n", HashMap[Id] );
        }else printf( "No Info\n" );
    }

    return 0;
}
