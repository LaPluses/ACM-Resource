#include <iostream>

using namespace std;

long long Solve( int n ){
	if( n == 0 ) return 0;
	long long num = 1ll * n * (n + 1) / 2;
	return ( 1 + 2 * num - 1 ) * num / 2;	
}

int main( int argc , char * argv[] ){
	int k;
	cin >> k;
	cout << Solve( k ) - Solve( k - 1 ) << endl;
	return 0;
}