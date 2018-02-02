#include <cstdio>
#include <algorithm>


using namespace std;

const int maxn = 2e5 + 50;

int n , a[maxn] , m , ret[maxn][17] , f[1 << 16][17] , g[1 << 16][17];

void Clear( int t[1 << 16][17] ){
	for(int i = 0 ; i < 1 << m ; ++ i)
		for(int j = 0 ; j <= m ; ++ j)
			t[i][j] = 0;
}

void Solve( int l , int r ){
	if( l >= r ) return;
	int mid = l + r >> 1;
	if( 1ll * (mid - l + 1) * (r - mid) <= (1 << m) * m * m )
		for(int i = l ; i <= mid ; ++ i)
			for(int j = mid + 1 ; j <= r ; ++ j)
				++ ret[j][ __builtin_popcount( a[i] ^ a[j] )];
	else{
		Clear( f );
		for(int i = l ; i <= mid ; ++ i)
			++ f[a[i]][0];
		for(int i = 0 ; i < m ; ++ i){
			Clear( g );
			for(int j = 0 ; j < 1 << m ; ++ j)
				for(int k = 0 ; k <= i ; ++ k)
					if( f[j][k] ){
						g[j][k] += f[j][k];
						g[j ^ (1 << i)][k + 1] += f[j][k];
					}
			for(int j = 0 ; j < 1 << m ; ++ j)
				for(int k = 0 ; k <= i + 1 ; ++ k)
					f[j][k] = g[j][k];
		}
		for(int i = mid + 1 ; i <= r ; ++ i)
			for(int j = 0 ; j <= m ; ++ j)
				ret[i][j] += f[a[i]][j];
	}
	Solve( l , mid );
	Solve( mid + 1 , r );
}

int main( int argc , char * argv[] ){
	scanf( "%d%d" , & n , & m );
	for(int i = 0 ; i < n ; ++ i)
		scanf( "%d" , a + i );
	Solve( 0 , n - 1 );
	for(int i = 0 ; i < n ; ++ i){
		for(int j = 0 ; j <= m ; ++ j){
			if( j ) putchar( 32 );
			printf( "%d" , ret[i][j] ); 
		}
		puts( "" );
	}
	return 0;
}