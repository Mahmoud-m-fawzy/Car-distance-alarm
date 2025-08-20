//#include <LiquidCrystal.h>

const int trigPin = 6;
const int echoPin = 7;
const int buzzerPin = 3;
const int led1 = A2;
const int led2 = 2;
const int led3 = 4;
const int led4 = 5;
const int alarm1 = 5;
const int alarm2 = 15;
const int alarm3 = 25;
const int alarm4 = 35;

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(buzzerPin, OUTPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    Serial.begin(9600);
    delay(1000);
}

void loop() {
    int distance = calcDist();
    
    // Check alarm levels and activate LEDs and buzzer accordingly
    if (distance <= alarm1) {
        activateAlarm(20);
        activateLeds(HIGH, HIGH, HIGH, HIGH);
    } else if (distance > alarm1 && distance <= alarm2) {
        activateAlarm(15);
        activateLeds(HIGH, HIGH, HIGH, LOW);
    } else if (distance > alarm2 && distance <= alarm3) {
        activateAlarm(10);
        activateLeds(HIGH, HIGH, LOW, LOW);
    } else if (distance > alarm3 && distance <= alarm4) {
        activateAlarm(15);
        activateLeds(HIGH, LOW, LOW, LOW);
    } else {
        deactivateAlarm();
        deactivateLeds();
    }

    Serial.print("Distance = ");
    Serial.println(distance);
    delay(1000);
}

int calcDist() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    int distance = (0.034 * duration) / 2;
    return distance;
}

void activateAlarm(int soundLevel) {
    tone(buzzerPin, soundLevel);
}

void deactivateAlarm() {
    noTone(buzzerPin);
}

void activateLeds(int led1State, int led2State, int led3State, int led4State) {
    digitalWrite(led1, led1State);
    digitalWrite(led2, led2State);
    digitalWrite(led3, led3State);
    digitalWrite(led4, led4State);
}

void deactivateLeds() {
    activateLeds(LOW, LOW, LOW, LOW);
}
