#include <stdio.h>
#include <stdlib.h>
#include "f2_poly.h"
int main()
{
/* les polynoms qui servira de test */
f2_poly_t polAES = 0x11b;     //X^8+X^4+X^3+X+1, irréductible non primitif
f2_poly_t polA51a = 0xe4001;  //X^19+X^18+X^17+X^14+1, irréductible primitif
 //f2_poly_t polA51b = 0x600001; //X^22+X^21+1, irréductible primitif
 f2_poly_t polA51c = 0xe00101; //X^23+X^22+X^21+X^8+1, irréductible primitif


 /* test pour le degré */
 printf("/***********************f2_poly_deg*****************************/\n");
 f2_deg_t k=f2_poly_deg(polAES);
 printf("\nle degré de plynome polAES : %u \n",k);
 printf("le degré de plynome polA51a : %u \n",f2_poly_deg(polA51a));

 printf("/***********************f2_poly_deg_bis*************************/\n");
 f2_deg_t kb=f2_poly_deg_bis(polAES);
 printf("\nle degré de plynome polAES : %u \n",kb);
 printf("le degré de plynome polA51a : %u \n",f2_poly_deg_bis(polA51a));

 /*test de la fonction d'affichage*/
 printf("/******************f2_poly_print**********************************/\n");
 printf(" \n affichage la fonction de PolAES : \n ");
 f2_poly_print(polAES,'x', NULL);
 printf(" \n affichage la fonction de PolA51c : \n ");
 f2_poly_print(polA51c,'x', NULL);


 /*test pour le quotient et le reste de la division*/
 printf("/**************** f2_poly_divBis************************************/\n");
 f2_poly_t quotient, reste;
 int tmp= f2_poly_div_bis(&quotient,&reste,0x63 , 0x17);
 if(tmp==0){
   printf("erreur lors de la division \n");
 }else{
   printf("\n divison de  ");
   f2_poly_print(0x63,'x',NULL);
   printf("  par ");
   f2_poly_print(0x17,'x',NULL);
   printf("\nquotient\n");
   f2_poly_print(quotient,'x', NULL);
   printf("reste\n");
   f2_poly_print(reste,'x', NULL);
 }

 printf("/**************** f2_poly_gcd bis************************************/\n");
 printf("\nle pgcd de ");
 f2_poly_print(0x311,'x', NULL);
 printf("par ");
 f2_poly_print(0xF,'x', NULL);
 printf("\n est :\n");
 f2_poly_print(f2_poly_gcd(0x311b,0xF),'x',NULL);

 printf(" et le pgcd de ");
 f2_poly_print(0x63,'x', NULL);
 printf("par ");
 f2_poly_print(0x17,'x', NULL);
 printf("\nest :\n");
 //f2_poly_print(f2_poly_gcd_bis(0x63,0x17),'x',NULL);
 f2_poly_print(f2_poly_gcd_bis(0x63,0x17),'x',NULL);
 /* test de la fonction f2_poly_xtimes */
 printf("/*******************f2_poly_xtimes*********************************/\n");
 printf("\nxtimes ");
 f2_poly_print(0x1FBF,'x', NULL);
 printf("par ");
 f2_poly_print(0x11B,'x', NULL);
 printf("\nest :\n");
 f2_poly_print(f2_poly_xtimes(0x1FBF,0x11B),'x',NULL);
 /* test de la fonction f2_poly_xtimes */
 printf("/*******************f2_poly_xtimes*********************************/\n");
 printf("\nxtimes ");
 f2_poly_print(0x1FBF,'x', NULL);
 printf("par ");
 f2_poly_print(0x11B,'x', NULL);
 printf("\nest :\n");
 f2_poly_print(f2_poly_xtimes_bis(0x1FBF,0x11B),'x',NULL);
 printf("/******************* f2_poly_times*********************************/\n");

 printf(" la fonction f2_poly_times qui retourne ");
 printf("retourne 0xE50 * 0x1 modulo  0x1B \n");
 f2_poly_print(f2_poly_times_bis(0xE50,0x1,0x1B),'x',NULL);

 printf("/******************f2_poly_x2n_bis**********************************/\n");
 printf("\nf2_poly_x2n qui  retourne X^{2^0x5} modulo 0x1d \n");
 f2_poly_print(f2_poly_x2n_bis(0x5, 0x1d),'x',NULL);

 /*test de la fonction de la parité*/
 printf("/*********************f2_poly_parity*******************************/\n");
 printf("\n voici un exemple de calcule de la paride \n");
 f2_poly_print(f2_poly_parity(f2_poly_x2n(f2_poly_deg(0xe00101), 0xe00101)),'x',NULL);
 tmp= f2_poly_div(&quotient,&reste,f2_poly_x2n(f2_poly_deg(0xe00101), 0xe00101) , 0x3);
 if(tmp==0){
   printf("erreur lors de la division \n");
 }else{
   printf("\n divison de  ");
   f2_poly_print(f2_poly_x2n(f2_poly_deg(0xe00101), 0xe00101),'x',NULL);
   printf("  par ");
   f2_poly_print(0x3,'x',NULL);
   printf("\nquotient\n");
   f2_poly_print(quotient,'x', NULL);
   printf("reste\n");
   f2_poly_print(reste,'x', NULL);
}
 /*test de la fonction de la parité*/
 printf("/*********************f2_poly_parity_bis************************/\n");
 printf("\n voici un exemple de calcule de la paride \n");
 f2_poly_print(f2_poly_parity_bis(f2_poly_x2n(f2_poly_deg(0xe00101), 0xe00101)),'x',NULL);

f2_poly_print(f2_poly_parity_bis((f2_poly_t)0x2D),'x',NULL);


/*test de la fonction qui calcule le polynome reciproque*/
 printf("/****************f2_poly_recip_bis************************************/\n");
 printf("le polynome reciproque de  ");
 f2_poly_print(0x43,'x', NULL);
 printf(" est ");
 f2_poly_print(f2_poly_recip_bis(0x43),'x',NULL);

printf("/****************f2_poly_irred_bis************************************/\n");
 printf("\n le polynome polAES est-il irreductible 1 si oui 0 sinon:\n");
 printf(" %d\n", f2_poly_irred_bis(polAES));
 printf("\n le polynome polA51a est-il irreductible 1 si oui 0 sinon:\n");
 printf(" %d\n", f2_poly_irred_bis(polA51a));
 printf("\n le polynome polA51c est-il irreductible 1 si oui 0 sinon:\n");
 printf(" %d\n", f2_poly_irred_bis(polA51c));

 printf("\n le polynome 0x84 est-il irreductible 1 si oui 0 sinon:\n");
 printf(" %d\n", f2_poly_irred_bis((0x54)));

 /*test qui retourne X^{arg1} modulo arg 2 ie f2_poly_xn */
 printf("/************************f2_poly_xn****************************/\n");
 printf("f2_poly_xn(6,0xf) :\n");
 f2_poly_print( f2_poly_xn(6,0xf),'x', NULL);
 /*test qui retourne X^{arg1} modulo arg 2 ie f2_poly_xn */
 printf("/************************f2_poly_xn_bis****************************/\n");
 printf("f2_poly_xn(6,0xf) :\n");
 f2_poly_print( f2_poly_xn_bis(6,0xf),'x', NULL);

 /*test pour prouver qu'une polynome est primitif ou non*/
 printf("/*********************f2_poly_primitive*******************************/\n");
 printf("est  primitif polAES? 1 pour oui 0 sinon:\n %d\n",f2_poly_primitive(polAES));
//printf("est  primitif polA51a? 1 pour oui 0 sinon:\n %d\n",f2_poly_primitive(polA51a));
// printf("est  primitif polA51b? 1 pour oui 0 sinon:\n %d\n",f2_poly_primitive(polA51c));

 /*test pour qui renvoit l'ordre multiplication de d'une racine pour e polynome irreductible ie f2_poly_irred_order */
 printf("/*******************f2_poly_irred_order*********************************/\n");
 printf("odre de polAES : %" PRIu64  "\n",f2_poly_irred_order(polAES));
//printf("odre de polA51a : %" PRIu64 " \n",f2_poly_irred_order(polA51a));
 /*test de la fonction qui  retourne un polynôme tiré au hasard parmi les polynômes de degré < arg ie f2_poly_random_inf*/
 printf("/*********************f2_poly_random_inf*******************************/\n");
 printf("voici cinq polynome tiré au hasad de degre < cing\n");
 printf("f2_poly_random_inf(5):\n");
 int i;

 for(i=1;i<5;i++){

   f2_poly_print(f2_poly_random_inf(5),'x', NULL);
 }
 /*test pour la fonction f2_poly_random qui retourne un polynôme tiré au hasard parmi les polynômes de degré = arg  */
 printf("/**********************f2_poly_random******************************/\n");
 printf("voici cinq polynome tiré au hasad de degre = cing\n");
 printf("f2_poly_random(5):\n");
 int j;
 for(j=1;j<5;j++){

   f2_poly_print(f2_poly_random(5),'x', NULL);
 }
 /*test qui retourne un polynôme tiré au hasard parmi les polynômes irréductibles de degré = arg2 ie f2_poly_irred_random  */
 printf("/********************f2_poly_irred_random********************************/\n");
 printf("voici cinq polynome irreductible tiré au hasad de degre = cing\n");
 printf("f2_poly_irred_random(5):\n");
 for(i=1;i<5;i++){

   f2_poly_print(f2_poly_irred_random(5),'x', NULL);
 }

 printf("/********************f2_poly_primitive_random********************************/\n");
 printf("voici cinq polynome primitif tiré au hasad de degre = cing\n");
 printf("f2_poly_irred_random(5):\n");
 for(i=1;i<5;i++){

   f2_poly_print(f2_poly_primitive_random(5),'x', NULL);
 }

 //printf(" f2_poly_irred_count(11):\n");
//printf("%"PRIu64"\n",f2_poly_irred_count(17));
 //printf(" f2_poly_irred_count(14):\n");
//printf("%"PRIu64 "\n",f2_poly_primitive_count(14));
 return 0;
}
