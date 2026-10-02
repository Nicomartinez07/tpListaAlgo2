#include "src/lista.h"
#include <stdbool.h>
#include <stdio.h>

const int ERROR = -1;
const int CANTIDAD_MINIMA_PARAMETROS = 3;
const char RESULTADO_INVALIDO = 'E';
const char SUMA = '+';
const char RESTA = '-';
const char MULTIPLICACION = '*';
const char DIVISION = '/';

typedef struct resultado {
	bool valido;
	int valor;
} resultado_t;

/*
 *Imprime el vector de resultados, en caso de resultado no valido, imprime E
 */
void imprimir_resultados(lista_t *resultados, size_t tope)
{
	for (size_t i = 0; i < tope; i++) {
		resultado_t *resultado = lista_obtener(resultados, i);
		if (resultado->valido) {
			printf("%d", resultado->valor);
		} else {
			printf("E");
		}

		if (i + 1 < tope) {
			printf(",");
		}
	}

	printf("\n");
}

/*
 * Devuelve true si algun iterador del vector, tiene elementos para seguir iterando. False en caso contrario.
 */
bool algun_iterador_puede_iterar(lista_iterador_t **iteradores, int tope)
{
	if (!iteradores)
		return false;

	bool se_puede_iterar = false;

	int i = 0;
	while (i < tope && !se_puede_iterar) {
		if (lista_iterador_se_puede_iterar(iteradores[i])) {
			se_puede_iterar = true;
		}
		i++;
	}

	return se_puede_iterar;
}

/*
 * Dada una string que represente la lista ingresada por el usuario, crea una lista, e inserta los valores en ella.
 */
lista_t *parsear_lista(char *texto)
{
	if (!texto)
		return NULL;

	lista_t *lista = lista_crear();
	if (!lista)
		return NULL;

	char *posicion = texto;
	char *fin;

	while (*posicion != '\0') {
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

/*
 * Libera memoria de cada iterador y del vector
 */
void liberar_memoria_iteradores(lista_iterador_t **iteradores, int tope)
{
	for (int i = 0; i < tope; i++) {
		lista_iterador_destruir(iteradores[i]);
	}
	free(iteradores);
}

/*
 * Libera memoria de cada lista y del vector 
 */
void liberar_memoria_listas(lista_t **listas, int tope)
{
	for (int i = 0; i < tope; i++) {
		lista_destruir_todo(listas[i], free);
	}
	free(listas);
}

/*
 * Libera memoria de todos los elementos solicitados en el main 
 */
void liberar_memorias(lista_t **listas, lista_iterador_t **iteradores,
		      lista_t *resultados, int tope)
{
	liberar_memoria_listas(listas, tope);
	liberar_memoria_iteradores(iteradores, tope);
	lista_destruir_todo(resultados, free);
}

/*
 * Aplica el operador, a cada operando y devuelve el resultado.
 */
resultado_t *operar(char operador, int *operandos, int tope,
		    resultado_t *resultado)
{
	if (!operandos || !resultado || tope == 0) {
		return NULL;
	}

	resultado->valido = true;

	if (operador == SUMA) {
		resultado->valor = 0;

		for (int i = 0; i < tope; i++) {
			resultado->valor += operandos[i];
		}
	} else if (operador == RESTA) {
		resultado->valor = operandos[0];

		for (int i = 1; i < tope; i++) {
			resultado->valor -= operandos[i];
		}
	} else if (operador == MULTIPLICACION) {
		resultado->valor = 1;

		for (int i = 0; i < tope; i++) {
			resultado->valor *= operandos[i];
		}
	} else if (operador == DIVISION) {
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
	lista_t **listas = malloc(sizeof(lista_t *) * (size_t)cantidad_listas);
	if (!listas)
		return ERROR;

	for (int i = 0; i < cantidad_listas; i++) {
		listas[i] = parsear_lista(argv[i + 2]);
	}

	lista_iterador_t **iteradores =
		malloc(sizeof(lista_iterador_t *) * (size_t)cantidad_listas);
	if (!iteradores) {
		liberar_memoria_listas(listas, cantidad_listas);
		return ERROR;
	}

	for (int i = 0; i < cantidad_listas; i++) {
		iteradores[i] = lista_iterador_crear(listas[i]);
	}

	lista_t *resultados = lista_crear();
	if (!resultados) {
		liberar_memoria_listas(listas, cantidad_listas);
		liberar_memoria_iteradores(iteradores, cantidad_listas);
		return ERROR;
	}

	while (algun_iterador_puede_iterar(iteradores, cantidad_listas)) {
		int *elementos = malloc(sizeof(int) * (size_t)cantidad_listas);
		if (!elementos) {
			liberar_memorias(listas, iteradores, resultados,
					 cantidad_listas);
			return ERROR;
		}
		bool todos_tienen_elementos = true;

		for (int i = 0; i < cantidad_listas; i++) {
			if (lista_iterador_se_puede_iterar(iteradores[i])) {
				elementos[i] =
					*(int *)lista_iterador_obtener_elemento(
						iteradores[i]);
			} else {
				todos_tienen_elementos = false;
			}
		}

		size_t cant_actual = lista_cantidad(resultados);
		resultado_t *resultado = malloc(sizeof(resultado_t));
		if (!resultado) {
			liberar_memorias(listas, iteradores, resultados,
					 cantidad_listas);
			return ERROR;
		}

		if (todos_tienen_elementos) {
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

	liberar_memorias(listas, iteradores, resultados, cantidad_listas);

	return 0;
}
