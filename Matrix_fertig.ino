/* IT - GFS
   LED-Matrix
   von Jona Maletic und Stefanie Stefanescu  Juli 2015
   erweiter um Dauerschleife  Arno Weinheimer 15.12.2015
*/
#include <SoftwareSerial.h>

#include "Arduino.h"
#include "MaxMatrix.h"
//#include "TimerOne.h"   //irrelevant

#include <avr/pgmspace.h>
SoftwareSerial btSerial(11, 12); // RX, TX Bluetthoth Modul HC06
// String mytext ="Frohe Weihnachten   ";
//String mytext= "Herzlich willkommen im TG Informationstechnik       ";
  
PROGMEM const unsigned char CH[] = 
{
  3, 8, B00000000, B00000000, B00000000, B00000000, B00000000, // space
  1, 8, B01011111, B00000000, B00000000, B00000000, B00000000, // !
  3, 8, B00000011, B00000000, B00000011, B00000000, B00000000, // "
  5, 8, B00010100, B00111110, B00010100, B00111110, B00010100, // #
  4, 8, B00100100, B01101010, B00101011, B00010010, B00000000, // $
  5, 8, B01100011, B00010011, B00001000, B01100100, B01100011, // %
  5, 8, B00110110, B01001001, B01010110, B00100000, B01010000, // &
  1, 8, B00000011, B00000000, B00000000, B00000000, B00000000, // '
  3, 8, B00011100, B00100010, B01000001, B00000000, B00000000, // (
  3, 8, B01000001, B00100010, B00011100, B00000000, B00000000, // )
  5, 8, B00101000, B00011000, B00001110, B00011000, B00101000, // *
  5, 8, B00001000, B00001000, B00111110, B00001000, B00001000, // +
  2, 8, B10110000, B01110000, B00000000, B00000000, B00000000, // ,
  4, 8, B00001000, B00001000, B00001000, B00001000, B00000000, // -
  2, 8, B01100000, B01100000, B00000000, B00000000, B00000000, // .
  4, 8, B01100000, B00011000, B00000110, B00000001, B00000000, // /
  4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // 0
  3, 8, B01000010, B01111111, B01000000, B00000000, B00000000, // 1
  4, 8, B01100010, B01010001, B01001001, B01000110, B00000000, // 2
  4, 8, B00100010, B01000001, B01001001, B00110110, B00000000, // 3
  4, 8, B00011000, B00010100, B00010010, B01111111, B00000000, // 4
  4, 8, B00100111, B01000101, B01000101, B00111001, B00000000, // 5
  4, 8, B00111110, B01001001, B01001001, B00110000, B00000000, // 6
  4, 8, B01100001, B00010001, B00001001, B00000111, B00000000, // 7
  4, 8, B00110110, B01001001, B01001001, B00110110, B00000000, // 8
  4, 8, B00000110, B01001001, B01001001, B00111110, B00000000, // 9
  2, 8, B01001000, B00000000, B00000000, B00000000, B00000000, // :
  2, 8, B10000000, B01010000, B00000000, B00000000, B00000000, // ;
  3, 8, B00010000, B00101000, B01000100, B00000000, B00000000, // <
  3, 8, B00010100, B00010100, B00010100, B00000000, B00000000, // =
  3, 8, B01000100, B00101000, B00010000, B00000000, B00000000, // >
  4, 8, B00000010, B01011001, B00001001, B00000110, B00000000, // ?
  5, 8, B00111110, B01001001, B01010101, B01011101, B00001110, // @
  4, 8, B01111110, B00010001, B00010001, B01111110, B00000000, // A
  4, 8, B01111111, B01001001, B01001001, B00110110, B00000000, // B
  4, 8, B00111110, B01000001, B01000001, B00100010, B00000000, // C
  4, 8, B01111111, B01000001, B01000001, B00111110, B00000000, // D
  4, 8, B01111111, B01001001, B01001001, B01000001, B00000000, // E
  4, 8, B01111111, B00001001, B00001001, B00000001, B00000000, // F
  4, 8, B00111110, B01000001, B01001001, B01111010, B00000000, // G
  4, 8, B01111111, B00001000, B00001000, B01111111, B00000000, // H
  3, 8, B01000001, B01111111, B01000001, B00000000, B00000000, // I
  4, 8, B00110000, B01000000, B01000001, B00111111, B00000000, // J
  4, 8, B01111111, B00001000, B00010100, B01100011, B00000000, // K
  4, 8, B01111111, B01000000, B01000000, B01000000, B00000000, // L
  5, 8, B01111111, B00000010, B00001100, B00000010, B01111111, // M
  5, 8, B01111111, B00000100, B00001000, B00010000, B01111111, // N
  4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // O
  4, 8, B01111111, B00001001, B00001001, B00000110, B00000000, // P
  4, 8, B00111110, B01000001, B01000001, B10111110, B00000000, // Q
  4, 8, B01111111, B00001001, B00001001, B01110110, B00000000, // R
  4, 8, B01000110, B01001001, B01001001, B00110010, B00000000, // S
  5, 8, B00000001, B00000001, B01111111, B00000001, B00000001, // T
  4, 8, B00111111, B01000000, B01000000, B00111111, B00000000, // U
  5, 8, B00001111, B00110000, B01000000, B00110000, B00001111, // V
  5, 8, B00111111, B01000000, B00111000, B01000000, B00111111, // W
  5, 8, B01100011, B00010100, B00001000, B00010100, B01100011, // X
  5, 8, B00000111, B00001000, B01110000, B00001000, B00000111, // Y
  4, 8, B01100001, B01010001, B01001001, B01000111, B00000000, // Z
  2, 8, B01111111, B01000001, B00000000, B00000000, B00000000, // [
  4, 8, B00000001, B00000110, B00011000, B01100000, B00000000, // \ backslash
  2, 8, B01000001, B01111111, B00000000, B00000000, B00000000, // ]
  3, 8, B00000010, B00000001, B00000010, B00000000, B00000000, // ^
  4, 8, B01000000, B01000000, B01000000, B01000000, B00000000, // _
  2, 8, B00000001, B00000010, B00000000, B00000000, B00000000, // `
  4, 8, B00100000, B01010100, B01010100, B01111000, B01110000, // a
  4, 8, B01111111, B01000100, B01000100, B00111000, B00000000, // b
  4, 8, B00111000, B01000100, B01000100, B00101000, B00000000, // c
  4, 8, B00111000, B01000100, B01000100, B01111111, B00000000, // d
  4, 8, B00111000, B01010100, B01010100, B00011000, B00000000, // e
  3, 8, B00000100, B01111110, B00000101, B00000000, B00000000, // f
  4, 8, B10011000, B10100100, B10100100, B01111000, B00000000, // g
  4, 8, B01111111, B00000100, B00000100, B01111000, B00000000, // h
  3, 8, B01000100, B01111101, B01000000, B00000000, B00000000, // i
  4, 8, B01000000, B10000000, B10000100, B01111101, B00000000, // j
  4, 8, B01111111, B00010000, B00101000, B01000100, B00000000, // k
  3, 8, B01000001, B01111111, B01000000, B00000000, B00000000, // l
  5, 8, B01111100, B00000100, B01111100, B00000100, B01111000, // m
  4, 8, B01111100, B00000100, B00000100, B01111000, B00000000, // n
  4, 8, B00111000, B01000100, B01000100, B00111000, B00000000, // o
  4, 8, B11111100, B00100100, B00100100, B00011000, B00000000, // p
  4, 8, B00011000, B00100100, B00100100, B11111100, B00000000, // q
  4, 8, B01111100, B00001000, B00000100, B00000100, B00000000, // r
  4, 8, B01001000, B01010100, B01010100, B00100100, B00000000, // s
  3, 8, B00000100, B00111111, B01000100, B00000000, B00000000, // t
  4, 8, B00111100, B01000000, B01000000, B01111100, B00000000, // u
  5, 8, B00011100, B00100000, B01000000, B00100000, B00011100, // v
  5, 8, B00111100, B01000000, B00111100, B01000000, B00111100, // w
  5, 8, B01000100, B00101000, B00010000, B00101000, B01000100, // x
  4, 8, B10011100, B10100000, B10100000, B01111100, B00000000, // y
  3, 8, B01100100, B01010100, B01001100, B00000000, B00000000, // z
  3, 8, B00001000, B00110110, B01000001, B00000000, B00000000, // {
  1, 8, B01111111, B00000000, B00000000, B00000000, B00000000, // |
  3, 8, B01000001, B00110110, B00001000, B00000000, B00000000, // }
  4, 8, B00001000, B00000100, B00001000, B00000100, B00000000, // ~  ASCII 126
  4, 8, B00100000, B01010101, B01010100, B01111001, B00000000, // ä   //CH[95] kleiner machen va ö ü 
  4, 8, B01111101, B00010010, B00010010, B01111101, B00000000, // A
  4, 8, B00110000, B01001001, B01001000, B00110001, B00000000, // ö
  4, 8, B00111001, B01000100, B01000100, B00111001, B00000000, // O
  4, 8, B00111000, B01000001, B01000000, B01111001, B00000000, // ü
  4, 8, B00111101, B01000000, B01000000, B00111101, B00000000, // Ü
};

