#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main( int argc, const char *argv[] ){

    int D, P;
    cin >> D >> P;
    vector<int> Resoution, NextRound;
    Resoution.push_back( D );
    Resoution.push_back( 0 );
    for( int i = 0 ; i < P - 2 ; i++ ){
        NextRound.resize( Resoution.size() );
        sort( Resoution.begin(), Resoution.end() );
        int Median = Resoution.size()/2 + Resoution.size()%2 - 1;
        int Sum = 0;
        for( int j = 0 ; j < Resoution.size() ; j++ ){
            if( j <= Median ){
                NextRound[j] = Resoution[j] + 1;
                Sum += NextRound[j];
            }else NextRound[j] = 0;
        }
        NextRound.push_back( D - Sum );
        Resoution = NextRound;
        // for( auto i : Resoution )
        //     cout << i << ' ';
        // cout << endl;
    }
    cout << Resoution[P-1];

    return 0;
}
