# 1 "c:\\Users\\ash6c\\Documents\\projects\\Anu-aji-tank_project\\main.ino"
int MOTOR_PIN = 2; // output        motor
int FS_SV0_T = 3; // input pullup   tank 1 overflow
int FS_SV0_B = 4; // input pullup   tank 1 underflow
int FS_SV1_T = 5; // input pullup   tank 2 overflow
int FS_SV1_B = 6; // input pullup   tank 2 underflow
int SV = 7; // output               solenoid valve
bool tankID = false; //             false = tank 1, true = tank 2
bool isFilling = false; //          false = not filling, true = filling

void setup () {
    pinMode(MOTOR_PIN, 0x1); // motor
    pinMode(FS_SV0_T, 0x2); // overflow of tank 1
    pinMode(FS_SV0_B, 0x2); // underflow of tank 1
    pinMode(FS_SV1_T, 0x2); // overflow of tank 2
    pinMode(FS_SV1_B, 0x2); // underflow of tank 2
    pinMode(SV, 0x1); // solenoid valve
    // set solenoid valve to off
    digitalWrite(SV, 0x1);
    // set motor to off
    digitalWrite(MOTOR_PIN, 0x1);
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
    if ((digitalRead(FS_SV0_B) == 0x1 || digitalRead(FS_SV1_B) == 0x1) && !isFilling) {
        // find which one is triggered
        if (digitalRead(FS_SV0_B) == 0x1) {
            // turn off solenoid valve
            digitalWrite(SV, 0x1);
            // turn on motor
            digitalWrite(MOTOR_PIN, 0x0);
            // set the tank ID
            tankID = false;
            // set the filling status
            isFilling = true;
        } else {
            // turn on solenoid valve
            digitalWrite(SV, 0x0);
            // turn on motor
            digitalWrite(MOTOR_PIN, 0x0);
            // set the tank ID
            tankID = true;
            // set the filling status
            isFilling = true;
        }
    }
    // check if any overflow is triggered and any tank is filling
    if ((digitalRead(FS_SV0_T) == 0x0 || digitalRead(FS_SV1_T) == 0x0) && isFilling) {
        // find which one is triggered
        if (digitalRead(FS_SV0_T) == 0x0 && tankID == false) {
            // turn off motor
            digitalWrite(MOTOR_PIN, 0x1);
            // set the filling status
            isFilling = false;
        } else if (digitalRead(FS_SV1_T) == 0x0 && tankID == true) {
            // turn off motor
            digitalWrite(MOTOR_PIN, 0x1);
            // set the filling status
            isFilling = false;
            // turn off solenoid valve
            digitalWrite(SV, 0x1);
        }
    }
    // delay of 10 seconds
    delay(10000);
}
