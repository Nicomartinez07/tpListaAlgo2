#include "src/lista.h"
#include <stdbool.h>

const int ERROR = -1;
const int CANTIDAD_MINIMA_PARAMETROS = 3;
const char RESULTADO_INVALIDO = 'E';

bool iteradores_pueden_iterar(lista_iterador_t **iteradores, int tope) {
	if(!iteradores) return false;

	bool se_puede_iterar = true;
	for(int i = 0; i < tope; i++) {
		if(!lista_iterador_se_puede_iterar(iteradores[i])) {
			se_puede_iterar = false;
		}
	}

	return se_puede_iterar;
}

lista_t *parsear_lista(char* texto) {
	if(!texto) return NULL;

	lista_t *lista = lista_crear();
	size_t lista_cantidad = 0;
	if(!lista) return NULL;

	char *posicion = texto;
	char *fin;

	while(*posicion != '\0') {
		long numero = strtol(posicion, &fin, 10);

		int *valor = malloc(sizeof(int));
		if(!valor) return NULL;


		*valor = (int)numero;

		lista_insertar(lista, valor, lista_cantidad);
		lista_cantidad++;

		posicion = fin;

		if(*posicion == ',') posicion++;
	}

	return lista;
}

void liberar_memoria_iteradores(lista_iterador_t **iteradores, int tope) {
	for(int j = 0; j < tope; j++) {
		lista_iterador_destruir(iteradores[j]);
	}
	free(iteradores);
}

void liberar_memoria_listas(lista_t **listas, int tope) {
	for(int l = 0; l < tope; l++) {
		lista_destruir_todo(listas[l], free);
	}
	free(listas);
}

bool operar(char operador, int *operandos, int tope, int *resultado)
{
    if (!operandos || !resultado || tope == 0)
        return false;

		bool operacion_valida = true;

    if (operador == '+') {
        *resultado = 0;

        for (int i = 0; i < tope; i++) {
            *resultado += operandos[i];
        }
    } else if (operador == '-') {
        *resultado = operandos[0];

        for (int i = 1; i < tope; i++) {
            *resultado -= operandos[i];
        }
    } else if (operador == '*') {
        *resultado = 1;

        for (int i = 0; i < tope; i++) {
            *resultado *= operandos[i];
        }
    } else if (operador == '/') {
        *resultado = operandos[0];

        for (int i = 1; i < tope; i++) {
            if (operandos[i] == 0) {
				operacion_valida = false;
			} else {
				*resultado /= operandos[i];
			}
        }
    } else {
        operacion_valida =  false;
    }

    return operacion_valida;
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
	if(!listas) return ERROR;

	for (size_t i = 0; i < cantidad_listas; i++) {
		listas[i] = parsear_lista(argv[i + 2]);
	}

	lista_iterador_t **iteradores = malloc(sizeof(lista_iterador_t *) * cantidad_listas);
	if(!iteradores) {
		liberar_memoria_listas(listas, cantidad_listas);
		return ERROR;
	}

	for(int i = 0; i < cantidad_listas; i++) {
		iteradores[i] = lista_iterador_crear(listas[i]);
	}

	lista_t *resultados = lista_crear();
	if(!resultados)  {
		liberar_memoria_listas(listas, cantidad_listas);
		liberar_memoria_iteradores(iteradores, cantidad_listas);
		return ERROR;
	}

	while(iteradores_pueden_iterar(iteradores, cantidad_listas)) {
		int *elementos = malloc(sizeof(int) * cantidad_listas);
		if(!elementos) {
			liberar_memoria_listas(listas, cantidad_listas);
			liberar_memoria_iteradores(iteradores, cantidad_listas);
			return ERROR;
		}
		int tope_elementos = 0;

		for (size_t i = 0; i < cantidad_listas; i++) {
			elementos[i] = *(int *)lista_iterador_obtener_elemento(iteradores[i]);
			tope_elementos++;
		}

		size_t cant_actual = lista_cantidad(resultados);
		int *resultado = malloc(sizeof(int));
		bool operacion_valida = operar(argv[1], elementos, tope_elementos, &resultado); 

		if(operacion_valida) {
			lista_insertar(resultados, resultado, cant_actual);
		} else {
			lista_insertar(resultados, 'E', cant_actual);
		}

		for (size_t i = 0; i < cantidad_listas; i++) {
			lista_iterador_siguiente(iteradores[i]);
		}

		free(elementos);
	}

	imprimir_resultados(resultados);
	
	liberar_memoria_iteradores(iteradores, cantidad_listas);
	liberar_memoria_listas(listas, cantidad_listas);
	lista_destruir(resultados);

	return 0;
}
