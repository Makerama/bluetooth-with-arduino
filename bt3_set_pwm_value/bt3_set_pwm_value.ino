/*
	Exemplo de controle de um modulo PWM por Bluetooth

	O circuito:
	* RX eh o pino digital 2 (conectar ao TX do outro dispositivo)
	* TX eh o pino digital 3 (conectar ao RX do outro dispositivo)
	* O sensor eh o pino PWM 9

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

// Comandos de ligar e desligar modulo
#define ON_COMMAND '1'
#define OFF_COMMAND '0'


// Modulo Bluetooth
SoftwareSerial bluetoothSerial(2, 3); // RX, TX

// Pino do modulo PWM
int module_pin = 9;


void setup()
{
	// Abre a comunicacao serial da USB
	Serial.begin(9600);
	Serial.println("Hello World!");

	// Abre a comunicacao software serial (bluetooth)
	bluetoothSerial.begin(9600);
	bluetoothSerial.println("Hello, world?");
	bluetoothSerial.setTimeout(50);

	// Define o modulo digital como OUTPUT
	pinMode(module_pin, OUTPUT);

	// Pisca o LED
	for (int i = 0; i < 3; i++)
	{
		digitalWrite(module_pin, HIGH);
		delay(100);
		digitalWrite(module_pin, LOW);
		delay(100);
	}
}


void loop()
{
	// Caso tenha algo pra ser lido do Bluetooth, le e atualiza o modulo
	if (bluetoothSerial.available())
	{
		// Leitura do Bluetooth
		int bt_value = bluetoothSerial.parseInt();
		// Mapeamento para passar da escala de 0-100 para 0-255, padrao de PWM na Arduino
		bt_value = map(bt_value, 0, 100, 0, 255);
		// Define a intensidade do PWM
		analogWrite(module_pin, bt_value);
		// Serial.println(bt_value, DEC);
	}
}

