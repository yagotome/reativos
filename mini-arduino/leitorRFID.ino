/*
	Programa: Controle de Acesso com leitor RFID
	Autores: Lucas Alves
		 Gustavo Silva
		 Luiz Andrade
*/

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Cria instância MFRC522

LiquidCrystal lcd(6, 7, 5, 4, 3, 2); // Inicializa a biblioteca com os números dos pins da interface

void setup() {
	lcd.begin(16, 2); //Define o número de colunas e linhas do LCD
	msgInicial();
}

void loop() {
	if (! mfrc522.PICC_IsNewCardPresent()) { // Procura por novos cartões
		return;
	}
  
	if (! mfrc522.PICC_ReadCardSerial()) { // Aceita somente se um cartão for lido por vez
		return;
	}
  
	Serial.print("UID da tag :"); // Exibe UID na serial
	String conteudo= "";
	byte letra;
	
	for (byte i = 0; i < mfrc522.uid.size; i++) { // Testar o que acontece na prática
		Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
		Serial.print(mfrc522.uid.uidByte[i], HEX);
		conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
		conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
	}
	
	conteudo.toUpperCase();
	  
	if (conteudo.substring(1) == "ED 78 03 CA") { //UID 1 - Chaveiro (verificar parâmetro)
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("Ola, professor!");
		lcd.setCursor(0,1);
		lcd.print("Acesso liberado!");
		delay(3000);
		mensageminicial();
	}
 
	if (conteudo.substring(1) == "BD 9B 06 7D") { //UID 2 - Cartao (verificar parâmetro)
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("Ola, aluno!");
		lcd.setCursor(0,1);
		lcd.print("Acesso Negado!");
		delay(3000);
		mensageminicial();
	}
}

void msgInicial() {
	lcd.clear();
	lcd.print(" Aproxime o seu");  
	lcd.setCursor(0,1);
	lcd.print("cartao do leitor");
}	
