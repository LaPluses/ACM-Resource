#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

const int maxn = 1e5 + 50;

struct Segment{
	int l , r , y;

	friend bool operator < ( const Segment & a , const Segment & b ){
		return a.y < b.y || (a.y == b.y && a.l < b.l);
	}

}Seg[maxn];

int n , m , mx[maxn << 2];
pair < int , int > f[maxn][2];

int Update( int ql , int qr , int l , int r , int x , int o ){
	if( ql <= l && r <= qr ) mx[o] = max( mx[o] , x );
	else{
		int mid = l + r >> 1;
		if( ql <= mid ) Update( ql , qr , l , mid , x , o << 1 );
		if( qr > mid ) Update( ql , qr , mid + 1 , r , x , o << 1 | 1 );
	}
}

int Query( int l , int r , int x , int o ){
	int w = mx[o];
	if( l < r ){
		int mid = l + r >> 1;
		if( x <= mid ) w = max( w , Query( l , mid , x , o << 1 ) );
		else w = max( w , Query( mid + 1 , r , x , o << 1 | 1 ) );
	}
	return w;
}

int Search( int x , int y ){
	vector < pair < int , int > > vi;
	while( f[x][y].first ){
		vi.push_back( { x , y } );
		auto go = f[x][y];
		x = go.first;
		y = go.second;
	}
	for(auto it : vi)
		f[it.first][it.second] = { x , y };
	return y == 0 ? Seg[x].l : Seg[x].r;
}

int main( int argc , char * argv[] ){
	freopen( "Sample" , "r" , stdin );
	scanf( "%d%d" , & n , & m );
	for(int i = 1 ; i <= n ; ++ i)
		scanf( "%d%d%d" , & Seg[i].l , & Seg[i].r , & Seg[i].y );
	sort( Seg + 1 , Seg + n + 1 );
	for(int i = 1 ; i <= n ; ++ i){
		int a = Query( 1 , 100000 , Seg[i].l , 1 );
		int b = Query( 1 , 100000 , Seg[i].r , 1 );
		if( a )
			if( Seg[i].l - Seg[a].l <= Seg[a].r - Seg[i].l )
				f[i][0] = { a , 0 };
			else
				f[i][0] = { a , 1 };
		if( b )
			if( Seg[i].r - Seg[b].l <= Seg[b].r - Seg[i].r )
				f[i][1] = { b , 0 };
			else
				f[i][1] = { b , 1 };
		Update( Seg[i].l , Seg[i].r , 1 , 100000 , i , 1 );
	}
	for(int i = 1 ; i <= m ; ++ i){
		int x;
		scanf( "%d" , & x );
		int t = Query( 1 , 100000 , x , 1 );
		int ans = x;
		if( t ){
			int yt = 0;
			if( Seg[t].r - x < x - Seg[t].l )
				yt = 1;
			ans = Search( t , yt );
		}
		printf( "%d\n" , ans );
	}
	return 0;
}