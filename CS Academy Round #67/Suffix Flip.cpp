#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 1e5 + 50;

int n;
char s[maxn];

int main( int argc , char * argv[] ){
	scanf( "%d%s" , & n , s + 1 );
	if( s[n] == '1' )
		puts( "1" );
	else
		puts( "0" );
	return 0;
}
