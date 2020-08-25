
#include<math.h>
#include<sstream>
#include<iostream>
using namespace std;
stringstream ss;//string 流存数据，这样可以一个一个空格的读取 
int flag;//错误标志 
double f()//运算函数 
{
    char c[9];//数据不会超过九位数 
    if (!(ss >> c))flag = 1;  //流不进去说明数据不够。错误 
    if (c[1] == '\0'){//只有一位，可能会是运算符 
        double numb1, numb2;
        switch (c[0])
        {
        case '+':return f() + f(); break;
        case '-':return f() - f(); break;
        case '*':return f()*f(); break;
        case '/'://除号要避免非零错误 和准确的错误 
            numb1 = f(); numb2 = f();
            if (fabs(numb2-0.0)<0.0000001){//精度错误 
                flag = 1;
                return 0.0;
            }
            else return numb1 / numb2; break;
        }
        //不是符号是数的话不影响。后面会return 
    }
    return atof(c);//把运算数返回 
}
int main()
{
    string s;
    flag = 0;
    getline(cin, s);//整行读入 
    ss << s;//存进流里面 
    double n = f();//算出结果 
    if (flag)cout << "ERROR" << endl;
    else printf("%.1lf\n", n);
}

/*
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>


using namespace std;

stringstream SS;
bool isError = false;
double Fun();
int main( int argc, const char *argv[] ){

    string S;
    getline( cin, S );
    SS << S;
    double X = Fun();
    if( isError ) printf( "ERROR\n" );
    else printf( "%.1f", X );
    return 0;
}

double Fun(){
    char c[9];
    if( !(SS >> c) ) isError = true;
    if( c[1] == '\0' ){
        double A, B;
        switch( c[0] ){
            case '+': return Fun() + Fun() ; 
            case '-': return Fun() - Fun();
            case '*': return Fun() * Fun();
            case '/':
                A = Fun(); B = Fun();
                if( fabs( B - 0.0 ) < 0.0000001 ){
                    isError = true;
                    return 0.0;
                }else return A / B; break;
        }
    }
    return atof( c );
}







*/
