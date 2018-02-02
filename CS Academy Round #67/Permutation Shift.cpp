#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 100 + 15;

int p[maxn << 1] , n , ret[maxn];

int main( int argc , char * argv[] ){
	scanf( "%d" , & n );
	for(int i = 0 ; i < n ; ++ i)
		scanf( "%d" , p + i ) , p[n + i] = p[i];
	int ans = 0;
	for(int i = 0 ; i < n ; ++ i){
		int cnt = 0;
		for(int j = 0 ; j < n ; ++ j)
			if( p[i + j] == j + 1 )
				++ cnt;
		ans = max( ans , cnt );
	}
	printf( "%d\n" , ans );
	return 0;
}