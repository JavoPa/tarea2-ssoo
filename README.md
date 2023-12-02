# tarea2-ssoo
Tarea 2: procesamiento paralelo

# Para la ejecución del programa, ejecutar los siguientes comandos:

## Instalación de paquetes (Linux Ubuntu/Debian):

`sudo apt update`

`sudo apt install libopencv-dev`

`sudo apt install build-essential`

`sudo apt install cmake`

## Creación de carpetas y ubicación:

`git clone https://github.com/JavoPa/tarea2-ssoo.git`

`cd tarea2-ssoo/ProgramaSecuencial` o `cd tarea2-ssoo/paralela-thread` o `cd tarea2-ssoo/paralela-api`, dependiendo de la que quieras utilizar

## Compilación y ejecución:

`cmake .`

`make`

Para el programa secuencial:

`./ProgramaSecuencial FotoColor.jpg FotoGris.jpg`, donde FotoColor.jpg es la imagen original y FotoGris.jpg es la que se generará

Para las implementaciones paralelas:

foto.jpg es la original y foto_gris.jpg es la que se generará

`./paralela-thread foto.jpg foto_gris.jpg 4`, donde `4` es el numero de hilos a ejecutar

`./paralela-api foto.jpg foto_gris.jpg 4`, donde `4` es el numero de hilos a ejecutar