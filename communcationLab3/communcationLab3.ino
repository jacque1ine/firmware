int pintwo = 2;
int pinthree = 3;
int pinfive = 5;
int pinsix = 6;
int pinseven = 7;
int pineight = 8; // Set up pins 2, 3, 4, 5, 6, 7, 8
int var1, var2, var3, var4; // Set up variables
int blink_rate;

void setup() { // Make 2, 3, 7, 8 input pullup pins and 5, 6 output pins
  Serial.begin(9600);
  pinMode(pintwo, INPUT_PULLUP);
  pinMode(pinthree, INPUT_PULLUP);
  pinMode(pinfive, OUTPUT);
  pinMode(pinsix, OUTPUT);
  pinMode(pinseven, INPUT_PULLUP);
  pinMode(pineight, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  var1 = digitalRead(pintwo);
  var2 = digitalRead(pinthree); // Take input from pins 2 and 3, put into var1,var2 (these inputs will either be HIGH or LOW, depending on whether your wires are attached to GND or not on the breadboard - GND is LOW and anywhere else is HIGH)

  digitalWrite(pinfive, var1);
  digitalWrite(pinsix, var2); // Output var1,var2 through to pins 5 and 6

  var3 = digitalRead(pinseven);
  var4 = digitalRead(pineight); // Input from pins 7 and 8, because they're attached to 5 and 6 on the other board

   // Set the blink rate depending on how many wires are attached to GND
   // Both GND: very slow, only one GND: medium slow, neither GND: fast
  if (var3 == LOW && var4 == LOW) { 
    blink_rate = 1000;
  } 
  else if (var3 == HIGH && var4 == HIGH) {
    blink_rate = 100
  } 
  else {
    blink_rate = 500;
  }

  // Turn on LED for the blink rate time, then turn it off for the blink rate time (it will repeat on its own)
  digitalWrite(LED_BUILTIN, HIGH);
  delay(blink_rate);
  digitalWrite(LED_BUILTIN, LOW);
  delay(blink_rate);

  /*for testing variables and rate
  Serial.print("Var1: ");
  Serial.println(var1);
  Serial.print("Var2: ");
  Serial.println(var2);
  Serial.print("Var3: ");
  Serial.println(var3);
  Serial.print("Var4: ");
  Serial.println(var4);
  Serial.print("Rate: ");
  Serial.println(blink_rate);*/
}