#include "pila.h"

struct pila {
    struct *lista;
}

const int NO_ENCONTRADO = -1;

pila_t *pila_crear() {
    pila_t *pila = lista_crear();

    return pila;
}

bool pila_apilar(pila_t *p, void *e) {
    if(!pila)   return NULL;

    bool resultado = lista_insertar(p, e, 0);

    return resultado;
}

/*
 * Devuelve el primer elemento de la pila
 */
void *pila_desapilar(pila_t *p) {
    if(!pila)   return NULL;

    void *dato = lista_eliminar(p, 0)

    return
}

/*
 * Devuelve el elemento en el tope de la pila sin desapilarlo
 */
void *pila_tope(pila_t *p) {
    if(!pila)   return NULL;

    void *dato = lista_obtener(p, 0);

    return dato;
}

/*
 * Devuelve true si la pila está vacía
 */
bool pila_esta_vacia(pila_t *p) {
    if(!pila)   return NULL;

    bool resultado = lista_esta_vacia(p);

    return resultado;
}

/*
 * Devuelve la cantidad de elementos que almacena la pila.
 */
size_t pila_cantidad(pila_t *p) {
    if(!pila)   return NULL;

    size_t cantidad = lista_cantidad(p);

    return cantidad;
}

/*
 * Libera la pila y toda la memoria asociada.
 */
void pila_destruir(pila_t *pila) {
    if(!pila)   return NULL;

    lista_destruir(pila);
}