#include <iostream>
#include <vector>

using namespace std;

double Caculate( double Num1, double Num2, char op );
int main( int argc, const char *argv[] ){

    vector<char> Op(4);
    Op[0] = '+',Op[1] = '-', Op[2] = '*', Op[3] = '/';
    vector<double> Number( 4 );
    for( int i = 0 ; i < 4 ; i++ )
        cin >> Number[i];
    double n1, n2, n3, n4, Result;
    char op1, op2, op3;
    double Temp1, Temp2;
    for( int i = 0 ; i < 4 ; i++ ){
        n1 = Number[i];
        for( int I = 0 ; I < 4 ; I++ ){
            op1 = Op[I];
            for( int j = 0 ; j < 4 ; j++ ){
                if( j != i ){
                    n2 = Number[j];
                    // Temp1 = Caculate( n1, n2, op1 );
                    for( int J = 0 ; J < 4 ; J++ ){
                        op2 = Op[J];
                        for( int k = 0 ; k < 4 ; k++ ){
                            if( k != i && k != j ){
                                n3 = Number[k];
                                // Temp2 = Caculate( Temp1, n3, op2 );
                                for( int K = 0 ; K < 4 ; K++ ){
                                    op3 = Op[K];
                                    for( int l = 0 ; l < 4 ; l++ ){
                                        if( l != i && l != j && l != k ){
                                            n4 = Number[l];
                                            // Result = Caculate( Temp2, n4, op3 );
                                            Temp1 = Caculate( n1, n2, op1 );
                                            Temp2 = Caculate( Temp1, n3, op2 );
                                            Result = Caculate( Temp2, n4, op3 );
                                            if( Result == 24 ){
                                                cout << "((" << n1 << op1 << n2 << ')' << op2 << n3 << ')' << op3 << n4;
                                                return 0;
                                            }
                                            Temp1 = Caculate( n2, n3, op2 );
                                            Temp2 = Caculate( n1, Temp1, op1 );
                                            Result = Caculate( Temp2, n4, op3 );
                                            if( Result == 24 ){
                                                cout << '(' << n1 << op1 << '(' << n2 << op2 << n3 << "))" << op3 << n4;
                                                return 0;
                                            }                                            
                                            Temp1 = Caculate( n1, n2, op1 );
                                            Temp2 = Caculate( n3, n4, op3 );
                                            Result = Caculate( Temp1, Temp2, op2 );
                                            if( Result == 24 ){
                                                cout << '(' << n1 << op1 << n2 << ')' << op2 << '(' << n3  << op3 << n4 << ')';
                                                return 0;
                                            }  
                                            Temp1 = Caculate( n2, n3, op2 );
                                            Temp2 = Caculate( Temp1, n4, op3 );
                                            Result = Caculate( n1, Temp2, op1 );
                                            if( Result == 24 ){
                                                cout  << n1 << op1 << "((" << n2 << op2 << n3 << ')' << op3 << n4 << ')';
                                                return 0;
                                            }
                                            Temp1 = Caculate( n3, n4, op3 );
                                            Temp2 = Caculate( n2, Temp1, op2 );
                                            Result = Caculate( n1, Temp2, op1 );
                                            if( Result == 24 ){
                                                cout << n1 << op1 << '(' << n2  << op2 << '(' <<  n3 << op3 << n4 << "))";
                                                return 0;
                                            }                                                                                                                                                                    
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "-1";
    return 0;
}

double Caculate( double Num1, double Num2, char op ){

    double Ret;
    switch( op ){
        case '+': Ret = Num1 + Num2; break;
        case '-': Ret = Num1 - Num2; break;
        case '*': Ret = Num1 * Num2; break;
        case '/': Ret = Num1 / Num2; break;
    }
    return Ret;
}
