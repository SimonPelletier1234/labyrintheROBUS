// Avancer droit (contrôle P) — LibRobUS
#include <LibRobus.h>

// === Réglages simples ===
const float vitesseBase = 0.10f;        // consigne de vitesse (0..1)
const float gainProportionnel = 0.02f;  // Kp : corrige l’écart gauche-droite
const uint16_t periodeEchantillonnageMs = 20;

long ticksGauchePrecedent = 0;
long ticksDroitePrecedent = 0;

void setup() {
  BoardInit();            // init moteurs + encodeurs
  ENCODER_Reset(0);       // 0 = encodeur moteur gauche
  ENCODER_Reset(1);       // 1 = encodeur moteur droit

  // démarrage à la vitesse de base
  MOTOR_SetSpeed(0, vitesseBase);
  MOTOR_SetSpeed(1, vitesseBase);

  ticksGauchePrecedent = ENCODER_Read(0);
  ticksDroitePrecedent = ENCODER_Read(1);
}

void loop() {
  // 1) lecture des encodeurs
  long ticksGauche = ENCODER_Read(0);
  long ticksDroite = ENCODER_Read(1);

  // 2) variation de ticks ≈ vitesse instantanée
  long deltaTicksGauche = ticksGauche - ticksGauchePrecedent;
  long deltaTicksDroite = ticksDroite - ticksDroitePrecedent;

  // 3) erreur de vitesse (si >0, la gauche va plus vite que la droite)
  long erreurVitesse = deltaTicksGauche - deltaTicksDroite;

  // 4) correction proportionnelle
  float correction = gainProportionnel * erreurVitesse;

  // 5) commandes gauche/droite (on baisse celle qui va trop vite)
  float commandeGauche = vitesseBase - correction;
  float commandeDroite = vitesseBase + correction;

  // 6) bornes de sécurité
  if (commandeGauche > 1)  commandeGauche = 1;
  if (commandeGauche < -1) commandeGauche = -1;
  if (commandeDroite > 1)  commandeDroite = 1;
  if (commandeDroite < -1) commandeDroite = -1;

  // 7) envoi aux moteurs
  MOTOR_SetSpeed(0, commandeGauche);
  MOTOR_SetSpeed(1, commandeDroite);

  // 8) mémorisation + tempo d'échantillonnage
  ticksGauchePrecedent = ticksGauche;
  ticksDroitePrecedent = ticksDroite;
  delay(periodeEchantillonnageMs);
}