int USE_POT_CONTROL = 1;  //H: geschwindigkeit (SCROLL_DELAY) wird nich beachtet, wenn "0"

int data = 8;    // 8, DIN Pin auf MAX7219 Modul
int load = 9;    // 9, CS Pin auf MAX7219 Modul
int clock = 10;   // 10, CLK Pin auf MAX7219 Modul

int sec = 0;
//int timerMin = 0;  //irrelevant
int timerStop = 0;//in sec

int maxInUse = 4;    // wieviele Matrizen angeschlossen sind
int maxNumber = maxInUse*8; // Anzahl der Spalten

int Intensity = 2; //0..15 Helligkeit
int BUF_SIZE = 10; //Anzahl der Zeichen / Worte die gesendet werden 

int SPEED_IN = A0;
int SCROLL_DELAY = 100; //Schnelligkeit der Textausgabe in msec

int t;
int scrollDelay;
char serialMessage[100];
char newMessage[100];
char *curMessage;
boolean newMessageAvailable = true;

MaxMatrix m(data, load, clock, maxInUse); // definiere Modul

byte buffer[100];
//char string1[] = "";    //irrelevant?
String mytext = ".";
String defaultText = "Hello World! :)";

/*
void changeDefaultText(String text){
  defaultText = text;
}

void setSec(int i){
  sec = i;
}


*/

