#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main( int argc, const char *argv[] ){

    int N;
    cin >> N;
    vector<int> Count( 51, 0 );
    int Age;
    for( int i = 0; i < N; i++ ){
        scanf( "%d", &Age );
        Count[Age]++;
    }
    for( int i = 0; i < 51; i++ ){
        if( Count[i] != 0 ) printf( "%d:%d\n", i, Count[i] );
    }

    return 0;
}


