#include "pa2m.h"
#include "pruebas.h"

int main()
{
	pa2m_nuevo_grupo("============== PRUEBAS DEL TP X ===============");

  pa2m_nuevo_grupo("Pruebas de cola");
  pruebas_cola();

  pa2m_nuevo_grupo("Pruebas de pila");
  pruebas_pila();

  pa2m_nuevo_grupo("Pruebas de lista");
  pruebas_lista();

  pa2m_nuevo_grupo("Pruebas de programa");
  pruebas_programa();

  return pa2m_mostrar_reporte();
}
