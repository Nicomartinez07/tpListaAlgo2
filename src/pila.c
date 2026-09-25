#include "pila.h"
#include "lista.h"

#include <stdlib.h>
#include <stdbool.h>

struct pila {
    lista_t *lista;
};

pila_t *pila_crear() {
    pila_t *pila = malloc(sizeof(pila_t));
    if(!pila) {
        return NULL;
    }

    pila->lista = lista_crear();
    if(!pila->lista) {
        free(pila);
        return NULL;
    }

    return pila;
}

bool pila_apilar(pila_t *p, void *e) {
    if(!p)   return false;

    bool resultado = lista_insertar(p->lista, e, 0);

    return resultado;
}

/*
 * Devuelve el primer elemento de la pila
 */
void *pila_desapilar(pila_t *p) {
    if(!p)   return NULL;

    void *dato = lista_eliminar(p->lista, 0);

    return dato;
}

/*
 * Devuelve el elemento en el tope de la pila sin desapilarlo
 */
void *pila_tope(pila_t *p) {
    if(!p)   return NULL;

    void *dato = lista_obtener(p->lista, 0);

    return dato;
}

/*
 * Devuelve true si la pila está vacía
 */
bool pila_esta_vacia(pila_t *p) {
    if(!p)   return false;

    bool resultado = lista_esta_vacia(p->lista);

    return resultado;
}

/*
 * Devuelve la cantidad de elementos que almacena la pila.
 */
size_t pila_cantidad(pila_t *p) {
    if(!p)   return 0;

    size_t cantidad = lista_cantidad(p->lista);

    return cantidad;
}

/*
 * Libera la pila y toda la memoria asociada.
 */
void pila_destruir(pila_t *p) {
    if(!p)   return;

    lista_destruir(p->lista);
    free(p);
}