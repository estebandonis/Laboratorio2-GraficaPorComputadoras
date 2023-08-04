# CC2018-lab2
Utilizar SDL para simular el algoritmo de The Game of Life de Conway
## Using MacOS
Para ejecutarlo, debemos de tener los frameworks de SDL en el folder de /Library/Frameworks

Y luego ejecutar el siguiente comando en la terminal:
```shell
cmake -S . -B build
```

Luego debemos de entrar en la carpeta build:
```shell
cd build
```

Para después utilizar la librería make:
```shell
make
```

Y por ultimo ejecutar el archivo compilado (En este caso yo lo llame GAME, revise CMakeLists.txt):
```shell
./GAME
```

Al ejecutarlo se verá algo así:


![GameOfLife](https://github.com/estebandonis/Laboratorio2-GraficaPorComputadoras/assets/77749546/2b7e4f3a-a233-43b2-b163-4309b81ee01d)
