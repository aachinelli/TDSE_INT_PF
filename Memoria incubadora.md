<div align="center">

<img width="535"  alt="image" src="https://github.com/Embebidos-Fran-Marcos-Nacho/tdse-tf_1-2/blob/08290a7a62c8a7d3fcd22fc57871dafbbf35ab15/logo-fiuba.png" />

**UNIVERSIDAD DE BUENOS AIRES**  
**Facultad de Ingeniería**  
**TA134 – Sistemas Embebidos**  
Curso X – Grupo X

# Incubadora automática de huevos de ave  
Sistema de monitoreo atmósferico y control de humedad y temperatura.  (a revisar)

## Autores
Pablo Martínez Madero — Legajo 106516  
Agustín Ezequiel Achinelli — Legajo 110124


**Fecha:** XX/08/2026  
**Cuatrimestre de cursada:** 1er cuatrimestre 2026  

*Trabajo realizado en la Ciudad Autónoma de Buenos Aires entre junio 2026 y agosto 2026.*
</div>

---

PROGRESO

FALTA ÍNDICE E HIPERVÍNCULOS
REVISAR HISTORIAL DE REVISIONES





## Resumen

Se desarrolló el prototipo de una incubadora de huevos automática, un sistema embebido en un microcontrolador.
El mismo cuenta con:
-
-

Esta memoria justifica su necesidad, detalla los requisitos y proporciona información y esquemas sobre su diseño en hardware y firmware. Además, se documentan los ensayos y pruebas realizados y el estado final del proyecto.


---

## Registro de versiones

*Historial de revisiones del documento.*

La Tabla 0.1 resume el historial de revisiones y entregas de esta memoria.

| Revisión | Cambios realizados | Fecha |
| :---: | --- | :---: |
| 1.0 | Escritura inicial de la memoria | 02/08/2026 |
| 1.1 | Primer entrega, sin vídeo | /2026 |


<em>Tabla 0.1 — Registro de versiones del documento.</em><br><br>

---



# Índice General




