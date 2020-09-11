#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Student{
    string Id, Name;
    int Grade;
};

bool Compare( Student &S1, Student &S2 );
int C;
int main( int argc, const char *argv[] ){

    int N;
    cin >> N >> C;
    vector<Student> Stu;
    Student Temp;
    for( int i = 0; i < N; i++ ){
        cin >> Temp.Id >> Temp.Name >> Temp.Grade;
        Stu.push_back( Temp );
    }
    sort( Stu.begin(), Stu.end(), Compare );
    for( auto i : Stu ){
        printf( "%s %s %d\n",i.Id.c_str(), i.Name.c_str(), i.Grade );
    }
    

    return 0;
}



bool Compare( Student &S1, Student &S2 ){
    bool Ret;
    switch( C ){
        case 1: Ret = ( S1.Id < S2.Id ); break;
        case 2:
            if( S1.Name != S2.Name ) Ret = ( S1.Name < S2.Name );
            else Ret = (S1.Id < S2.Id);
            break; 
        case 3:
            if( S1.Grade != S2.Grade ) Ret = ( S1.Grade < S2.Grade );
            else Ret = (S1.Id < S2.Id);
            break; 
    }

    return Ret;
}

