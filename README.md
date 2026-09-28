# Tetris - tetrisProyect

Proyecto de Tetris desarrollado en C++ utilizando estructuras, punteros y listas enlazadas. El programa cuenta con una interfaz gráfica para jugar y diferentes funcionalidades como movimiento, rotación, hold, piezas siguientes, puntuación, niveles, pausa, deshacer/rehacer y reproducción de la partida.

## Librería gráfica

El proyecto utiliza:

* **SFML 2** (Simple and Fast Multimedia Library)
* Lenguaje: **C++**
* IDE utilizado: **ZinjaI**

SFML se utiliza para crear la ventana del juego, dibujar el tablero, las piezas, botones, textos y demás elementos de la interfaz gráfica.

## Requisitos

Para ejecutar el proyecto se necesita:

* ZinjaI
* Compilador MinGW incluido/configurado en ZinjaI
* SFML 2
* Sistema operativo Windows

## Compilación

1. Descargar o clonar el repositorio.
2. Abrir el archivo `tetrisProyect.zpr` con ZinjaI.
3. Verificar que ZinjaI tenga configurada la librería SFML 2.
4. Compilar el proyecto desde ZinjaI utilizando la opción de compilación.
5. Si la compilación termina correctamente, ejecutar el programa desde ZinjaI.

## Ejecución

El programa se puede ejecutar directamente desde ZinjaI después de realizar la compilación.

También se puede ejecutar el archivo `.exe` generado por el compilador, siempre que las bibliotecas necesarias de SFML estén disponibles.

## Estructura del proyecto

El proyecto está dividido en diferentes archivos según la funcionalidad:

* `main.cpp` - Inicio y control principal del programa.
* `pieza.cpp / pieza.h` - Manejo de las piezas de Tetris.
* `tablero.cpp / tablero.h` - Manejo del tablero.
* `cola.cpp / cola.h` - Manejo de la cola de piezas siguientes.
* `pila.cpp / pila.h` - Manejo de la pieza Hold.
* `eventos.cpp / eventos.h` - Manejo de eventos del juego.
* `juego.cpp / juego.h` - Lógica principal del juego.
* `interfaz.cpp / interfaz.h` - Interfaz gráfica.
* `replay.cpp / replay.h` - Sistema de deshacer, rehacer y reproducción de la partida.
* `tetrisProyect.zpr` - Archivo de proyecto de ZinjaI.

## Controles

* ` <- ` / ` -> ` - Mover la pieza.
* ` ^ ` - Rotar la pieza.
* ` v ` - Bajar la pieza.
* ` SPACE ` - Bajar la pieza rápidamente.
* ` C ` - Guardar/intercambiar pieza Hold.
* ` A ` - Deshacer movimiento.
* ` D ` - Rehacer movimiento.
* ` Pausar ` - Pausar la partida.
* ` CONTINUAR ` - Continuar una partida pausada.
