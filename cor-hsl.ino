#include <EEPROM.h>

// Programa : Detector de cores usando modulo TCS230
//
// Baseado no programa original de Martin Mason
// http://www.arduinoecia.com.br/2014/02/sensor-de-reconhecimento-de-cor-tcs230.html

// Elaborado por Masaki Kawabata Neto

/* README.MD
 * Este programa utiliza o sensor de cor TCS230 para ler as informações RGB de cor apresentadas ao sensor 
 * e as transforma em HSL (http://en.wikipedia.org/wiki/HSL_color_space).
 * Nesse formato é possível detectar as cores procurando manter independência do nível de luminosidade
 * do ambiente.
 * 
 * O progrma utiliza um botão para realizar a calibração do branco.
 * A calibração serve para ajustar o ganho de cada cor do sendor.
 * 
 * O programa permite a ligação de um led RGB que permite reproduzir até
 * 6 cores que são; vermelho, verde, azul, ciano, magenta e amarelo, além do branco.
 * 
 * 
 * 
 * 
 * */
 


//
// 21/7/2015
// incluido led rgb para mostrar a cor

// 22/07/2015, rev2
// clenaup do codigo
//
// 23/07/2015, rev3
// trocado int por byte nos pinos
// colocado id de cor e saida analogica

// 24/07/2015
// incluido data para exportar pro robo

// data
// cores intermediarias mescladas
//

// Pinos de conexao do modulo TCS230
// OE do sensor deve ser connectado no terra
const byte s0 = 8;
const byte s1 = 9;
const byte s2 = 12;
const byte s3 = 11;
const byte out = 10;

// estes pinos são para exportar a informação de cor para o módulo de controle da PETE
// um sinal de dados (pino 5)
// e outro sinal de controle do sensor de cor (vcc->68K-3k3->gnd)
// http://loja.pete.com.br/
const byte data = 5;
const byte id = 6;

// pino de calibracao. Resistor pro terra. Se alto, calibra
const byte calpin = 7; 

// pinos do led RGB
const byte redpin = 2; 
const byte greenpin = 3;
const byte bluepin = 4;

// Variaveis que armazenam o valor das cores
int red = 0; 
int green = 0;
int blue = 0;
int white = 0;
double hsl[3];

const int scale = 5000; // maior divide mais, depende do divisor do sensor
// 5000 vai bem para 100%
// 600 vai bem para 20%
const int bl = 15; // black level: valor abaixo de luninancia é considerado preto
const int wl = 80; // white level

// parametros de calibracao lidos da memoria flash
int cal_r; 
int cal_g;
int cal_b;
int cal_w;
int eeAddress;

// -------------------------------------------------------------
void setup()
{
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  pinMode(calpin, INPUT);
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(id, OUTPUT);

  analogWrite(id, 8);  // seta o id de cor

  Serial.begin(57600);

  // ecolha uma das opções abaixo

  //  digitalWrite(s0, HIGH);  // define escala 20%
  //  digitalWrite(s1, LOW);

  digitalWrite(s0, HIGH);  // define escala 100%
  digitalWrite(s1, HIGH);

  readConfig(); // le configuracao da memoria flash
}

void loop()
{
  if (digitalRead(calpin)) {
    calibrate();
  }
  color(); // le as cores RGBW
  rgbToHsl(red, green, blue, hsl); // converte para HSL
  print_serial(); // mostra os resultados
}

void calibrate () {
  int i;
  for (i = 0; i < 40; i++) { // pisca por 2s
    ledcolor('w');
    delay (25);
    ledcolor('k');
    delay (25);
  }
  cal_r = cal_g =  cal_b = cal_w = 0;
  for (i = 0; i < 10; i++) { // faz a média de 10 leituras
    cal_r += getFrequency(out, 'r');
    cal_g += getFrequency(out, 'g');
    cal_b += getFrequency(out, 'b');
    cal_w += getFrequency(out, 'w');
  }
  cal_r /= 10;
  cal_g /= 10;
  cal_b /= 10;
  cal_w /= 10;

  Serial.print(cal_r, DEC);
  Serial.print(":");
  Serial.print(cal_g, DEC);
  Serial.print(":");
  Serial.print(cal_b, DEC);
  Serial.print(":");
  Serial.println(cal_w, DEC);

  ledcolor('w');
  writeConfig();
  delay (1000);
  ledcolor('k');
  delay (300);
  readConfig();
}

