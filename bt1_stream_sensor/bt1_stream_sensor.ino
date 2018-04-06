/*
	Exemplo de stream de dados de um sensor para o Bluetooth

	O circuito:
	* RX eh o pino digital 2 (conectar ao TX do outro dispositivo)
	* TX eh o pino digital 3 (conectar ao RX do outro dispositivo)
	* O sensor eh o pino analogico A0

	Nota:
	Nem todos pinos da Arduino Mega nem Mega 2560 suportam interrupcoes,
	entao somente os seguintes pinos podem ser usados para RX:
	10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
	Nem todos pinos da Arduino Leonardo suportam interrupcoes, 
	entao somente os seguintes pinos podem ser usados para RX:
	8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
*/

// Biblioteca de comunicacao software serial
#include <SoftwareSerial.h>

// Modulo Bluetooth
SoftwareSerial bluetoothSerial(2, 3); // RX, TX

// Sensor analogico a ser feito o stream
int sensor_pin = A0;

void setup()
{
	// Abre a comunicacao serial da USB
	Serial.begin(9600);
	Serial.println("Hello World!");

	// Abre a comunicacao software serial (bluetooth)
	bluetoothSerial.begin(9600);
	bluetoothSerial.println("Hello, world?");
}

void loop()
{
	// Faz leitura do sensor analogico
	int sensor_value = analogRead(sensor_pin);

	// Envia a leitura para o bluetooth
	bluetoothSerial.println(sensor_value, DEC);
	delay(200);
}

