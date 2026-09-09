# TDA Lista/Pila/Cola

Se pide implementar en **C99** una lista simplemente enlazada, una pila y una cola según las interfaces definidas en clase.

Los TDAs entregados deberan compilar y pasar las pruebas dispuestas por la cátedra sin errores, adicionalmente estas pruebas deberán ser ejecutadas **sin pérdida de memoria**.

Recordar que es obligatorio entregar un informe que explique cómo se implementaron los TDAs, cómo funcionan, la complejidad de las operaciones y cualquier aclaración que sea necesaria para el corrector.

Recordar también que es obligatorio entregar **pruebas_alumno.c** con las pruebas realizadas para verificar el correcto funcionamiento de los TDA.

## main.c

En el archivo main.c se debe implementar un programa que por línea de comandos reciba un operador y n listados de enteros separados por coma.

El programa debe utilizar el TDA implementado para obtener el resultado de
aplicar el operador a los enteros. Se espera como salida otra lista de enteros
separados por coma (sin espacios). En caso de no poder realizarse la operación
para un conjunto de números se debe imprimir "E" y continuar con el resto de los
elementos.

Por ejemplo
```txt
./main + "1,2,3,4" "5,6,7,8"
6,8,10,12
```

```txt
./main - "10,10,10,10,10" "1,2,3,4,5" "0,3,7,12,1"
9,5,0,-6,4
```

```txt
./main * "1,2,3" "0,1,2"
0,2,6
```

```txt
./main / "1,2,4" "0,2,2"
E,1,2
```

```txt
./main + "1,2" "1,2,3,4"
2,4,E,E
```



## Restricciones

  Para que el trabajo se considere aprobado, la implementación debe cumplir los siguientes requisitos:

  - Las lista debe ser simplemente enlazada
  - Las operaciones para **apilar**, **desapilar** y obtener el **tope** de la pila deben ser **O(1)**
  - Las operaciones para **encolar**, **desencolar** y obtener el **frente** de la cola deben ser **O(1)**
  - Las implementaciones de pila y cola deben reutilizar la implementación de lista

## Parte teórica

Explicar teóricamente los siguientes puntos (no necesariamente en orden, pero por favor usando diagramas):

   - Explicar qué es una lista, lista enlazada y lista doblemente enlazada.
     - Explicar las características de cada una.
     - Explicar las diferencias internas de implementación de cada una.
     - Explicar ventajas y desventajas de cada una, si existen.
   - Explicar qué es una lista circular y de qué maneras se puede implementar.
   - Explicar la diferencia de funcionamiento entre cola y pila.
   - Explicar la diferencia entre un iterador interno y uno externo.
