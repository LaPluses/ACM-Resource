#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
using ull = unsigned long long;

const int maxn = 1e5 + 50;

int n , m , deep[maxn] , lca[maxn][20];
vector < int > G[maxn];
vector < pair < int , int > > Path;
ull val[maxn];

ull gen(){
	ull ret = 0;
	for(int i = 0 ; i < 64 ; ++ i)
		if( rand() & 1 )
			ret |= (1ull << i);
	return ret;
}

void Dfs( int u , int fa = 0 ){
	for(auto v : G[u]){
		if( v == fa )
			continue;
		deep[v] = deep[u] + 1;
		lca[v][0] = u;
		Dfs( v , u );
	}
}

int QueryLca( int u , int v ){
	if( deep[u] < deep[v] )
		swap( u , v );
	for(int i = 19 ; i >= 0 ; -- i)
		if( deep[u] - (1 << i) >= deep[v] )
			u = lca[u][i];
	if( u == v )
		return u;
	for(int i = 19 ; i >= 0 ; -- i)
		if( lca[u][i] ^ lca[v][i] )
			u = lca[u][i] , v = lca[v][i];
	return lca[u][0];
}

void Dfs2( int u , int fa = 0 ){
	val[u] ^= val[fa];
	for(auto v : G[u]){
		if( v == fa ) continue;
		Dfs2( v , u );
	}
}

int main( int argc , char * argv[] ){
	scanf( "%d%d" , & n , & m );
	for(int i = 2 ; i <= n ; ++ i){
		int u , v;
		scanf( "%d%d" , & u , & v );
		G[u].emplace_back( v );
		G[v].emplace_back( u );
	}
	Dfs( 1 );
	for(int j = 1 ; j < 20 ; ++ j)
		for(int i = 1 ; i <= n ; ++ i)
			lca[i][j] = lca[lca[i][j - 1]][j - 1];
	for(int i = 1 ; i <= m ; ++ i){
		int u , v ;
		scanf( "%d%d" , & u , & v );
		if( deep[u] > deep[v] )
			swap( u , v );
		if( u == v ) continue;
		int lc = QueryLca( u , v );
		ull t = gen();
		if( lc == u ){
			val[u] ^= t;
			val[v] ^= t;
			Path.push_back( make_pair( v , u ) );
		}else{
			val[u] ^= t;
			val[v] ^= t;
			val[lc] ^= t;
			Path.push_back( make_pair( v , lc ) );
			Path.push_back( make_pair( u , lc ) );
		}
	}
	Dfs2( 1 );
	for(auto it : Path){
		ull c = val[it.first] ^ val[ lca[it.second][0] ];
		if( c ){
			printf( "%d %d\n" , it.first , it.second );
			puts( "No" );
			return 0;
		}
	}
	puts( "Yes" );
	return 0;
}