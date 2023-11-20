#include <Adafruit_BMP280.h>
#include <WiFi.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// 32 (amarelo) - temp solo
// 33 (verde) - DHT11
// 25 (azul) - umidade solo
// 26 (laranja) - chuva

// Sensor fotovoltaico
#define LIGHT_PIN 32
float light = 0;

// Sensor DHT
#define DHT_PIN 33
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);
float temperature = 0;
float humidity = 0;

// Sensor de umidade do solo
#define SOIL_HUMIDITY_PIN 25
float soilHumidity = 0;

// Sensor de chuva
#define RAIN_PIN 26
float rain = 0;

// Sensor de temperatura do solo
#define SOIL_TEMPERATURE_PIN 27
float soilTemperature = 0;
OneWire oneWire(SOIL_TEMPERATURE_PIN);
DallasTemperature sensors(&oneWire);

// Barômetro
Adafruit_BMP280 bmp;
float airPressure = 0;

void setup() {
  pinMode(SOIL_TEMPERATURE_PIN, INPUT);

  Serial.begin(115200);
  while (!Serial);

  dht.begin();
  sensors.begin();

  int status = bmp.begin(0x76);
  bmp.

  while (!status) {
    Serial.print("Erro ao iniciar o barômetro! SensorID: 0x");
    Serial.println(bmp.sensorID());
    delay(5000);
  }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void listarDHT() {
  temperature = dht.readTemperature();   
  humidity = dht.readHumidity();

  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println("°C");

  Serial.print("Humidade: ");
  Serial.print(humidity);
  Serial.println("%");
}

void listarHumidadeDoSolo() {
  soilHumidity = map(analogRead(SOIL_HUMIDITY_PIN), 0, 4095, 100, 0); 

  Serial.print("Humidade do solo: ");
  Serial.print(soilHumidity);
  Serial.println("%");
}

void listarChuva() {
  rain = map(analogRead(RAIN_PIN), 0, 4095, 100, 0);

  Serial.print("Humidade: ");
  Serial.print(rain);
  Serial.println("%");
}

void listarLuz() {
  light = map(analogRead(LIGHT_PIN), 0, 4095, 100, 0);

  Serial.print("Luz: ");
  Serial.println(light);
}

void listarTemperaturaDoSolo() {
  sensors.requestTemperatures();
  soilTemperature = sensors.getTempCByIndex(0);

  Serial.print("Temperatura do solo: ");
  Serial.print(soilTemperature);
  Serial.println("°C");
}

void listarBarometro() {
  airPressure = bmp.readPressure() / 100;

  Serial.print("Pressão do ar: ");
  Serial.print(airPressure);
  Serial.println( "hPa");
}

void loop() {
  Serial.println("<=====================>");
  listarDHT();
  listarHumidadeDoSolo();
  listarLuz();
  listarChuva();
  listarTemperaturaDoSolo();
  listarBarometro();
  Serial.println("<=====================>\n\n");
  delay(5000);
}
