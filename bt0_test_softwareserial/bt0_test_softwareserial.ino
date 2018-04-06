/*
	Exemplo traduzido da IDE Arduino
	Envia para a software serial tudo que receber da serial por hardware (USB)
	Envia para a serial por hardware (USB) tudo que receber da software serial

	O circuito:
	* RX eh o pino digital 2 (conectar ao TX do outro dispositivo)
	* TX eh o pino digital 3 (conectar ao RX do outro dispositivo)

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


void setup()
{
	// Abre a comunicacao serial da USB
	Serial.begin(9600);
	Serial.println("Hello World!");

	// Abre a comunicacao software serial (bluetooth)
	// set the data rate for the SoftwareSerial port
	bluetoothSerial.begin(9600);
	bluetoothSerial.println("Hello, world?");
}


void loop()
{
	// Caso tenha algo pra ser lido da software serial, le e manda pra serial da USB
	if (bluetoothSerial.available())
		Serial.write(bluetoothSerial.read());

	// Caso tenha algo pra ser lido da serial da USB, le e manda pra software serial
	if (Serial.available())
		bluetoothSerial.write(Serial.read());
}

