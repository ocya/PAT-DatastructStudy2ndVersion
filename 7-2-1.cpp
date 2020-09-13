#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool Compare( int &A, int &B );

int main( int argc, const char *argv[] ){

    int N, M;
    vector<int> PosA, NegA, PosB, NegB;
    int Value;
    cin >> N;
    for( int i = 0; i < N; i++ ){
        scanf( "%d", &Value );
        if( Value > 0 ) PosA.push_back( Value );
        else NegA.push_back( Value );
    }
    cin >> M;

    for( int i = 0; i < M; i++ ){
        scanf( "%d", &Value );
        if( Value > 0 ) PosB.push_back( Value );
        else NegB.push_back( Value );
    }    

    sort( PosA.begin(), PosA.end(), Compare );
    sort( PosB.begin(), PosB.end(), Compare );
    sort( NegA.begin(), NegA.end() );
    sort( NegB.begin(), NegB.end() );

    int Sum = 0;
    for( int i = 0; i < PosA.size() && i < PosB.size(); i++ ){
        Sum += PosA[i] * PosB[i];
    }
    for( int i = 0; i < NegA.size() && i < NegB.size(); i++ ){
        Sum += NegA[i] * NegB[i];
    }
    if( (NegA.empty() && PosB.empty()) || (PosA.empty() && PosB.empty() ) )
        Sum = 0;
    cout << Sum;
    return 0;
}


bool Compare( int &A, int &B ){
    return ( A > B );
}

