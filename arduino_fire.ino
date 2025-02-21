// Pin Definitions
#define THERMISTOR_PIN A1  // Thermistor input (voltage divider output)
#define FAN_PIN 6          // Fan control (via transistor)
#define BUZZER_PIN 7       // Active buzzer control
#define LED_PIN 8          // LED control

// Temperature Threshold (in °C) for triggering the devices
#define TEMP_THRESHOLD 50

// Thermistor and Voltage Divider Constants
#define SERIES_RESISTOR 10000.0       // 10kΩ resistor used in the voltage divider
#define NOMINAL_RESISTANCE 10000.0      // Thermistor resistance at 25°C (10kΩ)
#define NOMINAL_TEMPERATURE 25.0        // 25°C (reference temperature)
#define B_COEFFICIENT 3950.0            // Beta coefficient of the thermistor

void setup() {
  Serial.begin(9600);
  
  // Initialize output pins
  pinMode(FAN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Start with all devices OFF
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Read the raw ADC value from the thermistor voltage divider
  int rawValue = analogRead(THERMISTOR_PIN);
  
  // Avoid division by zero (in case rawValue is 0)
  if (rawValue == 0) {
    rawValue = 1;
  }
  
  // Calculate the resistance of the thermistor:
  // Using the formula: R_thermistor = SERIES_RESISTOR * ((1023 / rawValue) - 1)
  float resistance = SERIES_RESISTOR * ((1023.0 / rawValue) - 1);
  
  // Apply the Steinhart-Hart equation to compute temperature in Kelvin
  float steinhart = log(resistance / NOMINAL_RESISTANCE) / B_COEFFICIENT;
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15); // in Kelvin
  steinhart = 1.0 / steinhart;  // Temperature in Kelvin
  float temperatureC = steinhart - 273.15;  // Convert Kelvin to Celsius
  
  // Print the temperature for debugging
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  
  // Temperature-based logic: If temperature exceeds threshold, activate devices
  if (temperatureC > TEMP_THRESHOLD) {
    digitalWrite(FAN_PIN, HIGH);       // Turn on Fan
    digitalWrite(BUZZER_PIN, HIGH);      // Activate Buzzer
    digitalWrite(LED_PIN, HIGH);         // Light up LED
    Serial.println("Temperature above threshold: Devices ON");
  } else {
    digitalWrite(FAN_PIN, LOW);        // Turn off Fan
    digitalWrite(BUZZER_PIN, LOW);       // Deactivate Buzzer
    digitalWrite(LED_PIN, LOW);          // Turn off LED
    Serial.println("Temperature below threshold: Devices OFF");
  }
  
  delay(1000);  // Delay 1 second before next reading
}
