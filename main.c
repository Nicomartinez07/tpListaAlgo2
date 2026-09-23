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

lista_t *parsear_lista(char* texto) {
	lista_t *lista = lista_crear();
	size_t lista_cantidad = 0;
	if(!lista) return NULL;

	char *posicion = texto;
	char *fin;

	while(*posicion != '\0') {
		long numero = strtol(posicion, &fin, 10);

		int *valor = malloc(sizeof(int));
		if(!valor) return NULL;


		valor = (int)numero;

		lista_insertar(lista, numero, lista_cantidad);
		lista_cantidad++;

		posicion = fin;

		if(*posicion == ',') posicion++;
	}

	return lista;
}

int main(int argc, char **argv)
{
	if (argc < CANTIDAD_MINIMA_PARAMETROS) {
    	printf("Se deben ingresar como minimo 3 parametros para el correcto "
        	   "funcionamiento del programa.\n Uso: ./ejecutable <operacion_a_ejecutar> "
        	   "<operando1> ... <operando n>\n");
    	return ERROR;
  	}

	int cantidad_listas = argc - 2;
	lista_t **listas = malloc(sizeof(lista_t *) * cantidad_listas);
	if(!listas) return NULL;

	for(size_t i = 0; i < argc; i++) {
		listas[i] = parsear_lista(argv[i+2]);
	}

	lista_iterador_t **iteradores = malloc(sizeof(lista_iterador_t *) * cantidad_listas);

	for(int i = 0; i < cantidad_listas; i++) {
		iteradores[i] = lista_iterador_crear(listas[i]);
	}

	lista_t *resultados = lista_crear();
	if(!resultados) return ERROR;

	while(iteradores_pueden_iterar(iteradores, cantidad_listas)) {

		for (size_t i = 0; i < cantidad_listas; i++) {
			void *elemento =
				lista_iterador_obtener_elemento(iteradores[i]);

			// usar elemento
		}

		for (size_t i = 0; i < cantidad_listas; i++) {
			lista_iterador_siguiente(iteradores[i]);
		}
	}

	imprimir_resultados(resultados);


	
	for(size_t j = 0; j < cantidad_listas; j++) {
		lista_iterador_destruir(iteradores[j]);
	}
	for(size_t l = 0; l < cantidad_listas; l++) {
		lista_destruir_todo(listas[l], free);
	}
	lista_destruir(resultados);

	return 0;
}
