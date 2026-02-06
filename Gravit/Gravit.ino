#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int PIN_BUTTON = 2;
const int GROUND_Y = 46;       
const float GRAVITY = 1.2;     
const float JUMP_IMPULSE = 10; 

float dinoY = GROUND_Y;
float velocityY = 0;
bool isGrounded = true;


bool lastButtonState = HIGH;

void setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  display.clearDisplay();

  bool currentButtonState = digitalRead(PIN_BUTTON);
  
  // Rilevamento click (Fronte di discesa)
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    
    if (isGrounded) {
      // PRIMO SALTO: Partenza da terra
      velocityY = -JUMP_IMPULSE;
      isGrounded = false;
      canDoubleJump = true; // Abilita la possibilità di un secondo click
    } 
    else if (canDoubleJump) {
      // SECONDO SALTO: Aggiunge spinta alla velocità CORRENTE
      // Non resettiamo dinoY, cambiamo solo il vettore velocità
      velocityY = -JUMP_IMPULSE * 0.8; 
      canDoubleJump = false; // Disabilita ulteriori salti finché non tocca terra
    }
  }
  lastButtonState = currentButtonState;

  // MOTORE FISICO (Sempre attivo se non è a terra)
  if (!isGrounded) {
    dinoY += velocityY;    // Somma la velocità alla posizione ATTUALE
    velocityY += GRAVITY;  // La gravità frena la salita e accelera la discesa

    // Controllo Atterraggio
    if (dinoY >= GROUND_Y) {
      dinoY = GROUND_Y;
      velocityY = 0;
      isGrounded = true;
      canDoubleJump = false;
    }
  }

  // DISEGNO
  display.fillRect(20, (int)dinoY, 10, 10, WHITE); 
  display.drawFastHLine(0, 57, 128, WHITE);        
  
  display.display();
  delay(20); 
}