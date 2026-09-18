#include "cola.h"
#include "lista.h"

struct cola {
    struct lista_t *lista;
};


cola_t *cola_crear() {
    cola_t *cola = lista_crear();

    return cola;
}

bool cola_encolar(cola_t *c, void *e) {
    if(!c)   return false;

    size_t cantidad = lista_cantidad(c);

    bool resultado = lista_insertar(c, e, cantidad);

    return resultado;
}

void *cola_desencolar(cola_t *c) {
    if(!c)   return NULL;

    void *dato = lista_eliminar(c, 0);

    return dato;
}

void *cola_frente(cola_t *c) {
    if(!c)   return NULL;

    void *dato = lista_obtener(c, 0);

    return dato;
}

bool cola_esta_vacia(cola_t *c) {
    if(!c)   return NULL;

    bool resultado = lista_esta_vacia(c);

    return resultado;
}

size_t cola_cantidad(cola_t *c) {
    if(!c)   return NULL;

    size_t cantidad = lista_cantidad(c);

    return cantidad;
}

void cola_destruir(cola_t *cola) {
    if(!cola)   return NULL;

    lista_destruir(cola);
}

