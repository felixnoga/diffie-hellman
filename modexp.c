#include<stdio.h>
#include<math.h>
#include<stdint.h>
#include <stdlib.h>
#include <time.h>


/*
Función mod_Exp
Dados b=base, e=exponente y p=modulo, calcula x=b^e mod p y retorna x
El exponente se expande en binario. 
Ejemplo: Dado el exponente 5, tenemos que 5 base 10 = 0000 0101 base 2 -> 2^0+2^2 
Si a_j=1 (es decir, el bit j-ésimo de la expansión del exponente es 1), el agoritmo muliplica el valor actual x por b^2^j mod p 
y reduce el resultado módulo p.
*/


int mod_exp(int b, int e, int p) {

    uint64_t i, x;
    uint64_t power;
    x=1;
    power = b % p;
    for(i=0; i<8*sizeof(int); i++) {
        if(e & 1) { //Chequeamos si el bit actual del exponente es 1 (1&1=1)
            x=(x*power) % p; 
            
        }
        e >>=1; //Hacemos un "shift" a la derecha del valor binario del exponente "e" para pasar al siguiente bit
        power=(power*power) % p;
        }
        
        return x;
}



/*
Función principal main
Si llamamos g a la raiz primitiva dada (14) Y p al módulo dado (2^31-1), se generan en ella:
 - nuestro número secreto "x" (aleatorio y en módulo 100 para realizar los cálculos más sencillos). Número al que elevamos la raiz primitiva g.
 - El número "z" que le pasamos a otro compañero (z=g^x mod p)
 - Se genera a modo de ejemplo para comprobaciones del algoritmo, el número w=g^y mod p que debería calcular el compañero, siendo "y" su número aleatorio secreto.
 - La clave compartida "K" (donde K^x mod p = K^y mod p, siendo x e y las claves secretas nuestra y de nuestro compañero)
*/

int main(){

    /*
    Los números dados para la operación modular son la raíz primitiva g=14
    y el módulo número primo 2^31-1. Declaramos también el resto de variables utilizadas.
    */
    int numero, z, w, resejem, k;  
    int g = 14; //base de la exponenciación (raiz primitiva)
    int p = pow(2,31)-1;  //módulo p dado     
    srand(time(0)); //Inicializamos con una semilla la función para generar número aleatorio (la semilla es la hora actual)
    int x = rand() %100;    //Generamos el número "x" aleatorio al que exponenciaremos g (g^x mod p = X, siendo X (mayúscula) el número que le enviamos a la otra persona)
    
    //Imprimimos en pantalla el número aleatorio secreto (NOTA: este número es secreto del usuario y no debería compartirse. Se comparte con fines de comprobación del algoritmo.)
    printf("\n");
    printf("ACTIVIDAD GRUPAL: IMPLEMENTACION ALGORITMO DIFFIE-HELLMAN\n");
    printf("===============================================================================\n");
    printf("\n");
    printf("Nuestro numero secreto aleatorio que hemos generado es: %i \n", x);
    z = mod_exp(g, x , p); // Ejecutamos la función mod_exp que calcula z=g^x mod p
    printf("El numero que debes enviar a la otra parte es: %i \n", z);
    

    int y = rand() %100; //Generamos un numero aleatorio para simular la acción del otro interlocutor al aplicar su algoritmo.
    w= mod_exp(g, y, p); //Generamos w=g^y mod p (respuesta de ejemplo que podría enviarnos el otro interlocutor)
    printf("\n");
    printf("\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("NOTA: a continuacion generamos un valor de ejemplo \"Y\" que la parte contraria te puede enviar si su numero secreto aleatorio es %i. \n", y);
    printf("Se ha calculado dicho numero Y=14^%i mod(2^31-1), siendo 14 la raiz primitiva dada y el modulo 2^31-1\n", y);

    printf("Numero que nos envia la otra parte: %i\n", w);
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n");
    printf("\n");
    printf("Introduce el numero que te ha enviado la otra parte:  \n");
    
    scanf("%d", &w);
 
    k = mod_exp(w, x , p);
    printf("La clave compartida \"K\" es: \n");
    printf("%d", k);
    
}