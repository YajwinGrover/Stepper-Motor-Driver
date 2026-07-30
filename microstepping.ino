
// The number of "mini" steps in a step is MICRO_STEPS / 4 since I defined micro step as the number of steps to
// complete one period of a wave, not a step. For example MICRO_STEPS = 16 is 4 microsteps per step or 4x resolution
// MICRO_STEPS 8 is equivalent to half stepping and 4 is wave stepping
#define MICRO_STEPS 16

//Voltage the motor is receiving
#define INPUT_VOLTAGE 10.0

//Resistance of each coil
#define COIL_A_R 5.0
#define COIL_B_R 5.0
//Max current the motor can handle
#define MAX_CURRENT 1

int phaseALookup[MICRO_STEPS];
int phaseBLookup[MICRO_STEPS];

int currentStep = 0;


void setup() {
  Serial.begin(9600);
  //Phase A Side One
  pinMode(44, OUTPUT); digitalWrite(44, HIGH);
  pinMode(45, OUTPUT); digitalWrite(45, LOW);
  //Phase A Side Two
  pinMode(46, OUTPUT); digitalWrite(46, HIGH);
  pinMode(47, OUTPUT); digitalWrite(47, LOW);
  //Phase B Side One
  pinMode(48, OUTPUT); digitalWrite(48, HIGH);
  pinMode(49, OUTPUT); digitalWrite(49, LOW);
  //Phase B Side Two
  pinMode(50, OUTPUT); digitalWrite(50, HIGH);
  pinMode(51, OUTPUT); digitalWrite(51, LOW);

  //Master chopper transistors
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  //Calculate the max PWM that can be applied to each coil to keep it under its max current limit
  double coilAVoltageMax = COIL_A_R * MAX_CURRENT; 
  int calculatedAPWM = (int) (255.0 * (coilAVoltageMax/INPUT_VOLTAGE));
  int coilAPWMMax = min(255, calculatedAPWM);

  //Scale the max PWM with a sine wave
  double radScaling = (2* PI) / MICRO_STEPS;
  for(int i = 0; i < MICRO_STEPS; i++){
    phaseALookup[i] = sin(radScaling * i) * coilAPWMMax;
  }

  //Repeat for coil B
  double coilBVoltageMax = COIL_B_R * MAX_CURRENT; 
  int calculatedBPWM = (int) (255.0 * (coilBVoltageMax/INPUT_VOLTAGE));
  int coilBPWMMax = min(255, calculatedBPWM);

  for(int i = 0; i < MICRO_STEPS; i++){
    phaseBLookup[i] = cos(radScaling * i) * coilBPWMMax;
  }

  //Debugging print statements
  Serial.println("Phase A");
  for(int i = 0; i < MICRO_STEPS; i++){
    Serial.print(phaseALookup[i]);
    Serial.print(" ");
  }
  Serial.println("");

  Serial.println("Phase B");
  for(int i = 0; i < MICRO_STEPS; i++){
    Serial.print(phaseBLookup[i]);
    Serial.print(" ");
  }
  Serial.println("");
  
  //Change PWM on timer 3 (only arduino mega, not uno) to be faster by setting the x8 prescaler 
  TCCR3B = (TCCR3B & 0b11111000) | 0x02;
}

void loop() {
  // Serial.print("Step: "); Serial.print(currentStep);
  // Serial.print(" | PWM A (Pin 2): "); Serial.print(abs(phaseALookup[currentStep]));
  // Serial.print(" | PWM B (Pin 3): "); Serial.println(abs(phaseBLookup[currentStep]));
  step();
  //Rudimentary speed control
  delayMicroseconds(300);
}

void setDirection(){
  if(phaseALookup[currentStep] > 0){
    //Phase A Side 1:
    digitalWrite(44, LOW); digitalWrite(45, LOW);
    //Phase A Side 2:
    digitalWrite(46, HIGH); digitalWrite(47, HIGH);
  } else if(phaseALookup[currentStep] < 0){
    //Phase A Side 1:
    digitalWrite(44, HIGH); digitalWrite(45, HIGH);
    //Phase A Side 2:
    digitalWrite(46, LOW); digitalWrite(47, LOW);

  } else{
    //Turn everything off
    digitalWrite(44, HIGH); digitalWrite(45, LOW);
    digitalWrite(46, HIGH); digitalWrite(47, LOW);
  }

  if(phaseBLookup[currentStep] > 0){
    //Phase B Side 1:
    digitalWrite(48, LOW); digitalWrite(49, LOW);
    //Phase B Side 2:
    digitalWrite(50, HIGH); digitalWrite(51, HIGH);
  } else if(phaseBLookup[currentStep] < 0){
    //Phase B Side 1:
    digitalWrite(48, HIGH); digitalWrite(49, HIGH);
    //Phase B Side 2:
    digitalWrite(50, LOW); digitalWrite(51, LOW);

  } else{
    //Turn everything off
    digitalWrite(48, HIGH); digitalWrite(49, LOW);
    digitalWrite(50, HIGH); digitalWrite(51, LOW);
  }

}

void setMasterChopper(){
  analogWrite(2, abs(phaseALookup[currentStep]));
  analogWrite(3, abs(phaseBLookup[currentStep]));
}

void step(){
  //Turn of PWM to reduce risk of shoot through
  analogWrite(2, 0);
  analogWrite(3, 0);
  //Allow the transistors to actually settle
  delayMicroseconds(10); 

  setDirection();
  setMasterChopper();

  currentStep = (currentStep + 1) % MICRO_STEPS;
}


