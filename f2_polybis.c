#include <stdio.h>
#include <stdlib.h>
#include "f2_poly.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "arithm.h"
f2_deg_t f2_poly_deg(f2_poly_t p)
{
   	f2_deg_t degre=0;
   	f2_poly_t tmp=p;
   	//on parcours du poids fort au poids faible
   	//jusuq'à trouvé le premier valeur
   	// et on le retourne
    int i;
    for(i=63; i>=0; i--)
    {

        if(((tmp>>i)&(0x1))==1)
        {
            degre=( uint8_t)i;
            break;
        }
    }
    return degre;
}
f2_deg_t f2_poly_deg_bis(f2_poly_t p)
{
   	f2_deg_t degre=0;
    f2_poly_t tmp=p;
    //on parcours du poids fort au poids faible
   	//jusuq'à trouvé le premier valeur
   	// et on le retourne
    int i;
    for(i=63; i>=0; i--)
    {

        if(((( uint64_t)0x1<<i)&tmp))
        {
            degre=( uint8_t)i;
            break;
        }
    }
    return degre;
}

int f2_poly_print(f2_poly_t p, char x, FILE * f)
{
// écriture polynomiale usuelle, avec pour variable le second argument
    f2_deg_t degre=f2_poly_deg(p);
    int i;
    for(i=degre; i>=0; i--)
    {
	//test si le i eme bit vaut 1
        int tmp=((p>>(uint64_t)i)&(0x1))==1;
        if(i==0 && tmp&& degre!=0)
        {
            printf("+1");

        }
        else if(i==0 && tmp&& degre==0)
            printf("1");
        else if(tmp&& i>=1&&i!=degre)
        {
            printf("+ %c^%d ",x,i);
        }
        else if(tmp&& i==degre)
        {
            printf("%c^%d ",x,i);
        }

    }
    printf("\n");
    return 1;

}
int
f2_poly_div(f2_poly_t *arg1,f2_poly_t *arg2, f2_poly_t arg3, f2_poly_t arg4)
{
// (arg1, arg2) = (quotient, reste) de arg3 par arg4
    if(arg4==0)
		return 0;

    f2_poly_t quotient = 0;
    f2_deg_t diffDegre = 1;
    f2_poly_t x = 1;

    if(arg4 == 1) { /* division par 1 ... */
    quotient = arg3;
    *arg2 = 0;
    return 0;
  }
  if(arg4 > arg3){ /* si le diviseur est plus grand que le dividende ... */
    quotient = 0;
    *arg2 = arg3;
    return 0;
}

    while((f2_poly_deg(arg3)>=f2_poly_deg(arg4)) && arg3!=0)
    {
        if(f2_poly_deg(arg3)==f2_poly_deg(arg4))
        {
            arg3 = arg3^arg4;
            quotient=quotient^1;
            break;
        }
        else
        {
            diffDegre = (uint64_t)(f2_poly_deg(arg3) - f2_poly_deg(arg4));
            arg3 = arg3^(arg4<<diffDegre);
            quotient=quotient^((uint64_t)(x<<diffDegre));
        }
    }

    *arg1=quotient;
    *arg2=arg3;

    return 1;
}

int
f2_poly_div_bis(f2_poly_t * arg1,f2_poly_t *arg2, f2_poly_t arg3, f2_poly_t arg4){
// (arg1, arg2) = (quotient, reste) de arg3 par arg4

// (arg1, arg2) = (quotient, reste) de arg3 par arg4
    if(arg4==0)
		return 0;

    f2_poly_t quotient = 0;
    f2_deg_t diffDegre = 1;
    f2_poly_t x = 1;

    if(arg4 == 1) { /* division par 1 ... */
        quotient = arg3;
        *arg2 = 0;
        return 0;
    }
  if(arg4 > arg3){ /* si le diviseur est plus grand que le dividende ... */
        quotient = 0;
        *arg2 = arg3;
        return 0;
}

    while((f2_poly_deg(arg3)>=f2_poly_deg(arg4)) && arg3!=0)
    {
        if(f2_poly_deg(arg3)==f2_poly_deg(arg4))
        {
            arg3 = arg3^arg4;
            quotient=quotient^1;
            break;
        }
        else
        {
            diffDegre = (uint64_t)(f2_poly_deg(arg3) - f2_poly_deg(arg4));
            arg3 = arg3^(arg4<<diffDegre);
            quotient=quotient^((uint64_t)(x<<diffDegre));
        }
    }

    *arg1=quotient;
    *arg2=arg3;

    return 1;
}

