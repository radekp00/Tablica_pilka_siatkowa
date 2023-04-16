
/*
   Program: Tablica
   Autor: Radosław Pawełek
   Data kompilacji: 12.10.2016
   Płytka: Arduino uno R3
   Opis: Oprogramowanie odbiornika i sterownika do
   tablicy sportowej na salę gimnastyczną.

*/




const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 3;
const int transmit_en_pin = 4;
char odebranedane[0];
int dane;
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int f = 0;
int latchPinp = 130;
int clockPinp = 120;
int dataPinp = 110;
int latchPinl = 5;
int clockPinl = 7;
int dataPinl = 8;
int lastdane = 0;
int newdane = 0;
int lastdanex = 0;
int newdanex = 0;
int zegarloop = 0;

byte dataArrayA[10];
byte dataArrayB[10];


void setup() {
  delay(1000);
  Serial.begin(9600);

  //Konfiguracja liczb wyświetlanych na segmentach poprzez 74hc595
  pinMode(latchPinl, OUTPUT);
  pinMode(clockPinl, OUTPUT);
  pinMode(dataPinl, OUTPUT);
  pinMode(latchPinp, OUTPUT);
  pinMode(clockPinp, OUTPUT);
  pinMode(dataPinp, OUTPUT);
  dataArrayA[0] = 246; //11110110 - 0 Wyświetlane
  dataArrayA[1] = 144; //10010000
  dataArrayA[2] = 124; //01111100
  dataArrayA[3] = 220; //11011100
  dataArrayA[4] = 154; //10011010
  dataArrayA[5] = 206; //11001110
  dataArrayA[6] = 238; //11101110
  dataArrayA[7] = 148; //10010100
  dataArrayA[8] = 254; //11111110
  dataArrayA[9] = 222; //11011110

  dataArrayB[0] = 0; //00000000 - 0  Nie wyświetlane
  dataArrayB[1] = 144; //10010000
  dataArrayB[2] = 124; //01111100
  dataArrayB[3] = 220; //11011100
  dataArrayB[4] = 154; //10011010
  dataArrayB[5] = 206; //11001110
  dataArrayB[6] = 238; //11101110
  dataArrayB[7] = 148; //10010100
  dataArrayB[8] = 254; //11111110
  dataArrayB[9] = 222; //11011110


  digitalWrite(latchPinl, LOW);
  shiftOut(dataPinl, clockPinl, MSBFIRST, 255);
  shiftOut(dataPinl, clockPinl, MSBFIRST, 0);
  shiftOut(dataPinl, clockPinl, MSBFIRST, 255);
  shiftOut(dataPinl, clockPinl, MSBFIRST, 0);
  shiftOut(dataPinl, clockPinl, MSBFIRST, 255);
  shiftOut(dataPinl, clockPinl, MSBFIRST, 255);
  digitalWrite(latchPinl, HIGH);
}
void loop() {

  if (Serial.available() > 0) {
    odebranedane[0] = Serial.read();
    dane = odebranedane[0];
  }

  newdanex = dane;
  if (lastdanex != newdanex && zegarloop == 0) {
    lastdanex = dane;
    /* Przetworzenie danych z pilota na dane zrozumiałe dla tablicy */
    if (dane == 49) {
      a++;
    }
    if (dane == 1) { //50
      a--;
    }
    if (dane == 53) {
      e++;
    }
    if (dane == 54) {
      e--;
    }
    if (dane == 51) {
      c++;
    }
    if (dane == 52) {
      c--;
    }
    if (dane == 55) {
      f++;
    }
    if (dane == 56) {
      f--;
    }
    if (dane == 57) { //RESET
      a = 0;
      b = 0;  //0 NIE WYSWIETLANE
      c = 0;
      d = 0;
      e = 0;  //0 NIE WYSWIETLANE
      f = 0;
    }
    /* Przesunięcie liczy jedności do dziesiątek */

    if (a == 10) {
      b++;
      a = 0;
    }
    if (e == 10) {
      d++;
      e = 0;
    }
    if (a == -1) {
      b--;
      a = 9;
    }
    if (e == -1) {
      d--;
      e = 9;
    }
    newdane = dane;
    if (lastdane != newdane) {
      lastdane = dane;
      digitalWrite(latchPinl, LOW);
      shiftOut(dataPinl, clockPinl, MSBFIRST, dataArrayA[c]);
      shiftOut(dataPinl, clockPinl, MSBFIRST, dataArrayB[b]);
      shiftOut(dataPinl, clockPinl, MSBFIRST, dataArrayA[a]);
      shiftOut(dataPinl, clockPinl, MSBFIRST, dataArrayB[d]);
      shiftOut(dataPinl, clockPinl, MSBFIRST, dataArrayA[e]);
      shiftOut(dataPinl, clockPinl, MSBFIRST, dataArrayA[f]);
      digitalWrite(latchPinl, HIGH);

    }
  }
}


