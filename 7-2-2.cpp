#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool Compare( int &A, int &B );

int main( int argc, const char *argv[] ){

    int N;
    int A[101], B[101];
    cin >> N;
    for( int i = 0; i < N; i++ )
        cin >> A[i];
    for( int i = 0; i < N; i++ )
        cin >> B[i];
    int OrderedIdx, UnOrderedIdx;
    for( OrderedIdx = 0; OrderedIdx < N-1 && B[OrderedIdx] <= B[OrderedIdx+1]; OrderedIdx++ );
    for( UnOrderedIdx = OrderedIdx+1; UnOrderedIdx < N && A[UnOrderedIdx] == B[UnOrderedIdx]; UnOrderedIdx++ );
    if( UnOrderedIdx == N ){
        cout << "Insertion Sort\n";
        sort( B, B+OrderedIdx+2 );     
    }else{
        cout << "Heap Sort\n";
        for( UnOrderedIdx = N - 1; UnOrderedIdx > 0 && B[UnOrderedIdx] > B[UnOrderedIdx-1]; UnOrderedIdx-- );
        int Temp = B[UnOrderedIdx];
        B[UnOrderedIdx] = B[0];
        B[0] = Temp;
        int Parent, Child;
        for( Parent = 0; Parent*2+1 < UnOrderedIdx; Parent = Child ){
            Child = Parent*2 + 1;
            if( Child != UnOrderedIdx - 1 && B[Child] < B[Child+1] )
                Child++;
            if( B[Child] < Temp ) break;
            else B[Parent] = B[Child];
        }
        B[Parent] = Temp;
    }

    for( int i = 0; i < N; i++ ){
        if( i != 0 ) cout << ' ';
        cout << B[i];
    }

    return 0;
}


bool Compare( int &A, int &B ){
    return ( A > B );
}