f2_poly_t f2_poly_rem(f2_poly_t arg1, f2_poly_t arg2){
// reste de arg1 par arg2
	f2_poly_t reste=0, quotient=0;
	//int tmp= f2_poly_div_bis(&quotient,&reste,arg1,arg2);
	f2_poly_div_bis(&quotient,&reste,arg1,arg2);
	return reste;
}

f2_poly_t f2_poly_gcd_bis(f2_poly_t arg1, f2_poly_t arg2){
// pgcd(arg1, arg2)

	//Si le diviseur est plus grand que le dividente
	// on interchange
	 if(f2_poly_deg(arg2)>f2_poly_deg(arg1))
    {
        f2_poly_t tmp= arg1;
        arg1=arg2;
        arg2=tmp;

    }
     if(f2_poly_deg(arg2)==f2_poly_deg(arg1)){
		// si ils ont le même degré
		// et le diviseur est superieur à la dividente
		// on interchange
		int i ;
		int degre=f2_poly_deg(arg1);
 			for ( i = degre; i >=0; i--)
 			{
 				if(((( uint64_t)0x1<<i)&arg2)>((( uint64_t)0x1<<i)&arg1)){
          	  		f2_poly_t tmp= arg1;
       				arg1=arg2;
        			arg2=tmp;
        			break;
       		 	}
 			}
    }

	if(arg2==0x0)
		return arg1;
	else{
        // on applique l'agorithme d'Euclide
        f2_poly_t rest= f2_poly_rem(arg1,arg2);
        return f2_poly_gcd_bis(arg2,rest);
        }

}
f2_poly_t
f2_poly_gcd(f2_poly_t arg1, f2_poly_t arg2)
{
// pgcd(arg1, arg2)
    if(arg2 > arg1)
    {
        f2_poly_t tmp= arg1;
        arg1=arg2;
        arg2=tmp;

    }

    if( arg2 == (uint64_t)0x0)
	    return arg1;

    f2_poly_t r=(uint64_t)0x1;
    
    while(arg2!=0x0)
    {

        r=f2_poly_rem(arg1,arg2);
        arg1=arg2;
        arg2=r;

    }
    return arg1;
}
f2_poly_t f2_poly_xtimes_bis(f2_poly_t arg1, f2_poly_t arg2){
// retourne X*arg1 mod (arg2)

	return f2_poly_rem(arg1<<1,arg2);
}

f2_poly_t
f2_poly_xtimes(f2_poly_t arg1, f2_poly_t arg2)
{
// retourne X*arg1 mod (arg2)
    f2_poly_t tmp;
// c'est un decalage à droite
    tmp=arg1<<1;
//rourne le reste
    return f2_poly_rem(tmp,arg2);

}
f2_poly_t f2_poly_times_bis(f2_poly_t arg1, f2_poly_t arg2, f2_poly_t arg3){
// retourne arg1 * arg2 modulo  arg3

	f2_poly_t tmp = 0;
	f2_poly_t x=1;
	 while(arg2!=0){
	 	// on teste si le poids minimal est egale à 1
	 	// dans ce cas on fait la exponentiation
	 	if((arg2>>(f2_poly_deg(arg2)))&0x1){

	 		tmp^=(arg1<<f2_poly_deg(arg2));
	 		tmp=f2_poly_rem(tmp,arg3);
	 		arg2^=(x<<f2_poly_deg(arg2));
	 	}else{
	 		// sinon on avance vers la gauche
	 		// c'est à dire on multiplie par deux
	 		tmp<<=1;
	 	}
	 }
	 return tmp;
}

