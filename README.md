<div align="right">
    <img width="32px" src="img/algo2.svg">
</div>

# TP

## Información del estudiante

* Nicolas Martinez
* 115882
* nmartinez@fi.uba.ar
* Nicomartinez07

## Índice
* [1. Instrucciones](#1-Instrucciones)
  * [1.1. Compilar el proyecto y correr pruebas con valgrind](#11-Compilar-el-proyecto-y-correr-pruebas-con-valgrind)
  * [1.2. Ejecutar las pruebas](#12-Ejecutar-las-pruebas)
  * [1.3. Ejecutar las pruebas con Valgrind](#13-Ejecutar-las-pruebas-con-Valgrind)
* [2. Funcionamiento](#2-Funcionamiento)
* [3. Estructura](#3-Estructura)
  * [3.1. Diagrama de memoria](#31-Diagrama-de-memoria)
  * [3.2. Análisis de complejidades](#32-Análisis-de-complejidades)
* [4. Decisiones de diseño y/o complejidades de implementación](#4-Decisiones-de-diseño-yo-complejidades-de-implementación)
* [5. Respuestas a las preguntas teóricas](#5-Respuestas-a-las-preguntas-teóricas)

## 1. Instrucciones.

### 1.1. Compilar el proyecto y correr pruebas con valgrind
```bash
make
```

### 1.2. Ejecutar las pruebas 
```bash
make pruebas
```

### 1.3. Ejecutar las pruebas con Valgrind
```bash
make valgrind_alumno
```

## 2. Funcionamiento
El usuario ejecuta el programa con un operador y una determinada cantidad de listas. Independiente del operador que se ejecute se realiza el proceso de parsear las listas enviadas por el usuario y guardarlas en un vector de listas. En esta etapa se realiza una verificacion de que los parametros enviados sean validos.

Posteriormente se crean iteradores de listas, para poder en cada iteracion obtener los elementos contenidos en cada lista y posteriormente operar con los mismos.  

Luego de realizar las operación correspondiente con los elementos de cada lista, se realiza una inserción del resultado a una lista de resultados. Por ultimo, se realiza una impresion de los resultados obtenidos por pantalla. Una vez finalizado ese proceso se libera toda la memoria solicitada en la ejecucion del programa.

<div align="center">
  <img src="img/diagrama_flujo_programa.svg" width="70%">
  <p>Diagrama de flujo del programa explicado con más detalle.</p>
</div>

## 3. Estructura
El TDA Lista esta compuesto por tres campos

Hay dos punteros del tipo struct nodo. El primero apunta siempre al primer elemento que contenga la lista. El otro apunta siempre al ultimo elemento que contenga la lista. Esta estructura me permite pensar la lista como un conjunto de nodos, donde siempre se cual es el primero y el ultimo. Cada nodo esta compuesto de un dato de tipo void* para poder manipular cualquier tipo de objeto, y un puntero apuntando al siguiente nodo. 
 Una lista tambien contiene un size_t cantidad el cual representa la cantidad actual de elementos que contiene la lista.

Por otra parte el TDA lista_iterador, contiene una lista asociada y un nodo actual el cual se utiliza para marcar el nodo al que se esta apuntando en esa correspondiente iteracion. 

El TDA Cola esta compuesto unicamente de una lista debido a que con una lista se pueden realizar las operaciones basicas de una cola simplemente encolando los elementos en la ultima posición, desencolando los elementos en la primera posición y obteniendo los elementos de la primera posición. El resto de las operaciones se pueden realizar reutilizando las funciones de la lista.

Asimismo el TDA Pila esta compuesto unicamente de una lista debido a que con una lista consultando en la primera posición se pueden realizar las operaciones de apilar, desapilar y consultar el tope. El resto de las operaciones se pueden realizar reutilizando las funciones de la lista.

### 3.1. Diagrama de memoria
Realizar un diagrama de memoria de la estructura de memoria durante la ejecución del programa, esto debe incluir el stack y el heap con las estructuras contenidas en ellos.


RESOLUCION: DIAGRAMA DE MEMORIA EL CUAL MUESTRE TODO EL FUNCIONAMIENTO DEL MAIN: TEXTO Q ME AYUDE A EPLXIAR

### 3.1 Diagrama de memoria (EJEMPLO)
<div align="center">
  <img src="img/diagrama_memoria__1.svg" width="70%">
  <p>Diagrama de memoria de la estructura.</p>
</div>


### 3.2. Análisis de complejidades

A continuacion se va a realizar un analisis de complejidad sobre los 3 tipos de TDA distintos que se piden implementar en el TP. 

### Análisis de complejidades de funciones TDA lista.

* `lista_crear` tiene una complejidad de $O(1)$ ya que únicamente se realizan instrucciones para solicitar memorias e inicializar variables.

* `lista_cantidad` tiene una complejidad de $O(1)$ ya que únicamente se retorna un dato perteneciente a la lista.

* `lista_esta_vacia` tiene una complejidad de $O(1)$ ya que se únicamente se retorna un valor, en base a un dato de la lista.

* `lista_insertar` tiene una complejidad de $O(n)$ debido a que si queremos insertar en una posición que no es la primera o la ultima de la lista. Se realiza un recorrido de Posición-1 nodos, hasta encontrar la posición correcta e insertarlo, en el peor de los casos esto podría significar n -1 iteraciones. Si solamente se pudiera insertar en la primera o en la ultima posición la función tendria una complejidad de $O(1)$ debido a que son instrucciones constantes, no se debería realizar iteración por la estructura interna que tiene la lista_t.

* `lista_eliminar` tiene una complejidad de $O(n)$ debido a que si queremos eliminar un elemento en una posición que no es la primera. Se realiza una iteración de  nodos, hasta encontrar su posición y eliminarlo, en el peor de los casos esto podría significar recorrer toda la lista. Si solamente se pudiera eliminar en la primera la función tendria una complejidad de $O(1)$ debido a que son instrucciones constantes.

* `lista_reemplazar` tiene una complejidad de $O(n)$ ya que para reemplazar un elemento hay que recorrer la lista hasta encontrarlo y reemplazarlo. Tomando el peor de los casos (el que el elemento este en la ultima posición) se tiene que recorrer la lista entera para reemplazarlo.

* `lista_obtener` tiene una complejidad de $O(n)$ ya que para obtener un elemento hay que recorrer la lista hasta encontrarlo y retornarlo. Tomando como el peor de los casos (el elemento este en la ultima posición), se recorre la lista entera para obtenerlo.

* `lista_buscar` tiene una complejidad de $O(n)$ considerando que la función comparador tiene una complejidad $O(1)$, debido a que en el peor caso el elemento buscado se encuentra en el N elemento. Si fuera el caso de que la función comparador tiene una complejidad $O(m)$ la complejidad final seria $O(n x m)$ lo que se reduce a $O(n)$.

* `lista_iterar` tiene una complejidad de $O(n)$ ya que en el peor de los casos todos los elementos al aplicarle la función F, devuelven Verdadero, por ende se recorrería la cantidad de nodos que contenga la lista.

* `lista_destruir` tiene una complejidad de $O(n)$ ya que se tiene que recorrer N cantidad de nodos, y aplicarle una cantidad de instrucciones constantes. 

* `lista_destruir_todo` tiene una complejidad de $O(n)$ ya que se tiene que recorrer N cantidad de nodos, y aplicarle una cantidad de instrucciones constantes. 

* `lista_iterador_crear` tiene una complejidad de $O(1)$ ya que únicamente se realizan instrucciones para solicitar memorias y vincular la lista pasada por parámetro.

* `lista_iterador_se_puede_iterar` tiene una complejidad de $O(1)$ ya que realiza una sola instrucción que es una verificación.

* `lista_iterador_siguiente` tiene una complejidad de $O(1)$ ya que únicamente se repunta el elemento actual de la lista iterada.

* `lista_iterador_obtener_elemento` tiene una complejidad de $O(1)$ ya que únicamente se retorna el dato del elemento al que el iterado esta apuntando.

* `lista_iterador_destruir` tiene una complejidad de $O(1)$ ya que simplemente es una instrucción para liberar memoria.


### Análisis de complejidades de funciones TDA cola.

* `cola_crear` tiene una complejidad de $O(1)$ ya que únicamente se realizan instrucciones para solicitar memorias e inicializar variables.

* `cola_encolar` tiene una complejidad de $O(1)$ debido a que se invoca a la función lista_insertar() que con los parámetros enviados, es de complejidad $O(1)$ por ende al sumar la cantidad de instrucciones mas la función encolar termina siendo un proceso de complejidad $O(1)$.

* `cola_desencolar` tiene una complejidad de $O(1)$  debido a que se invoca a la función lista_eliminar() que cuando se eliminar el primer elemento de la lista, es de complejidad $O(1)$ por ende al sumar la cantidad de instrucciones mas la función eliminar termina siendo un proceso de complejidad $O(1)$.

* `cola_frente` tiene una complejidad de $O(1)$ porque a pesar de que se invoca a la función lista_obtener() que en el peor caso tiene complejidad $O(n)$, con los parámetros ingresados se cumple el mejor caso y pasa a ser una función $O(1)$ y la suma total de complejidad es de $O(1)$

* `cola_esta_vacia` tiene una complejidad de $O(1)$ porque únicamente se retorna el resultado de invocar una función (lista_esta_vacia) cuya complejidad es $O(1)$.

* `cola_cantidad` tiene una complejidad de $O(1)$ porque únicamente se retorna el resultado de invocar una función (lista_cantidad) cuya complejidad es $O(1)$.

* `cola_destruir` tiene una complejidad de $O(n)$  debido a que se invoca una función cuya complejidad es $O(n)$  porque tiene que eliminar cada elemento asociado a la lista.

### Análisis de complejidades de funciones TDA pila.

* `pila_crear` tiene una complejidad de $O(1)$ ya que únicamente se realizan instrucciones para solicitar memorias e inicializar variables.

* `pila_apilar` tiene una complejidad de $O(1)$ debido a que se invoca a la función lista_insertar() que con los parámetros enviados, es de complejidad $O(1)$ por ende al sumar la cantidad de instrucciones mas la función encolar termina siendo un proceso de complejidad $O(1)$.

* `pila_desapilar` tiene una complejidad de $O(1)$ debido a que se invoca a la función lista_eliminar() que cuando se eliminar el primer elemento de la lista, es de complejidad $O(1)$ por ende al sumar la cantidad de instrucciones mas la función eliminar termina siendo un proceso de complejidad $O(1)$.

* `pila_tope` tiene una complejidad de $O(1)$ porque a pesar de que se invoca a la función lista_obtener() que en el peor caso tiene complejidad $O(n)$, con los parámetros ingresados se cumple el mejor caso y pasa a ser una función $O(1)$ y la suma total de complejidad es de $O(1)$

* `pila_esta_vacia` tiene una complejidad de $O(1)$ porque únicamente se retorna el resultado de invocar una función (lista_esta_vacia) cuya complejidad es $O(1)$.

* `pila_cantidad` tiene una complejidad de $O(1)$ porque únicamente se retorna el resultado de invocar una función (lista_cantidad) cuya complejidad es $O(1)$.

* `pila_destruir` tiene una complejidad de $O(n)$ debido a que se invoca una función cuya complejidad es $O(n)$  porque tiene que eliminar cada elemento asociado a la lista.

## 4. Decisiones de diseño y/o complejidades de implementación 

La mayor complejidad en el TP se encuentra en mantener las operaciones **apilar**, **desapilar**, **encolar**, **desencolar**, obtener el **tope** y obtener el **frente** con una complejidad **O(1)**. Con la estructura interna de la lista que plantee en un primer momento se me era imposible, debido a que solamente contenia la lista, y un puntero apuntando a la primera posición. Esto me llevaba a que si queria encolar al final necesariamente tenga que recorrer los N elementos de la lista. Lo cual traia una complejidad **O(n)**. Para evitar esto decidi sumar un puntero para en todo momento saber cual es el ultimo elemento de la lista. Esto me permite simplemente realizar una cantidad constante de instrucciones para hacer que las funciones pedidas mantengan una complejidad **O(1)**.

Además, un problema que me costo mucho identificar era que al ejecutar mi programa con el operador de multiplicación sin comillas, el programa interpreta al caracter *  como un comodin y lo reemplaza por todo el contenido en la carpeta como un argumentos, esto sumado a la forma que tenia de parsear las listas con la función strtol, la cual no encuentra ningun numero y establecia el final como la posición y despues establecia la posición como el fin, me llevaba a que en cada ciclo del while se repita el proceso y se cree un bucle sin fin. Al agregar la validacion y posteriormente abortar la función independientemente de lo enviado por el usuario me encuentro protegido ante ese caso.

A pesar de la complicacion y todo el tiempo implementado para descubrir el error. Me llevo como aprendizaje que independientemente de las validaciones minimas para evitar casos de usos incorrectos por parte del usuario, siempre hay que manejar todos los posibles casos de error para no sufrir problemas con la memoria u optimizar el tiempo de ejecucion.


## 5. Respuestas a las preguntas teóricas

### 5.1. Explicar qué es una lista, lista enlazada y lista doblemente enlazada.


- Explicar las características de cada una.
- Explicar las diferencias internas de implementación de cada una.
- Explicar ventajas y desventajas de cada una, si existen.

### 5.2 Explicar qué es una lista circular y de qué maneras se puede implementar.
Para implementar el....

### 5.3 Explicar la diferencia de funcionamiento entre cola y pila.
La principal diferencia entre una pila y una cola es la forma de manipular los elementos que estan contenidos en ellas. 
Es decir una cola tiene una estructura FIFO, el primero que entra en la cola, es el primero en salir, esto hace que las operaciones con los elementos se realicen en los extremos unicamente. Los cuales son llamados el frente y ultima posición.
En cambio las pilas mantienen una estructura LIFO, debido a que el ultimo elemento en ser apilado, es el primer elemento que posteriormente se saca. Por ese simplemente interactuamos con el elemento en un extremo, que usualmente es llamado el tope. 

### 5.4 Explicar la diferencia entre un iterador interno y uno externo.






clang-format -i -style=file pruebas/*.c src/*.c main.c