void setup()
{  
  //if(i >= 0){

  mytext += "     ";
  defaultText += "     ";
    
  
  Serial.begin(9600); // start serial connection
  
  while (!Serial) 
  {
    ; // warten auf Serial
  }
  Serial.println("Verbindung besteht");
  // setze Datenrate f�r Serial
  btSerial.begin(9600);
  m.init(); // module initialize
  m.setIntensity(Intensity); // dot matix intensity 0-15

  if (USE_POT_CONTROL)
  {
    pinMode(SPEED_IN, INPUT);
  }
  else
  {
    scrollDelay = 10;
  }
  newMessage[0] = '\0';
}


ISR(TIMER1_COMPA_vect) { // called by timer1; Doesnt work for mytext = ""
  sec++;
  Serial.println(sec);
  Serial.println("######################################");
  if(sec >= timerStop){
    timer_stop();
    sec = 0;
  }
}


void setMin(int timerMin){  //, String text){    //für Robert!!!!!
  sec = timerMin * 60;


  //MARK: Timer init
  
  //tmr.initialize(10000, thl);   //irrelevant
  //tmr.start();
  //TODO: only start if we have sec != 0
  cli(); // disable interrupts
  
  // reset
  TCCR1A = 0; // set TCCR1A register to 0
  TCCR1B = 0; // set TCCR1B register to 0
  TCNT1  = 0; // reset counter value
  
  OCR1A = 15624; // compare match register

  // set prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);   //1:1024
  
  TCCR1B |= (1 << WGM12); // turn on CTC mode
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  
  sei(); // allow interrupts
    //} //end of if sec >= 0
}


