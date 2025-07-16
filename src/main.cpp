#include <Keypad.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* SSID = "Wokwi-GUEST";
const char* Password = "";

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS]={
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte rowsPin[ROWS]= {13, 12, 14, 27};
byte colsPin[COLS]= {26, 25, 33, 32};
Keypad keypad = Keypad(makeKeymap(keys), rowsPin, colsPin, ROWS, COLS);

#define SDApin 4
#define SCLpin 5
#define SCREEN_W 128
#define SCREEN_H 64
Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, -1);
String mssv = "";
const byte max_mssv = 8;
const String URLsheet = "https://script.google.com/macros/s/AKfycbwWEtSIi84afllAnhjBEh15U0FB3GyW6CB7tI_Bk-NAYEreVEKYVqNKGdLNzPhQ8xDu2w/exec";
void ketnoiWiFi(){
	WiFi.begin(SSID, Password);
	Serial.print("dang ket noi Wifi");
	while(WiFi.status()!= WL_CONNECTED){
		Serial.print(".");
		delay(500);
	}
	Serial.print(" Da ket noi WiFi");
}
void sentggsheet(){
  if(WiFi.status() == WL_CONNECTED){
    WiFiClientSecure client;
    client.setInsecure();  
    
    HTTPClient http;
    http.begin(client, URLsheet);  // Kết nối tới Google Script
    http.addHeader("Content-Type", "application/json");
    
    String data = "{\"mssv\":\"" + mssv + "\"}";
    int response = http.POST(data);
    
    Serial.print(" Gửi MSSV: ");
    Serial.println(mssv);
    Serial.print(" Phản hồi: ");
    Serial.println(response);
    
    http.end();
  }
  else {
    Serial.println("Không kết nối WiFi");
  }
}

void khoidongoled(){
	display.clearDisplay();
	display.setCursor(40,32);
	display.setTextColor(WHITE);
	display.setTextSize(1);
	display.print("xin chao");
	display.display();
}
void xacnhanmssv(){
	display.clearDisplay();
	display.setCursor(1,1);
	display.setTextColor(WHITE);
	display.setTextSize(1);
	display.print("Da xac nhan");
	display.setCursor(0, 25);
	display.println(mssv);
	display.display();
	sentggsheet();
			
	mssv = "";
	delay(1000);
	display.clearDisplay();
	display.setTextSize(1);
	display.setCursor(0,0);
	display.setTextColor(WHITE);
	display.print("MSSV: ");
	display.display();
}
void xoamssv(){
	mssv = "";
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(30,32);
	display.print("Da xoa MSSV");
	display.display();
	delay(1500);
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.print("MSSV: ");
	display.display();
}
void hienthimssv(){
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.print("MSSV: ");
	display.setCursor(0, 20);
	display.println(mssv);
	display.display();
}
void mssvmax(){
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(20, 30);
	display.print("MSSV day");
	display.display();
}
void setup(){
	Serial.begin(115200);
	ketnoiWiFi();
	Wire.begin(SDApin, SCLpin);
	if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
		Serial.print("khong tim thay man hinh");
		while(1);
	}
	khoidongoled();
}
void loop(){
	char key = keypad.getKey();
	if(key){
		if(key == '#'){
			xacnhanmssv();
		}
		else if(key == '*'){
			xoamssv();
		}
		else{
			if(mssv.length() < max_mssv){
				mssv += key;
				hienthimssv();
			}
			else{
				mssvmax();
				delay(1000);
				hienthimssv();
			}
		}
	}
	delay(250);
}
