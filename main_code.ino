
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Stepper.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);   
int Sensor= 0; 
int value= 0;
float h;
float t;
bool up = true;

const int stepsPerRevolution = 264; 
Stepper myStepper(stepsPerRevolution, 6, 5, 4, 3); 

void setup() {
  lcd.init();                     
  lcd.backlight();
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();

  myStepper.setSpeed(14);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Moist:");
  lcd.print(value);
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Hum:");
  lcd.print(h,0);
  lcd.print(" ");
  lcd.print("Temp:");
  lcd.print(t,0);

  delay(2000);
  lcd.clear();
  h = dht.readHumidity();
  t = dht.readTemperature();

  if (isnan(h) || isnan(t)) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  value= analogRead(A3);
  value= value/10;
  
  if (value < 110 && up ) {
      myStepper.step(-stepsPerRevolution);
      up = false;
    
  }

  if (value > 110 && !up) {
     myStepper.step(stepsPerRevolution);
     up = false;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println("");

  Serial.print("MOISTURE LEVEL : ");
  Serial.println(value);
  delay(1000);
}


