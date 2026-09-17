#include "lista.h" 

struct nodo {
    void *dato;
    struct nodo *siguiente;
};

struct lista {
    struct nodo *primero;
    size_t cantidad;
};


const int NO_ENCONTRADO = -1;


/*
 * Crea una lista y la devuelve.
 */
lista_t *lista_crear() {
    lista_t *lista = malloc(sizeof(lista_t));
    if(!lista) {
        return NULL;
    }

    lista->cantidad = 0;
    lista->primero = NULL;

    return lista;
}

/*
 * Devuelve la cantidad de elementos que almacena la lista.
 */
size_t lista_cantidad(lista_t *lista) {
    if(!lista) {
        return 0;
    }

    return lista->cantidad;
}

/*
 * Devuelve true si la lista está vacía
 */
bool lista_esta_vacia(lista_t *lista) {
    if(!lista) {
        return false;
    }

    return lista->cantidad == 0;
}

/*
 * Inserta un dato en la posicion dada de la lista y devuelve true si pudo.
 *
 * Si la posición está mas allá del final de la lista, no se puede insertar.
 *
 * Si no puede insertar devuelve false.
 */
bool lista_insertar(lista_t *lista, void *dato, size_t posicion) {
    if(!lista || !dato || posicion > lista->cantidad) {
        return false;
    }

    struct nodo *actual = lista->primero;   
    struct nodo *a_insertar = malloc(sizeof(struct nodo));
    if(!a_insertar) return false;
    a_insertar->dato = dato;

    size_t posicion_actual = 0;

    if(posicion == 0) {
        a_insertar->siguiente = lista->primero;
        lista->primero = a_insertar;
    } else {
        while(actual->siguiente != NULL && posicion_actual < posicion - 1) {
            actual = actual->siguiente;
            posicion_actual++;
        }
        a_insertar->siguiente = actual->siguiente;
        actual->siguiente = a_insertar;
    }

    lista->cantidad++;
    return true; 
}

/*
 * Elimina un dato en la posicion dada de la lista y devuelve el elemento eliminado.
 *
 * Si la posición está mas allá del final de la lista, no se puede eliminar y devuelve NULL.
 */
void *lista_eliminar(lista_t *lista, size_t posicion) {
    if(!lista || posicion >= lista->cantidad) return NULL;

    struct nodo *actual = lista->primero;   
    struct nodo *anterior = NULL; 
    size_t posicion_actual = 0;

    if(posicion == 0) {
        lista->primero = actual->siguiente;
    } else {
        while(actual && posicion_actual < posicion) {
            anterior = actual;
            actual = actual->siguiente;
            posicion_actual++;
        }
        anterior->siguiente = actual->siguiente;
    }

    void *dato_a_devolver = actual->dato;
    free(actual);
    lista->cantidad--;

    return dato_a_devolver;
}

/*
 * Reemplaza un dato en la posición dada de la lista y lo devuelve.
 */
void *lista_reemplazar(lista_t *lista, void *dato, size_t posicion) {
    if(!lista || posicion >= lista->cantidad) return NULL;

    struct nodo *actual = lista->primero;   
    size_t posicion_actual = 0;

    while(actual && posicion_actual < posicion) {
        actual = actual->siguiente;
        posicion_actual++;
    }

    void *dato_anterior = actual->dato;
    actual->dato = dato;

    return dato_anterior;
}

/*
 * Devuelve el elemento que se encuentra en la posición de la lista.
 */
void *lista_obtener(lista_t *lista, size_t posicion) {
    if(!lista || posicion >= lista->cantidad) return NULL;

    struct nodo *actual = lista->primero;   
    size_t posicion_actual = 0;

    while(actual && posicion_actual < posicion) {
        actual = actual->siguiente;
        posicion_actual++;
    }

    return actual;
}

/*
 * Busca un elemento en la lista utilizando el comparador. Si lo encuentra devuelve la posición en la que se encuentra.
 *
 * Si no lo encuentra devuelve -1.
 *
 * Si se provee el puntero encontrado, en dicho puntero se almacena el elemento encontrado o NULL en caso de no encontrarse.
 */
int lista_buscar(lista_t *lista, void *buscado,
		 int (*comparador)(void *, void *), void **encontrado) {
    if(!lista || !buscado || !comparador) {
        return NO_ENCONTRADO;
    } 
    bool se_encontro = false;
    if(encontrado) 
        *encontrado = NULL;

    struct nodo *actual = lista->primero;   
    int i = 0;

    while(actual && i < lista->cantidad && !se_encontro) {
        if(comparador(actual->dato, buscado)) {
            if(encontrado)
                *encontrado = actual->dato;
            se_encontro = true;
        } 
        actual = actual->siguiente;
        i++;
    }

    if(se_encontro) {
        return i-1;
    }

    return NO_ENCONTRADO;
}   

/*
 * Recorre la lista aplicando la función f. Devuelve la cantidad de veces que fue invocada f.
 *
 * Si f devuevle false, se deja de iterar.
 */
size_t lista_iterar(lista_t *lista, bool (*f)(void *, void *), void *extra) {
    if(!lista || !f) 
        return 0;

    size_t contador = 0;
    bool seguir = true;
    struct nodo *actual = lista->primero; 

    while (contador < lista->cantidad && seguir) {
        seguir = f(actual->dato, extra);
        actual = actual->siguiente;
        contador++;
    }

    return contador;
}

/*
 * Libera la lista y toda la memoria asociada.
 */
void lista_destruir(lista_t *lista) {
    if(!lista) return;
    
    struct nodo *actual = lista->primero;   

    while(actual) {
        struct nodo *aux = actual->siguiente;

        free(actual->dato);
        free(actual);
        actual = aux;   
    }

    free(lista);
}

/*
 * Libera la lista y toda la memoria asociada.
 *
 * Adicionalmente aplica la función destructora a cada elemento almacenado *
 */
void lista_destruir_todo(lista_t *lista, void (*destructor)(void *)) {
    if(!lista) return;

    struct nodo *actual = lista->primero;   

    while(actual) {
        struct nodo *aux = actual->siguiente;

        destructor(actual->dato);
        free(actual);
        actual = aux;   
    }

    free(lista);
}

/*
 * Crea un iterador de lista
 */
lista_iterador_t *lista_iterador_crear(lista_t *lista) {

}

/*
 * Devuelve true si hay mas elementos para iterar
 */
bool lista_iterador_se_puede_iterar(lista_iterador_t *it) {

}

/*
 * Avanza a la siguiente iteración
 */
void lista_iterador_siguiente(lista_iterador_t *it) {

}

/*
 * Devuelve el elemento actual iterado
 */
void *lista_iterador_obtener_elemento(lista_iterador_t *it) {

}

/*
 * Destruye el iterador
 */
void lista_iterador_destruir(lista_iterador_t *it) {

}