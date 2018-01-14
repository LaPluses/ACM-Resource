#include <cstdio>

using namespace std;

const int mod = 1e9 + 7;

int n , k , x;

inline void ins( int & x , int y ){
	if( ( x += y ) >= mod )
		x -= mod;
}

int main( int argc , char * argv[] ){
	scanf( "%d%d%d" , & n , & k , & x );
	int f0 = 0 , f1 = 0;
	if( x == 1 ) f1 = 1;
	else f0 = 1;
	for(int i = 2 ; i <= n ; ++ i){
		int g0 = 0 , g1 = 0;
		ins( g0 , 1ll * f0 * ( k - 2 ) % mod );
		ins( g1 , f0 );
		ins( g0 , 1ll * f1 * ( k - 1 ) % mod );
		f0 = g0 , f1 = g1;
	}
	printf( "%d\n" , f1 );
	return 0;
}