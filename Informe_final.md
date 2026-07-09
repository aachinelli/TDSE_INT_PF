<p align="center">
 <img src="https://www.fi.uba.ar/images/logo-fiuba.png" aling="center" alt="image2" width="50%">
</p>

# Memoria del trabajo final: [Incubadora de huevos automática]

<table align="center">
  <tr>
    <th>Autor</th>
    <th>Padrón</th>
    <th>Mail</th>
  </tr>
  <tr>
    <td>Achinelli, Agustín Ezequiel</td>
    <td>110124</td>
    <td>aachinelli@fi.uba.ar</td>
  </tr>
  <tr>
    <td>Martinez Madero, Pablo</td>
    <td>106516</td>
    <td>pmartinezm@fi.uba.ar</td>
  </tr>
</table>

<p align="center">
  2026 | 1er Cuatrimestre
</p>

<p align="center">
  Taller de Sistemas Embebidos (TA134)
</p>

<p align="center">
  Universidad de Buenos Aires | Facultad de Ingeniería
</p>

<p align="center">
  Este trabajo ha sido realizado en la ciudad de Haedo y en la ciudad de Tigre, entre junio de 2026 y agosto de 2026.
</p>

# Resumen

En el trabajo a continuación se detallará el desarrollo de una incubadora de huevos automática, teniendo como soporte principal la placa NUCLEO-F103RB y código en lenguaje C. Para llevar a cabo este proyecto, se utilizarán varios módulos descriptos a continuación que se integrarán en conjunto para cumplir con los requisitos propuestos.
La idea del mismo es integrar en conjunto los conceptos vistos en la cátedra tales como lectura analógica digital, comunicación SPI, PWM, entre otros.

# Índice general

