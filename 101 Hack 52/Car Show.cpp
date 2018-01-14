#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

const int maxn = 1e5 + 50;

using namespace std;

int n , Q , A[maxn] , cnt[maxn * 10] , rht[maxn];
long long ans[maxn];
vector < pair < int , int > > Ask[maxn];

struct Node{
	int l , r;
	long long sum , lzy;

	void ins( long long x ){
		lzy += x;
		sum += x * ( r - l + 1 );
	}
}tree[maxn << 2];

void Build( int l , int r , int o ){
	tree[o].l = l , tree[o].r = r;
	if( l < r ){
		int mid = l + r >> 1;
		Build( l , mid , o << 1 );
		Build( mid + 1 , r , o << 1 | 1 );
	}
}

void push_up( int o ){
	tree[o].sum = tree[o << 1].sum + tree[o << 1 | 1].sum;
}

void push_down( int o ){
	if( tree[o].lzy ){
		tree[o << 1].ins( tree[o].lzy );
		tree[o << 1 | 1].ins( tree[o].lzy );
		tree[o].lzy = 0;
	}
}

void Modify( int ql , int qr , int x , int o ){
	int l = tree[o].l , r = tree[o].r;
	if( ql <= l && r <= qr ) tree[o].ins( x );
	else{
		int mid = l + r >> 1;
		push_down( o );
		if( ql <= mid ) Modify( ql , qr , x , o << 1 );
		if( qr > mid ) Modify( ql , qr , x , o << 1 | 1 );
		push_up( o );
	}
}

long long Query( int ql , int qr , int o ){
	int l = tree[o].l , r = tree[o].r;
	if( ql <= l && r <= qr ) return tree[o].sum;
	else{
		int mid = l + r >> 1;
		long long sum = 0;
		push_down( o );
		if( ql <= mid ) sum += Query( ql , qr , o << 1 );
		if( qr > mid ) sum += Query( ql , qr , o << 1 | 1 );
		return sum;
	}
}

int main( int argc , char * argv[] ){
	scanf( "%d%d" , & n , & Q );
	for(int i = 1 ; i <= n ; ++ i) scanf( "%d" , A + i);
	Build( 1 , n , 1 );
	for(int i = 1 , j = 1 ; i <= n ; ++ i){
		while( j <= n && cnt[A[j]] == 0 ){
			cnt[A[j]] = 1;
			++ j;
		}
		rht[i] = j - 1;
		cnt[A[i]] = 0;
		Modify( i , rht[i] , 1 , 1 );
	}
	for(int i = 1 ; i <= Q ; ++ i){
		int l , r ;
		scanf( "%d%d" , & l , & r );
		Ask[l].push_back( { r , i } );
	}
	for(int i = 1 ; i <= n ; ++ i){
		for(auto && it : Ask[i]) ans[it.second] = Query( 1 , it.first , 1 );
		Modify( i , rht[i] , -1 , 1 );
	}
	for(int i = 1 ; i <= Q ; ++ i)
		printf( "%lld\n" , ans[i] );
	return 0;
}