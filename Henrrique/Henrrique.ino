#include <dht11.h>
dht11 DHT;

#include<LiquidCrystal.h>
LiquidCrystal lcd(8,9,10,11,12,13);


//var
int P=6; //POWER SWITCH
int T=A2; // A2 has already been defined as Analog Pin 2 in arduino lib
int L=A4; // A4 has already been defined as Analog Pin 4 in arduino lib
int H=A5; // A5 has already been defined as Analog Pin 5 in arduino lib

void setup()
{
   lcd.begin(16,2);
   pinMode(P, INPUT);

}

////////////////// TEMPERATURE////////////////
 
void Temperature()
{
  int value_temp=analogRead(T); //reading from A2 pin
  float milivolts_temp=((value_temp/1023.0)*5000);
  float CELSIUS=milivolts_temp/10;
  lcd.setCursor(0,1); // column, row
  lcd.print("T:");
  lcd.print(CELSIUS);
}

/////////////// CAPTURE DE POwER STATUS AND DISPLAY

void POWER()
{
    if(digitalRead(P)==LOW)
    {
      lcd.setCursor(0,0);// column, row
      lcd.print("P:");
      lcd.print("OFF");
    }
    else
    {
      lcd.setCursor(0,0);// column, row
        lcd.print("P:");
        lcd.print("ON");
    }
}

///////////////Main funtion///////////////

void loop()

{
    Temperature();
    POWER();
    Light();
    delay(2000);
    lcd.clear();
    
    HUMIDITY();
    delay(2000);
    lcd.clear();
    
}


////////////////Light////////////////
void Light()
{
  int Light_value=analogRead(L); //reading from A4 pin
  float volts_lig=((Light_value/1023.0)*5);
  int LIGHT=500/(4*((5-volts_lig)/volts_lig));
  lcd.setCursor(6,0); // column, row
  lcd.print("Lux:");
  lcd.print(LIGHT);
}

///////////////Humidity//////////////////

void HUMIDITY()
{
  int chk = DHT.read(H);
  float HUM = DHT.humidity;
  lcd.clear();
  lcd.setCursor(9,0);
  lcd.print("H:");
  lcd.print(HUM);
  lcd.print("%");

}
