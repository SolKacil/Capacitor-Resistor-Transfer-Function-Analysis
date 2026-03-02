// --- Configuración del Sistema ---
const float R = 100000.0;      // Resistencia de carga en Ohms
const float C = 0.0000100;       // Capacitor en Faradios 
const float Vin_Max = 3.3;      // Para Arduino Due, que opera a 3.3V
const float tau = R * C;        

unsigned long tiempoReferencia;
bool estadoCargando = false;
bool estadoDescargando = false;

void setup() {
  Serial.begin(115200); // Mayor velocidad para el Arduino Due - (ver configuración de tu tarjeta)
  
  // Configurar resolución de 12 bits (0-4095)
  analogReadResolution(12); 
  
  pinMode(A1, INPUT); // Entrada analógica A01
  
  Serial.println("Setpoint,Modelo_Matematico,Voltaje_Real"); //Mostrar encabezado en el monitor serial
}

void loop() {
  // Lectura con resolución de 12 bits
  int lecturaADC = analogRead(A1);
  float vReal = (lecturaADC / 4095.0) * Vin_Max;

  // Detección de carga (Botón de carga presionado)
  if (!estadoCargando && vReal > 0.05 && vReal < (Vin_Max - 0.5)) {
    estadoCargando = true;
    estadoDescargando = false;
    tiempoReferencia = millis();
  }

  // detección de descarga
  if (estadoCargando && (vReal < 0.05)) {
    estadoCargando = false;
  }

  float vTeorico = 0; 
  float t = (millis() - tiempoReferencia) / 1000.0;

  if (estadoCargando) {
    // Modelo de carga: Vc = Vin * (1 - e^-t/tau)
    vTeorico = Vin_Max * (1.0 - exp(-t / tau)); //Modelo matemático para la carga del capacitor
  } else {
    // Modelo de descarga: Vc = Vo * e^-t/tau
    // vTeorico = 0 para cuando el capacitor se descargue, mostrar el valor del modelo matemático en cero
    vTeorico = 0;  //Se puede usar el modelo de descarga también para ver la curva de descarga del modelo teórico
  }

  // Salida para el Serial Plotter
  Serial.print(0); //Para acotar la escala del plotter desde a 3.3V
  Serial.print(",");
  Serial.print(Vin_Max); //Para acotar la escala del plotter desde a 3.3V
  Serial.print(",");
  Serial.print(t); //Imprime el tiempo para monitoreo, se reinicia a cero cuando el capacitor comienza a cargarse
  Serial.print(",");
  Serial.print(vTeorico); //Imprime el valor del modelo teórico para carga e imprime cero cuando el capacitor se descarga
  Serial.print(",");
  Serial.println(vReal); //Muestra el valor medido del capacitor tomado de la entrada analógica A0

  delay(100); //Se pone un delay de 100 ms para ver los datos y la gráfica
}  
