

#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

#include <Stepper.h> // Include the header file

#define BLYNK_PRINT Serial



#define STEPS 64



Stepper stepper(STEPS, D1, D3, D2, D4);

char auth[] = "l_b47mF1hioCc_7FzdKMJJeFnJjTxxxx";


char ssid[] = "satish";

char pass[] = "satish123";


boolean closed = false;

boolean opened = true; 

void disable_motor() 

{

  digitalWrite(D1,LOW);

  digitalWrite(D2,LOW);

  digitalWrite(D3,LOW);

  digitalWrite(D4,LOW);

}

void setup()

{

  pinMode(D0, OUTPUT);

  digitalWrite(D0,HIGH); 

  Serial.begin(9600);

  stepper.setSpeed(500);

  Blynk.begin(auth, ssid, pass);


  digitalWrite(D0,LOW); //turn it off after connecting to blynk 

}

BLYNK_WRITE(V1) 

  {

    Serial.println("Closing Blinds");

    if (opened == true)

    {

    for (int c_val = 0; c_val <= 130; c_val++) //rotate in Counter-Clockwise for closing

    {

      stepper.step(c_val);

      yield();

    }

    closed = true;

    opened = false; 

    disable_motor(); 
    }

  }

  BLYNK_WRITE(V2)

  {

    Serial.println("Opening Blinds");

    if (closed == true)

    {

    for (int cc_val = 0; cc_val >= -130; cc_val--) 

    {

      stepper.step(cc_val);

      yield();

    }

    opened = true; 

    closed = false;

    }

    disable_motor(); 

  }

void loop()

{

  Blynk.run();

}

