#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 1e5 + 50;

int n , A[maxn] , K , OR[maxn][20] , AND[maxn][20] , MX[maxn][20] , MI[maxn][20] , Len[maxn];
priority_queue < int > p , q;
vector < int > add[maxn] , del[maxn];

int Queryor( int l , int r ){
	int z = Len[r - l + 1];
	return OR[l][z] | OR[r - (1 << z) + 1][z];
}

int Queryand( int l , int r ){
	int z = Len[r - l + 1];
	return AND[l][z] & AND[r - (1 << z) + 1][z];
}

int Querymx( int l , int r ){
	int z = Len[r - l + 1];
	return max( MX[l][z] , MX[r - (1 << z) + 1][z] );
}

int Querymi( int l , int r ){
	int z = Len[r - l + 1];
	return min( MI[l][z] , MI[r - (1 << z) + 1][z] );
}


int main( int argc , char * argv[] ){
	scanf( "%d%d" , & n , & K );
	Len[0] = -1;
	for(int i = 1 ; i <= n ; ++ i){
		Len[i] = Len[i >> 1] + 1;
		scanf( "%d" , A + i );
		OR[i][0] = AND[i][0] = MX[i][0] = MI[i][0] = A[i];
	}
	for(int j = 1 ; j < 20 ; ++ j)
		for(int i = 1 ; i + ( 1 << j ) - 1 <= n ; ++ i)
			OR[i][j] = OR[i][j - 1] | OR[i + (1 << j - 1)][j - 1] ,
			AND[i][j] = AND[i][j - 1] & AND[i + (1 << j - 1)][j - 1] ,
			MX[i][j] = max( MX[i][j - 1] , MX[i + (1 << j - 1)][j - 1] ) ,
			MI[i][j] = min( MI[i][j - 1] , MI[i + (1 << j - 1)][j - 1] ) ;
	for(int i = 1 ; i <= n ; ++ i){
		int pob = i , ret = -1;
		while( pob <= n ){
			int l = pob , r = n , ba = Queryor( i , l ) - Queryand( i , l );
			while( l < r ){
				int mid = l + r + 1 >> 1;
				if( Queryor( i , mid ) - Queryand( i , mid ) == ba )
					l = mid;
				else
					r = mid - 1;
			}
			int lft = pob , rht = l;
			while( lft < rht ){
				int mid = lft + rht + 1 >> 1;
				if( ( long long ) ba - ( long long ) Querymx( i , mid ) + ( long long ) Querymi( i , mid ) >= K )
					lft = mid;
				else
					rht = mid - 1;
			}
			if( ( long long ) ba - ( long long ) Querymx( i , lft ) + ( long long ) Querymi( i , lft ) >= K )
				ret = lft;
			pob = l + 1;
		}
		if( ~ret ) add[i].push_back( ret - i + 1 ) , del[ret].push_back( ret - i + 1 );
	}
	for(int i = 1 ; i <= n ; ++ i){
		for(auto && it : add[i]) p.push( it );
		while( !p.empty() && !q.empty() && p.top() == q.top() )
			p.pop() , q.pop();
		int ans = p.empty() ? -1 : p.top();
		printf( "%d\n" , ans );
		for(auto && it : del[i]) q.push( it );
	}
	return 0;
}