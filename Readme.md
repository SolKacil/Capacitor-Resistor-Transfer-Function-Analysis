# Análisis de un Circuito RC: Función de Transferencia

Este repositorio contiene un script de MATLAB diseñado para modelar, simular y analizar el comportamiento dinámico de un circuito eléctrico **Resistencia-Capacitor (RC)** de primer orden. El enfoque principal es validar la relación entre los parámetros físicos del circuito y su respuesta en el tiempo.

<div align="center">
  <h4>Captura del Osciloscopio Digital</h4>
  <img src="CircuitoRC.png" width="200">
  <br>
  <p><i>Circuito RC.</i></p>
</div>


## 1. Fundamentación Teórica: Sistemas de Primer Orden

Un sistema de primer orden es aquel cuya dinámica está descrita por una ecuación diferencial lineal de primer grado. En ingeniería de control, estos sistemas se caracterizan por una respuesta exponencial suave sin oscilaciones.

### Forma General de la Función de Transferencia
La representación estándar en el dominio de Laplace ($s$) es:

$$G(s) = \frac{K}{\tau s + 1}$$

Donde:
* **$K$ (Ganancia estática):** Es el valor final que alcanza la respuesta ante una entrada escalón unitario.
* **$\tau$ (Constante de tiempo):** Representa el tiempo que le toma al sistema alcanzar el 63.2% de su valor final.

Para este circuito RC, la función de transferencia se define como:
$$H(s) = \frac{1}{RCs + 1}$$

### Ecuación de la Respuesta en el Tiempo
Ante una entrada escalón de amplitud $A$, la respuesta temporal $y(t)$ es:

$$y(t) = A(1 - e^{-t/\tau})$$

## 2. Configuración del Sistema

Se han definido los siguientes valores para la simulación, correspondientes a componentes comerciales estándar:
* **Resistencia (R):** $10,000 \, \Omega$ (10 kΩ).
* **Capacitor (C):** $0.000100 \, F$ (100 µF).
* **Voltaje de Entrada (Escalón):** 5V.

## 3. Implementación en MATLAB
En esta sección se detalla el uso de comandos especializados para transformar los parámetros físicos de resistencia y capacitancia en un modelo matemático ejecutable.

### Definición de Variables y Constantes
El script comienza estableciendo los valores comerciales de los componentes. Se utiliza notación decimal para la capacitancia para asegurar que MATLAB procese correctamente la magnitud en Faradios.

```matlab
% Parámetros del circuito RC
R = 10000;      % Resistencia en Ohms (10k)
C = 0.000100;   % Capacitor en Faradios (100uF)
```
### Simulación de la Respuesta Temporal
Para construir la función $H(s) = \frac{1}{RCs + 1}$, se definen los vectores de coeficientes del numerador y denominador en potencias descendentes de la variable compleja $s$:

* **Numerador (`num`):** Al tener una ganancia unitaria, se define simplemente como `[1]`.
* **Denominador (`den`):** Se define como `[R*C 1]`, donde el primer término es el coeficiente de $s^1$ (la constante de tiempo $\tau$) y el segundo es el término independiente ($s^0$).

```matlab
% Implementación en MATLAB
num = [1]; 
den = [R*C 1]; 
H = tf(num, den);
```
### Simulación de la Respuesta Temporal

Se utiliza el comando `step` para obtener los datos de la carga del capacitor. En este análisis, la entrada se escala por un factor de **5** para representar una fuente de alimentación de 5V DC.

```matlab
% Generación de datos de salida (y) y tiempo (t) para un escalón de 5V
[y, t] = step(t, 5*H);
```

## 4. Visualización y Análisis de Resultados

En esta sección se presentan las gráficas obtenidas mediante la simulación, las cuales permiten validar el comportamiento teórico del circuito RC frente a los datos experimentales calculados por MATLAB.

<div align="center">
  <h4>Mapa de Polos y Ceros</h4>
  <img src="CerosYPolos_RC.png" width="400">
  <br>
  <p><i><strong>Figura 1:</strong> Ubicación del polo real único en el plano complejo s. Se observa que el sistema es absolutamente estable al encontrarse en el semiplano izquierdo (s = -1).</i></p>
</div>

<div align="center">
  <h4>Respuesta al Escalón</h4>
  <img src="RespuestaEscalon_RC.png" width="400">
  <br>
  <p><i><strong>Figura 2:</strong> Curva de carga del capacitor ante una entrada de 5V. Se han marcado los puntos críticos de tau y el tiempo de establecimiento.</i></p>
</div>

### Análisis Detallado de la Respuesta Temporal
Basado en los valores físicos de los componentes ($R = 10k\Omega$ y $C = 100\mu F$), el análisis de los resultados arroja las siguientes conclusiones:

