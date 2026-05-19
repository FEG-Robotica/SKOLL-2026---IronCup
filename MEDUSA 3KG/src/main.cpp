#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "sensores.h"

std::string comando = "p";

#define bleRobo "SKOLL"

bool deviceConnected = false;
bool oldDeviceConnected = false;
bool bleBool = false;

BLEServer *pServer = NULL;

BLECharacteristic bleComCharacteristics("e2fe15af-73bd-4a03-ab67-b81a25d89488", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor bleComDescriptor(BLEUUID((uint16_t)0x2902));

BLECharacteristic bleLinhaCharacteristics("53726fe7-5444-42a2-965c-2057e225ef7e", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor bleLinhaDescriptor(BLEUUID((uint16_t)0x2902));

BLECharacteristic bleDistanciaCharacteristics("cb7f3f53-ff67-44c0-941c-5ed5d2422e69", BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor bleDistanciaDescriptor(BLEUUID((uint16_t)0x2902));

class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
    Serial.println("CONECTADO");
  };
  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
    pServer->startAdvertising();
    Serial.println("DESCONECTADO");
  }
};

class MyCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string value = pCharacteristic->getValue();
    comando = value;
    Serial.println(value.c_str());

    if (value.substr(0, 3) == "vel")
    {
      velmotor = std::stoi(value.substr(3, 7));
    }

    if (value.substr(0, 3) == "par")
    {
      parametro = std::stoi(value.substr(3, 7));
    }
  }
};

void enviaDist()
{
  leituraSensoresDistancia();
  std::string sensores = "LE:";
  sensores.append(std::to_string(distancia_esq));
  sensores.append(" FE:");
  sensores.append(std::to_string(distancia_front_esq));
  sensores.append(" C:");
  sensores.append(std::to_string(distancia_cent));
  sensores.append(" FD:");
  sensores.append(std::to_string(distancia_front_dir));
  sensores.append(" LD:");
  sensores.append(std::to_string(distancia_dir));
  bleDistanciaCharacteristics.setValue(sensores);
  bleDistanciaCharacteristics.notify();
  delay(100);
}

void enviaLinha()
{
  leituraSensoresLinha();
  std::string sensores = "LINHAESQ:";
  sensores.append(std::to_string(linha_esq));
  sensores.append(" LINHADIR:");
  sensores.append(std::to_string(linha_dir));
  bleLinhaCharacteristics.setValue(sensores);
  bleLinhaCharacteristics.notify();
  delay(100);
}

void setup()
{
  pinMode(SENSOR_LINHA_FRONTAL_ESQ, INPUT);
  pinMode(SENSOR_LINHA_FRONTAL_DIR, INPUT);

  pinMode(SENSOR_DIST_FRONTAL_ESQ, INPUT_PULLUP);
  pinMode(SENSOR_DIST_FRONTAL_DIR, INPUT_PULLUP);
  pinMode(SENSOR_DIST_ESQ, INPUT_PULLUP);
  pinMode(SENSOR_DIST_DIR, INPUT_PULLUP);
  pinMode(SENSOR_DIST_CENTRAL, INPUT_PULLDOWN);

  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(PWMC, OUTPUT);
  pinMode(PWMD, OUTPUT);

  pinMode(START, INPUT_PULLDOWN);

  pinMode(LED, OUTPUT);

  ledcSetup(0, 5000, 10);
  ledcAttachPin(PWMA, 0);
  ledcSetup(1, 5000, 10);
  ledcAttachPin(PWMB, 1);
  ledcSetup(2, 5000, 10);
  ledcAttachPin(PWMC, 2);
  ledcSetup(3, 5000, 10);
  ledcAttachPin(PWMD, 3);

  Serial.begin(9600);

  BLEDevice::init(bleRobo);
  BLEServer *pServer = BLEDevice::createServer();

  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE |
          BLECharacteristic::PROPERTY_NOTIFY);

  pService->addCharacteristic(&bleDistanciaCharacteristics);
  bleDistanciaDescriptor.setValue("bleDist");
  bleDistanciaCharacteristics.addDescriptor(&bleDistanciaDescriptor);

  pService->addCharacteristic(&bleLinhaCharacteristics);
  bleLinhaDescriptor.setValue("Linha");
  bleLinhaCharacteristics.addDescriptor(&bleLinhaDescriptor);

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("ENVIAR CMD");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pServer->getAdvertising()->start();
  pAdvertising->start();
}

// Atualizar leitura dos sensores de linha e distancia

void leituraSensoresLinha()
{
  linha_esq = analogRead(SENSOR_LINHA_FRONTAL_ESQ);
   //Serial.print("LE: ");
   //Serial.println(linha_esq);
  linha_dir = analogRead(SENSOR_LINHA_FRONTAL_DIR);
   //Serial.print("LD: ");
   //Serial.println(linha_dir);

   delay(1000);
}
void leituraSensoresDistancia()
{
  distancia_esq = digitalRead(SENSOR_DIST_ESQ);
  //Serial.print("ESQ: ");
  //Serial.println(distancia_esq);

  distancia_front_esq = digitalRead(SENSOR_DIST_FRONTAL_ESQ);
   //Serial.print("FE: ");
   //Serial.println(distancia_front_esq);

  distancia_front_dir = digitalRead(SENSOR_DIST_FRONTAL_DIR);
  //Serial.print("FD: ");
  //Serial.println(distancia_front_dir);

  distancia_dir = digitalRead(SENSOR_DIST_DIR);
  //Serial.print("DIR: ");
  //Serial.println(distancia_dir);

  distancia_cent = digitalRead(SENSOR_DIST_CENTRAL);
  //Serial.print("C: ");
  //Serial.println(distancia_cent);

  //delay(500);
}

#include "motor.h"
#include "estrategias.h"
#include "testes.h"

void loop()
{
  //Serial.print("START: ");
  //Serial.println(digitalRead(START));

  leituraSensoresDistancia();
  leituraSensoresLinha();

  if (deviceConnected)
  {
    enviaDist();
    enviaLinha();
    delay(5);
  }

  if (!deviceConnected && oldDeviceConnected)
  {
    delay(500);
    pServer->startAdvertising();
    oldDeviceConnected = deviceConnected;
  }

  if (deviceConnected && !oldDeviceConnected)
  {
    oldDeviceConnected = deviceConnected;
  }

  /*while (digitalRead(START) == 0)
  {
    parar();
    Serial.print("START: ");
    Serial.println(digitalRead(START));
  }
    */

  // COMANDOS PARA TESTE DE BANCADA
  if (comando == "led")
  {
    piscar_led();
    Serial.print("LED: ");
    Serial.print(digitalRead(LED));
    delay(1000);
  }
  if (comando == "p")
  {
    parar();
  }
  if (comando == "f")
  {
    frente();
  }

  if (comando == "t")
  {
    tras();
  }

  if (comando == "eixo")
  {
    girar_eixo();
  }

  if (comando == "180")
  {
    girar_180();
  }

  if (comando == "ll")
  {
    leitura_linha();
  }

  // COMANDO PARA AS MELHORES ESTRATÉGIAS
  if (comando == "m")
  {
    missil();
  }

  if (comando == "b")
  {
    busca();
  }

  if (comando == "a")
  {
    arco();
  }

  if (comando == "est")
  {
    estrela();
  }

  if (comando == "toq")
  {
    toquinho();
  }
}