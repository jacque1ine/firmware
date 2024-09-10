# 5-Bar Pick and Place Mechanism

## Project Objective

1. Your system must take an input that specifies a destination location (target 1, 2, or 3) for the 
payload. Using that input your mechanism will then move to the current location of the 
payload, pick it up and move it to the location specified by the input. 
2. You and your partner’s systems must track the current location of the payload and 
communicate it between the two systems so that both systems know where to go to pick up the 
payload.
3. You must designate a home location where your mechanism goes when it is not moving the 
payload

## Project Description
The goal of this project is to create two identical robotic mechanisms capable of:
- Receiving an input to designate a target location.
- Moving to the payload's current location to pick it up.
- Relocating the payload to the specified target while maintaining communication between the two systems.

Both mechanisms utilize Arduinos to communicate their respective locations, allowing them to coordinate actions during payload handling.


**Example**
Both robots start at Home. Robot A goes to target 1 and picks up the payload, drops of the payload at target 2, and tells Robot B the payload position is now at target 2. 
Robot B receives the information from Robot A and goes to target 2 to pick up the payload, and drops off the payload at target 3. 

Some challenges are: 
1) The communication piece
2) even though the targets are fixed, the relative positions are different. Ex. to move from target 1 to target 2, is different from moving from target 3 to target1.

   

## Hardware Components
- **5-Bar Mechanism**: Two identical 5-bar mechanisms built with aluminum t-slot extrusion.
- **Servos**: Hitec HS-645MG servos controlling all motion.
- **Botboarduino**: Acts as the primary controller, operating through Arduino IDE.
- **Cylindrical Payload**: A 2”x0.75” steel cylinder utilized for testing and demonstration.


## Capabilities
- **Autonomous Movement**: Each mechanism autonomously moves between preset target locations.
- **Payload Handling**: Can pick and place a designated payload based on user input.
- **Sensor Feedback**: Utilizes digital sensors to detect the payload’s current position.
- **Real-time Communication**: Communicates the payload’s location data between the two mechanisms via Arduino serial communication.

## Implementation Details
### Code Structure
- The code is structured around controlling servo motors and processing user input via serial communication.
- Functions include:
  - `setup()`: Initializes servo connections and serial communication.
  - `loop()`: Main routine for continuous operation, processing input and executing movement commands.
  - `moveToTargetSmooth()`: Smoothly maneuvers the mechanism to the specified coordinates.
  - `updateStatusPins()`: Outputs status information based on the last drop-off location.

### Usage
Connect the system components according to the provided schematics.
Upload the Arduino code to both Botboarduino controllers.
Open the Serial Monitor in the Arduino IDE and enter the desired target location (1, 2, or 3).
Observe each mechanism picking and placing the payload according to the coordinated input received.
<img width="789" alt="image" src="https://github.com/user-attachments/assets/948d6fa0-9005-4733-a1a2-7d89b64d0e13">