f2_poly_t
f2_poly_times(f2_poly_t arg1 , f2_poly_t arg2, f2_poly_t arg3)
{
// retourne arg1 * arg2 modulo  arg3
    f2_poly_t p = 0;

    f2_poly_t x=1;

    while(f2_poly_deg(arg1)>0)
    {

        p=p^(arg2<<f2_poly_deg(arg1));
        p=f2_poly_rem(p,arg3);
        arg1=arg1^(x<<f2_poly_deg(arg1));

    }
    if(arg1&1)
    {
        p^=arg2;
        p=f2_poly_rem(p,arg3);
    }
    return p;
}

f2_poly_t
f2_poly_x2n_bis(f2_deg_t arg1, f2_poly_t arg2){
// retourne X^{2^arg1} modulo arg 2

f2_poly_t tmp=0x1;
int i;
for (i = 0; i <(1<<arg1); ++i)
{
	tmp=f2_poly_xtimes_bis(tmp,arg2);

}
return tmp;
}

f2_poly_t
f2_poly_x2n(f2_deg_t arg1, f2_poly_t arg2)
{
// retourne X^{2^arg1} modulo arg 2
    f2_poly_t res=0x2;
    int i;
    for(i=1; i<=arg1; i++)
    {
        res=f2_poly_times( res, res,arg2);
    }
    return res;
}

f2_poly_t
f2_poly_parity_bis(f2_poly_t arg1){
//retourne le reste de la division par X+1 (xor des bits)
	f2_poly_t tmp=0;
	// tant que la divente est superieur à X+1
	while(f2_poly_deg(arg1)>=1){
		//on enleve à la divedente x+1 c'est à dire 0x37
		//decalé de degré de la dividente moins 1
		tmp= arg1^(((f2_poly_t)0x3)<<(f2_poly_deg(arg1)-1));
		arg1=tmp;
		//on teste le dernier bit de la divente
		if (f2_poly_deg(arg1)==1 && !(arg1&( uint64_t)0x1)){
			return arg1;
		} else if(f2_poly_deg(arg1)==1 ){
			return arg1^((f2_poly_t)0x3);
		}
	}

return arg1;
}

f2_poly_t
f2_poly_parity(f2_poly_t arg)
{
//retourne le reste de la division par X+1 (xor des bits)

    return f2_poly_rem(arg,( uint64_t) 0x3);
}

f2_poly_t
f2_poly_recip_bis(f2_poly_t polP){
// retourne le polynôme réciproque considéré comme de degré le second argument

/* pour renverser l'ordre des bits sur 64 bits :*/
	f2_deg_t tmp =63- f2_poly_deg(polP);
     polP = ((polP & 0x5555555555555555ULL) << 1)
	  ^ ((polP & 0xaaaaaaaaaaaaaaaaULL) >> 1);
     polP = ((polP & 0x3333333333333333ULL) << 2)
	  ^ ((polP & 0xccccccccccccccccULL) >> 2);
     polP = ((polP & 0x0f0f0f0f0f0f0f0fULL) << 4)
	  ^ ((polP & 0xf0f0f0f0f0f0f0f0ULL) >> 4);
     polP = ((polP & 0x00ff00ff00ff00ffULL) << 8)
	  ^ ((polP & 0xff00ff00ff00ff00ULL) >> 8);
     polP = ((polP & 0x0000ffff0000ffffULL) << 16)
	  ^ ((polP & 0xffff0000ffff0000ULL) >> 16);
     polP = ((polP & 0x00000000ffffffffULL) << 32)
	  ^ ((polP & 0xffffffff00000000ULL) >> 32);

	  //*/
return polP>>(tmp);
}

f2_poly_t
f2_poly_recip(f2_poly_t arg)
{
// retourne le polynôme réciproque considéré comme de degré le second argument
    f2_poly_t reci=0;
    int i;
    f2_deg_t d=f2_poly_deg(arg);
    for (i = 0; i <=d ; i++)
    {
        if (arg & ((uint64_t)1 << i))
            reci = reci | ((uint64_t)1 << (d - i));

    }
    return reci;
}

