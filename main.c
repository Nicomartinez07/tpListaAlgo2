#include "src/lista.h"
#include <stdbool.h>
#include <stdio.h>

const int ERROR = -1;
const int CANTIDAD_MINIMA_PARAMETROS = 3;
const char RESULTADO_INVALIDO = 'E';

typedef struct resultado{
    bool valido;
    int valor;
} resultado_t;

void imprimir_resultados(lista_t *resultados, size_t tope) {
	for(size_t i = 0; i < tope; i++) {
		resultado_t *resultado = lista_obtener(resultados, i);
		if (resultado->valido) {
			printf("%d", resultado->valor);
		} else {
			printf("E");
		}

		if(i+1 < tope) {
			printf(",");
		}
	}

	printf("\n");
}

bool algun_iteradores_puede_iterar(lista_iterador_t **iteradores, int tope) {
	if(!iteradores) return false;

	bool se_puede_iterar = false;

	int i = 0;
	while(i < tope && !se_puede_iterar) {
		if(lista_iterador_se_puede_iterar(iteradores[i])) {
			se_puede_iterar = true;
		}
		i++;
	}

	return se_puede_iterar;
}

lista_t *parsear_lista(char* texto) {
	if(!texto) return NULL;

	lista_t *lista = lista_crear();
	if(!lista) return NULL;
 
	char *posicion = texto;
	char *fin;

	while(*posicion != '\0') {
		long numero = strtol(posicion, &fin, 10);

    if (fin == posicion) {
        lista_destruir_todo(lista, free);
        return NULL;
    }

    int *valor = malloc(sizeof(int));
    if (!valor) {
        lista_destruir_todo(lista, free);
        return NULL;
    }

    *valor = (int)numero;

    if (!lista_insertar(lista, valor, lista_cantidad(lista))) {
        free(valor);
        lista_destruir_todo(lista, free);
        return NULL;
    }

    posicion = fin;

    if (*posicion == ',') {
        posicion++;
    }
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

resultado_t *operar(char operador, int *operandos, int tope, resultado_t *resultado)
{
    if (!operandos || !resultado || tope == 0) {
		return NULL;
	}

	resultado->valido = true;


    if (operador == '+') {
        resultado->valor = 0;

        for (int i = 0; i < tope; i++) {
            resultado->valor += operandos[i];
        }
    } else if (operador == '-') {
        resultado->valor = operandos[0];

        for (int i = 1; i < tope; i++) {
            resultado->valor -= operandos[i];
        }
    } else if (operador == '*') {
        resultado->valor = 1;

        for (int i = 0; i < tope; i++) {
    		resultado->valor *= operandos[i];
        }
    } else if (operador == '/') {
        resultado->valor = operandos[0];

        for (int i = 1; i < tope; i++) {
            if (operandos[i] == 0) {
				resultado->valido = false;
			} else {
				resultado->valor /= operandos[i];
			}
        }
    } else {
		resultado->valido = false;
	}

    return resultado;
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

	for (int i = 0; i < cantidad_listas; i++) {
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

	while(algun_iteradores_puede_iterar(iteradores, cantidad_listas)) {
		int *elementos = malloc(sizeof(int) * cantidad_listas);
		if(!elementos) {
			liberar_memoria_listas(listas, cantidad_listas);
			liberar_memoria_iteradores(iteradores, cantidad_listas);
			return ERROR;
		}
		bool todos_tienen_elementos = true;

		for (int i = 0; i < cantidad_listas; i++) {
			if(lista_iterador_se_puede_iterar(iteradores[i])){
				elementos[i] = *(int *)lista_iterador_obtener_elemento(iteradores[i]);
			} else {
				todos_tienen_elementos = false;
			}
		}

		size_t cant_actual = lista_cantidad(resultados);
		resultado_t *resultado = malloc(sizeof(resultado_t));
		if(!resultado) {
			liberar_memoria_listas(listas, cantidad_listas);
			liberar_memoria_iteradores(iteradores, cantidad_listas);
			return ERROR;
		}

		if(todos_tienen_elementos) {
			operar(*argv[1], elementos, cantidad_listas, resultado); 
		} else {
			resultado->valido = false;
			resultado->valor = 0;
		}

		lista_insertar(resultados, resultado, cant_actual);

		for (int i = 0; i < cantidad_listas; i++) {
			lista_iterador_siguiente(iteradores[i]);
		}

		free(elementos);
	}

	imprimir_resultados(resultados, lista_cantidad(resultados));
	
	liberar_memoria_iteradores(iteradores, cantidad_listas);
	liberar_memoria_listas(listas, cantidad_listas);
	lista_destruir(resultados);

	return 0;
}
