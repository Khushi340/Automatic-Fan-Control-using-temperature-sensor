#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int temp_pin= A0; //output pin of temprature sensor lm35
int fan= 9; //fan pin
int on_led= 10;  //red led pin
int off_led= 11; //green led pin
float temp; 
int mintemp=25; //temp where the fan starts
int maxtemp=40; //temp when the fan speed is at highest speed 
float fan_speed;
int fan_lcd;
int dt=1500;
int avg= (maxtemp-mintemp)/5;


void setup() 
{
  // put your setup code here, to run once:
  pinMode(fan, OUTPUT);
  pinMode(off_led, OUTPUT);
  pinMode(on_led, OUTPUT);
  lcd.begin(16,2);
  lcd.setCursor(0,1);
  Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  
  temp= readTemp(); //get the temprature from the surrounding
  Serial.print(temp);
  if(temp<mintemp)
  {
    fan_speed=0;
    analogWrite(fan, fan_speed);
    fan_lcd=0;
    digitalWrite(fan,LOW);
    digitalWrite(on_led, HIGH);
    digitalWrite(off_led, LOW);
  }
  if((temp>mintemp)&&(temp<=mintemp+avg))
  {
    fan_speed=51;
    analogWrite(fan, fan_speed);
    fan_lcd=1;
    digitalWrite(on_led, LOW);
    digitalWrite(off_led, HIGH);
  }
  if((temp>mintemp)&&(temp<=mintemp+((avg)*2)))
  {
    fan_speed=102;
    analogWrite(fan, fan_speed);
    fan_lcd=2;
    digitalWrite(on_led, LOW);
    digitalWrite(off_led, HIGH);
  }
  if((temp>mintemp)&&(temp<=mintemp+((avg)*3)))
  {
    fan_speed=153;
    analogWrite(fan, fan_speed);
    fan_lcd=3;
    digitalWrite(on_led, LOW);
    digitalWrite(off_led, HIGH);
  }
  if((temp>mintemp)&&(temp<=mintemp+((avg)*4)))
  {
    fan_speed=204;
    analogWrite(fan, fan_speed);
    fan_lcd=4;
    digitalWrite(on_led, LOW);
    digitalWrite(off_led, HIGH);
  }
  if(temp>mintemp+((avg)*4))
  {
    fan_speed=255;
    analogWrite(fan, fan_speed);
    fan_lcd=5;
    digitalWrite(on_led, LOW);
    digitalWrite(off_led, HIGH);
  }
  lcd.print("Temprature: ");
  lcd.print(temp);
  lcd.print("C");
  lcd.setCursor(0,1);

  lcd.print("Speed level:");
  lcd.print(fan_lcd);

  delay(dt);
  lcd.clear();
}

int readTemp()  // get the temperature and convert it to celsius
{  temp = analogRead(temp_pin);
  return (temp * 0.48828125);
}
