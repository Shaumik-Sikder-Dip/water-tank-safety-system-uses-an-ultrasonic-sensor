#define TRIG_PIN 9
#define ECHO_PIN 10
#define RELAY_PIN 8
#define BUZZER_PIN 7

// Define tank dimensions (in centimeters)
const int emptyLevel = 100; // Distance when tank is empty
const int fullLevel = 15;   // Distance when tank is full

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Start with the pump OFF (Assuming an active-low relay)
  digitalWrite(RELAY_PIN, HIGH); 
  Serial.begin(9600);
}

void loop() {
  long duration, distance;
  
  // Trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW); 
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pulse
  duration = pulseIn(ECHO_PIN, HIGH);
  
  // Convert time to distance in cm
  distance = (duration / 2) / 29.1; 

  Serial.print("Distance to water (cm): ");
  Serial.println(distance);

  // Safety Logic
  if (distance >= emptyLevel) {
    // Tank is empty: Turn pump ON
    digitalWrite(RELAY_PIN, LOW); 
    Serial.println("Status: Pump ON");
  } 
  else if (distance <= fullLevel) {
    // Tank is full: Turn pump OFF to prevent overflow
    digitalWrite(RELAY_PIN, HIGH); 
    Serial.println("Status: Pump OFF (Tank Full)");
    
    // Briefly sound the buzzer
    digitalWrite(BUZZER_PIN, HIGH); 
    delay(1000); 
    digitalWrite(BUZZER_PIN, LOW);
  }
  
  delay(1000); // Wait 1 second before the next reading
}