#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// Pins
#define ONE_WIRE_BUS 4
#define RELAY_PIN 5
#define BUZZER_PIN 12


// RGB LED pins 
#define RGB_RED_PIN   18
#define RGB_GREEN_PIN 19
#define RGB_BLUE_PIN  23

// Temperature thresholds
#define TEMP_LOW     50.0
#define TEMP_HIGH    55.0
#define TEMP_OVERHEAT 60.0

enum SystemState {
  IDLE,
  HEATING,
  STABILIZING,
  TARGET_REACHED,
  OVERHEAT
};

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
SystemState currentState = IDLE;
bool heaterOn = false;

void setup() {
  Serial.begin(115200);
  sensors.begin();

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RGB_RED_PIN, OUTPUT);
  pinMode(RGB_GREEN_PIN, OUTPUT);
  pinMode(RGB_BLUE_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); // Ensure it's off initially


  digitalWrite(RELAY_PIN, LOW);
  setRGBColor(255, 255, 255);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

}

void loop() {
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temp);
  display.println(" C");

  display.print("State: ");
  display.println(stateToString(currentState));
  display.display();


  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");

  if (temp >= TEMP_OVERHEAT) {
    currentState = OVERHEAT;
    heaterOn = false;
  } else if (temp >= TEMP_HIGH) {
    currentState = TARGET_REACHED;
    heaterOn = false;
  } else if (temp >= TEMP_LOW) {
    currentState = STABILIZING;
    heaterOn = true;
  } else {
    currentState = HEATING;
    heaterOn = true;
  }

  digitalWrite(RELAY_PIN, heaterOn ? HIGH : LOW);

switch (currentState) {
  case IDLE:
    setRGBColor(255, 255, 255); // White
    digitalWrite(BUZZER_PIN, LOW);
    break;
  case HEATING:
    setRGBColor(255, 0, 0); // Red
    digitalWrite(BUZZER_PIN, LOW);
    break;
  case STABILIZING:
    setRGBColor(255, 255, 0); // Yellow
    digitalWrite(BUZZER_PIN, LOW);
    break;
  case TARGET_REACHED:
    setRGBColor(0, 255, 0); // Green
    digitalWrite(BUZZER_PIN, LOW);
    break;
  case OVERHEAT:
    setRGBColor(0, 0, 255); // Blue
    digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
    break;
}

  Serial.print("State: ");
  Serial.println(stateToString(currentState));

  delay(1000);
}

void setRGBColor(int red, int green, int blue) {
  analogWrite(RGB_RED_PIN, red);
  analogWrite(RGB_GREEN_PIN, green);
  analogWrite(RGB_BLUE_PIN, blue);
}

String stateToString(SystemState state) {
  switch (state) {
    case IDLE: return "IDLE";
    case HEATING: return "HEATING";
    case STABILIZING: return "STABILIZING";
    case TARGET_REACHED: return "TARGET_REACHED";
    case OVERHEAT: return "OVERHEAT";
    default: return "UNKNOWN";
  }
}