- [Capítulo 1: Introducción general](#capítulo-1-introducción-general)
  - [1.1 Análisis de necesidad y objetivo](#11-análisis-de-necesidad-y-objetivo) 		AGREGAR ESTO
  - [1.2 Productos comparables](#12-productos-comparables)
  - [1.3 Alcance y limitaciones](#13-alcance-y-limitaciones)
- [Capítulo 2: Introducción específica](#capítulo-2-introducción-específica)
  - [2.1 Requisitos](#21-requisitos)
  - [2.2 Casos de uso](#22-casos-de-uso)
    - [2.2.1 ](#221)		AGREGAR NOMBRES
    - [2.2.2 ](#222)
    - [2.2.3 ](#223)
  - [2.3 Descripción de módulos y Hardware](#23)
    - [2.3.1 Módulo de control (NUCLEO-F103RB)](#231)
    - [2.3.2 Módulo sensor de temperatura y humedad ](#232)
    - [2.3.3 Módulo de actuadores](#233)
    - [2.3.4 Módulo de interfaz](#234)
    - [2.3.5 Memoria EEPROM](#235)
- [Capítulo 3: Diseño e implementación](#capítulo-3-diseño-e-implementación)
  - [3.1 Arquitectura general](#31-arquitectura-general)
  - [3.2 Diseño de hardware](#32-diseño-de-hardware)
  - [3.3 Diseño de firmware](#33-diseño-de-firmware)
    - [3.3.1 Arquitectura de ejecución](#231)
    - [3.3.2 Máquina de estados del sistema](#232)
- [Capítulo 4: Ensayos y resultados](#capítulo-4-ensayos-y-resultados)
  - [4.1 Integración](#41)
  - [4.2 Pruebas funcionales de hardware Y software](#42)
  - [4.3 Ocupación de memoria: Console & Build Analyzer](#43)
  - [4.4 Medición y análisis de tiempos de ejecución (WCET)](#44)
    - [4.4.1 Metodología]()
    - [4.4.2 Resultados ]()
  - [4.5 Cálculo del Factor de Uso (U) de la CPU]()
  - [4.6 Medición y análisis de consumo]
  - [4.7 Cumplimiento de requisitos]
- [Capítulo 5: Conclusiones](#capítulo-5-conclusiones)
  - [5.1 Resultados obtenidos]()
  - [5.2 Posibles mejoras]()
- [Capítulo 6: Uso de herramientas de IA](#capítulo-6-uso-de-herramientas-de-ia)
- [Capítulo 7: Bibliografía y referencias](#capítulo-7-bibliografía-y-referencias)





# Capítulo 1: Introducción general

## 1.1 Análisis de necesidad y objetivo

Las incubadoras de huevos de ave cubren una necesidad industrial y doméstica que puede ser abordada por un sistema embebido. Su funcionamiento requiere mantener una 
temperatura y humedad ideal de incubación según el tipo de ave durante un período de tiempo (algunas semanas). También requieren una rotación periódica de los huevos durante las primeras semanas. El objetivo de este trabajo es diseñar e implementar un prototipo 
funcional de incubadora utilizando la arquitecura STM32.


## 1.2 Productos comparables

Se realizó un relevamiento del mercado local y se encontraron 2 alternativas similares, una de estilo industrial, de la marca Tinzer, y otra de un estilo casero o de baja gama, de la marca Brinsea.


1. **Incubadora estilo industrial Tinzer**  

<img src="https://github.com/aachinelli/TDSE_INT_PF/blob/main/Gr%C3%A1ficos%20y%20fotos/incubadoraTinzer.jpg" width="600" />
<em>Figura 1.X — XX(referencia comercial).</em><br><br>

Incubadora Tinzer. Características: 
Costo aproximado: $ ARS ($ USD)

2. **Incubadora estilo doméstico BRINSEA**  

<img src="https://github.com/aachinelli/TDSE_INT_PF/blob/main/Gr%C3%A1ficos%20y%20fotos/incubadora-brinsea.jpg" width="600" />
<em>Figura 1.X — XX(referencia comercial).</em><br><br>

Incubadora Brinsea. Características: 
Costo aproximado: $ ARS ($ USD)


Diferencias con el enfoque elegido

La Tabla 1.1 contrasta las prestaciones de los dos productos comerciales de referencia contra el prototipo desarrollado en este trabajo.

| Aspecto | TINZER  | BRINSEA | Prototipo desarrollado |
| :--- | :--- | :--- | :--- |
| **Monitoreo de temperatura y humedad** | POSEE | POSEE | POSEE |
| **Sensor de temperatura y humedad** |  |  | Sensor analógico SHT30  |
| **Interfaz de usuario** | Display 7 segmentos | PDisplay 7 segmentos | Pantalla LCD 16×2 con menú interactivo de dos niveles |
| **Selección de modos** | No disponible | No disponible | 3 modos precargados en una EEPROM externa. Modos personalizables. |
| **Registro de eventos** | No disponible | No disponible | Guardado del estado previo a un corte de suministro |
| **Base de tiempo** | No posee | No posee | RTC interno del STM32 |   ***REVISAR***
| **Consumo** | Consumo de 70 W a 220V | N/A (Sistema puramente mecánico) | Modo reposo (*Sleep*) con apagado de display | ***Se podría llegar a agregar un modo sleep?***
| **Rotación de huevos** | Motor eléctrico de bajo consumo |  | Servomotor SG90 sobre maqueta |
| **Construcción de la capsula** | Acero, melamina y policarbonato | Plástico transparente | No implementada (fuera de alcance) |
| **Costo** | ~$350.000 ARS | ~$300 USD a ~$700  | Prototipo de laboratorio - Precio estimado en componentes: ~$50000 ARS |



En resumen, el mercado ofrece soluciones parciales que cubren algunos de los objetivos del proyecto, pero ninguna combina la personalización por modo de incubación, el registro de estado en EEPROM y la interfaz configurable mediante display LCD y teclado. 
Esto justifica el desarrollo de un sistema propio que cubra todas estas funcionalidades con hardware disponible localmente.
Quedan fuera del alcance del proyecto implementaciones utilizadas por los productos comerciales, como el diseño de la caja incubadora.


## 1.3 Alcance y limitaciones

Alcance implementado:
- Electrónica de control
- Interfaz de usuario 
- Lógica de funcionamiento automático
- Guardado de eventos en memoria externa

Fuera de alcance actual:
- Construcción de la caja contenedora de huevos.
- Implementación de elementos térmicos y de aporte de humedad (se modelan con luces)

El detalle de los requisitos cumplidos se aborda en la sección 4.7.


---

# Capítulo 2: Introducción específica

Se procede a listar los requisitos a cumplir en el presente trabajo, en su primer versión (link) y en el informe de avance (link). Además, se listan los casos de uso.
En la sección 4.X se detalla el cumplimiento final de los requisitos.

## 2.1 Requisitos


|**Grupo**|**ID**|**Descripción**|
| :-: | :-: | :-: |
|**Temperatura**|1\.1|El sistema medirá continuamente la temperatura interior mediante un sensor dedicado.|
||1\.2|El sistema activará el elemento calefactor cuando la temperatura esté por debajo del umbral configurado.|
||1\.3|El sistema desactivará el elemento calefactor cuando la temperatura supere el umbral configurado.|
|**Humedad**|2\.1|El sistema medirá continuamente la humedad relativa interior.|
||2\.2|El sistema activará el humidificador cuando la humedad esté por debajo del umbral configurado.|
||2\.3|El sistema desactivará el humidificador cuando la humedad supere el umbral configurado.|
|**Rotación**|3\.1|El sistema rotará los huevos automáticamente a intervalos de tiempo configurables por tipo de huevo.|
||3\.2|El sistema indicará mediante un LED cada vez que se realice una rotación.|
||3\.3|El sistema inhibirá la rotación durante los últimos días del ciclo de incubación (lockdown), según el modo seleccionado.|
|**Interfaz de usuario**|4\.1|El sistema contará con una pantalla LCD para mostrar temperatura, humedad, día del ciclo y modo activo.|
||4\.2|El sistema contará con un teclado matricial para navegar entre menús y configurar parámetros.|
||4\.3|El sistema contará con LEDs indicadores de estado: calentador activo, humidificador activo y rotación.|
||4\.4|El sistema contará con un buzzer para alertas sonoras (alarmas y confirmaciones).|
|**Modos de incubación**|5\.1|El sistema soportará al menos tres modos predefinidos: huevo de gallina, pato y codorniz, con sus respectivos parámetros de temperatura, humedad y ciclo.|
||5\.2|El usuario podrá seleccionar el modo desde el menú de la interfaz gráfica.|
||5\.3|El sistema indicará en el display el día actual del ciclo de incubación.|
|**Alarmas**|6\.1|El sistema emitirá una alarma sonora y visual si la temperatura supera un umbral crítico configurable.|
||6\.2|El sistema emitirá una alarma sonora y visual si la humedad supera o cae por debajo de umbrales críticos.|
||6\.3|El sistema emitirá una alarma si el motor de rotación no completa el giro en el tiempo esperado.|
|**Almacenamiento**|7\.1|El sistema almacenará en la EEPROM externa el historial de temperatura, humedad y eventos de rotación.|
||7\.2|El sistema preservará la configuración activa y el día del ciclo ante cortes de energía.|

*Tabla 2.1: Requisitos iniciales del proyecto*

| GRUPO | ID | TAREA |
|----|----|----|
| Teperatura | 1.1 | El sistema medirá continuamente la temperatura interior mediante un sensor dedicado. |
|   | 1.2 | El sistema activará el elemento calefactor cuando la temperatura esté por debajo del umbral configurado. |
|   | 1.3 | El sistema desactivará el elemento calefactor cuando la temperatura supere el umbral configurado. |
| Humedad | 2.1 | El sistema medirá continuamente la humedad relativa interior. |
|   | 2.2 | El sistema activará el humidificador cuando la humedad esté por debajo del umbral configurado. |
|   | 2.3 | El sistema desactivará el humidificador cuando la humedad supere el umbral configurado. |
| Rotación | 3.1 | El sistema rotará los huevos automáticamente a intervalos de tiempo configurables por tipo de huevo. |
|   | 3.2 | El sistema indicará mediante un LED cada vez que se realice una rotación. |
|   | 3.3 | El sistema inhibirá la rotación durante los últimos días del ciclo de incubación (lockdown), según el modo seleccionado. |
| Interfaz | 4.1 | El sistema contará con una pantalla LCD para mostrar temperatura, humedad, día del ciclo y modo activo. |
|   | 4.2 | El sistema contará con un teclado matricial para navegar entre menús y configurar parámetros. |
|   | 4.3 | El sistema contará con LEDs indicadores de estado: calentador activo, humidificador activo y rotación. |
|   | 4.4 | El sistema contará con un buzzer para alertas sonoras (alarmas y confirmaciones). |
| Modos de incubación | 5.1 | El sistema soportará al menos tres modos predefinidos: huevo de gallina, pato y codorniz, con sus respectivos parámetros de temperatura, humedad y ciclo. |
|   | 5.2 | El usuario podrá seleccionar el modo desde el menú de la interfaz gráfica. |
|   | 5.3 | El sistema indicará en el display el día actual del ciclo de incubación. |
| Alarmas | 6.1 | El sistema emitirá una alarma sonora y visual si la temperatura supera un umbral crítico configurable. |
|   | 6.2 | El sistema emitirá una alarma sonora y visual si la humedad supera o cae por debajo de umbrales críticos. |
|   | 6.3 | El sistema emitirá una alarma si el motor de rotación no completa el giro en el tiempo esperado. |
| Almacenamiento | 7.1 | El sistema almacenará en la EEPROM externa el historial de temperatura, humedad y eventos de rotación. |
|   | 7.2 | El sistema preservará la configuración activa y el día del ciclo ante cortes de energía. |

<em>Tabla 2.2 — Requisitos ajustados en el informe de avances (alcance reducido por tiempos).</em><br><br>

## 2.2 Casos de uso

En las tablas 2.2 a 2.4 se presentan 3 casos de uso para el sistema. En estos casos de uso se puede apreciar el funcionamiento esperado del prototipo con flujos principales y flujos alternativos.

|**Disparador**|El usuario desea iniciar un ciclo de incubación seleccionando un modo y confirmando los parámetros.|
| :- | :- |
|**Precondiciones**|El sistema está encendido. No hay un ciclo de incubación activo. La pantalla LCD muestra el menú principal.|
|**Flujo principal**|El usuario navega con el teclado hasta el menú «Nuevo ciclo». Selecciona el tipo de huevo (gallina, pato o codorniz). El sistema muestra en el display los parámetros predefinidos para ese modo (temperatura, humedad, duración, intervalo de rotación). El usuario confirma con la tecla de aceptar. El sistema guarda la configuración en la EEPROM y comienza el ciclo: activa el calentador si es necesario, programa las rotaciones y emite un pitido de confirmación. El LCD pasa a mostrar la pantalla de monitoreo con temperatura, humedad y día del ciclo.|
|**Flujos alternativos**|a. El usuario cancela la selección con la tecla de retroceso: el sistema vuelve al menú principal sin iniciar ningún ciclo. b. La temperatura inicial está fuera del rango objetivo: el sistema activa inmediatamente el calentador y espera hasta alcanzar el rango antes de dar la confirmación sonora.|

*Tabla 2.2: Caso de uso 1 — El usuario inicia un ciclo de incubación*

|**Disparador**|La temperatura interior sale del rango permitido para el modo activo.|
| :- | :- |
|**Precondiciones**|El sistema está encendido con un ciclo de incubación activo. El sensor DHT22 está operativo.|
|**Flujo principal**|El sensor detecta que la temperatura supera o cae por debajo del umbral configurado. El sistema activa o desactiva el elemento calefactor según corresponda. El LED de calentador activo se enciende o apaga acorde. El LCD actualiza el valor de temperatura en tiempo real. Cuando la temperatura vuelve al rango, el sistema estabiliza el calentador y registra el evento en la EEPROM.|
|**Flujos alternativos**|a. La temperatura supera el umbral crítico (fallo grave): el sistema emite una alarma sonora prolongada mediante el buzzer, parpadea el LED de alarma y muestra un mensaje de error en el LCD hasta que el usuario reconozca la alarma. b. El sensor no responde: el sistema emite una alarma y detiene el ciclo de forma segura, registrando el fallo en la EEPROM.|

*Tabla 2.3: Caso de uso 2 — El sistema detecta temperatura fuera de rango*

|**Disparador**|Se alcanza el intervalo de tiempo programado para la rotación de huevos.|
| :- | :- |
|**Precondiciones**|El sistema está encendido con un ciclo de incubación activo. No se está en el período de lockdown (últimos días antes de la eclosión).|
|**Flujo principal**|El temporizador de rotación expira. El sistema activa el motor de paso para girar los huevos el ángulo configurado (típicamente 45° alternados). El LED de rotación parpadea durante el movimiento. El buzzer emite un pitido breve de confirmación. El sistema registra el evento de rotación en la EEPROM con timestamp. El motor se detiene y el sistema reanuda el monitoreo normal.|
|**Flujos alternativos**|a. El motor no completa el movimiento en el tiempo esperado (posible traba mecánica): el sistema emite una alarma sonora y visual, detiene el motor y registra el fallo en la EEPROM. b. El ciclo está en período de lockdown: el sistema omite la rotación, registra el evento y muestra en el LCD un mensaje indicando que la rotación está inhibida.|

*Tabla 2.4: Caso de uso 3 — El sistema rota los huevos automáticamente*


## 2.3 Descripción de módulos y Hardware

***AGREGAR FOTOS DE HARDWARE POR MÓDULOS***
En esta sección se muestran los principales módulos de hardware utilizados. Los mismos fueron seleccionados para cumplir con los requisitos mínimos de Hardware y su posibilidad de implementación junto a la placa NUCLEO STM32.
Además, se busco que los componentes sean compatibles con los requisitos de Software y permitan un procesamiento menor a 1 ms.

### 2.3.1 Módulo de control (NUCLEO-F103RB)
La placa NUCLEO-F103RB fue la provista para ser de procesador central. Todos los componentes de Hardware son controlados por su microcontrolador STM32. 

<div align="center">
<img width="800" alt="NUCLEO" src="NUCLEO" />
<p><em>Figura X: NUCLEO.</em></p>
</div>

### 2.3.2 Módulo sensor de temperatura y humedad

Para la tarea de sensado atmósferico de temperatura y humedad se optó por un shield compatible con STM32 que contiene un sensor SHT30.
El mismo es analógico, tiene comunicación por I2C, es de bajo consumo y de rápido funcionamiento (400 kHz).

<div align="center">
<img width="800" alt="SHT30" src="https://github.com/aachinelli/TDSE_INT_PF/blob/main/Gr%C3%A1ficos%20y%20fotos/SHT30.jfif" />
<p><em>Figura X: SHT30.</em></p>
</div>


### 2.3.3 Módulo de actuadores

Para simular el funcionamiento de un motor que rote los huevos con cierta periodicidad se utilizó un servomotor SG90. El mismo se comunica por PWM, lo que permite programar rotaciones parciales según la necesidad.

<div align="center">
<img width="800" alt="SERVO" src="https://github.com/aachinelli/TDSE_INT_PF/blob/main/Gr%C3%A1ficos%20y%20fotos/servo.jpg" />
<p><em>Figura X: SERVO.</em></p>
</div>

El actuador que simula el funcionamiento de un componente que aporte calor (resistencia térmica o lámparas de calor) es un led en serie con un relé genérico de 5 V. 
Este mismo se usa para demostrar que se conecta el led en un bus con suministro eléctrico, logrando calentar el recinto cuando sea necesario solamente alimentando el relé

<div align="center">
<img width="800" alt="RELÉ/LED" src="RELÉ/LED" />
<p><em>Figura X: RELÉ/LED.</em></p>
</div>


### 2.3.4 Módulo de interfaz

Por la necesidad de mostrar el estado actual de la incubación, la elección de modos, de mostrar estados previos a cortes de suministro y la elección de parámetros personalizados se buscó un componente único que pueda mostrar estos mensajes con facilidad.
El componente elegido fue un display LCD 16x2. Nos permite mostrar simbolos alfanuméricos y presentar los mensajes necesarios con un bajo consumo y con la posibilidad de cambiar su brillo.

<div align="center">
<img width="800" alt="LCD" src="https://github.com/aachinelli/TDSE_INT_PF/blob/main/Gr%C3%A1ficos%20y%20fotos/display_LCD.jpg" />
<p><em>Figura X: LCD.</em></p>
</div>

Se diseñaron opciones de entrada de datos al sistema acotadas y sencillas para disminuir el código y la lógica. Por esto se optó por un teclado de membrana de 4x1, al que se le mapearon 4
funciones: "OK/CONTINUAR", "VOLVER", "ARRIBA" y "ABAJO". Se conectó mediante las entradas GPIO a la placa NUCLEO.

<div align="center">
<img width="800" alt="TECLADO" src="https://github.com/aachinelli/TDSE_INT_PF/blob/main/Gr%C3%A1ficos%20y%20fotos/Teclado-Matricial-de-Membrana-4-Teclas-1-1.jpg" />
<p><em>Figura X: teclado.</em></p>
</div>



### 2.3.5 Memoria EEPROM

Para proporcionar una memoria externa con lectura y escritura se utilizó una memoria EEPROM 24C256. La misma nos da versatilidad y aproximadamente 32 kB de memoria. El uso de esta memoria será monitoreado
en la sección 5.X. 

<div align="center">
<img width="800" alt="EEPROM" src="https://github.com/aachinelli/TDSE_INT_PF/blob/main/Gr%C3%A1ficos%20y%20fotos/memoria_eeprom.jpg" />
<p><em>Figura X: EEPROM.</em></p>
</div>
---

# Capítulo 3: Diseño e implementación

## 3.1 Arquitectura general

Conociendo los requisitos propuestos y el hardware elegido se diseñó un diagrama en bloques.

En la Figura 3.1 se presenta el diagrama en bloques general. En el se presentan los distintos módulos y se muestran los sensores, actuadores y displays.

<img src="https://github.com/aachinelli/TDSE_INT_PF/blob/main/Gr%C3%A1ficos%20y%20fotos/Incubadora-diagrama.jpeg" width="600" />
<em>Figura 3.1 — Diagrama en bloques general.</em><br><br>


A partir del diagrama de la figura 3.1 se obtuvo una idea de la cantidad de conexiones con la placa NUCLEO. 
A medida que las pruebas fueron avanzando y considerando los puertos disponibles por la placa NUCLEO, se optó por utilizar el siguiente esquema XXX.

<img src="CONEXIONES" width="600" />
<em>Figura 3.1 — CONEXIONES.</em><br><br>




## 3.2 Diseño de hardware

En el siguiente apartado se detallan las soluciones de Hardware adoptadas en línea con las pautas de entrega. El objetivo final es conseguir un conexionado de todo el Hardware de (prolijidad, soldado, etc.)
Se optó por usar una placa experimental ...

Como se mencionó previamente, se utilizó el diagrama 3.X de guía para el conexionado con la placa. Considerando que es necesario conectar los siguientes actuadores y sensores.
Se procedieron a asignar los siguientes pines 


| Función | Puerto | Protocolo |
| :--- | :--- | :--- |
|Teclado-Volver|PC7|GPIO|
|Teclado-Enter|PB6|GPIO|
|Teclado-Abajo|PA7|GPIO|
|Teclado-Arriba|PA6|GPIO|
|SCL - 1 (LCD y EEPROM)|PB10|I2C| 
|SDA - 1 (LCD Y EEPROM)|PB11|I2C|
|SCL - 2 (SENSOR)|PB8|I2C|
|SDA - 2 (SENSOR)|PB9|I2C|
|Led|PC8|GPIO|   
|Relé|PC9|GPIO|
|Servo|PA15|PWM (TIM2 CH1)|

<p align="center"><em>Tabla X.X: Asignación de pines de la placa núcleo.</em></p>



## 3.3 Diseño de firmware
En este apartado se detalla la construcción del Software desarrollado para el funcionamiento del prototipo de incubadora. El mismo fue desarrollado bajo una estructura 
Bare Metal, con un sistema determinado por eventos. Se utilizó una estructura modular. Se utilizaron 3 módulos: modulos de sensado, procesado y actuación.
Se buscó cuidar el consumo energético, la memoria y obtener un código legible y de fácil comprensión.



****
○ Bare Metal (sin Sistema Operativo), del tipo Event-Triggered System
○ Estructurada/Modular (Escrutar/Procesar/Actuar), nada de código Spaguetti
○ Patrones de software:
■ Ejecutor cíclico, Super-Loop (polling & interrupts) => 1 vuelta < 1mS
■ Tick = 1mS (Systick => Callback)
■ Tareas de código no bloqueante, ya sea temporizada o no temporizada
■ Modelos - Diagramas de Estado - c/Interfaces (colas, estructuras, array de estructuras)
■ Menú Interactivo
■ Bajo Consumo
■ Al menos dos modos de operación (NORMAL, SET_UP, FALLA, ...)
■ Periféricos con comunicación SPI y/o I2C
■ Periféricos gestionados por Polling (siempre que no sea código bloqueante), Interrupts o DMA
(=> Callbacks), por ejemplo
****


### 3.3.1 Arquitectura de ejecución

Todas las tareas a realizar se rigen por un ejecutor cíclico con velocidad de 1kHz, obteniendo tareas que se realizan en su totalidad en menos de 1 ms. El ejecutor cíclico se 
guía por el `SysTick`, que al ejecutar un loop se ejecuta la lista de tareas vistas en la figura 3.X. ****REVISAR****

 Además, se utilizan tareas no bloqueantes, es decir no se utiliza el `HAL_Delay()` para generar una temporización. 


Se recorren las tareas en el siguiente orden

1. `task_sensor_update`
2. `task_memory_update`
3. `task_system_update`
4. `task_actuator_update`
5. `task_display_update`


Cada tarea se ejecuta en cada tick y su tiempo se mide con contador de ciclos (`DWT->CYCCNT`) para cálculo de WCET.

 
El firmware se organiza como un ejecutivo cíclico gobernado por el `SysTick`, configurado a 1000 ticks por segundo. 
El *callback* del SysTick incrementa un contador de ticks pendientes; el lazo principal detecta ese contador y, por cada tick pendiente, 
ejecuta una vuelta completa de la lista de tareas en el orden fijo que ilustra la Figura 3.9:


<div align="center">
<img width="650" alt="ejecutivo ciclico" src="https://raw.githubusercontent.com/Matias-J-Sanchez-Q/tdse-tf_2026-1erC_2-02/main/escrutar.jpeg" />
<p><em>Figura 3.9: Orden de despacho de las tareas dentro de una vuelta del ejecutivo cíclico.</em></p>
</div>
 
El orden que muestra la Figura 3.9 no es arbitrario: garantiza que un evento generado por un sensor en el tick *N* sea procesado por la FSM y ejecutado por los actuadores en ese mismo tick, acotando la latencia de punta a punta a 1 ms.
 
Ninguna tarea bloquea. No se utiliza `HAL_Delay()` en el lazo principal: todas las temporizaciones (mensajes, refresco de UI, inactividad, pulsos de alarma, ciclo de escritura de la EEPROM) se resuelven con contadores de ticks.
 
Además, las tareas se comunican por interfaces. No hay comunicación por variables globales. Cada tarea tiene asignada una interfaz: 


|Tarea|Interfaz|
| `task_sensor_update` | `task_sensor_interface` |
| `task_memory_update` | `task_memory_interface` |
| `task_system_update` | `task_system_interface` |
| `task_actuator_update` |`task_actuator_interface` |
| `task_display_update`| `task_display_interface` |


### 3.3.2 Máquina de estados del sistema



---

# Capítulo 4: Ensayos y resultados

Esta sección está dedicada a mostrar los resultados de la integración de Software y Hardware en el armado del prototipo de la incubadora automática.

## 4.1 Integración 

En el siguiente video se muestra el correcto funcionamiento del prototipo integrado, simulando distintas situaciones atmósfericas y mostrando las respuestas del sistema a estas.

VÍDEO 



## 4.2 Pruebas funcionales de hardware Y software

| Subsistema | Ensayo realizado | Resultado / Criterio de validación | Estado |
| :--- | :--- | :--- | :---: |
| **Hardware** | Verificación de continuidad  | Ausencia de cortocircuitos o falsos contactos en la placa experimental | ✅ |
| **Hardware** | Respuesta correcta del teclado | Correcta atenuación y respuesta lineal en el ADC (potenciómetro y LDR) | ✅ |
| **Hardware** | Correcta visualización del LCD | Correcta atenuación y respuesta lineal en el ADC (potenciómetro y LDR) | ✅ |
| **Hardware** | Correcto funcionamiento del sensor | Correcta atenuación y respuesta lineal en el ADC (potenciómetro y LDR) | ✅ |
| **Firmware** | FSM de antirrebote de pulsadores | Filtrado exitoso de rebotes mecánicos en el botón de confirmación y sensor magnético | ✅ |
| **Firmware** | Correcta inerpretación del sensor | Mapeo estable del sensor por código | ✅ |
| **Firmware** | Persistencia en EEPROM y RTC | Lectura y escritura correcta de marcas de tiempo e historial por bus I²C | ✅ |
| **Firmware** | Máquina de estados global | Transiciones robustas y sin bloqueos entre `NORMAL`, `SET_UP` y `REPOSO` | ✅ |

<p align="center"><em>Tabla 4.1: Resumen de ensayos funcionales de hardware y firmware.</em></p>



## 4.3 Ocupación de memoria: Console & Build Analyzer
 
 
## 4.4 Medición y análisis de tiempos de ejecución (WCET)


### 4.4.1 Metodología
 
 
### 4.4.2 Resultados
 

## 4.5 Cálculo del Factor de Uso (U) de la CPU
 

## 4.6 Medición y análisis de consumo
 


 
## 4.7 Cumplimiento de requisitos


| Estado | Descripción      |
|-----|---------------------|
| 🟢 | Implementado |
| 🟡 | Implementado parcialmente |
| 🔴 | Sin implementar/requerimiento descartado |

| ESTADO | GRUPO | ID | TAREA |
|:--:|----|----|----|
| 🟢 | Temperatura | 1.1 | El sistema medirá continuamente la temperatura interior mediante un sensor dedicado. |
| 🟢 |   | 1.2 | El sistema activará el elemento calefactor cuando la temperatura esté por debajo del umbral configurado. |
| 🟢 |   | 1.3 | El sistema desactivará el elemento calefactor cuando la temperatura supere el umbral configurado. |
| 🟢 | Humedad | 2.1 | El sistema medirá continuamente la humedad relativa interior. |
| 🔴 |   | 2.2 | El sistema activará el humidificador cuando la humedad esté por debajo del umbral configurado. |
| 🔴 |   | 2.3 | El sistema desactivará el humidificador cuando la humedad supere el umbral configurado. |
| 🟢 | Rotación | 3.1 | El sistema rotará los huevos automáticamente a intervalos de tiempo configurables por tipo de huevo. |
| 🟢 |   | 3.2 | El sistema indicará mediante un LED cada vez que se realice una rotación. |
| 🟢 |   | 3.3 | El sistema inhibirá la rotación durante los últimos días del ciclo de incubación (lockdown), según el modo seleccionado. |
| 🟢 | Interfaz | 4.1 | El sistema contará con una pantalla LCD para mostrar temperatura, humedad, día del ciclo y modo activo. |
| 🟢 |   | 4.2 | El sistema contará con un teclado matricial para navegar entre menús y configurar parámetros. |
| 🟡 |   | 4.3 | El sistema contará con LEDs indicadores de estado: calentador activo, humidificador activo y rotación. |
| 🔴 |   | 4.4 | El sistema contará con un buzzer para alertas sonoras (alarmas y confirmaciones). |
| 🟢 | Modos de incubación | 5.1 | El sistema soportará al menos tres modos predefinidos: huevo de gallina, pato y codorniz, con sus respectivos parámetros de temperatura, humedad y ciclo. |
| 🟢 |   | 5.2 | El usuario podrá seleccionar el modo desde el menú de la interfaz gráfica. |
| 🟢 |   | 5.3 | El sistema indicará en el display el día actual del ciclo de incubación. |
| 🔴 | Alarmas | 6.1 | El sistema emitirá una alarma sonora y visual si la temperatura supera un umbral crítico configurable. |
| 🔴 |   | 6.2 | El sistema emitirá una alarma sonora y visual si la humedad supera o cae por debajo de umbrales críticos. |
| 🔴 |   | 6.3 | El sistema emitirá una alarma si el motor de rotación no completa el giro en el tiempo esperado. |
| 🟡 | Almacenamiento | 7.1 | El sistema almacenará en la EEPROM externa el historial de temperatura, humedad y eventos de rotación. |
| 🟢 |   | 7.2 | El sistema preservará la configuración activa y el día del ciclo ante cortes de energía. |


---

# Capítulo 5: Conclusiones

## 5.1 Resultados obtenidos

El prototipo simula satisfactoriamente el funcionamiento de un ciclo de incubación en tiempo y forma. Además, se cumplieron los requisitos mínimos de Hardware y Firmware. Por último se cumplieron la mayoría de los objetivos,
 dejando de lado aquellos que significaban un aumento sustancial en tiempo de desarrollo.

## 5.2 Posibles mejoras




---

# Capítulo 6: Uso de herramientas de IA

Se explicita el uso de herramientas de Inteligencia Artificial en las siguientes tareas:

- Corrección de errores en los informes

- Programación STM32 (estructura y funcionamiento)

- Depuración y solución de problemas: consultas a las herramientas sobre problemas en el código o posibles errores no tenidos en cuenta

---

# Capítulo 7: Bibliografía y referencias

1. STMicroelectronics, *UM1724 - STM32 Nucleo-64 boards user manual*.  
2. STMicroelectronics, *MB1136 - Electrical Schematic - STM32 Nucleo-64 boards*.  
3. STMicroelectronics, *STM32F103RB Datasheet*.  
4. ON Semiconductor, *MOC3023M Datasheet*.  
5. STMicroelectronics, *BTA06-600C Datasheet / notas de aplicación TRIAC*.  
6. Repositorio del proyecto: `https://github.com/Embebidos-Fran-Marcos-Nacho/tdse-tf_1-2`.

Hoja de datos SHT30 !!!
Hoja de datos LCD !!!


Referencias internas del repositorio:
- `README.md`
- `Informe_de_Avances.md`
- `Seguimiento.md`
- `Diagrama de Harel/STATECHART_EXPLANATION.md`
- `Memoria técnica/cosas e imagenes para memoria técnica - hardware/*`
- `listado de cosas hechas con IA.txt`


[1] STMicroelectronics. *STM32F103RB Datasheet*.

[2] STMicroelectronics. *RM0008 – STM32F10xxx Reference Manual*.

[3] STMicroelectronics. *UM1724 – STM32 Nucleo-64 boards user manual*.

[4] Maxim Integrated. *DS3231 Extremely Accurate I²C-Integrated RTC/TCXO/Crystal Datasheet*.

[5] Microchip/Atmel. *AT24C32 EEPROM Datasheet*.

[6] Texas Instruments. *PCF8574 Remote 8-Bit I/O Expander Datasheet*.

[7] TowerPro. *SG90 Micro Servo Datasheet*.


---

● Hardware obligatorio & Hardware adicional de su Propuesta
● Programación obligatorio & Programación adicional de su Propuesta
● El documento deben incluir lo siguiente, tal como se indicó más arriba en el contenido de la secciones:
○ Link a un Video breve de su Trabajo Final funcionando en la sección "Pruebas de
Integración"; en la columna "video" pueden ver ejemplos de videos apropiados

TA134 – TdSE – TF – Entregas – 2026 – Rev.: 05 | Página: 6

TA134 – Taller de Sistemas Embebidos

Trabajo Final
Pautas y Requisitos

○ Esquema eléctrico, vistas del cableado (similar a vistas del libro “A Beginner’s Guide to
Designing Embedded System Applications on Arm Cortex-M Microcontroller”)
○ Descripción del comportamiento
○ Salida de la pantalla Console & Build Analyzer, indicando asignación de memoria luego de
compilar la versión definitiva, por secciones (tamaño de text, data, bss ... en bytes) y regiones
(tamaño de RAM, FLASH en byte y %)
○ Medición y análisis de tiempos de ejecución de cada tarea (WCET)
○ Cálculo del Factor de Uso (U) de la CPU
○ Medición y análisis de consumo de 3,3V y 5V (con miliamperímetro y osciloscopio), sin y con
bajo consumo
○ Detalle del uso de herramientas de IA en su trabajo (ejemplo)
