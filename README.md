# Philosophers

## Descripción breve

El proyecto **Philosophers** forma parte del currículo de 42 Madrid y consiste en resolver el clásico problema de los *filósofos cenando*. Este desafío combina conceptos avanzados de concurrencia y sincronización, simulando cómo un grupo de filósofos comparten recursos limitados (tenedores) mientras alternan entre pensar, comer y dormir.  

---

## Objetivo del proyecto

El propósito de este proyecto es profundizar en la programación concurrente mediante:  

- La gestión eficiente de recursos compartidos.  
- La prevención de condiciones de carrera (*race conditions*) y bloqueos (*deadlocks*).  
- La implementación de una simulación robusta que cumpla con las restricciones del problema.  

---

## Características principales

- **Multithreading:** Cada filósofo se ejecuta como un hilo independiente.  
- **Sincronización eficiente:** Uso de *mutexes* para evitar conflictos en el acceso a los tenedores.  
- **Escalabilidad:** Permite personalizar el número de filósofos y otros parámetros de la simulación.  
- **Tolerancia a fallos:** Manejo preciso de errores y eventos críticos, como la muerte de un filósofo.  

---

## Funcionamiento técnico

### Flujo principal
1. **Creación de filósofos:** Cada filósofo se asocia a un hilo.  
2. **Ciclo de vida:** Los filósofos alternan entre:
   - **Pensar:** Esperan para intentar comer.  
   - **Comer:** Adquieren dos tenedores adyacentes (mutexes).  
   - **Dormir:** Liberan los recursos y descansan antes de volver a pensar.  
3. **Control de tiempo:** Se monitorean los intervalos de tiempo para evitar que un filósofo muera por inanición.  

### Sincronización
- Los tenedores se representan como *mutexes*, garantizando acceso exclusivo.  
- Se implementan estrategias para prevenir interbloqueos, como asignar recursos de manera ordenada.  

---

## Diagrama de flujo

```mermaid
graph TD;
    Inicio[Inicio] --> Configuración[Configurar parámetros iniciales]
    Configuración --> CrearHilos[Crear hilos para los filósofos]
    CrearHilos --> CicloDeVida[Ciclo de vida de cada filósofo]
    CicloDeVida --> Pensar[Pensar]
    Pensar --> IntentarComer[Intentar tomar dos tenedores]
    IntentarComer --> Comer[Comer]
    Comer --> Dormir[Dormir]
    Dormir --> Pensar
    Comer --> ChequearMuerte[¿Murió algún filósofo?]
    ChequearMuerte -->|Sí| Fin[Terminar simulación]
    ChequearMuerte -->|No| Pensar
