![](media/image1.png){width="5.5787379702537185in" height="1.8586472003499563in"}

**UNIVERSIDAD DE BUENOS AIRES\
Facultad de Ingeniería\
(TA134) Sistemas Embebidos**

Memoria del Trabajo Final:

**Incubadora de huevos automática**

\[1° cuatrimestre 2026\]

**Autores:**

**Achinelli Agustin Ezequiel -- 110124**

**Martinez Madero Pablo - 106516**

*Este trabajo fue realizado en la ciudad de Haedo y ciudad de Tigre entre junio y agosto de 2026.*

**RESUMEN**

En el trabajo a continuación se detallará el desarrollo de una incubadora de huevos automática, teniendo como soporte principal la placa NUCLEO-F103RB y código en lenguaje C. Para llevar a cabo este proyecto, se utilizarán varios módulos descriptos a continuación que se integrarán en conjunto para cumplir con los requisitos propuestos.

La idea del mismo es integrar en conjunto los conceptos vistos en la cátedra tales como lectura analógica digital, comunicación SPI, PWM, entre otros.

**Índice General**

**CAPÍTULO 1**

**Introducción general**

**Objetivos**

El objetivo de este proyecto es diseñar e implementar un mecanismo automático de cuidado de huevos para aves domésticas que permita medir, registrar y modificar variables ambientales (temperatura y humedad) en un ambiente controlado, e implementar calentamiento y rotación de los huevos para asegurar su desarrollo correcto. Además, se proyecta diseñar distintos modos de funcionamiento según el tipo de huevo y etapa de su desarrollo, seleccionables a través de una interfaz gráfica compuesta por un display LCD y un teclado matricial.

**Funcionamiento de una incubadora**

La idea general de una incubadora doméstica, que es a lo que se apunta con este proyecto, es que una vez encendido el prototipo se pueda comenzar a incubar un nuevo tipo de especie, cargando los parámetros que se requieren desde 0, ya precargados en la memoria, o bien continuar con este proceso en caso de alguna interrupción externa.

Luego de haber seteado los parámetros de una u otra forma, comienza a calentar o ventilar el interior de la incubadora hasta llegar a los valores fijados que serán sensados cada cierto tiempo para obtener el control del mismo. Es importante que durante lo que dure el proceso según el tipo de huevo se muestren por pantalla los valores actuales del interior y notifique en caso de un exceso o disminución de los mismos.

Una vez que se complete el proceso se avisara por pantalla al usuario y dará la posibilidad de que el mismo decida si es necesario que permanezcan un poco más del tiempo solicitado.

**Desarrollo de las funcionalidades**

Para llevar a cabo las funciones, desde la programación se diseña un ejecutor cíclico el cuál va realizando el llamado a las distintas tareas que se requieren dentro del sistema la limitación en recorrer todas las operaciones es de un milisegundo de forma que se vaya ejecutando en tiempo real.

Para sensar la temperatura y humedad se optó por el DHT22 que integra ambas funciones y se maneja gracias a una librería externa; El LCD 16X2 que se utiliza para mostrar al usuario se maneja con el protocolo SPI y también es llamado con funciones de librería externa.

El control para las opciones dentro del menú se realiza con una botonera del tipo membrana 4X1 configurada como pines de entrada a la placa y gracias al control del ciclo de trabajo por PWM, controlamos la posición de un servomotor.

**CAPÍTULO 2**

**Introducción específica**

**Requisitos**

En la siguiente tabla se pueden agrupar por módulos los requerimientos del proyecto

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

**Servomotor**

Para simular la rotación del soporte para los huevos, fue conveniente considerar una salida PWM del microcontrolador y controlar el servomotor SG90, que si bien tiene un bajo consumo de corriente es uno de los dispositivos que se debe alimentar por fuera de la placa ya que por algún esfuerzo en particular puede superar la corriente máxima del pin y quemar este puerto.

**Figura x.x:** Ilustración.

**Sensor DHT22**

Este sensor se eligió ya que integra ambos sensores y se puede controlar mediante un solo pin de datos. Mide temperaturas de -40°C a 80°C con ± 0.5°C de precisión gracias a su termistor interno y humedad del 0% al 100% con una exactitud del 2% gracias un sensor capacitivo que envían señales analógicas a un pequeño chip integrado que se encarga de convertirlas en una señal digital.

**Figura x.x:** Ilustración.

**LCD 16X2**

Este display alfanumérico se consideró a modo de interfaz con el usuario para poder establecer comunicación con el sistema a través de la selección en el menú, los modos de incubación y realizar una visualización en tiempo real del estado actual.

**Figura x.x:** Ilustración.

**CAPÍTULO 3**

**Diseño e implementación**

**Hardware del microcontrolador**

En la figura que sigue se muestra el diagrama en bloques del proyecto general par tener una visión más abstracta de cada módulo y su conexión con la placa.

**Figura x.x:** Ilustración.

**Placa con microcontrolador**

El trabajo se desarrolló en torno a la placa NUCLEO-F103RB de STMicroelectronics, la cual cuenta con un procesador ARM 32-bit Cortex-M3. Se utilizó dicha placa por haber sido la plataforma adoptada por la cátedra en el presente cuatrimestre, la cual cuenta con todas las características necesarias para desarrollar el trabajo.

En lo que respecta a la alimentación, durante los momentos de pruebas en el desarrollo desde el puerto USB, si bien es suficiente al no tener los dispositivos que más consumen, sería de amplia ventaja el diseño de un bus general de alimentación y desde ahí centrarse en alimentar la placa.

**Figura x.x:** Ilustración.

**Teclado de membrana**

Configurados como pines de entrada, se utilizarán por el usuario para manejarse por el menú de la incubadora siendo: arriba, abajo, entrar y volver.

**Figura x.x:** Ilustración.

**LEDs**

Se tendrán en consideración 3 leds testigos que indiquen estratégicamente falta de tensión o falla de algún tipo dentro del proceso de incubación.

**Figura x.x:** Ilustración.

**Firmware del microcontrolador**

Completar con desarrollo del código y su comportamiento

**CAPÍTULO 4**

**Ensayos y resultados**

**Pruebas funcionales del hardware**
