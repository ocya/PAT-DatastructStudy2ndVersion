#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
bool Compare( int &a, int &b );
int main( int argc, const char *argv[] ){
    int N, M;
    cin >> N >> M;
    getchar();
    vector<int> Data( N );
    for( int i = 0; i < N; i++ )
        scanf( "%d", &Data[i] );
    sort( Data.begin(), Data.end(), Compare );
    for( int i = 0; i < M && i < N; i++ ){
        if( i != 0 ) cout << ' ';
        cout << Data[i];
    }
    return 0;
}

bool Compare( int &a, int &b ){
    return ( a > b );
}
