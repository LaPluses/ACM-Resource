#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>
#include <ctime>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

double f[605][605] , g[605][605];

void Deal( int lena , int lenb , double p[605][605] ){
	for(int i = 0 ; i <= lena ; ++ i)
		for(int j = 0 ; j <= lena + lenb ; ++ j)
			p[i][j] = 0;
	p[0][0] = 0.5;
	double sum = 0.5;
	for(int i = 1 ; i < lenb ; ++ i) p[0][i] = p[0][i - 1] * 0.5 , sum += p[0][i];
	p[0][lenb] = 1. - sum;
	for(int i = 1 ; i < lena ; ++ i)
		for(int j = i ; j <= i + lenb ; ++ j){
			p[i][j] = p[i][j - 1] + p[i - 1][j - 1];
			if( j != i + lenb ) p[i][j] *= 0.5;
		}
}

vector < gp_hash_table < int , double > > Solve( int * a , int from , int to ){
	vector < gp_hash_table < int , double > > ret( to - from + 1 );
	if( to == from ){
		ret[0].insert( make_pair( from , 1.0 ) );
		return ret;
	}
	int mid = from + to >> 1;
	auto lft = Solve( a , from , mid );
	auto rht = Solve( a , mid + 1 , to );
	int le = 0 , re = 0 , cur = 0;
	while( le < lft.size() || re < rht.size() ){
		if( le == lft.size() )
			ret[cur ++] = rht[re ++];
		else if( re == rht.size() )
			ret[cur ++] = lft[le ++];
		else if( a[lft[le].begin()->first] < a[rht[re].begin()->first] )
			ret[cur ++] = lft[le ++];
		else if( a[lft[le].begin()->first] > a[rht[re].begin()->first] )
			ret[cur ++] = rht[re ++];
		else{
			int lstle = le;
			int lstre = re;
			while( lstle < lft.size() && a[lft[lstle].begin()->first] == a[lft[le].begin()->first] )
				++ lstle;
			while( lstre < rht.size() && a[rht[lstre].begin()->first] == a[rht[re].begin()->first] )
				++ lstre;
			int lena = lstle - le;
			int lenb = lstre - re;
			Deal( lena , lenb , f );
			Deal( lenb , lena , g );
			for(int i = 0 ; i < lena ; ++ i)
				for(int j = i ; j <= i + lenb ; ++ j)
					for(auto && it : lft[i + le])
						ret[j + cur][it.first] += it.second * f[i][j];
			for(int i = 0 ; i < lenb ; ++ i)
				for(int j = i ; j <= i + lena ; ++ j)
					for(auto && it : rht[i + re])
						ret[j + cur][it.first] += it.second * g[i][j];
			le = lstle;
			re = lstre;
			cur += lena + lenb;
		}
	}
	return ret;
}

int n , a[666];
double ans[666];

int main( int argc , char * argv[] ){
	scanf( "%d" , & n );
	for(int i = 1 ; i <= n ; ++ i)
		scanf( "%d" , a + i );
	auto ret = Solve( a , 1 , n );
	for(int i = 0 ; i < n ; ++ i)
		for(auto && it : ret[i])
			ans[it.first] += 1.0 * (i + 1) * it.second;
	for(int i = 1 ; i <= n ; ++ i)
		printf( "%.9f\n" , ans[i] );
	return 0;
}