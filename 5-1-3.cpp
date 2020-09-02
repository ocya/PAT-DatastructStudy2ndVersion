#include <iostream>
#include <vector>

using namespace std;

int main( int argc, const char *argv[] ){

    int N, P;
    cin >> N >> P;
    vector<int> HashMap( P, -1 );
    int TempData;
    int Pos;
    for( int i = 0 ; i < N ; i++ ){
        cin >> TempData;
        Pos = TempData % P;
        while( HashMap[Pos] != -1 ){
            if( HashMap[Pos] == TempData ){
                break;
            }
            Pos += 1;
            Pos %= P;
        }
        HashMap[Pos] = TempData;
        if( i != 0 ) cout << " ";
        cout << Pos;
    }

    return 0;
}