void readConfig() {
  eeAddress = 0;
  EEPROM.get( eeAddress, cal_r ); eeAddress += sizeof(int);
  EEPROM.get( eeAddress, cal_g ); eeAddress += sizeof(int);
  EEPROM.get( eeAddress, cal_b ); eeAddress += sizeof(int);
  EEPROM.get( eeAddress, cal_w );
}

void writeConfig() {
  eeAddress = 0;
  EEPROM.put( eeAddress, cal_r ); eeAddress += sizeof(int);
  EEPROM.put( eeAddress, cal_g ); eeAddress += sizeof(int);
  EEPROM.put( eeAddress, cal_b ); eeAddress += sizeof(int);
  EEPROM.put( eeAddress, cal_w );
}

void print_serial () //Mostra no serial monitor os valores detectados
{
  Serial.print("RGBW: ");
  Serial.print(red, DEC);
  Serial.print(":");
  Serial.print(green, DEC);
  Serial.print(":");
  Serial.print(blue, DEC);
  Serial.print(":");
  Serial.print(white, DEC);

  Serial.print(" HSL: ");
  Serial.print(int(hsl[0]), DEC);
  Serial.print(':');
  Serial.print(int(hsl[1]), DEC);
  Serial.print(':');
  Serial.print(int(hsl[2]), DEC);
  Serial.print(':');

  if (white < bl || (hsl[1] < 20 && white < 40)) {
    Serial.write(" preto ");
    ledcolor('k');
    analogWrite(data, 210);
  }

  if (hsl[1] < 20 && 40 < white && white < 60) {
    Serial.write(" Cinza ");
    ledcolor('k');
    analogWrite(data, 210);
  }

  if (white > wl || (hsl[1] < 20 && white > 60)) {
    Serial.write(" Branco ");
    ledcolor('w');
    analogWrite(data, 180);
  }

  if (bl < white && white < wl && hsl[1] > 20)
  {
    if ((120 - 30) < hsl[0] && hsl[0] < (120 + 30)) {
      Serial.print(" verde ");
      ledcolor('g');
      analogWrite(data, 144);
    }
    if ((240 - 30) < hsl[0] && hsl[0] < (240 + 30)) {
      Serial.print(" azul ");
      ledcolor('b');
      analogWrite(data, 36);
    }
    if ((360 - 30) < hsl[0] || hsl[0] < (0 + 30)) {
      Serial.print(" vermelho ");
      ledcolor('r');
      analogWrite(data, 72);
    }
    if ((180 - 30) < hsl[0] && hsl[0] < (180 + 30)) {
      Serial.print(" ciano ");
      ledcolor('c');
      analogWrite(data, 36); // indefinido: 255
    }
    if ((300 - 30) < hsl[0] && hsl[0] < (300 + 30)) {
      Serial.print(" magenta ");
      ledcolor('m');
      analogWrite(data, 72); // indefinido
    }
    if ((60 - 30) < hsl[0] && hsl[0] < (60 + 30)) {
      Serial.print(" amarelo ");
      ledcolor('y');
      analogWrite(data, 108);
    }
  }
  Serial.println();
}

void ledcolor(char color) {  //valores: wkrgbcmy
  switch (color) {
    case 'w':
      digitalWrite(bluepin, LOW);
      digitalWrite(redpin, LOW);
      digitalWrite(greenpin, LOW);
      break;
    case 'k':
      digitalWrite(redpin, HIGH);
      digitalWrite(greenpin, HIGH);
      digitalWrite(bluepin, HIGH);
      break;
    case 'r':
      digitalWrite(redpin, LOW);
      digitalWrite(greenpin, HIGH);
      digitalWrite(bluepin, HIGH);
      break;
    case 'g':
      digitalWrite(redpin, HIGH);
      digitalWrite(greenpin, LOW);
      digitalWrite(bluepin, HIGH);
      break;
    case 'b':
      digitalWrite(redpin, HIGH);
      digitalWrite(greenpin, HIGH);
      digitalWrite(bluepin, LOW);
      break;
    case 'c':
      digitalWrite(redpin, HIGH);
      digitalWrite(greenpin, LOW);
      digitalWrite(bluepin, LOW);
      break;
    case 'm':
      digitalWrite(redpin, LOW);
      digitalWrite(greenpin, HIGH);
      digitalWrite(bluepin, LOW);
      break;
    case 'y':
      digitalWrite(greenpin, LOW);
      digitalWrite(redpin, LOW);
      digitalWrite(bluepin, HIGH);
      break;
  }
}

