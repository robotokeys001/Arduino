#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Costanti Fisiche
const int PIN_BUTTON = 2;
const int TERRENO_Y = 57;
const int DINO_X = 15;
const float GROUND_Y = 46.0; 
const float GRAVITY = 1.2;     // Forza di gravità costante
const float JUMP_FORCE = 8.0; // Potenza del salto singolo

// Variabili Dino (Uso float per fluidità fisica)
float dinoY = GROUND_Y;
float velocitaVerticale = 0;
bool isGrounded = true;
bool canDoubleJump = false; // Stato per gestire il secondo salto
bool lastButtonState = HIGH; // Per intercettare il click singolo

// Variabili Ostacoli e Gioco
int cactusX = 128;
int foodX = 200;
bool foodAttivo = true;
int score = 0;
int highScore = 0;
bool gameOver = false;

void setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  randomSeed(analogRead(0));
}

void loop() {
  if (gameOver) {
    gestisciGameOver();
    return;
  }

  display.clearDisplay();

  // 1. GESTIONE INPUT (Filtro per click rapido)
  bool currentButtonState = digitalRead(PIN_BUTTON);
  
  // Il click viene processato solo se il tasto passa da non premuto a premuto
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    if (isGrounded) {
      velocitaVerticale = -JUMP_FORCE; // Spinta verso l'alto
      isGrounded = false;
       canDoubleJump = true;
    }
    else if (canDoubleJump) {
      // SECONDO SALTO: Aggiunge spinta alla velocità CORRENTE
      // Non resettiamo dinoY, cambiamo solo il vettore velocità
      velocitaVerticale = -JUMP_FORCE * 0.8; 
      canDoubleJump = false; // Disabilita ulteriori salti finché non tocca terra
    }
  }
  lastButtonState = currentButtonState;

  // 2. MOTORE FISICO (Indipendente, non resetta mai dinoY)
  if (!isGrounded) {
    dinoY += velocitaVerticale;    // Muove dalla posizione attuale
    velocitaVerticale += GRAVITY;  // Applica la gravità progressivamente

    // Controllo atterraggio (Senza reset immediato a ogni ciclo)
    if (dinoY >= GROUND_Y) {
      dinoY = GROUND_Y;
      velocitaVerticale = 0;
      isGrounded = true;
       canDoubleJump = false;
    }
  }

  // 3. MOVIMENTO ORIZZONTALE
  cactusX -= (6 + (score / 10));
  if (cactusX < -10) {
    cactusX = 128;
    score++;
  }

  foodX -= 5;
  if (foodX < -15) {
    int nuovaX = 128 + random(60, 180);
    if (abs(nuovaX - cactusX) < 40) nuovaX += 50; 
    foodX = nuovaX;
    foodAttivo = true;
  }

  // 4. DISEGNO E COLLISIONI
  disegnaScena();
  controllaCollisioni();

  display.display();
  delay(30); 
}

void disegnaScena() {
  display.drawFastHLine(0, TERRENO_Y, 128, WHITE);
  display.fillRect(DINO_X, (int)dinoY, 10, 10, WHITE); // Casting a int solo per il disegno
  display.fillRect(cactusX, 47, 6, 10, WHITE);
  if (foodAttivo) display.fillCircle(foodX, 32, 3, WHITE);
  
  display.setTextSize(1);
  display.setCursor(0, 0); display.print("HI:"); display.print(highScore);
  display.setCursor(85, 0); display.print("S:"); display.print(score);
}

void controllaCollisioni() {
  if (cactusX < (DINO_X + 8) && cactusX > (DINO_X - 5) && dinoY > 38) {
    gameOver = true;
  }
  if (foodAttivo && abs(foodX - DINO_X) < 10 && abs(32 - (int)dinoY) < 10) {
    score += 5;
    foodAttivo = false;
  }
}

void gestisciGameOver() {
  if (score > highScore) highScore = score;
  display.clearDisplay();
  display.setTextSize(2); display.setCursor(10, 5); display.print("GAME OVER");
  display.setTextSize(1);
  display.setCursor(25, 30); display.print("Score: "); display.print(score);
  display.setCursor(25, 42); display.print("Record: "); display.print(highScore);
  display.setCursor(15, 55); display.print("Premi per Reset");
  display.display();

  if (digitalRead(PIN_BUTTON) == LOW) {
    delay(300);
    cactusX = 128;
    foodX = 220;
    score = 0;
    dinoY = GROUND_Y;
    velocitaVerticale = 0;
    isGrounded = true;
    gameOver = false;
    lastButtonState = LOW; // Evita salto immediato al restart
  }
}