int
f2_poly_irred(f2_poly_t arg)
{
// vérifie si le polynôme arg1 est irréductible

    /* x^2^{(degre de arg)/2}+x*/
    f2_poly_t tmp1= f2_poly_x2n(f2_poly_deg(arg)>>1,arg)^0x2;
    /*x^2^{(degre de arg)}+x*/
    f2_poly_t tmp2=f2_poly_x2n(f2_poly_deg(arg),arg)^0x2;

    if(f2_poly_gcd(arg,tmp1)==0x1&& f2_poly_rem(tmp2,arg)==0)
        return 1;

    return 0;
}
int
f2_poly_irred_bis(f2_poly_t arg1){
// vérifie si le polynôme arg1 est irréductible

 /* x^2^{(degre de arg)/2}+x*/
	//int resul=0;
	f2_deg_t deg=f2_poly_deg(arg1);
	f2_poly_t ppd=( uint64_t)0x1;
	if(deg<1){
		printf("degre\n");
		return 0;
	}

	if(f2_poly_parity_bis(arg1)==0){
		// 1 est racine ie x+1 est un facteur de arg1
		printf("parité\n");
		return 0;
	}

   /*x^2^{(degre de arg)}+x*/
	// une des condition pour l'irrecditiblié
	f2_poly_t tmp1=f2_poly_x2n(deg,arg1)^(uint64_t)0x2;
	if(f2_poly_rem(tmp1,arg1)!=(uint64_t)0x0){
		printf("rest probleme\n");
		return 0;
	}

	f2_poly_t puissance = deg;

	while(puissance!=( uint64_t)0x1){
		// cette fonction retourne le plus petit diviseur premier
		ppd=pp_diviseur_premier(puissance);
		//une autre condition pour qu'une polynome
		// soit irredictible
	f2_poly_t tmp2= f2_poly_x2n_bis(deg/ppd,arg1)^( uint64_t)0x2;
		puissance=puissance/ppd;
		if(f2_poly_gcd(arg1,tmp2)!=( uint64_t)0x1)
			return 0;
	}
	return 1;

}

f2_poly_t
f2_poly_xn_bis(uint64_t arg1, f2_poly_t arg2){
// retourne X^{arg1} modulo arg 2
	f2_poly_t tmp = 1;
	f2_poly_t res = 1;
	f2_deg_t deg=f2_poly_deg(arg1);
	int i;
	for(i=0;i<=deg;i++){
		if(((arg1>>(uint64_t)i)&1)>0){
			tmp=f2_poly_x2n(i,arg2);
			res = f2_poly_times_bis(res,tmp,arg2);

		}
	}
	return res;
}

f2_poly_t
f2_poly_xn(uint64_t arg1, f2_poly_t arg2){
// retourne X^{arg1} modulo arg 2

	f2_poly_t res=0x2;
	f2_poly_t result=0x1;

	while(arg1>0){

		if(arg1&1)
			result=f2_poly_times_bis(result,res,arg2);
		arg1>>=(uint64_t)1;
		res=f2_poly_times_bis(res,res,arg2);
	}
	return result;
}
f2_poly_t
f2_poly_xntt(uint64_t arg1, f2_poly_t arg2)
{
// retourne X^{arg1} modulo arg 2
    f2_poly_t result = 0x1;
    f2_poly_t res=0x2;
// similaire à l'exponation  rapide
    while (arg1> 0)
    {
        if ((arg1 & 1) > 0)
            result = f2_poly_times(result,res,arg2);
        arg1 >>= (uint64_t)1;
        res =f2_poly_times(res,res,arg2);
    }

    return result;

}
int
f2_poly_primitive(f2_poly_t arg){
	// vérifie si le polynôme arg1 est primitif

	f2_deg_t deg=f2_poly_deg(arg);
	uint64_t ppd=( uint64_t)0x1;
	// si le polynome n'est pas irreductible
	// alors il ne sera pas primitif
	if(!f2_poly_irred_bis(arg))
		return 0;

	//uint64_t rest = 0;
	uint64_t puissance =(1<<deg)-1;

	uint64_t tmp =(1<<deg)-1;
	//uint64_t tmp3=0;

	while(puissance!=1){
		// cette fnction retourne le plus petit diviseur premier
		ppd=pp_diviseur_premier(puissance);
		f2_poly_t tmp2= f2_poly_xn_bis(tmp/ppd,arg)^( uint64_t)0x1;

		puissance=puissance/ppd;



		//une autre condition pour qu'une polynome
		// soit primitif

		if(f2_poly_gcd(arg,tmp2)!= 0x1){
			return 0;
		}
	}
	return 1;
}

