char incomingdata;  
void setup() {  
    pinMode(13, OUTPUT);  
    Serial.begin(9600);  
}  
void loop() {  
    incomingdata = Serial.read(); {  
        if (incomingdata == 'a') {  
            digitalWrite(13, HIGH);  
        } else if (incomingdata == 'b') {  
            digitalWrite(13, LOW);  
        }  
    }  
}  
