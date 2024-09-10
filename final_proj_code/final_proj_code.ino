#include <Servo.h>

// Pin Constants
const int AX1_PIN = 11; // Front servo
const int AX2_PIN = 10; // Back servo
const int GRIPPER_PIN = 12; // Gripper servo
const int STATUS_PIN_1 = 5; // Output binary state 1
const int STATUS_PIN_2 = 6; // Output binary state 2
const int SENSOR_PIN_1 = 7; // Sensor input 1
const int SENSOR_PIN_2 = 8; // Sensor input 2

// Gripper Positions
const int GRIPPER_OPEN = 0; // Gripper open position
const int GRIPPER_CLOSE = 45; // Gripper close position

// Home Positions
const float AX1_HOME = 20.0; // Axis 1 home position
const float AX2_HOME = 75.0; // Axis 2 home position
const float AX1_OFFSET = 20.0; // Axis 1 offset

// Pickup Location Enum
enum PickupLocation {
    LOCATION_1 = 1,
    LOCATION_2,
    LOCATION_3
};

Servo gripper; 
Servo ax1;
Servo ax2;
float ax1_current = AX1_HOME; // Current position of axis 1
float ax2_current = AX2_HOME; // Current position of axis 2

void setup() {
    ax1.attach(AX1_PIN); // Attach servo for axis 1
    ax2.attach(AX2_PIN); // Attach servo for axis 2
    gripper.attach(GRIPPER_PIN); // Attach gripper servo
    gripper.write(GRIPPER_OPEN); // Initialize gripper in open position

    // Initialize Serial Communication
    Serial.begin(9600);
    pinMode(STATUS_PIN_1, OUTPUT);
    pinMode(STATUS_PIN_2, OUTPUT);
    pinMode(SENSOR_PIN_1, INPUT);
    pinMode(SENSOR_PIN_2, INPUT);

    // Set axes to home position
    goHome();
}

void loop() {
    // Wait for Serial input
    waitForSerialInput();
    
    // Parse dropoff location from Serial input
    int dropoff_location = Serial.parseInt();
    
    // Determine pickup location based on sensors
    int pickup_location = determinePickupLocation();
    
    // Smoothly move to pickup location and then drop-off location
    moveToTargetSmooth(pickup_location, true);
    moveToTargetSmooth(dropoff_location, false);
    
    // Update status output pins based on dropoff location
    updateStatusPins(dropoff_location);
}

void waitForSerialInput() {
    // Block until serial input is available
    while (Serial.available() == 0) {}
}

int determinePickupLocation() {
    int var1 = digitalRead(SENSOR_PIN_1); // Read state of sensor pin 1
    int var2 = digitalRead(SENSOR_PIN_2); // Read state of sensor pin 2
    
    // Determine pickup location based on sensor states
    if (var1 == LOW && var2 == LOW) return LOCATION_1;
    if (var1 == HIGH && var2 == HIGH) return LOCATION_2;
    return (var1 == LOW) ? LOCATION_3 : LOCATION_1; // Return default
}

void moveTopos(float ax1s, float ax1e, float ax2s, float ax2e) {
    /*
    This function takes the starting and ending angles for both axes and
    divides them into an even number of steps. This ensures that the movement
    from both motors occurs simultaneously. It also reduces the speed of
    movement to help protect the mechanism. This is a workable but sub-optimal
    way of moving the mechanism.
    
    ax1s -> Axis 1 Start Position
    ax1e -> Axis 1 End Position
    ax2s -> Axis 2 Start Position
    ax2e -> Axis 2 End Position
    */

    float num_steps = max(abs(ax1e - ax1s), abs(ax2e - ax2s)); // Determine number of steps based on the largest movement
    float inc1 = (ax1e - ax1s) / num_steps; // Increment for axis 1
    float inc2 = (ax2e - ax2s) / num_steps; // Increment for axis 2

    // Perform the movement in steps
    for (int stp = 0; stp <= num_steps; ++stp) {
        ax1_current += inc1;
        ax2_current += inc2;
        ax1.write(ax1_current);
        ax2.write(ax2_current);
        delay(25); // Delay to slow movement
    }
}

void moveToTargetSmooth(int target_num, bool pick_up) {
    /*
    This function determines the target positions for the axes based on
    the specified target number and performs a smooth movement to those
    positions. The gripper's state is also controlled based on whether
    it is picking up or dropping off.
    */

    float ax1_target;
    float ax2_target;

    switch (target_num) {
        case LOCATION_1:
            ax1_target = 100 + AX1_OFFSET; 
            ax2_target = 125; 
            break;
        case LOCATION_2:
            ax1_target = 63 + AX1_OFFSET;  
            ax2_target = 90; 
            break;
        case LOCATION_3:
            ax1_target = 35 + AX1_OFFSET; 
            ax2_target = 60; 
            break;
        default:
            return; // Handle unexpected target
    }
    
    moveTopos(ax1_current, ax1_target, ax2_current, ax2_target); // Move to target positions
    gripper.write(pick_up ? GRIPPER_CLOSE : GRIPPER_OPEN); // Control gripper based on action
    delay(250); // Wait for arm to stabilize
    goHome(); // Move back to home position
}

void goHome() {
    // Move to home positions for both axes
    ax1.write(AX1_HOME);
    ax2.write(AX2_HOME);
}

void updateStatusPins(int dropoff_location) {
    /*
    This function updates output pins based on the drop-off 
    location to reflect the corresponding state.
    */

    switch (dropoff_location) {
        case LOCATION_1:
            digitalWrite(STATUS_PIN_1, LOW);
            digitalWrite(STATUS_PIN_2, LOW);
            break;
        case LOCATION_2:
            digitalWrite(STATUS_PIN_1, HIGH);
            digitalWrite(STATUS_PIN_2, HIGH);
            break;
        case LOCATION_3:
            digitalWrite(STATUS_PIN_1, LOW);
            digitalWrite(STATUS_PIN_2, HIGH);
            break;
    }
}