1.  **Constante de Tiempo ($\tau$):**
    * Calculada matemáticamente como $\tau = R \times C = 1.0 \, \text{segundo}$.
    * En la gráfica de respuesta al escalón, se valida que a los **1.0s**, el sistema alcanza **3.16V**, lo que representa exactamente el 63.2% del valor final (5V).
2.  **Tiempo de Establecimiento ($T_s$):**
    * Definido teóricamente como $5\tau = 5.0 \, \text{segundos}$.
    * La simulación muestra que en la marca de los **5.0s**, el capacitor alcanza **4.96V** (99.3% de la entrada), lo que indica que el sistema ha entrado formalmente en su estado estacionario.
3.  **Estabilidad del Sistema:**
    * La ausencia de una parte imaginaria en el polo ($s = -1$) confirma que la respuesta es puramente exponencial y carece de oscilaciones, característica fundamental de los sistemas de primer orden.

## 5. Validación mediante Simulación en Proteus

Para corroborar los resultados obtenidos en MATLAB, se realizó una simulación de hardware virtual en Proteus, permitiendo observar el comportamiento del circuito en un entorno cercano a la implementación física.

### Configuración del Circuito
El montaje en Proteus se realizó utilizando componentes con los mismos valores nominales que el modelo matemático:

* **Fuente de Alimentación (BAT1):** Configurada a 5V DC para representar la entrada escalón.
* **Interruptor (SW1):** Un conmutador SPDT para controlar el inicio de la carga del capacitor.
* **Etapa RC:** Resistencia de 10kΩ en serie con un capacitor electrolítico de 100µF.
* **Instrumentación:** Se conectó un osciloscopio digital al nodo compartido entre la resistencia y el capacitor para medir el voltaje de salida $V_c(t)$.

<div align="center">
  <h4>Esquemático del Circuito RC</h4>
  <img src="SimulacionRC_Proteus.png" width="500">
  <br>
  <p><i>Conexión de los componentes y el osciloscopio para la medición de la carga.</i></p>
</div>

### Respuesta en el Osciloscopio
Al accionar el interruptor, el osciloscopio muestra la curva de carga característica del capacitor:

1. **Comportamiento Transitorio:** Se observa una curva exponencial que inicia en 0V y asciende suavemente hacia el valor de la fuente.
2. **Validación de Tiempos:** La escala horizontal del osciloscopio permite verificar que el sistema alcanza su estado estacionario aproximadamente a los 5 segundos, coincidiendo con el tiempo de establecimiento $5\tau$ calculado previamente.

<div align="center">
  <h4>Captura del Osciloscopio Digital</h4>
  <img src="SimulacionRC_respuesta.png" width="500">
  <br>
  <p><i>Respuesta temporal medida en Proteus, validando el modelo de primer orden.</i></p>
</div>

---
## 6. Ejercicio para practicar

Para fortalecer el dominio sobre los sistemas de primer orden, se propone realizar el análisis completo de los siguientes dos casos de estudio. El objetivo es comparar los resultados obtenidos mediante el modelo matemático en **MATLAB**, la simulación de hardware en **Proteus** y la **implementación física** en laboratorio.

### Casos de Estudio

| Caso | Resistencia (R) | Capacitor (C) | Objetivo de Análisis |
| :--- | :--- | :--- | :--- |
| **A** | $10\,k\Omega$ | $470\,\mu F$ | Observar el efecto de aumentar la capacitancia en el tiempo de establecimiento. |
| **B** | $1\,k\Omega$ | $470\,\mu F$ | Analizar cómo la reducción de la resistencia acelera la respuesta del sistema. |

### Actividades a realizar:
1. **Análisis en MATLAB:** Modificar el script proporcionado en este repositorio con los nuevos valores de $R$ y $C$ para obtener las gráficas de respuesta al escalón y el mapa de polos y ceros.
2. **Simulación en Proteus:** Ajustar los valores de los componentes en el esquemático y utilizar el osciloscopio digital para medir el tiempo en que el capacitor alcanza el 63.2% de su carga ($\tau$).
3. **Implementación Física:** Armar el circuito en una protoboard y utilizar un osciloscopio real para cronometrar el tiempo de establecimiento ($5\tau$).

### Preguntas de análisis
* ¿Cómo cambió la ubicación del polo en el plano $s$ al disminuir la resistencia en el Caso B?
* ¿Hubo diferencias significativas entre el tiempo de establecimiento teórico y el medido físicamente? ¿A qué crees que se deba (tolerancia de componentes, resistencia de cables, etc.)?

---
**Guía:** Compara tus gráficas con las de este repositorio para validar los resultados.