uint64_t
f2_poly_irred_order(f2_poly_t polP){
	// renvoie 0 si le polynôme polP n'est pas irréductible,
// l'ordre multiplicatif d'une racine, soit de  X modulo P sinon
// Si cet ordre égale 1 << f2_poly-deg(P), le polynôme est primitif.

	if(f2_poly_irred(polP)==0){
		printf("non irréductible\n");
		return 0;
	}
	f2_deg_t  deg = f2_poly_deg(polP);
	printf("rest deg%"PRId8"\n",deg );
	uint64_t tmp=(1<<deg);
	printf("rest tmp%"PRId64"\n",tmp);

	uint64_t i;
	for (i = 1; i <= tmp-1; i++)
	{
		if(f2_poly_xn(i,polP)==( uint64_t)0x1){

			return (uint64_t)i;
		}
	}
	return (uint64_t)0;
}


f2_poly_t
f2_poly_random_inf(f2_deg_t arg){
	// retourne un polynôme tiré au hasard parmi les polynômes de degré < arg
 FILE *f;
    uint64_t  random;
    //choix de la valeur aleatoire
    if ((f = fopen(RANDOMFILE,"r")) == NULL)
    {
        perror("probleme fopen");
        exit(1);
    }
    fread(&random, sizeof(random), 1, f);

    fclose(f);
    // pour que le polynome tiré au hasard soit de degré infeier arg1
    //il est necesaire et suffisante que le reste avec le masque
    //est degré infirieur à d
    return f2_poly_rem(random,MASK((arg+1)));
}

f2_poly_t
f2_poly_random(f2_deg_t arg){
	// retourne un polynôme tiré au hasard parmi les polynômes de degré = arg

	// on tire au hasard un polynome de degré inferieur à arg
	// on ajoute 1<<arg
	return f2_poly_random_inf(arg)^(1<<arg);
}

f2_poly_t
f2_poly_irred_random(f2_deg_t arg){
// retourne un polynôme tiré au hasard parmi les polynômes irréductibles
// de degré = arg2
	f2_poly_t result;
	do{

		result=f2_poly_random(arg);

	}while(!f2_poly_irred_bis(result));
return result;
}

f2_poly_t
f2_poly_primitive_random(f2_deg_t arg){
// retourne un polynôme tiré au hasard parmi les polynômes primitifs
// de degré = arg2
	f2_poly_t result;
	do{

		result=f2_poly_random(arg);

	}while(!f2_poly_primitive(result));
return result;
}

uint64_t
f2_poly_irred_count(f2_deg_t n){

	f2_poly_t polymax=1<<(n+1);
	f2_poly_t polymin=1<<(n);
	uint64_t compteur = 0x0;
	if(n==1)
		return 2;

	while(f2_poly_deg(polymin)<f2_poly_deg(polymax)){
		polymin++;

		if(f2_poly_irred_bis(polymin)){
			compteur++;
		}
	}
	return compteur;
}

uint64_t
f2_poly_primitive_count(f2_deg_t n){

	if(n==1)
        return 2;
    f2_poly_t polyMax=1<<(n+1);
    f2_poly_t polyMin=1<<(n);
    uint64_t compteur=0x0;
    while(f2_poly_deg(polyMin)<f2_poly_deg(polyMax))
    {
        polyMin++;
        if(f2_poly_primitive(polyMin))
        {
            compteur++;
        }

    }
    return compteur;
}
