/*
	Exemplo de controle de um modulo digital por Bluetooth

	O circuito:
	* RX eh o pino digital 2 (conectar ao TX do outro dispositivo)
	* TX eh o pino digital 3 (conectar ao RX do outro dispositivo)
	* O sensor eh o pino digital 13 (builtin LED)

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

// Pino do modulo digital
int module_pin = 9;


void setup()
{
	// Abre a comunicacao serial da USB
	Serial.begin(9600);
	Serial.println("Hello World!");

	// Abre a comunicacao software serial (bluetooth)
	serialPorSoftware.begin(9600);
	serialPorSoftware.println("Hello, world?");

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
	if (serialPorSoftware.available())
	{
		// Leitura do Bluetooth
		char command = (char)serialPorSoftware.read();
		// Filtra a quebra de linha
		if (command != '\n' && command != '\r')
		{
			switch (command)
			{
				// Caso seja o comando de ligar, ativa o modulo
				case ON_COMMAND:
					digitalWrite(module_pin, HIGH);
					Serial.println("ON");
					serialPorSoftware.println("ON");
					break;
				// Caso seja o comando de desligar, desativa o modulo
				case OFF_COMMAND:
					digitalWrite(module_pin, LOW);
					Serial.println("OFF");
					serialPorSoftware.println("OFF");
					break;
				// Caso seja o comando seja invalido, nao modifica o modulo
				default:
					Serial.print("Error. Received '");
					Serial.print(command);
					Serial.println("'");
					serialPorSoftware.print("Error. Received '");
					serialPorSoftware.print(command);
					serialPorSoftware.println("'");
			}
		}
	}
}

