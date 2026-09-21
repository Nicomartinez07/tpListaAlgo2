#include "src/lista.h"

const int ERROR = -1;
const int CANTIDAD_MINIMA_PARAMETROS = 3;
const char RESULTADO_INVALIDO = 'E';

bool iteradores_pueden_iterar(lista_iterador_t **iteradores, size_t tope) {
	for(size_t i = 0; i < tope; i++) {
		if(!lista_iterador_se_puede_iterar(iteradores[i])) {
			return false;
		}
	}

	return true;
}

void operar() {

}


int main(int argc, char **argv)
{
	if (argc < CANTIDAD_MINIMA_PARAMETROS) {
    	printf("Se deben ingresar como minimo 3 parametros para el correcto "
        	   "funcionamiento del programa.\n Uso: ./ejecutable <operacion_a_ejecutar> "
        	   "<operando1> ... <operando n>\n");
    	return ERROR;
  	}

	lista_t *resultados = malloc(sizeof(struct lista_t));
	if(!resultados) return ERROR;

	lista_iterador_t *iteradores;
	size_t tope = 0;

	for(int i = 2; i < argc; i++) {

	}


	while(iteradores_pueden_iterar(&iteradores, tope)) {

		for (size_t i = 0; i < tope; i++) {
			void *elemento =
				lista_iterador_obtener_elemento(iteradores[i]);

			// usar elemento
		}

		for (size_t i = 0; i < tope; i++) {
			lista_iterador_siguiente(iteradores[i]);
		}
	}

	for(size_t j = 0; j < tope; j++) {
		lista_iterador_destruir(*iteradores[i]);
	}

	return 0;
}
