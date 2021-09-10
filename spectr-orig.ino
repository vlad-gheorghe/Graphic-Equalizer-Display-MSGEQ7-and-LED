//http://kazus.ru/shemes/showpage/0/1548/
#define STROBE_PIN 11 // MSGEQ7 PIN 4 (17)
#define RESET_PIN 12 // MSGEQ7 PIN 7  (18)
#define PWM_PIN 10 // УПРАВЛЕНИЕ ЯРКОСТЬЮ (nefolosit)
#define SOUND_PIN A0 // АНАЛИЗ УРОВНЯ СИГНАЛА (A0=23)

byte band_pins[7]={2,3,5,6,7,8,9}; // ПОРТЫ СТОЛБЦОВ (4,5,11,12,13,14,15)
byte band_bright[7]={200,200,200,200,200,200,200}; // УРОВНИ ЯРКОСТИ ДЛЯ КАЖДОГО ЦВЕТА
byte band_analys[7]; // МАССИВ ДЛЯ АНАЛИЗА УРОВНЕЙ
byte band_counter;

void setup(){
  TCCR1B&=~7; // УСТАНАВЛИВАЕМ ЧАСТОТУ PWM 64кГц
  TCCR1B|=2;  // ...
  for(int i=2; i<13; i++) pinMode(i,OUTPUT);
  pinMode(SOUND_PIN,INPUT);
}

void loop(){
  MSGEQ7();
}

void MSGEQ7(){
  digitalWrite(RESET_PIN,HIGH);
  delayMicroseconds(1);
  digitalWrite(RESET_PIN,LOW);
  delayMicroseconds(72); 
  for (int i=0; i<7; i++)
    {
    band_counter=0;
    analogWrite(PWM_PIN, band_bright[i]);
    digitalWrite(STROBE_PIN,LOW);
    delayMicroseconds(36); 
    band_analys[i]=map(analogRead(SOUND_PIN),5,1023,0,255);
    if (band_analys[i]>4)
      {
      for (int j=0; j<7; j++)
        if ((j!=i) && (band_analys[j]>4)) band_counter++;
      }
    if (band_counter>2) digitalWrite(band_pins[i],LOW);
    delayMicroseconds(1600);
    digitalWrite(band_pins[i],HIGH);
    digitalWrite(STROBE_PIN,HIGH);
    delayMicroseconds(36);
    }
} 
