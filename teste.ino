#include <HCSR04.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

const byte triggerPin = 13;
const byte echoPin = 12;
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

void setup () {
    Wire.begin();
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
    while (!Serial);             
    Serial.println("\nI2C Scanner");
    lcd.begin (16,2);
}

void loop () {
  
  
  

  byte error, address;
  int nDevices;
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("Endereço I2C encontrado: 0x");
      if (address<16)
        Serial.print("0 ");
      Serial.println(address,HEX);
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("ERRO ");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("Nenhum endereço i2C encontrado ");
  else
    
    Serial.println(" Feito !");
 
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    int d1 = 0;
    int d2 = 0;
    int d3 = 0;

    Serial.println("============================================");
    Serial.println("Ciclo de medição de água:");
    delay(500);

    d1 = distanceSensor.measureDistanceCm();
    Serial.print("Primeira medição do nível da água: ");
    Serial.print(d1);
    Serial.println("cm");
    
    delay(3000);

    d2 = distanceSensor.measureDistanceCm();
    Serial.print("Segunda medição do nível da água: ");
    Serial.print(d2);
    Serial.println("cm");

    lcd.setBacklight(HIGH);
    lcd.setCursor(1,0);
  lcd.print("Sem riscos");
  delay(3000);
  lcd.setBacklight(LOW);

    if(d1 - d2 >= 3){
      d3 = d1 - d2;
      Serial.print("A água subiu ");
      Serial.print(d3);
      Serial.println("cm");
      Serial.println("Fique atento a possíveis inundações.");
      lcd.setBacklight(HIGH);
  lcd.setCursor(1,0);
  lcd.print("Possível");
  lcd.setCursor(0,1);
  lcd.print("Inundacao");
      delay(5000);
      lcd.setBacklight(LOW);
    }

    Serial.println("============================================");
    
    delay(3000);

    
}