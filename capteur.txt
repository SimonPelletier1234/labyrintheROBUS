
#include <Arduino.h>

const int pinRouge = 2;
const int pinVert  = 3;

int Find_Mur() {
  bool rouge = digitalRead(pinRouge);
  bool vert  = digitalRead(pinVert);

  if (rouge == HIGH && vert == LOW) {
    return 1;  
  }
  else if (rouge == LOW && vert == HIGH) {
    return 2;   
  }
  else if (rouge == LOW && vert == LOW) {
    return 0;   
  }
  else {
    return 3;   
  }
}


