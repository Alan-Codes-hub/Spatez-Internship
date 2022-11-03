const int trigPin = 2;

const int echoPin = 4;


void setup() {

Serial.begin(9600);}

void loop()

{

float duration, inches, cm;

pinMode(trigPin, OUTPUT);



digitalWrite(trigPin, HIGH);

delay(100);

digitalWrite(trigPin, LOW);

pinMode(echoPin, INPUT);

duration = pulseIn(echoPin, HIGH);

inches = microsecondsToInches(duration);

cm = microsecondsToCentimeters(duration);

Serial.print(inches);

Serial.print("in, ");

Serial.print(cm);

Serial.print("cm");

Serial.println();

delay(100);

}

float microsecondsToInches(float microseconds)

{return microseconds / 74 / 2;

}

float microsecondsToCentimeters(float microseconds)

{return microseconds / 29 / 2;}
