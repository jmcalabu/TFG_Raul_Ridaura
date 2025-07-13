

#include <WiFi.h>
#include <WebServer.h>
#include <math.h>          


// Configuración de pines

#define STEP_L   17   // Step motor izquierdo
#define DIR_L    16   // Dir  motor izquierdo
#define STEP_R   19  // Step motor derecho
#define DIR_R    18   // Dir  motor derecho

#define EN_R     22   // Enable left  (LOW = enabled)
#define EN_L     0   // Enable right (LOW = enabled)

#define V_PIN_1  23   //“V” siempre HIGH
#define V_PIN_2   4

#define STEP_DELAY_US 1500  // µs entre flancos STEP 


// Wi-Fi / HTTP

const char* ssid     = "ESP32-AP";
const char* password = "12345678";
WebServer server(80);


// Estado global

volatile bool movimientoEnCurso = false;
float orientacionActual = 0.0f;   // (-180, 180]


// Inicialización de pines de motor

void setupMotores()
{
  pinMode(STEP_L, OUTPUT);  pinMode(DIR_L, OUTPUT);
  pinMode(STEP_R, OUTPUT);  pinMode(DIR_R, OUTPUT);

  pinMode(EN_L, OUTPUT);    pinMode(EN_R, OUTPUT);
  digitalWrite(EN_L, LOW);  digitalWrite(EN_R, LOW);   // habilitar drivers

  pinMode(V_PIN_1, OUTPUT); pinMode(V_PIN_2, OUTPUT);
  digitalWrite(V_PIN_1, HIGH);
  digitalWrite(V_PIN_2, HIGH);
}


// Rutina de pasos simultáneos

void moverMotores(int pasos, bool dirIzq, bool dirDer)
{
  digitalWrite(DIR_L, dirIzq ? HIGH : LOW);
  digitalWrite(DIR_R, dirDer ? HIGH : LOW);

  for (int i = 0; i < pasos; ++i)
  {
    digitalWrite(STEP_L, HIGH);  digitalWrite(STEP_R, HIGH);
    delayMicroseconds(STEP_DELAY_US);
    digitalWrite(STEP_L, LOW);   digitalWrite(STEP_R, LOW);
    delayMicroseconds(STEP_DELAY_US);
  }
}


// Conversión mm / grados → pasos
// (factores geométricos + correctores )

int calcularPasosDesdeDistancia(float mm)
{
  float pasos = mm * 10.0f * 0.796f * 1.064f;   // ver memoria § …
  return (int)roundf(fabsf(pasos));
}

int calcularPasosDesdeGrados(float grados)
{
  float pasos = grados * 10.0f * 3.02f * 1.0142f;
  return (int)roundf(fabsf(pasos));
}


// Movimientos


void girar(float grados)
{
  if (grados == 0.0f) return;

  int pasos = calcularPasosDesdeGrados(grados);
  Serial.printf("GIRAR %s  %d pasos\n",
                grados > 0 ? "DERECHA" : "IZQUIERDA", pasos);

  // ambas ruedas en el mismo sentido → giro sobre eje 
  if (grados > 0)
      moverMotores(pasos, true,  true);   // antihorariohorario
  else
      moverMotores(pasos, false , false);  // horario

  orientacionActual += grados;
  if (orientacionActual >  180.0f) orientacionActual -= 360.0f;
  if (orientacionActual < -180.0f) orientacionActual += 360.0f;
}

void avanzar(float mm)
{
  if (mm == 0.0f) return;

  int pasos = calcularPasosDesdeDistancia(mm);
  Serial.printf("%s  %d pasos\n", mm > 0 ? "AVANZAR" : "RETROCEDER", pasos);

  // ruedas opuestas → desplazamiento lineal 
  if (mm > 0)
      moverMotores(pasos, false,  true);  // avanza
  else
      moverMotores(pasos, true, false);   // retrocede
}


// HTTP: /data?v1=..&v2=..&v3=..

void handleData()
{
  if (server.hasArg("v1") && server.hasArg("v2") && server.hasArg("v3"))
  {
    float v1 = server.arg("v1").toFloat();
    float v2 = server.arg("v2").toFloat();
    float v3 = server.arg("v3").toFloat();

    Serial.printf("v1=%.2f  v2=%.2f  v3=%.2f\n", v1, v2, v3);
    server.send(200, "text/plain", "OK");

    movimientoEnCurso = true;
    girar(v1);
    delay(3000);
    avanzar(v2);
    delay(3000);
    girar(v3);

    movimientoEnCurso = false;
  }
  else
  {
    server.send(400, "text/plain",
                "Faltan parámetros (v1, v2, v3)");
  }
}

void handleStatus()
{
  server.send(200, "text/plain",
              movimientoEnCurso ? "BUSY" : "READY");
}


// setup / loop

void setup()
{
  Serial.begin(115200); delay(100);

  WiFi.softAP(ssid, password);
  Serial.print("AP iniciado. IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/data",   handleData);
  server.on("/status", handleStatus);
  server.begin();

  setupMotores();
}

void loop()
{
  server.handleClient();
}
