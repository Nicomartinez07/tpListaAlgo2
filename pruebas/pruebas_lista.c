#include "../src/lista.h"
#include "pa2m.h"

#define NO_ENCONTRADO -1

int comparador(void *a, void *b)
{
    int val_a = *(int *)a;
    int val_b = *(int *)b;

    return (val_a > val_b) - (val_a < val_b);
}

void prueba_crear_lista()
{
	lista_t *l = lista_crear();
	if (!l)
		return;

	size_t cantidad = lista_cantidad(l);
	bool vacia = lista_esta_vacia(l);

	pa2m_afirmar(l != NULL, "Se creo una lista.\n");
	pa2m_afirmar(cantidad == 0, "La lista se creo con %zu elementos.\n",
		     cantidad);
	pa2m_afirmar(vacia, "La lista al crearse se encuentra vacia.\n");

	lista_destruir(l);
}

void prueba_insertar()
{
	lista_t *l = lista_crear();
	if (!l)
		return;

	int dato1 = 1;
	int dato2 = 2;
	int dato10 = 10;

	pa2m_afirmar(lista_insertar(l, &dato1, 0),
		     "Se apilo un elemento en la primer posicion.\n");
	pa2m_afirmar(lista_insertar(l, &dato2, lista_cantidad(l)),
		     "Se apilo un elemento en la ultima posicion.\n");
	pa2m_afirmar(
		lista_insertar(l, &dato10, lista_cantidad(l) + 10) == false,
		"No se puede aplicar un elemento mas alla de la cantidad de elementos de la lista.\n");

	void *elemento_primera_posicion = lista_obtener(l, 0);
	void *elemento_ultima_posicion =
		lista_obtener(l, lista_cantidad(l) - 1);
	void *elemento_posicion_invalida = lista_obtener(l, lista_cantidad(l));

	pa2m_afirmar(
		*(int *)(elemento_primera_posicion) == 1,
		"El elemento en la primera posicion condice con el elemento insertado en esa posicion\n");
	pa2m_afirmar(
		*(int *)(elemento_ultima_posicion) == 2,
		"El elemento en la ultima posicion condice con el elemento insertado en esa posicion\n");
	pa2m_afirmar(
		elemento_posicion_invalida == NULL,
		"Al intentar obtener un elemento en una posicion invalida devuelve NULL\n");

	lista_destruir(l);
}

void prueba_eliminar()
{
	lista_t *l = lista_crear();
	if (!l)
		return;

	int dato1 = 1;
	int dato2 = 2;
	int dato10 = 10;

	pa2m_afirmar(lista_insertar(l, &dato1, 0),
		     "Se apilo un elemento en la primer posicion.\n");
	pa2m_afirmar(
		!lista_esta_vacia(l),
		"Al apilarse un elemento la lista no se encuentra vacia.\n");
	pa2m_afirmar(lista_insertar(l, &dato2, lista_cantidad(l)),
		     "Se apilo otro elemento.\n");
	pa2m_afirmar(lista_insertar(l, &dato10, lista_cantidad(l)),
		     "Se apilo otro elemento.\n");

	void *eliminado = lista_eliminar(l, lista_cantidad(l) - 1);
	void *eliminado_invalido = lista_eliminar(l, lista_cantidad(l) + 1);
	pa2m_afirmar(
		*(int *)eliminado == dato10,
		"Al eliminar el elemento en la ultima posicion, se obtuvo el mismo.\n");
	pa2m_afirmar(
		eliminado_invalido == NULL,
		"Al eliminar el elemento de una posicion invalida, se obtiene NULL.\n");

	lista_destruir(l);
}

void prueba_buscar_sin_puntero_elemento()
{
	lista_t *l = lista_crear();
	if (!l)
		return;

	int dato1 = 1;
	int dato2 = 2;
	int dato10 = 10;

	pa2m_afirmar(lista_insertar(l, &dato1, lista_cantidad(l)),
		     "Se apilo un elemento en la primer posicion.\n");
	pa2m_afirmar(lista_insertar(l, &dato2, lista_cantidad(l)),
		     "Se apilo otro elemento.\n");
	pa2m_afirmar(lista_insertar(l, &dato10, lista_cantidad(l)),
		     "Se apilo otro elemento.\n");

	int inexistente = 11;

	int posicion_elemento_buscado = lista_buscar(l, &dato2, comparador, NULL);
	pa2m_afirmar(posicion_elemento_buscado == 1,
                 "El dato buscado esta en la posicion 1.\n");

	int posicion_elemento_buscado_inexistente = lista_buscar(l, &inexistente, comparador, NULL);
	pa2m_afirmar(posicion_elemento_buscado_inexistente == NO_ENCONTRADO,
                 "La posicion obtenida es -1 debido a que el elemento no esta en la lista.\n");

	

	lista_destruir(l);
}

