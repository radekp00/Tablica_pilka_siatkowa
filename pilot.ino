/*
 * Program: Tablica_Pilot                                                                          
 * Autor: Radosław Pawełek                                
 * Data kompilacji 12.10.2016                          
 * Płytka: Arduino nano 5V atmega328
 * Opis: Oprogramowanie nadajnika do tablicy sportowej                                                              
 * 
                                
 */

const int led_pin = 12;
const int transmit_pin = 2;
const int receive_pin = 98;
const int transmit_en_pin = 99;
char dane = '0';
int serial = 0;
int ab = 11;
int bb = 10;
int cb = 9;
int db = 8;
int eb = 7;
int fb = 6;
int gb = 5;
int hb = 4;
int ib = 3;
int as = 0;
int bs = 0;
int cs = 0;
int ds = 0;
int es = 0;
int fs = 0;
int gs = 0;
int hs = 0;
int is = 0;
int voltPin = 14;
int led_pinx = 12;
int wartosc = 0;
float wolty = 0;
int xyz = 0;
int danelicznik = 0;
int reset = 0;

void setup() {
  Serial.begin(9600);

  // IO
  pinMode(ab, INPUT_PULLUP);
  pinMode(bb, INPUT_PULLUP);
  pinMode(cb, INPUT_PULLUP);
  pinMode(db, INPUT_PULLUP);
  pinMode(eb, INPUT_PULLUP);
  pinMode(fb, INPUT_PULLUP);
  pinMode(gb, INPUT_PULLUP);
  pinMode(hb, INPUT_PULLUP);
  pinMode(ib, INPUT_PULLUP);
  pinMode(led_pinx, OUTPUT);
  delay(50);
  es = digitalRead(eb);
  gs = digitalRead(gb);
}

void loop() {
as = digitalRead(ab);
bs = digitalRead(bb);
cs = digitalRead(cb);
ds = digitalRead(db);
es = digitalRead(eb);
fs = digitalRead(fb);
gs = digitalRead(gb);
hs = digitalRead(hb);
is = digitalRead(ib);

    if (as == 0) {
    dane = '7'; //a++, Punkty lewa strona +1
    danelicznik = 5;
  }
    if (bs == 0) {
    dane = '5'; //a--, Punkty lewa strona -1
    danelicznik = 5;
  }
    if (cs == 0) {
    dane = '6'; //e++ Punkty prawa strona +1
    danelicznik = 5;
  }
    if (ds == 0) {
    dane = '8'; //e-- Punkty prawa strona -1
    danelicznik = 5;
  }
    if (es == 0) {
    dane = '9'; //c++ Sety lewa strona +1
    danelicznik = 5;
    reset ++;
  } else {
    reset = 0;
  }
    if (fs == 0) {
    dane = '3'; //c-- Sety lewa strona -1
    danelicznik = 5;
  }
    if (gs == 0) {
    dane = '1'; //f++ Sety prawa strona +1
    danelicznik = 5;
  }
    if (hs == 0) {
    dane = '2'; //f-- Sety prawa strona -1
    danelicznik = 5;
  }
    if (is == 0) {
    dane = '4'; //Reset All
    danelicznik = 5;
  }


if(danelicznik > 0){
char danex = {dane};
Serial.print(danex);
delay(10);
dane = '0';
danelicznik--;
}

  int wartosc = analogRead(voltPin); // odczytuję wartość na pinie analogowym  
  float wolty = wartosc / 204.8; // konwertuje wartość na napiecie 
  if(wolty < 3.60 && wolty > 3.51){
    digitalWrite(led_pinx, HIGH);
  } else {
    digitalWrite(led_pinx, LOW);
  }

  if(wolty < 3.55 && xyz > 500){
    digitalWrite(led_pinx, HIGH);
  } else {
    digitalWrite(led_pinx, LOW);
  }
xyz++;
if(xyz == 1000){
  xyz = 0;
}
if(reset > 100){
    dane = 'a'; //Reset All
    danelicznik = 5;
}

}



