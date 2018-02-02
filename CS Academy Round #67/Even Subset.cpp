#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 50;

int n;
long long f[2] , g[2];

int main( int argc , char * argv[] ){
	scanf( "%d" , & n );
	f[1] = -(1ll << 60);
	for(int i = 1 ; i <= n ; ++ i){
		int x;
		scanf( "%d" , & x );
		g[0] = g[1] = -(1ll << 60);
		g[0] = max( f[0] , f[1] + x );
		g[1] = max( f[1] , f[0] + x );
		f[0] = g[0] , f[1] = g[1];
	}
	printf( "%lld\n" , f[0] );
	return 0;
}