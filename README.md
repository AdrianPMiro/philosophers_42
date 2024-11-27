Disculpa la confusión! Aquí está el texto convertido a Markdown literal:

# Philosophers
🏆 42 Project

Philosophers es un proyecto de simulación diseñado para probar tus habilidades en concurrencia y sincronización. Basado en el clásico problema de los filósofos cenando, este proyecto simula cómo varios filósofos comparten recursos limitados mientras alternan entre pensar, comer y dormir.

## 🎯 **Objetivo del proyecto**
El objetivo principal de este proyecto es desarrollar una simulación eficiente y libre de errores que gestione múltiples hilos de ejecución. A través de esta experiencia, aprenderás a:
Evitar deadlocks y condiciones de carrera.
Sincronizar accesos a recursos compartidos utilizando mutexes.
Implementar lógica multihilo robusta y escalable.

## 🚀 **Características principales**
Gestión multihilo: Cada filósofo se ejecuta como un hilo independiente, gestionado de manera concurrente.
Sincronización segura: Uso de mutexes para evitar conflictos al acceder a los recursos (tenedores).
Prevención de bloqueos: Estrategias diseñadas para garantizar que los filósofos no queden en un estado de espera infinita.
Adaptabilidad: Configuración dinámica del número de filósofos y parámetros de simulación.

## 📁 **Estructura del proyecto**
```bash
Philosophers/
├── philo.c           # Lógica principal del programa
├── philo_routine.c   # Rutinas de los filósofos (pensar, comer, dormir)
├── check_end.c       # Verificaciones y condiciones de fin
├── philo.h           # Definiciones y cabeceras
├── Makefile          # Herramienta de compilación
└── README.md         # Este documento
```

## 💻 **Cómo usar**
1. **Instalación**
Clona el repositorio y compila el proyecto:
```bash
git clone https://github.com/tu_usuario/philosophers.git
cd philosophers
make
```
2. **Ejecución**
Lanza la simulación con los parámetros deseados:
```bash
./philo <número_de_filósofos> <tiempo_para_morir> <tiempo_para_comer> <tiempo_para_dormir> [número_de_comidas]
```
Parámetros:
* `<número_de_filósofos>`: Cantidad de filósofos en la mesa.
* `<tiempo_para_morir>`: Tiempo máximo (en ms) antes de que un filósofo muera de hambre.
* `<tiempo_para_comer>`: Tiempo que tarda un filósofo en comer.
* `<tiempo_para_dormir>`: Tiempo que un filósofo pasa durmiendo.
* `[número_de_comidas]` (opcional): Número de comidas necesarias para finalizar la simulación.

## 📖 **Funcionamiento técnico**
Los filósofos alternan entre pensar, comer y dormir en un ciclo continuo. Para comer, un filósofo debe tomar ambos tenedores adyacentes, representados como mutexes.
Si un filósofo no puede comer antes del tiempo límite, muere.

## 📊 **Diagrama del flujo**
```mermaid
graph TD;
    Inicio[Inicio] --> Configuración[Configurar parámetros]
    Configuración --> CrearHilos[Crear hilos para cada filósofo]
    CrearHilos --> CicloDeVida[Ciclo de vida de los filósofos]
    CicloDeVida --> Pensar[Pensar]
    Pensar --> IntentarComer[Intentar tomar dos tenedores]
    IntentarComer --> Comer[Comer]
    Comer --> Dormir[Dormir]
    Dormir --> Pensar
    Comer --> ChequearMuerte[¿Murió algún filósofo?]
    ChequearMuerte -->|Sí| Fin[Terminar simulación]
    ChequearMuerte -->|No| Pensar

## ✨ **Conclusión**
El proyecto Philosophers no solo representa un ejercicio práctico para aplicar conceptos de concurrencia y sincronización, sino que también enseña estrategias esenciales para trabajar con sistemas multihilo. A través de este desafío, aprenderás a manejar recursos limitados y desarrollar soluciones escalables para problemas complejos.

¿Estás listo para resolver el dilema de los filósofos cenando? 🍴