- [Registro de versiones](#registro-de-versiones)
- [Introducción general](#introducción-general)
  - [1.1. Objetivo del trabajo](#11-objetivo-del-trabajo)
  - [1.2. Motivaciones para realizar el trabajo](#12-motivaciones-para-realizar-el-trabajo)
  - [1.3. Funcionamiento de un órgano de tubos](#13-funcionamiento-de-un-órgano-de-tubos)
  - [1.4. Desarrollo de las funcionalidades en el microcontrolador](#14-desarrollo-de-las-funcionalidades-en-el-microcontrolador)
- [Introducción específica](#introducción-específica)
  - [2.1. Requisitos](#21-requisitos)
  - [2.2. Casos de uso](#22-casos-de-uso)
  - [2.5. Servomotor](#25-servomotor)
- [Diseño e implementación](#diseño-e-implementación)
  - [3.1. Hardware](#31-hardware)
    - [3.1.1. Placa con microcontrolador](#311-placa-con-microcontrolador)
    - [3.1.2. Potenciómetro](#312-potenciómetro)
    - [3.1.3. LEDs y display de 7 segmentos](#313-leds-y-display-de-7-segmentos)
    - [3.1.4. Botones](#314-botones)
    - [3.1.8. Servomotor](#318-servomotor)
  - [3.2. Firmware del microcontrolador](#32-firmware-del-microcontrolador)
- [Ensayos y resultados](#ensayos-y-resultados)
  - [4.1. Pruebas funcionales del hardware](#41-pruebas-funcionales-del-hardware)
  - [4.2. Pruebas funcionales del firmware](#42-pruebas-funcionales-del-firmware)
  - [4.3. Pruebas de integración](#43-pruebas-de-integración)
  - [4.4. Circuito esquemático](#44-circuito-esquemático)
  - [4.5. Medición y análisis del consumo energético](#45-medición-y-análisis-del-consumo-energético)
  - [4.6. Medición y análisis de tiempos de ejecución](#46-medición-y-análisis-de-tiempos-de-ejecución)
  - [4.7. Cumplimiento de requisitos](#47-cumplimiento-de-requisitos)
  - [4.8. Comparación con otros sistemas similares](#48-comparación-con-otros-sistemas-similares)
  - [4.9. Documentación del desarrollo realizado](#49-documentación-del-desarrollo-realizado)
- [Conclusiones](#conclusiones)
  - [5.1. Resultados obtenidos](#51-resultados-obtenidos)
  - [5.2. Próximos pasos](#52-próximos-pasos)
- [Bibliografía](#bibliografía)

# Registro de versiones

| Revisión | Cambios realizados | Fecha |
| --- | --- | --- |
| Versión 1.0 | N/A | 10/7/2026 |


# CAPÍTULO 1
# Introducción general

## 1.1. Objetivo del trabajo

El objetivo de este proyecto es diseñar e implementar un mecanismo automático de cuidado de huevos para aves domésticas que permita medir, 
registrar y modificar variables ambientales (temperatura y humedad) en un ambiente controlado, e implementar calentamiento y rotación de los huevos para asegurar su desarrollo correcto. 
Además, se proyecta diseñar distintos modos de funcionamiento según el tipo de huevo y etapa de su desarrollo, seleccionables a través de una interfaz gráfica compuesta por un display LCD y un teclado matricial.


## 1.3. Funcionamiento de una incubadora

La idea general de una incubadora doméstica, que es a lo que se apunta con este proyecto, es que una vez encendido el prototipo se pueda comenzar a incubar un nuevo tipo de especie, cargando los parámetros que se requieren desde 0, ya precargados en la memoria, o bien continuar con este proceso en caso de alguna interrupción externa. 
Luego de haber seteado los parámetros de una u otra forma, comienza a calentar o ventilar el interior de la incubadora hasta llegar a los valores fijados que serán sensados cada cierto tiempo para obtener el control del mismo. Es importante que durante lo que dure el proceso según el tipo de huevo se muestren por pantalla los valores actuales del interior y notifique en caso de un exceso o disminución de los mismos.


## 1.4. Desarrollo de las funcionalidades en el microcontrolador
Para llevar a cabo las funciones, desde la programación se diseña un ejecutor cíclico el cuál va realizando el llamado a las distintas tareas que se requieren dentro del sistema la limitación en recorrer todas las operaciones es de un milisegundo de forma que se vaya ejecutando en tiempo real.
Para sensar la temperatura y humedad se optó por el DHT22 que integra ambas funciones y se maneja gracias a una librería externa; El LCD 16X2 que se utiliza para mostrar al usuario se maneja con el protocolo SPI y también es llamado con funciones de librería externa.
El control para las opciones dentro del menú se realiza con una botonera del tipo membrana 4X1 configurada como pines de entrada a la placa y gracias al control del ciclo de trabajo por PWM, controlamos la posición de un servomotor.



# CAPÍTULO 2
# Introducción específica

## 2.1. Requisitos

En la siguiente tabla se pueden agrupar por módulos los requerimientos del proyecto

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


## 2.2. Servomotor
Para simular la rotación del soporte para los huevos, fue conveniente considerar una salida PWM del microcontrolador y controlar el servomotor SG90, 
que si bien tiene un bajo consumo de corriente es uno de los dispositivos que se debe alimentar por fuera de la placa ya que por algún esfuerzo en particular puede superar la corriente máxima del pin y quemar este puerto.

<p align="center">
 <img src="https://github.com/aachinelli/TDSE_INT_PF/blob/85cc1a70a32646fde2cac301acd4e5d191e399b5/servo.jpg" alt="image2" width="40%">
</p>

## 2.3. Sensor DHT22
Este sensor se eligió ya que integra ambos sensores y se puede controlar mediante un solo pin de datos. Mide temperaturas de -40°C a 80°C con ± 0.5°C de precisión gracias a su termistor interno y humedad del 0% al 100% con una exactitud del 2% gracias un sensor capacitivo que envían señales analógicas a un pequeño chip integrado que se encarga de convertirlas en una señal digital.

<p align="center">
 <img src="" alt="image2" width="40%">
</p>

## 2.4. Sensor LCD 16X2
Este display alfanumérico se consideró a modo de interfaz con el usuario para poder establecer comunicación con el sistema a través de la selección en el menú, los modos de incubación y realizar una visualización en tiempo real del estado actual.

<p align="center">
 <img src="https://github.com/aachinelli/TDSE_INT_PF/blob/85cc1a70a32646fde2cac301acd4e5d191e399b5/lcd_16x2.jpg" alt="image2" width="40%">
</p>

# CAPÍTULO 3
# Diseño e implementación

## 3.1. Hardware


### 3.1.1. Placa con microcontrolador


### 3.1.3. LEDs y display de 7 segmentos



## 3.2. Firmware del microcontrolador

El firmware ha sido desarrolado implementando en lenguaje C un gestor cíclico de tareas con cuatro tareas bajo su control. A excepción de Actuator, cada tarea tiene una interfaz asociada para recibir eventos provenientes de las otras tareas. En la figura 3.2 se presenta un esquema entendible de los bloques principales del firmware. 


El código comienza realmente en el main.c, el cual únicamente inicializa los periféricos y pasa el control a cyclic_executive.c. Seguidamente, cyclic_executive se encarga de inicializar el DWT (Data Watchpoint and Trace) para poder medir el tiempo con alta precisión, posteriormente inicializa todas las tareas, para comenzar a ejecutar todas, cada vez que se produce un SysTick, una vez por milisegundo.

Una vez actualizadas todas las tareas, entra en modo sleep sin suspender el tick del sistema, dejando los relojes de los periféricos y de la SRAM activos para continuar de forma correcta las transferencias vía DMA presentes en cada tarea. De esa manera, espera la siguiente interrupción para volver a actualizar las tareas y así ahorrar energía en el intervalo libre. Si la interrupción ocurre debido a la finalización de una transferencia DMA, continúa el ciclio sin actualizar las tareas ya que g_cyclic_executive_tick_cnt es 0 y vuelve a entrar en modo sleep.

Cyclic_executive se encarga también de medir el peor tiempo de ejecución (WCET) de cada tarea, contando el tiempo que le lleva a cada una actualizarse, cada vez que da dicha orden. Esto permite mantener los márgenes de ejecución de cada tarea dentro de un marco lo más estable y predecible posible.

Hasta el presente punto, se trabajó de igual manera que se lo hizo durante la cursada, el código es completamente estándard, sin particularidades.





# CAPÍTULO 4
# Ensayos y resultados

## 4.1. Pruebas funcionales del hardware

Tres veces se recurrió a realizar pruebas estrictamente sobre el hardware, debido a que se trabajó principalmente realizando pruebas de integración a medida que se fue avanzando el trabajo.


## 4.2. Pruebas funcionales del firmware


## 4.3. Pruebas de integración



## 4.4. Circuito esquemático


## 4.5. Medición y análisis del consumo energético



## 4.6. Medición y análisis de tiempos de ejecución



## 4.7. Cumplimiento de requisitos



## 4.8. Comparación con otros sistemas similares

(...) Comparación resaltando principalmente ventajas de este sistema con respecto a otros (...)

## 4.9. Documentación del desarrollo realizado

En la tabla 4.8 se presentan los elementos que resumen la información más importante a tener en cuenta a la hora de revisar el trabajo y entender qué, por qué y cómo se realizó. 


# CAPÍTULO 5
# Conclusiones

## 5.1. Resultados obtenidos

Los principales aportes del trabajo realizado son los siguientes:

- Haber aprendido a desarrollar un sistema embebido de forma ordenada y estandarizada.
- Haber aprendido a optimizar código para realizar las tareas de forma más eficiente.
- Haber aprendido a utilizar la mayor cantidad de funcionalidades que presenta el microcontrolador para lograr mayores y más estables velocidades de ejecución.
- Haber aprendido a documentar de forma detallada los pasos realizados.
- Haber aprendido a aplicar los distintos protocolos presentes en el trabajo.
- Haber comenzado a trabajar con componentes SMD.
- Haber tenido que familiarizarse con la revisión eficiente de hojas de datos.
- Haber aprendido a utilizar gestores de versiones de forma habitual.

## 5.2. Próximos pasos

(...) Próximos pasos a implementar para expandir el alcance del trabajo (...)

# Bibliografía

El trabajo se realizó exclusivamente con las presentaciones y ejemplos provistos por la cátedra, y consultas varias a las distintas IA.

\[1\] Notre-Dame organ, Yves Castagnet plays Dupré Prelude & fugue in B major (June 2017). [Online]. Available: https://www.youtube.com/watch?v=9HskcJlixGs

\[2\] Módulo Bluetooth ESP32 C3 RISC-V. [Online]. Available: https://www.espressif.com/en/products/socs/esp32-c3

\[3\] Librería ESP32 BLE Arduino. [Online]. Available: https://docs.arduino.cc/libraries/esp32-ble-arduino

\[4\] The Bluetooth Low Energy Primer. [Online]. Available: https://www.bluetooth.com/bluetooth-le-primer

\[5\] RISC-V Ratified Specification. [Online]. Available: https://riscv.org/specifications/ratified

\[6\] MIDI Specifications. [Online]. Available: https://midi.org/specs

\[7\] Placa NUCLEO-F103RB. [Online]. Available: https://os.mbed.com/platforms/ST-Nucleo-F103RB

\[8\] Presentación del trabajo final. [Online]. Available: https://youtu.be/HGJKOISGU5c

\[9\] MB1136 - Electrical Schematic - STM32 Nucleo-64 boards. [Online]. Available: https://www.st.com/resource/en/schematic_pack/mb1136-default-c04_schematic.pdf

\[10\] Multímetro digital DT830D. [Online]. Available: https://noganet.ar/productos/dt-830d-tester-digital
