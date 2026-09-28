#include "../src/cola.h"
#include "pa2m.h"

void prueba_crear_cola() {
	cola_t *c = cola_crear();
	pa2m_afirmar(c != NULL, "Se creo una cola.");

	if (c) {
        cola_destruir(c);
    }
}

void prueba_encolar_posicion_valida() {
	cola_t *c = cola_crear();
	if (!c) {
        pa2m_afirmar(false, "No se pudo crear la cola para la prueba.");
        return;
    }

	int elemento = 2;
	pa2m_afirmar(cola_encolar(c, &elemento), "Se encolo un elemento.\n");
	pa2m_afirmar(cola_cantidad(c) == 1, "En la cola, se encuentra unicamente el elemento insertado.\n");
	
	cola_destruir(c);
}

void prueba_desencolar() {
	cola_t *c = cola_crear();
	if (!c) {
        pa2m_afirmar(false, "No se pudo crear la cola para la prueba.");
        return;
    }

	int elemento1 = 1, elemento2 = 2, elemento3 = 3;

	pa2m_afirmar(cola_encolar(c, &elemento1), "Se encolo el primer elemento.\n");

	pa2m_afirmar(cola_encolar(c, &elemento2), "Se encolo el segundo elemento.\n");

	pa2m_afirmar(cola_encolar(c, &elemento3), "Se encolo el tercer elemento.\n");

	size_t cantidad = cola_cantidad(c);
	void *resultado = cola_desencolar(c);
	
	pa2m_afirmar(cantidad == 3, "La cantidad de una lista de 3 elementos es %zu.\n", cantidad);
	pa2m_afirmar(*(int*)resultado == 1, "Al intentar desencolar un elemento de una cola, se devuelve el primer elemento de la cola.\n");
	pa2m_afirmar(cola_cantidad(c) == 2, "Al intentar desencolar un elemento de una cola, pasan a quedar %zu elementos.\n", cola_cantidad(c));

	cola_destruir(c);
}

void prueba_desencolar_cola_vacia() {
	cola_t *c = cola_crear();
	if (!c) {
        pa2m_afirmar(false, "No se pudo crear la cola para la prueba.");
        return;
    }

	void *resultado = cola_desencolar(c);

	pa2m_afirmar(resultado == NULL, "Al intentar desencolar un elemento de una cola vacia, se devuelve NULL.\n");
	

	cola_destruir(c);
}


void prueba_frente_cola_vacia() {
	cola_t *c = cola_crear();
	if (!c) {
        pa2m_afirmar(false, "No se pudo crear la cola para la prueba.");
        return;
    }

	bool vacia = cola_esta_vacia(c);
	void *elemento_obtenido = cola_frente(c);

	pa2m_afirmar(vacia, "Una cola sin elementos se considera vacia.\n");
	pa2m_afirmar(elemento_obtenido == NULL, "Al obtener el frente de una cola sin un elemento se obtiene NULL.\n");
	
	cola_destruir(c);
}

void prueba_frente_cola_valida() {
	cola_t *c = cola_crear();
	if (!c) {
        pa2m_afirmar(false, "No se pudo crear la cola para la prueba.");
        return;
    }

	int elemento = 2;
	pa2m_afirmar(cola_encolar(c, &elemento), "Se encolo un elemento.\n");

	void *elemento_obtenido = cola_frente(c);
	bool vacia = cola_esta_vacia(c);

	pa2m_afirmar(vacia == false, "Una cola con elementos no se considera vacia.\n");
	pa2m_afirmar(*(int*)elemento_obtenido == 2, "Al obtener el frente de una cola con un elemento se obtiene el mismo.\n");
	

	cola_destruir(c);
}

void pruebas_cola()
{
	pa2m_nuevo_grupo("Prueba crear cola");
	prueba_crear_cola();

	pa2m_nuevo_grupo("Prueba encolar en posicion valida");
	prueba_encolar_posicion_valida();

	pa2m_nuevo_grupo("Prueba encolar 3 elementos y desencolar el ultimo");
	prueba_desencolar();

	pa2m_nuevo_grupo("Prueba desencolar cola vacia");
	prueba_desencolar_cola_vacia();

	pa2m_nuevo_grupo("Prueba obtener frente cola vacia");
	prueba_frente_cola_vacia();

	pa2m_nuevo_grupo("Prueba obtener frente cola con elementos");
	prueba_frente_cola_valida();
}
