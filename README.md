# Sumo_Amateur_V2

🤖 Sumo_Amateur

Documentación técnica y funcionamiento:
	
	Componentes principales
1. Arduino Nano ATmega328P  

Es una placa de desarrollo basada en el microcontrolador ATmega328P, un chip de 8 bits con arquitectura AVR RISC. Tiene 32 KB de memoria Flash para el programa y 2 KB de SRAM. 

El Arduino Nano incluye su propio regulador de voltaje, un convertidor USB‑serie para programarlo y sus pines de entrada/salida permiten conectar y controlar los sensores del robot.

Se programa en el entorno Arduino IDE, con sus pines digitales, analógicos, PWM, I2C y SPI puedes controlar motores, leer sensores, comunicarte con otros dispositivos, etc. Es ideal para robots pequeños, prototipos y proyectos embebidos por su tamaño reducido.  

2. Sensor QRE1113  

Es un sensor óptico reflectivo que lleva un LED infrarrojo (940 nm) y un fototransistor en el mismo encapsulado, el LED emite una luz infrarroja, cuando esta rebota en una superficie y vuelve al fototransistor, el fototransistor detecta cuánta luz regresó, las superficies claras reflejan más luz que las obscuras.  

Se usa principalmente para seguidores de línea. Se coloca cerca de una superficie y se lee con un pin analógico del Arduino, detectando si la superficie es clara u oscura. También sirve para detectar bordes o la presencia de objetos cercanos.  

3. Sensor VL53L0X  

Es un sensor de distancia láser de alta precisión, utiliza la tecnología Time‑of‑Flight (ToF), que mide el tiempo que tarda un "rayo" de luz infrarroja en rebotar en un objeto y volver, como la velocidad de la luz siempre es la misma, el sensor puede calcular la distancia la fórmula:  

Distancia = ½ × (Velocidad de la luz × Tiempo de ida y vuelta)

A diferencia de los sensores ultrasónicos o de infrarrojo clásicos, este sensor mide la distancia sin depender de si el objeto es claro o obscuro (dentro de ciertos límites). El VL53L0X puede medir hasta 2 metros con buena precisión.

Se comunica por bus I2C. Se conecta a los pines SDA y SCL del Arduino Nano. Necesita la librería correspondiente (en este caso de Pololu o Adafruit). Es muy usado en robots para evitar obstáculos, medir distancias, detectar altura, etc.

4. Doble Puente H TB6612FNG

Es un driver de motores de doble puente H de Toshiba. Un puente H es un circuito formado por 4 transistores (MOSFET) en forma de “H” que permite controlar el sentido de la corriente que llega al motor. Al controlar la dirección de la corriente puedes hacer que el motor gire en un sentido u otro. Con señales PWM también se puede controlar la velocidad. El TB6612FNG tiene dos puentes H independientes, por lo que puede controlar dos motores DC de forma independiente.

Se alimenta con una fuente externa para los motores (VM) y con 5 V o 3,3 V para la lógica (VCC). Se controla con pines del Arduino:
- 2 pines de dirección + 1 pin PWM por motor
- Pin STBY (debe estar en HIGH para activarlo)

	Descripción general del proyecto

Sumo_Amateur es un robot autónomo diseñado para participar en la próxima competencia de mini sumo autónomo amateur.
Su funcionamiento general es:
Detectar los límites del ring.
Detectar dónde se encuentra el oponente.
Decidir qué movimiento realizar.
Controlar los motores.
Repetir este proceso rápidamente mientras dure el combate.

El robot no necesita que una persona lo controle durante la competencia. Todo el comportamiento se encuentra programado en Arduino.

El proyecto está dividido en varios módulos para que cada archivo tenga una responsabilidad específica:

	Sumo_Amateur.ino: Control general y toma de decisiones
	Infrarrojo.h/.cpp: Lectura de sensores infrarrojos y de línea
	Laser.h/.cpp: Medición de distancia mediante VL53L0X
	Movimiento.h/.cpp: Control de motores mediante TB6612FNG

Esta división hace que el programa sea más fácil de entender, modificar y corregir.

	Sumo_Amateur.ino

Este es el archivo principal del proyecto y puede considerarse el cerebro del robot.

Tiene una máquina de estados que organiza los comportamientos, podemos pensar en ella como los diferentes "modos" del robot (ATAQUE, RETROCO, AVANCE,              BUSQUEDA) y existe una situación especial ESCAPAR.

Esto hace que el comportamiento sea más predecible, en lugar de que el robot tenga instrucciones independientes que se contradigan, cada estado define qué comportamiento debe seguir.


