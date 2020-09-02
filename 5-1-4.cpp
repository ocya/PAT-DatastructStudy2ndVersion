#include <iostream>
#include <vector>
#include <map>

using namespace std;


int Hash( string Key, int P );
int main( int argc, const char *argv[] ){

    int N, P;
    cin >> N >> P;
    getchar();
    vector<string> HashMap( P );

    string  Key;
    int Pos, NewPos;
    for( int i = 0 ; i < N ; i++ ){
        cin >> Key;
        Pos = NewPos = Hash( Key, P );
        // Conflict
        int ConflictCount = 0;
        while( HashMap[NewPos] != "" && HashMap[NewPos] != Key){
            if( ++ConflictCount%2 ){
                NewPos = Pos + (ConflictCount + 1) * (ConflictCount + 1) / 4;
                if( NewPos >= P ) NewPos %= P;
            }else{
                NewPos = Pos - ( ConflictCount * ConflictCount ) / 4;
                while( NewPos < 0 ) NewPos += P;
            }

        }
        
        HashMap[NewPos] = Key;
        if( i != 0 ) cout << ' ';
        cout << NewPos;
    }


    return 0;
}



int Hash( string Key, int P ){
    if( Key.length() > 3 ){
        Key = Key.substr( Key.length() - 3 );
    }
    int KeyValue = 0;
    int i = 0;
    while( Key[i] != '\0' ){
        KeyValue = ( KeyValue << 5 ) + (int)(Key[i] - 'A');
        i++;
    }
    return KeyValue % P;
    
}
