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

`./tarea2 foto.jpg foto_gris.jpg`, donde foto.jpg es la imagen original y foto_gris.jpg es la que se generará

Para las implementaciones paralelas:
`./tarea2 foto.jpg foto_gris.jpg 4`, donde 4 es el numero de hilos a ejecutar