int boostPin = A2;
int boostVal = 0;
float boostVolt = 0;
float boostKPa = 0;
float boostPSI = 0;

void setup() {  
  
  Serial.begin(9600);
  Serial.println("Multigauge Start Up"); 

}

void loop() {
  
  boostVal = analogRead(boostPin);
  Serial.println("Boost Analog Value");
  Serial.println(boostVal);
  
  boostVolt = boostVal * (5 / 1023.0);
  Serial.println("Boost Voltage");
  Serial.println(boostVolt);
  
  boostKPa = (boostVal*(.00488)/(.022)+20);
  Serial.println("Boost KPa");
  Serial.println(boostKPa);

  boostPSI = (((boostVal/1023)+0.04)/0.004) * 0.145;
  Serial.println("Boost PSI");
  Serial.println(boostPSI);
  
  delay(250);

}