void timer_stop(){
  mytext = defaultText;

  TCCR1A = 0; // set TCCR1A register to 0
  TCCR1B = 0; // set TCCR1B register to 0
  TCNT1  = 0; // reset counter value
  cli();
}


void loop()
{
  //scrollDelay = 10;
  //getScrollDelay();
  
  //Serial.println("loop()");
  
  readSerial();
  scrollText();

}




void readSerial(void) //Eingabe �ber die serielle Schnittstelle 
{
  
  int putIndex = 0;
  //mytext = "";
  Serial.println("readSerial bt?!");
  while (btSerial.available())
  {
    mytext += (char)btSerial.read();     //'+=' ??
  }
  //Serial.print(mytext);
  //Serial.println("");
  // mytext = "Herzlich willkommen im TG Informationstechnik.     ";
  

  /*while (btSerial.available()) 
  {
       mytext += (char)btSerial.read();     
  }
  //Serial.print(mytext);
  //Serial.println("");*/
  
}

void scrollText(void)
{
  /*
  if(newMessageAvailable)
  {	// neuer Text ist vorhanden
    strcpy(serialMessage, newMessage);  // Text kopieren
    newMessageAvailable = false;
    printStringWithShift(serialMessage, scrollDelay);
    Serial.print(serialMessage);
  }
  */

  // Ausgabe an mytext String; in char umwandeln
  Serial.println("scrollText()");
  
  char charBuf[100];
  mytext.toCharArray(charBuf,100);
  curMessage = charBuf;
//  Serial.println(curMessage);
  printStringWithShift(curMessage, scrollDelay);
}

int getScrollDelay(void)
{
  Serial.println("scrollDelay");
  if (USE_POT_CONTROL)
  {
    t = analogRead(SPEED_IN);
    t = map(t, 0, 1023, 5, 300);
    return(t);
  }
  else
  {
    t = SCROLL_DELAY;
  }
}

void printCharWithShift(char c, int shift_speed)
{
  //Serial.println("pCWS");
  shift_speed = getScrollDelay();
  
  //Serial.println(int(c));
  
  if (c < 32){    //wenn zeichen nicht im ascii code
    switch(c){
      case -92: 
        c = 95;//?
        break;
        
      case -74: 
        c = 96;//?
        break;
        
      case -68: 
        c = 97;//?
        break;
        
      case -124: 
        c = 98;//?
        break;

      case -106: 
        c = 99;//?
        break;

      case -100: 
        c = 100;//?
        break;

      default:
        return;
    }
  }
  else{
      c -= 32;    //c is index ofCH[]
  }
  
  //Serial.println(int(c));
  
  memcpy_P(buffer, CH + 7*c, 7);
  m.writeSprite(maxNumber, 0, buffer);
  m.setColumn(maxNumber + buffer[0], 0);

  for (int i=0; i<buffer[0]+1; i++) 
  {
    delay(shift_speed);
    m.shiftLeft(false, false);
  }
}

void printStringWithShift(char* s, int shift_speed)
{
  Serial.println("pSWS");
  //Serial.println(s);
  while (*s != 0)
  {
    shift_speed = getScrollDelay();
    printCharWithShift(*s, shift_speed);
    //Serial.println(*s);
    s++;
  }
  Serial.println("END pSWS");
}

void printString(char* s)
{
  Serial.println("pS");
  unsigned char c;
  int col = 0;
  while (*s != 0)
  {
    if (*s < 32) continue; // Alles was kleiner als der ASCII-Code ist
    c = *s - 32; // Startwert auf des Leerzeichen setzen ASCII Leerzeichen = ASCII 32
    
   /* switch(c)
    {
      case 228: // ä
        c = 127;  // gepatchter ASCII-Code
        //c = 95;
        break; 
      case 196: // Ä
        c = 128;
        break;
      case 246: // ö
        c = 129;
        break;
      case 214: // Ö
        c = 130;
        break;
      case 252: // ü
        c = 131;
        break;
      case 220: // Ü
        c = 132;
        break;
    }*/

    memcpy_P(buffer, CH + 7*c, 7);
    m.writeSprite(col, 0, buffer);
    m.setColumn(col + buffer[0], 0);
    col += buffer[0] + 1;
    s++;
  }
}
