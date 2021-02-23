//pre procesador, antes del codigo fuente
#include <stdio.h> //standard input - output library (header)

int main() {
	/**
	 * char a = 'a';
	 * printf("%i\n", a); //printf tiene un formato para vars (ver tabla)
	 * int aux; //variable init
	 * scanf("%d", &aux); //guardar lo leido en la dirección de la variable
	 * printf("Value obtained: %d\n", aux);
	 *
	 * for(unsigned int i = 0; i < 10; ++i) {	//usigned quitar los valores negativos de una var
	 * printf("Hello World! %i\n", i);
	 * } 
	 * return 0;
	 */

	//printf("Hello World!\n");
	
	write(1, "Hello World!\n", sizeof("Hello World!\n"));
}
