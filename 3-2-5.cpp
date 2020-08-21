#include <iostream>
#include <stack>

using namespace std;

int main( int argc, const char *argv[] ){

    int N1, N2;
    char Op;
    int Num;
    stack<int> S1, S2;
    cin >> N1 >> N2;
    if( N1 > N2 ) swap( N1, N2 );
    cin >> Op;
    while( Op != 'T' ){
        switch( Op ){
            case 'A' : 
                cin >> Num;
                if( S1.size() != N1 ){
                    S1.push( Num );
                }else{
                    if( S2.empty() ){
                        while( !S1.empty() ){
                            S2.push( S1.top() );
                            S1.pop();
                        }
                        S1.push( Num );
                    }else{
                        cout << "ERROR:Full" << endl;
                    }
                }
                break;
            case 'D':
                if( S1.empty() && S2.empty() ){
                    cout << "ERROR:Empty" << endl;
                }else if( S2.empty() && !S1.empty() ){
                    while( !S1.empty() ){
                        S2.push( S1.top() );
                        S1.pop();
                    }
                    cout << S2.top() << endl;
                    S2.pop();
                }else if( !S2.empty() ){
                    cout << S2.top() << endl;
                    S2.pop();
                }
                break;
            case 'T': break;

        }
        cin >> Op;

    }


    return 0;
}
