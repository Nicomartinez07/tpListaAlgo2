#include "pa2m.h"
#include "pruebas.h"

int main()
{
	pa2m_nuevo_grupo("============== PRUEBAS DEL TP X ===============");

	pa2m_nuevo_grupo("");
	pa2m_nuevo_grupo("==== PRUEBAS DEL TDA COLA ====");
	pruebas_cola();

	pa2m_nuevo_grupo("");
	pa2m_nuevo_grupo("==== PRUEBAS DEL TDA PILA ====");
	pruebas_pila();

	pa2m_nuevo_grupo("");
	pa2m_nuevo_grupo("==== PRUEBAS DEL TDA LISTA ====");
	pruebas_lista();

	return pa2m_mostrar_reporte();
}