long getFrequency(int pin, char color) {
  const int SAMPLES = 16; // faz media de tempo para N pulsos de frequencia
  long freq;
  unsigned int j;

  switch (color) {
    case 'r':
      digitalWrite(s2, LOW);
      digitalWrite(s3, LOW);
      break;
    case 'g':
      digitalWrite(s2, HIGH);
      digitalWrite(s3, HIGH);
      break;
    case 'b':
      digitalWrite(s2, LOW);
      digitalWrite(s3, HIGH);
      break;
    case 'w':
      digitalWrite(s2, HIGH);
      digitalWrite(s3, LOW);
      break;
  }
  delay(1); // teste para ver se muda algo
  freq = 0;
  for (j = 0; j < SAMPLES; j++)
    freq += 500000 / pulseIn(pin, HIGH, 50000);
  return (freq / SAMPLES) / (scale / 100);
}

/**
   Converts an RGB color value to HSL. Conversion formula
   adapted from http://en.wikipedia.org/wiki/HSL_color_space.
   Assumes r, g, and b are contained in the set [0, 255] and
   returns h, s, and l in the set [0-360, 0-100, 0-100].

   @param   Number  r       The red color value
   @param   Number  g       The green color value
   @param   Number  b       The blue color value
   @return  Array           The HSL representation
*/
void rgbToHsl(byte r, byte g, byte b, double hsl[]) {
  double rd = (double) r / 255;
  double gd = (double) g / 255;
  double bd = (double) b / 255;
  double max = threeway_max(rd, gd, bd);
  double min = threeway_min(rd, gd, bd);
  double h, s, l = (max + min) / 2;
  l = rd * 0.3 + gd * 0.59 + bd * 0.11; // usando luma ao inves de luminancia

  if (max == min) {
    h = s = 0; // achromatic
  } else {
    double d = max - min;
    s = l > 0.5 ? d / (2 - max - min) : d / (max + min);
    if (max == rd) {
      h = (gd - bd) / d + (gd < bd ? 6 : 0);
    } else if (max == gd) {
      h = (bd - rd) / d + 2;
    } else if (max == bd) {
      h = (rd - gd) / d + 4;
    }
    h /= 6;
  }
  hsl[0] = h * 360;
  hsl[1] = s * 100;
  hsl[2] = l * 100;
}

double threeway_max(double a, double b, double c) {
  return max(a, max(b, c));
}

double threeway_min(double a, double b, double c) {
  return min(a, min(b, c));
}

void color() //Rotina que le o valor das cores
{
  double f;
  f = getFrequency(out, 'w');
  white = f * 100 / cal_w; // white vai de 0 a 100
  if (white < 0) white = 0;  // nao sei se precisa desse mas ...
  if (white > 100) white = 100;  // corrige pequenas variaçoes de calibracao

  if (white > bl) {
    f = getFrequency(out, 'r');
    red = f * 255 / cal_r;  // RGB escalam até 255.
    if (red < 0) red = 0;   // para compatibilidade com conversor para HSL
    if (red > 255) red = 255;

    f = getFrequency(out, 'g');
    green = f * 255 / cal_g;
    if (green < 0) green = 0;
    if (green > 255) green = 255;

    f = getFrequency(out, 'b');
    blue = f * 255 / cal_b;
    if (blue < 0) blue = 0;
    if (blue > 255) blue = 255;
  }
  else {
    red = 0;
    green = 0;
    blue = 0;
  }
}
