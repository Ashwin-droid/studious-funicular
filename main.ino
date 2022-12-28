int MOTOR_PIN = 2; // output        motor
int FS_SV0_T = 3; // input pullup   tank 1 overflow
int FS_SV0_B = 4; // input pullup   tank 1 underflow
int FS_SV1_T = 5; // input pullup   tank 2 overflow
int FS_SV1_B = 6; // input pullup   tank 2 underflow
int SV = 7; // output               solenoid valve
bool tankID = false; //             false = tank 1, true = tank 2
bool isFilling = false; //          false = not filling, true = filling

void setup () {
    pinMode(MOTOR_PIN, OUTPUT); // motor
    pinMode(FS_SV0_T, INPUT_PULLUP); // overflow of tank 1
    pinMode(FS_SV0_B, INPUT_PULLUP); // underflow of tank 1
    pinMode(FS_SV1_T, INPUT_PULLUP); // overflow of tank 2
    pinMode(FS_SV1_B, INPUT_PULLUP); // underflow of tank 2
    pinMode(SV, OUTPUT);   // solenoid valve
    // set solenoid valve to off
    digitalWrite(SV, HIGH);
    // set motor to off
    digitalWrite(MOTOR_PIN, HIGH);
}
void loop () {
    // //serial print for debugging
    // Serial.print("FS_SV0_T: ");
    // Serial.println(digitalRead(FS_SV0_T));
    // Serial.print("FS_SV0_B: ");
    // Serial.println(digitalRead(FS_SV0_B));
    // Serial.print("FS_SV1_T: ");
    // Serial.println(digitalRead(FS_SV1_T));
    // Serial.print("FS_SV1_B: ");
    // Serial.println(digitalRead(FS_SV1_B));
    // check if any underflow is triggered
    if ((digitalRead(FS_SV0_B) == HIGH || digitalRead(FS_SV1_B) == HIGH) && !isFilling) {
        // find which one is triggered
        if (digitalRead(FS_SV0_B) == HIGH) {
            // turn off solenoid valve
            digitalWrite(SV, HIGH);
            // turn on motor
            digitalWrite(MOTOR_PIN, LOW);
            // set the tank ID
            tankID = false;
            // set the filling status
            isFilling = true;
        } else {
            // turn on solenoid valve
            digitalWrite(SV, LOW);
            // turn on motor
            digitalWrite(MOTOR_PIN, LOW);
            // set the tank ID
            tankID = true;
            // set the filling status
            isFilling = true;
        }
    }
    // check if any overflow is triggered and any tank is filling
    if ((digitalRead(FS_SV0_T) == LOW || digitalRead(FS_SV1_T) == LOW) && isFilling) {
        // find which one is triggered
        if (digitalRead(FS_SV0_T) == LOW && tankID == false) {
            // turn off motor
            digitalWrite(MOTOR_PIN, HIGH);
            // set the filling status
            isFilling = false;
        } else {
            // turn off motor
            digitalWrite(MOTOR_PIN, HIGH);
            // set the filling status
            isFilling = false;
            // turn off solenoid valve
            digitalWrite(SV, HIGH);
        }
    }
    // delay of 10 seconds
    delay(10000);
}