#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int NextPrime( int M );

int main( int argc, const char *argv[] ){

    int N, M;
    cin >> M >> N;
    int TableSize = NextPrime( M );
    vector<int> HashMap( TableSize, -1 );

    int Data;
    int Pos, NewPos;
    for( int i = 0 ; i < N ; i++ ){
        cin >> Data;
        int ConflictCount = 0;
        Pos = NewPos = Data % TableSize;
        bool isFind = true;
        while ( HashMap[NewPos] != -1 && HashMap[NewPos] != Data ){
            ConflictCount++;
            NewPos = Pos + ConflictCount * ConflictCount;
            if( NewPos >= TableSize ) NewPos %= TableSize;
            if( NewPos == Pos ){
                isFind = false;
                break;
            }
        }
        if( i != 0 ) cout << ' ';
        if( isFind ){
            HashMap[NewPos] = Data;
            cout << NewPos;
        }else cout << '-';
    }



    return 0;
}
bool isPrime( int TableSize ){
    if( TableSize <= 1 ) return false;
    for( int i = 2 ; i <= sqrt( TableSize ) ; i++ ){
        if( TableSize % i == 0 ) return false;
    }
    return true;
}

int NextPrime( int M ){
    if( M == 1 ) return 2;
    int TableSize = ( M % 2 ) ? M + 2 : M + 1;
    while( !isPrime( TableSize ) ){
        TableSize += 2;
    }
    return TableSize;
}
