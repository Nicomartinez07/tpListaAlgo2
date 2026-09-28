#include "../src/pila.h"
#include "pa2m.h"

void prueba_crear_pila() {
	pila_t *p = pila_crear();

	pa2m_afirmar(p != NULL, "Se creo una pila.\n");

	pila_destruir(p);
}

void prueba_apilar_posicion_valida() {
	pila_t *p = pila_crear();
	if(!p) return;

	int elemento = 2;
	pa2m_afirmar(pila_apilar(p, &elemento), "Se apilo un elemento correctamente en la pila.\n");
	size_t cantidad = pila_cantidad(p);
	pa2m_afirmar(cantidad == 1, "En la pila, se encuentra unicamente el elemento apilado.\n");
	
	pila_destruir(p);
}

void prueba_desapilar() {
	pila_t *p = pila_crear();
	if(!p) return;
	int elemento1 = 1, elemento2 = 2, elemento3 = 3;

	pa2m_afirmar(pila_apilar(p, &elemento1), "Se apilo el primer elemento.\n");

	pa2m_afirmar(pila_apilar(p, &elemento2), "Se apilo el segundo elemento.\n");

	pa2m_afirmar(pila_apilar(p, &elemento3), "Se apilo el tercer elemento.\n");

	size_t cantidad = pila_cantidad(p);
	void *resultado = pila_desapilar(p);
	
	pa2m_afirmar(cantidad == 3, "La cantidad de 3 elementos es %zu.\n", cantidad);
	pa2m_afirmar(*(int*)resultado == 3, "Al intentar desapilar un elemento de una pila, se devuelve el primer elemento de la pila.\n");
	pa2m_afirmar(pila_cantidad(p) == 2, "Al desapilar un elemento de una pila, pasan a quedar 2 elementos.\n");


	pila_destruir(p);
}

void prueba_desapilar_pila_vacia() {
	pila_t *p = pila_crear();
	if(!p) return;

	void *resultado = pila_desapilar(p);

	pa2m_afirmar(resultado == NULL, "Al intentar desapilar un elemento de una pila vacia, se devuelve NULL.\n");

	pila_destruir(p);
}


void prueba_frente_pila_vacia() {
	pila_t *p = pila_crear();
	if(!p) return;

	bool vacia = pila_esta_vacia(p);
	void *elemento_obtenido = pila_tope(p);

	pa2m_afirmar(vacia, "Una pila sin elementos se considera vacia.\n");
	pa2m_afirmar(elemento_obtenido == NULL, "Al obtener el tope de una pila sin un elemento se obtiene NULL.\n");
	
	pila_destruir(p);
}

void prueba_frente_pila_valida() {
	pila_t *p = pila_crear();
	if(!p) return;

	int elemento = 2;
	pa2m_afirmar(pila_apilar(p, &elemento), "Se apilo el un elemento.\n");

	void *elemento_obtenido = pila_tope(p);
	bool vacia = pila_esta_vacia(p);

	pa2m_afirmar(vacia == false, "Una pila con elementos no se considera vacia.\n");
	pa2m_afirmar(*(int*)elemento_obtenido == 2, "Al obtener el tope de una pila con un elemento se obtiene el mismo.\n");
	

	pila_destruir(p);
}

void pruebas_pila()
{
	pa2m_nuevo_grupo("Prueba crear pila");
	prueba_crear_pila();

	pa2m_nuevo_grupo("Prueba apilar en posicion valida");
	prueba_apilar_posicion_valida();

	pa2m_nuevo_grupo("Prueba apilar 3 elementos y desapilar el ultimo");
	prueba_desapilar();

	pa2m_nuevo_grupo("Prueba desapilar pila vacia");
	prueba_desapilar_pila_vacia();

	pa2m_nuevo_grupo("Prueba obtener tope pila vacia");
	prueba_frente_pila_vacia();

	pa2m_nuevo_grupo("Prueba obtener tope pila con elementos");
	prueba_frente_pila_valida();
}
