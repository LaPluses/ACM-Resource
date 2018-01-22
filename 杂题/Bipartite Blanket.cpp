#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int n , m , f[1 << 20] , g[1 << 20] , a[20] , b[20] , lft[20] , rht[20] , K;
char s[22];
vector < int > ra , rb;

int main( int argc , char * argv[] ){
	scanf( "%d%d" , & n , & m );
	for(int i = 0 ; i < n ; ++ i){
		scanf( "%s" , s );
		for(int j = 0 ; j < m ; ++ j) 
			if( s[j] == '1' ) 
				lft[i] |= (1 << j), 
				rht[j] |= (1 << i);
	}
	for(int i = 0 ; i < n ; ++ i) scanf( "%d" , a + i );
	for(int i = 0 ; i < m ; ++ i) scanf( "%d" , b + i );
	scanf( "%d" , & K );
	for(int i = 0 ; i < 1 << n ; ++ i){
		int flag = 1 , val = 0 , dj = 0;
		for(int j = 0 ; j < n ; ++ j)
			if( i >> j & 1 )
				flag &= f[i &~ (1 << j)],
				dj |= lft[j],
				val += a[j];
		flag &= ( __builtin_popcount( dj ) >= __builtin_popcount( i ) );
		f[i] = flag;
		if( flag ) ra.push_back( val );
	}
	for(int i = 0 ; i < 1 << m ; ++ i){
		int flag = 1 , val = 0 , dj = 0;
		for(int j = 0 ; j < m ; ++ j)
			if( i >> j & 1 )
				flag &= g[i &~ (1 << j)],
				dj |= rht[j],
				val += b[j];
		flag &= ( __builtin_popcount( dj ) >= __builtin_popcount( i ) );
		g[i] = flag;
		if( flag ) rb.push_back( val );
	}
	sort( ra.begin() , ra.end() );
	sort( rb.begin() , rb.end() , greater < int >() );
	long long ans = 0;
	for(int i = 0 , j = 0 ; i < ra.size() ; ++ i){
		while( j < rb.size() && ( unsigned int )ra[i] + ( unsigned int )rb[j] >= K )
			++ j;
		ans += j;
	}
	printf( "%lld\n" , ans );
	return 0;
}