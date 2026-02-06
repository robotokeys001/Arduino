#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin Pulsanti
const int pinSu = 2;   // Joystick verso l'alto
const int pinGiu = 4;  // Joystick verso il basso
// Variabili Gioco
int paddleY = 22;
int paddleX = 10;
int paddleH = 20;
int ballX = 64, ballY = 32;
int ballDX = 2, ballDY = 2;
int score = 0;

void setup() {
  pinMode(pinSu, INPUT_PULLUP);
  pinMode(pinGiu, INPUT_PULLUP);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    for(;;); 
  }
  display.clearDisplay();
}

void loop() {
 // Se lo stick chiude il contatto verso massa (GND)
  if (digitalRead(pinSu) == LOW && paddleY > 0) {
    paddleY -= 4; // Più veloce!
  }
  if (digitalRead(pinGiu) == LOW && paddleY < SCREEN_HEIGHT - paddleH) {
    paddleY += 4;
  }

  // 2. Movimento Palla
  ballX += ballDX;
  ballY += ballDY;

  // Rimbalzo Pareti (Sopra/Sotto/Destra)
  if (ballY <= 0 || ballY >= SCREEN_HEIGHT - 2) ballDY *= -1;
  if (ballX >= SCREEN_WIDTH - 2) ballDX *= -1;

  // Controllo Collisione Racchetta
  if (ballX <= paddleX + 2 && ballY >= paddleY && ballY <= paddleY + paddleH) {
    ballDX *= -1;
    score++;
  }

  // Game Over (Palla esce a sinistra)
  if (ballX < 0) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(20, 20);
    display.print("GAME OVER");
    display.display();
    delay(2000);
    ballX = 64; ballY = 32; score = 0; // Reset
  }

  // 3. Disegno
  display.clearDisplay();
  display.fillRect(paddleX, paddleY, 3, paddleH, WHITE); // Racchetta
  display.fillCircle(ballX, ballY, 2, WHITE);           // Palla
  display.setCursor(100, 0);
  display.print(score);                                 // Punteggio
  display.display();
}