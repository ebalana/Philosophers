# Philosophers
> Proyecto de la escuela 42 desarrollado por Ernest Balañá

## Descripción

El proyecto **Philosophers** explora los conceptos de **concurrencia**, **procesos** e **hilos** en C a través de una simulación del clásico **problema de los filósofos comensales**.

El objetivo es entender y evitar problemas típicos en sistemas concurrentes como **deadlocks**, **race conditions** y **starvation**, todo ello sin utilizar funciones externas no autorizadas.

## Enunciado resumido

Cinco filósofos se sientan alrededor de una mesa. Cada uno piensa, luego intenta comer con los dos tenedores que tiene a su izquierda y derecha. Solo puede comer si ambos tenedores están disponibles.

## Requisitos del proyecto

- Manejo correcto de **threads**, **mutexes**
- No debe haber **deadlocks** ni **race conditions**
- Cada filósofo debe:
  - Pensar
  - Tomar los dos tenedores
  - Comer
  - Soltar los tenedores
  - Dormir

- Se debe detener el programa si:
  - Un filósofo muere (no ha comido a tiempo)
  - Todos han comido el número de veces requerido

## Compilación

```bash
git clone https://github.com/ebalana/Philosophers.git
cd Philosophers
make
```

## Uso

- `./philo 1 800 200 200` – *El filósofo no debería comer y debería morir*
- `./philo 5 800 200 200` – *Ningún filósofo debería morir*
- `./philo 5 800 200 200 7` – *Ningún filósofo debería morir y la simulación debería detenerse cuando todos hayan comido al menos 7 veces cada uno*
- `./philo 4 410 200 200` – *Ningún filósofo debería morir*
- `./philo 4 310 200 100` – *Un filósofo debería morir*
