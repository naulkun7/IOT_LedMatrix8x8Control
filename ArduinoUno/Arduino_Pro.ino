// Mario's Ideas
//MAX7219 - using SPI library to display 8x8 bitmap
#include <SPI.h>
#include <SoftwareSerial.h>

#define CS 7
typedef unsigned char byte;

// SoftwareSerial mySerial (0,1);

#define DECODE_MODE   9 
#define INTENSITY 0x0A
#define SCAN_LIMIT 0x0B 
#define SHUTDOWN 0x0C
#define DISPLAY_TEST 0x0F

char receiver[8];
// byte Cat[8] = {136,248,168,113,033,121,125,190};

void translate(char string[], char array[]) {
  int stringLength = strlen(string);
  int arrayIndex = 0;
  int ar = 0;
  char a[3];

  for (int i = 0; i < stringLength+1; i++) {
    if (string[i] != ',') {
      a[arrayIndex] = string[i];
      arrayIndex++;
    }
    else  {
      array[ar] = atoi(a);
      arrayIndex = 0;
      ar++;
    }
  }
}

void SendData(uint8_t address, uint8_t value) {  
  digitalWrite(CS, LOW);   
  SPI.transfer(address);      // Send address.
  SPI.transfer(value);        //   Send the value.
  digitalWrite(CS, HIGH); // Finish transfer.
}

void setup()   {
  pinMode(CS, OUTPUT);  
  SPI.setBitOrder(MSBFIRST);   // Most significant   bit first 
  SPI.begin();                 // Start SPI
  SendData(DISPLAY_TEST, 0x01);       // Run test - All LED segments lit.
  delay(1000);
  SendData(DISPLAY_TEST, 0x00);           // Finish test mode.
  SendData(DECODE_MODE, 0x00);            //   Disable BCD mode. 
  SendData(INTENSITY, 0x0e);              // Use lowest intensity.   
  SendData(SCAN_LIMIT, 0x0f);             // Scan all digits.   
  SendData(SHUTDOWN, 0x01);               // Turn on chip.

  Serial.begin(9600);
  // mySerial.begin(9600);
}
void loop()  {
  char data[33];
  String value = Serial.readStringUntil('\r');

  Serial.println(value);
  value.toCharArray(data,33);

  // char data[] = "024,008,118,255,255,255,122,052,";
  translate(data, receiver);

  for (int i=1;i<9;i++)   SendData(i, receiver[i-1]);
}