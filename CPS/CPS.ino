int IR1=7;
int IR2=8;
int IR1_out = HIGH; /* Avoiding initial false detections.    */
int IR2_out = HIGH; /* Avoiding initial false detections.    */
int counter = 0;
int i = 0;
void increaseAndDisplay() {
  counter++;
  if(counter > 10) {
    counter = 1;
  }
  Serial.println(counter);
}
void decreaseAndDisplay() {
  if(counter) {
    counter--;
    Serial.println(counter);
  }
}
void setup() {
  Serial.begin (9600);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
 
}

void loop() {
  IR1_out = digitalRead(IR1);
  IR2_out = digitalRead(IR2);
  if(IR1_out == LOW) {
    increaseAndDisplay();
    delay(500);
  }
  if(IR2_out == LOW) {
    decreaseAndDisplay();
    delay(500);
  } 
  delay(100);

}
