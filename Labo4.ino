#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SH1106G display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

const int TOUCH_PIN_1 = 4;
const int TOUCH_PIN_2 = 27;

const int UMBRAL_TOUCH = 700;

void setup() {

  Serial.begin(115200);

  Wire.begin(21, 22);

  if (!display.begin(OLED_ADDRESS, true)) {
    Serial.println("Error al iniciar la pantalla OLED");
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
}

void loop() {

  int touch1 = touchRead(TOUCH_PIN_1);
  int touch2 = touchRead(TOUCH_PIN_2);

  Serial.print("Boton 1: ");
  Serial.print(touch1);

  Serial.print(" | Boton 2: ");
  Serial.println(touch2);

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(26, 5);
  display.println("ESP32 TOUCH");

  if (touch1 < UMBRAL_TOUCH) {

    display.setCursor(20, 28);
    display.println("Boton 1 activado");

  }
  else if (touch2 < UMBRAL_TOUCH) {

    display.setCursor(20, 28);
    display.println("Boton 2 activado");

  }
  else {

    display.setCursor(32, 28);
    display.println("Esperando...");
  }

  display.display();

  delay(100);
}