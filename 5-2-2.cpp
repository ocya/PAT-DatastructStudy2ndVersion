#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>


using namespace std;


int main( int argc, const char *argv[] ){

    int N;
    map<string, int> HashMap;
    cin >> N;
    getchar();

    int Max = -1;
    string S;
    for( int i = 0 ; i < 2*N ; i++ ){
        cin >> S;
        HashMap[S] += 1;
        if( HashMap[S] > Max ) Max = HashMap[S];
    }
    
    vector<string> Ans;
    for( auto i = HashMap.begin() ; i != HashMap.end() ; i++ ){
        if( i->second == Max ) Ans.push_back( i->first );
    }
    sort( Ans.begin(), Ans.end() );
    cout << Ans[0] << ' ' << Max;
    if( Ans.size() != 1 ){
        cout << ' ' << Ans.size();
    }
    
    return 0;
}
