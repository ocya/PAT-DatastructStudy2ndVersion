#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool isPrime( long long N );
int main( int argc, const char *argv[] ){

    vector<int> Coefficient, Exponent;
    long long N, M;
    cin >> N;
    M = N;
    if( N == 1 ){
        cout << "1=1";
        return 0;
    }
    if( isPrime( N ) ){
        cout << N << "=" << N;
        return 0;
    }else{
        for( int i = 2 ; i <= N  ; i++ ){
            if( isPrime( i ) ){
                int Count = 0;
                while( N / i * i == N ){
                    N /= i;
                    Count++;
                }
                if( Count != 0 ){
                    Coefficient.push_back( i );
                    Exponent.push_back( Count );
                }
                if( N == 1 ) break;
            }
        }
    }
    cout << M << '=';
    for( int i = 0 ; i < Coefficient.size() ; i++ ){
        if( i != 0 ) cout << '*';
        cout << Coefficient[i];
        if( Exponent[i] != 1 ) cout << '^' << Exponent[i];
    }



    return 0;
}

bool isPrime( long long N ){
    if( N <= 1 ) return false;
    if( N == 2 ) return true;
    if( N % 2 == 0 ) return false;
    for( int i = 3 ; i <= sqrt( N ) ; i += 2 ){
        if( N % i == 0 ) return false;
    }
    return true;
}
