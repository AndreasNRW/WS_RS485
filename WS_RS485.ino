#include <SPI.h>
#include <stdlib.h>
#include <Controllino.h>  /* Usage of CONTROLLINO library allows you to use CONTROLLINO_xx aliases in your sketch. */

/*
  CONTROLLINO - Demonstration of RS485 interface usage, Version 02.00

  Compatible with CONTROLLINO MAXI and MEGA.

  IMPORTANT INFORMATION!
  Please, select proper target board in Tools->Board->Controllino MAXI/MEGA before Upload to your CONTROLLINO.
  
  (Refer to https://github.com/CONTROLLINO-PLC/CONTROLLINO_Library if you do not see the CONTROLLINOs in the Arduino IDE menu Tools->Board.)

  This example sketch requires external 12V or 24V power supply for your CONTROLLINO and RS485 communication partner device (e.g. RS485-USB converter and PC). 

  Created 12 Jan 2017, Updated 20.09.2018
  by Lukas

  https://controllino.biz/
  
  (Check https://github.com/CONTROLLINO-PLC/CONTROLLINO_Library for the latest CONTROLLINO related software stuff.)
*/


char buf[80];

int readline(int readch, char *buffer, int len) {
    static int pos = 0;
    int rpos;

    if (readch > 0) {
        switch (readch) {
            case '\n': // Ignore CR
                break;
            case '\r': // Return on new-line
                rpos = pos;
                pos = 0;  // Reset position index ready for next time
                return rpos;
            default:
                if (pos < len-1) {
                    buffer[pos++] = readch;
                    buffer[pos] = 0;
                }
        }
    }
    return 0;
}




void setup() {
  
  /* Initialize serial port for debug messages. */
  Serial.begin(9600);
  //hi
  
  /* Initialize CONTROLLINO RS485 direction control DE/RE pins and Serial3 */
  Controllino_RS485Init(9600);
  //Controllino_RS485RxEnable();

  Serial.println("Recieving RS485...");
}

void loop() {
  
 //Controllino_RS485RxEnable();
 
  
  
  if (readline(Serial3.read(), buf, 80) == 8) {
        Serial.print("You entered: >");
        Serial.print(buf);
        Serial.println("<");
        delay(500);
        char* buf_trunc = buf + 2;
        Serial.print("nach Umwandlung");
        Serial.println(buf_trunc);
        float number1 = atof(buf_trunc);
        Serial.print("nach atoi: ");
        Serial.println(number1);
    }
  }
  


/* 2018-09-20: The sketch was successfully tested with Arduino 1.8.5, Controllino Library 3.0.2 and CONTROLLINO MAXI and MEGA. */
