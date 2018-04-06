/*
	Exemplo de controle de um modulo digital por Bluetooth, utilizando serialEvent.
	Mais informacoes http://www.arduino.cc/en/Tutorial/SerialEvent

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
SoftwareSerial serialPorSoftware(2, 3); // RX, TX

// Pino do modulo digital
int module_pin = 9;

// Variaveis de controle para modificacao do estado do modulo
boolean last_led_state = true;
boolean led_state = false;


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



void loop() {
	// Caso haja mudanca no estado do comando, modifica o estado do modulo
	if (last_led_state != led_state)
	{
		// Atualiza o estado anterior do comando
		last_led_state = led_state;
		if (led_state == true)
		{
			digitalWrite(module_pin, HIGH);
			Serial.println("ON");
			serialPorSoftware.println("ON");
		}
		else
		{
			digitalWrite(module_pin, LOW);
			Serial.println("OFF");
			serialPorSoftware.println("OFF");
		}
	}
}


/*
	SerialEvent eh chamada sempre que um dado chega. Essa rotina
	eh chamada entre cada chamada da funcao loop, podendo atrasar a mesma.
 */
void serialEvent() {
	// Caso haja dados a serem lidos, realiza a leitura atualizando a variavel
	// de comando
	if (serialPorSoftware.available()) {
		// Le do Bluetooth e atualiza o estado do comando
		char command = serialPorSoftware.read();
		if (command == on_command)
			led_state = HIGH;
		else if (command == off_command)
			led_state = LOW;
	}
}

