#include <dht11.h>
dht11 DHT;

#include<LiquidCrystal.h>
LiquidCrystal lcd(8,9,10,11,12,13);


//var
int P=6; // Power switch
int R=5; // Reed switch
int X=7; // PIR sensor

int T=A2; // Temperature - A2 has already been defined as Analog Pin 2 in arduino lib
int L=A4; // Light - A4 has already been defined as Analog Pin 4 in arduino lib
int H=A5; // Humidity - A5 has already been defined as Analog Pin 5 in arduino lib

void setup()
{
   lcd.begin(16,2); // LCD columns,rows
   pinMode(P, INPUT);
   pinMode(R, INPUT);
   pinMode(X, INPUT);

}

////////////////// TEMPERATURE////////////////
 
void TEMPERATURE()
{
  int value_temp=analogRead(T); //reading from A2 pin
  delay(10);
  float milivolts_temp=((value_temp/1024.0)*5000); // (sensor reading)/ADC*Voltage
  float CELSIUS=milivolts_temp/10;
  lcd.setCursor(0,0); // column, row
  lcd.print("Temp:");
  lcd.print(CELSIUS);
}

////////////////Light////////////////
void LIGHT()
{
  int Light_value=analogRead(L); //reading from A4 pin
  float volts_lig=((Light_value/1023.0)*5);
  int LIGHT=500/(4*((5-volts_lig)/volts_lig));
  lcd.setCursor(0,0); // column, row
  lcd.print("Light:");
  lcd.print(LIGHT);
  lcd.print(" lux");
}

///////////////Humidity//////////////////

void HUMIDITY()
{
  int chk = DHT.read(H);
  float HUM = DHT.humidity;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A5:");
  lcd.print(chk);

  lcd.setCursor(0,1);
  lcd.print("Humid:");
  lcd.print(HUM);
  lcd.print("%");

}

/////////////// CAPTURE DE POwER STATUS AND DISPLAY

void POWER()
{
    if(digitalRead(P)==LOW)
    {
      lcd.setCursor(0,0);
      lcd.print("Power:");
      lcd.print("On");
    }
    else
    {
      lcd.setCursor(0,1);// column, row
        lcd.print("Power:");
        lcd.print("Off");
    }
}

// Reed Switch (Magnet)

void REED()
{
  if (digitalRead(R)==LOW)
  {
    lcd.setCursor(0,1);
    lcd.print("Magnet:Yes");
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("Magnet:No");
  }
}

// Infra Red Sensor
void PIR()
{
   if (digitalRead(X) == LOW)
   {
    lcd.setCursor(0,0);
    lcd.print("Human:No");
   }
   else
   {
    lcd.setCursor(0,1);
    lcd.print("Human:Yes");
   }
}

///////////////Main funtion///////////////

void loop()

{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Internet of Wild");
  lcd.setCursor(0,1);
  lcd.print("Animals");
  delay(2000);
  lcd.clear();
  while(1)
  {
    POWER();
    delay(1000);
    lcd.clear();
    
    TEMPERATURE();
    delay(1000);
    lcd.clear();
    
    LIGHT();
    delay(1000);
    lcd.clear();
    
    PIR();
    delay(1000);
    lcd.clear();
    
    REED();
    delay(1000);
    lcd.clear();
    
    //HUMIDITY();
  }
    
}
