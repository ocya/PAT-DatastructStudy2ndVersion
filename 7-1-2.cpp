#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main( int argc, const char *argv[] ){

    int N;
    cin >> N;
    vector<int> SortedData( N ), RawData( N );
    for( int i = 0; i < N; i++ )
        cin >> RawData[i];
    for( int i = 0; i < N; i++ )
        cin >> SortedData[i];
    int PartSortedIdx, UnsortedIdx;
    //注意这里的 <= 比较运算符，如果是 < 测试点4会报错
    for( PartSortedIdx = 0; PartSortedIdx < N - 1 && SortedData[PartSortedIdx] <= SortedData[PartSortedIdx+1]; PartSortedIdx++ );
    for( UnsortedIdx = PartSortedIdx+1; UnsortedIdx < N && SortedData[UnsortedIdx] == RawData[UnsortedIdx]; UnsortedIdx++ );
    if( UnsortedIdx == N ){
        cout << "Insertion Sort\n";
        sort( RawData.begin(), RawData.begin() + PartSortedIdx + 2 );
    }else{
        cout << "Merge Sort\n";
        int MergeStepLength = 1;
        bool isSame = false;
        while( !isSame ){
            if( SortedData == RawData )
                isSame = true;

            MergeStepLength *= 2;
            int i;
            for( i = 0; i < N / MergeStepLength; i++ )
                sort( RawData.begin() + i*MergeStepLength, RawData.begin() + ( i + 1 )*( MergeStepLength ) );  
            sort( RawData.begin() + i*MergeStepLength, RawData.end() );

        }

    } 


    for( int i = 0; i < N; i++ ){
        if( i != 0 ) cout << ' ';
        cout << RawData[i];
    }

    return 0;
}

/*

10
3 1 2 8 7 5 9 4 0 6
1 3 2 8 5 7 4 9 0 6


*/
