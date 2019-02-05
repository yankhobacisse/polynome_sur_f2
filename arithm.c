#include "f2_poly.h"
#include "arithm.h"

uint64_t
pp_diviseur_premier(uint64_t n){
 
if( n==( uint64_t)0x0 || n==( uint64_t)0x1){
 	printf("0 ou n\n");
 	return n;
 }

 if(f2_poly_rem(n,( uint64_t)0x2)==0){
 	//printf("le nombre est divisible par 2\n");
 	return ( uint64_t)2;
 }
	

uint64_t d=( uint64_t)3;

while(n%d!=0 && d*d<n  ){
	d+=( uint64_t)2;
	//printf("rest ppd%"PRId64"\n",d );

}

if(d*d>n){
	d=n;
	//printf("rest ppd%"PRId64"\n",d );
}

return d;
}