El ciclo principal se coordina en void setup() y void loop():
Los sensores infrarrojos.
Los sensores de línea.
Los sensores láser.
Los motores.
Los diferentes estados de comportamiento.
La lógica que decide qué debe hacer el robot.

	void setup()
La función setup() se ejecuta una sola vez, justo cuando el Arduino se enciende o reinicia.
Normalmente se utiliza para preparar el robot antes de comenzar el combate.
Se encarga de:
Configurar los pines.
Inicializar los sensores.
Preparar los motores.
Configurar los sensores láser.
Esperar aproximadamente 5 segundos antes de comenzar.
Ejecutar el movimiento inicial de salida de la posición de arranque.

	void loop()

Es la función más importante durante el combate pues se ejecuta continuamente:

El programa utiliza una máquina de estados para organizar las acciones del robot.
En lugar de tener muchas instrucciones mezcladas, antes de decidir qué hacer, el programa obtiene información de los sensores, con esta información el programa determina su situación y, dependiendo de la situación, ejecuta las siguientes acciones:

Avanzar.
Retroceder.
Girar.
Buscar al rival.
Atacar.
Detenerse.

	Infrarrojo.h e Infrarrojo.cpp

Estos módulos se encargan de trabajar con los sensores QRE1113, utilizados principalmente para detectar el borde del dohyo.

El módulo está dividido en dos archivos porque Arduino/C++ utiliza normalmente un archivo de declaraciones y otro de implementación. El archivo ".h" funciona como una lista de pines, variables y funciones. En el archivo ".cpp" se encuentra la implementación de las funciones, así el archivo principal solamente pregunta si el rival está enfrente o no.

	Laser.h y Laser.cpp

Estos módulos administran los sensores de distancia VL53L0X, estos sensores permiten estimar qué tan lejos está un objeto utilizando medición de distancia por luz.

Laser.h contiene las declaraciones necesarias para utilizar el módulo, mientras que Laser.cpp contiene la implementación de las mediciones, las cuales usa para  saber si el robot está cerca, a la izquierda, a la derecha o no está en el rango.
		
	Movimiento.h y Movimiento.cpp

Estos módulos controlan físicamente los motores. Utiliza el doble puente H TB6612FNG, que permite controlar el sentido y la velocidad de los motores.
Movimiento.h contiene las declaraciones de las funciones de movimiento, mientras que Movimiento.cpp controla el TB6612FNG y los motores mediante funciones tales como: 
Avanzar.
Retroceder.
Girar.
Detenerse.
Controlar la velocidad.

	Integración de todos los módulos

La verdadera fuerza del proyecto aparece cuando todos los módulos trabajan juntos.
El archivo principal funciona como coordinador.
Los módulos especializados hacen el trabajo concreto:
Infrarrojo: Los sensores QRE1113 detectan el borde.
Laser: Los sensores VL53L0X miden la distancia.
Movimiento: El doble Puente H TB6612FNG controla los Motores.
Sumo_Amateur: Toma de decisiones.


	Buenas prácticas para continuar el proyecto

Si se sigue desarrollando `Sumo_Amateur`, conviene mantener algunas reglas sencillas:
1. Usar nombres claros
	Es mejor: 
		Laser.cpp
		distanciaIzquierda
	que:
		Laser.cpp
		dI
Un nombre claro hace que el código sea más fácil de entender meses después.

2. Separar responsabilidades
Si una función controla motores, deberá encargarse sólo de motores.
Si una función lee un sensor, deberá encargarse sólo ese sensor.

Esto evita crear funciones gigantes y difíciles de mantener.

3. Evitar repetir lecturas
Es decir, evitar consultar el mismo sensor muchas veces dentro de una misma decisión.

4. Controlar valores inválidos
Los sensores físicos pueden fallar, por eso es buena práctica comprobar sus lecturas antes de utilizarlas.

5. Comentar las partes difíciles

No hace falta escribir comentarios para cada línea, pero es mas fácil entender cuando hay comentarios que explican lo que hacen las funciones.

  Conclusión

Sumo_Amateur utiliza una estructura modular que combina sensores, lógica de decisión y control de motores que hace que el proyecto sea más fácil de aprender y modificar.
Por ejemplo, si en el futuro se cambia un sensor de distancia, idealmente será necesario modificar principalmente Laser.cpp, sin tener que reescribir toda la estrategia del robot.
Del mismo modo, si se cambia el controlador de motores, el módulo Movimiento puede adaptarse manteniendo prácticamente intacta la lógica principal.
En conjunto, el proyecto es un buen ejemplo de cómo transformar un robot físico en un sistema autónomo: los sensores proporcionan información, el programa interpreta esa información y los motores ejecutan la decisión.
