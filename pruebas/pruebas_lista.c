#include "../src/lista.h"
#include "pa2m.h"

#define NO_ENCONTRADO -1

/*
buscar:
Elemento 1, en la lista-> devuelve 1 sin puntero
Elemento que no esta -> devuelve -1 
Elemento 1, en la lista-> devuelve elemento 1 en el puntero y posición 1
Elemento que no esta -> devuelve -1  y null
*/

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
}