void prueba_buscar_con_puntero_elemento()
{
	lista_t *l = lista_crear();
	if (!l)
		return;

	int dato1 = 1;
	int dato2 = 2;
	int dato10 = 10;

	pa2m_afirmar(lista_insertar(l, &dato1, lista_cantidad(l)),
		     "Se apilo un elemento en la primer posicion.\n");
	pa2m_afirmar(lista_insertar(l, &dato2, lista_cantidad(l)),
		     "Se apilo otro elemento.\n");
	pa2m_afirmar(lista_insertar(l, &dato10, lista_cantidad(l)),
		     "Se apilo otro elemento.\n");

	void *encontrado;
	int inexistente = 11;

	int posicion_elemento_buscado = lista_buscar(l, &dato2, comparador, &encontrado);
	pa2m_afirmar(posicion_elemento_buscado == 1,
                 "El dato buscado esta en la posicion 1.\n");
	pa2m_afirmar(encontrado == &dato10,
                 "Busco un elemento presente y devuelve el dato correcto.\n");
	
	int posicion_elemento_buscado_inexistente = lista_buscar(l, &inexistente, comparador, &encontrado);
	pa2m_afirmar(posicion_elemento_buscado_inexistente == NO_ENCONTRADO,
                 "La posicion obtenida es -1 debido a que el elemento no esta en la lista.\n");
	pa2m_afirmar(encontrado == NULL,
                 "Al no encontrar el elemento en la lista, devuelve NULL en encontrado.\n");

	lista_destruir(l);
}

void prueba_reemplazar()
{
	lista_t *l = lista_crear();
	if (!l)
		return;

	int dato1 = 1;
	int dato2 = 2;

	pa2m_afirmar(lista_insertar(l, &dato1, 0),
		     "Se apilo un elemento en la primer posicion.\n");

	void *reemplazado = lista_reemplazar(l, &dato2, 0);
	void *segundo_reemplazado = lista_reemplazar(l, NULL, 0);
	void *reemplazado_invalido =
		lista_reemplazar(l, NULL, lista_cantidad(l) + 1);

	pa2m_afirmar(
		*(int *)reemplazado == dato1,
		"Al reemplazar el primer elemento, se obtiene el mismo.\n");
	pa2m_afirmar(
		*(int *)segundo_reemplazado == dato2,
		"Al reemplazar el segundo elemento, se obtiene el mismo.\n");
	pa2m_afirmar(
		reemplazado_invalido == NULL,
		"Al reemplazar el elemento de una posicion invalida, se obtiene NULL.\n");

	lista_destruir(l);
}


void prueba_crear_iterador()
{
	lista_t *l = lista_crear();
	if (!l)
		return;

	lista_iterador_t *it = lista_iterador_crear(l);
	if (!it) {
		lista_destruir(l);
		return;
	}


	pa2m_afirmar(it != NULL, "Se creo un iterador externo a la lista.\n");

	lista_destruir(l);
	lista_iterador_destruir(it);
}

void prueba_iterar_lista_con_iterador()
{
	lista_t *l = lista_crear();
	if (!l)
		return;

	lista_iterador_t *it = lista_iterador_crear(l);
	if (!it) {
		lista_destruir(l);
		return;
	}

	int dato1 = 1;
	int dato2 = 2;
	int dato10 = 10;

	pa2m_afirmar(it != NULL, "Se creo un iterador externo a la lista.\n");

	pa2m_afirmar(lista_insertar(l, &dato1, 0),
		     "Se apilo un elemento en la primer posicion.\n");
	pa2m_afirmar(lista_insertar(l, &dato2, lista_cantidad(l)),
		     "Se apilo un elemento en la ultima posicion.\n");
	pa2m_afirmar(
		lista_insertar(l, &dato10, lista_cantidad(l) + 10) == false,
		"No se puede aplicar un elemento mas alla de la cantidad de elementos de la lista.\n");

	pa2m_afirmar(lista_iterador_se_puede_iterar(it),
			  "Se puede iterar la lista porque contiene elementos.\n");

	void *elemento_primera_posicion = lista_iterador_obtener_elemento(it);
	pa2m_afirmar(
		*(int *)(elemento_primera_posicion) == 1,
		"El elemento en la primera posicion condice con el elemento insertado en esa posicion\n");
	
	lista_iterador_siguiente(it);
	void *elemento_segunda_posicion = lista_iterador_obtener_elemento(it);
	pa2m_afirmar(
		*(int *)(elemento_segunda_posicion) != 1,
		"El elemento en la segunda posicion no condice con el elemento insertado en la primera posicion porque se itero la lista al siguiente elemento.\n");
	pa2m_afirmar(
		*(int *)(elemento_segunda_posicion) == 2,
		"El elemento en la segunda posicion coincide con el elemento insertado en esa posicion.\n");

	lista_destruir(l);
	lista_iterador_destruir(it);
}

void pruebas_lista()
{
	pa2m_nuevo_grupo("Prueba crear lista");
	prueba_crear_lista();

	pa2m_nuevo_grupo(
		"Prueba inserta elementos y verifica que se devuelven los correctos");
	prueba_insertar();

	pa2m_nuevo_grupo(
		"Prueba inserta elementos y los elimina verificando que se obtienen los correctos");
	prueba_eliminar();

	pa2m_nuevo_grupo(
		"Prueba inserta elementos y los reemplaza verificando que se devuelven los correctos");
	prueba_reemplazar();

	pa2m_nuevo_grupo(
		"Prueba inserta elementos y busca sin pasar como parametro un elemento para almacenar el buscado");
	prueba_buscar_sin_puntero_elemento();

	pa2m_nuevo_grupo(
		"Prueba inserta elementos y busca pasandole como parametro un elemento para almacenar el buscado");
	prueba_buscar_con_puntero_elemento();

	pa2m_nuevo_grupo("Prueba crear lista iterador");
	prueba_crear_iterador();

	pa2m_nuevo_grupo("Prueba crea un iterador en una lista con elementos y los itera obteniendo los elementos y comparandolos");
	prueba_iterar_lista_con_iterador();

}
