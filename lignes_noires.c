#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:

  //Initialise le port de communication et attend pour l'ouvrir:
  Serial.begin(9600);
  //Ce délai permet de s'assurer que le moniteur serie (Serial Monitor) soit disponible
  delay(1500);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Bonjour le monde!");

  delay(100);
}

// put function definitions here:
//{

int lignes_noires = {{1,0,0,1},
                    {1,1,1,1},
                    {1,0,0,1},
                    {1,1,1,1},
                    {1,0,0,1},
                    {1,1,1,1},
                    {1,0,0,1},
                    {1,1,1,1},
                    {1,0,0,1},
                    {1,1,1,1}}


//}