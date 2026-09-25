#include "cola.h"
#include "lista.h"

struct cola {
    lista_t *lista;
};


cola_t *cola_crear() {
    cola_t *cola = malloc(sizeof(cola_t));
    if(!cola) {
        return NULL;
    }

    cola->lista = lista_crear();
    if(cola->lista) {
        free(cola);
        return NULL;
    }

    return cola;
}

bool cola_encolar(cola_t *c, void *e) {
    if(!c)   return false;

    size_t cantidad = lista_cantidad(c->lista);

    bool resultado = lista_insertar(c->lista, e, cantidad);

    return resultado;
}

void *cola_desencolar(cola_t *c) {
    if(!c)   return NULL;

    void *dato = lista_eliminar(c->lista, 0);

    return dato;
}

void *cola_frente(cola_t *c) {
    if(!c)   return NULL;

    void *dato = lista_obtener(c->lista, 0);

    return dato;
}

bool cola_esta_vacia(cola_t *c) {
    if(!c)   return NULL;

    bool resultado = lista_esta_vacia(c->lista);

    return resultado;
}

size_t cola_cantidad(cola_t *c) {
    if(!c)   return 0;

    size_t cantidad = lista_cantidad(c->lista);

    return cantidad;
}

void cola_destruir(cola_t *c) {
    if(!c)   return;

    lista_destruir(c->lista);
    free(c);
}

