#include "../src/lista.h"
#include "pa2m.h"

#define NO_ENCONTRADO -1

void prueba_crear_lista() {
	lista_t *l = lista_crear();
	if(!l) return;

	size_t cantidad = lista_cantidad(l);
	bool vacia = lista_esta_vacia(l);

	pa2m_afirmar(l != NULL, "Se creo una lista.\n");
	pa2m_afirmar(cantidad == 0, "La lista se creo con %zu elementos.\n", cantidad);
	pa2m_afirmar(vacia, "La lista al crearse se encuentra vacia.\n");


	lista_destruir(l);
}

void prueba_insertar() {
	lista_t *l = lista_crear();
	if(!l) return;

	int dato1 = 1;
	int dato2 = 2;
	int dato10 = 10;

	pa2m_afirmar(lista_insertar(l, &dato1, 0), "Se apilo un elemento en la primer posicion.\n");
	pa2m_afirmar(lista_insertar(l, &dato2, lista_cantidad(l)), "Se apilo un elemento en la ultima posicion.\n");
	pa2m_afirmar(lista_insertar(l, &dato10, lista_cantidad(l)+10) == false, "No se puede aplicar un elemento mas alla de la cantidad de elementos de la lista.\n");


	void *elemento_primera_posicion = lista_obtener(l, 0);
	void *elemento_ultima_posicion = lista_obtener(l, lista_cantidad(l));

	pa2m_afirmar(*(int *)(elemento_primera_posicion) == 1, "El elemento en la primera posicion condice con el elemento insertado en esa posicion\n");
	pa2m_afirmar(*(int *)(elemento_ultima_posicion) == 2, "El elemento en la ultima posicion condice con el elemento insertado en esa posicion\n");


	lista_destruir(l);
}


void pruebas_lista()
{
	prueba_crear_lista();
	prueba_insertar();
}
