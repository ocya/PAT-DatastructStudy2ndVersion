#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>


using namespace std;

int main( int argc, const char *argv[] ){

    int N;
    map<string, int> AccountMap;
    map<string, string> PasswordMap;
    cin >> N;
    getchar();
    
    char Order;
    string Number, Password;

    for( int i = 0 ; i < N ; i++ ){
        cin >> Order >> Number >> Password;
        switch( Order ){
            case 'L':
                if( AccountMap[Number] != 0 ){
                    if( PasswordMap[Number] == Password ) cout << "Login: OK\n";
                    else cout << "ERROR: Wrong PW\n";
                }else{
                    cout << "ERROR: Not Exist\n";
                }
                break;
            case 'N':
                if( AccountMap[Number] != 0 ){
                    cout << "ERROR: Exist\n";
                }else{
                    AccountMap[Number] += 1;
                    PasswordMap[Number] = Password;
                    cout << "New: OK\n";
                }
                break;
        }
    }


    return 0;
}
