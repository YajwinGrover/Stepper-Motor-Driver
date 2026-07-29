
void setup() {
  Serial.begin(9600);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(51, OUTPUT);

  // put your setup code here, to run once:

}

#define DELAY_TIME 1
#define HALF_STEP
// #define WAVE_STEP
// #define FULL_STEP


void loop() {

#if defined(WAVE_STEP) || defined(HALF_STEP)
  // A Pos 
  all_off(); delayMicroseconds(10);
  digitalWrite(44, LOW);  digitalWrite(47, HIGH); 
  delay(DELAY_TIME);
#endif


#if defined(FULL_STEP) || defined(HALF_STEP)
  // A Pos + B Pos
  all_off(); delayMicroseconds(10);
  digitalWrite(44, LOW);  digitalWrite(47, HIGH); 
  digitalWrite(48, LOW);  digitalWrite(51, HIGH); 
  delay(DELAY_TIME);
#endif

#if defined(WAVE_STEP) || defined(HALF_STEP)
  // B Pos
  all_off(); delayMicroseconds(10);
  digitalWrite(48, LOW);  digitalWrite(51, HIGH); 
  delay(DELAY_TIME);
#endif

#if defined(FULL_STEP) || defined(HALF_STEP)
  // A Neg + B Pos
  all_off(); delayMicroseconds(10);
  digitalWrite(46, LOW);  digitalWrite(45, HIGH); 
  digitalWrite(48, LOW);  digitalWrite(51, HIGH); 
  delay(DELAY_TIME);
#endif

#if defined(WAVE_STEP) || defined(HALF_STEP)
  // A Neg
  all_off(); delayMicroseconds(10);
  digitalWrite(46, LOW);  digitalWrite(45, HIGH); 
  delay(DELAY_TIME);
#endif

#if defined(FULL_STEP) || defined(HALF_STEP)
  // A Neg + B Neg
  all_off(); delayMicroseconds(10);
  digitalWrite(46, LOW);  digitalWrite(45, HIGH); 
  digitalWrite(50, LOW);  digitalWrite(49, HIGH); 
  delay(DELAY_TIME);
#endif

#if defined(WAVE_STEP) || defined(HALF_STEP)
  // B Neg
  all_off(); delayMicroseconds(10);
  digitalWrite(50, LOW);  digitalWrite(49, HIGH); 
  delay(DELAY_TIME);
#endif

#if defined(FULL_STEP) || defined(HALF_STEP)
  // A Pos + B Neg
  all_off(); delayMicroseconds(10);
  digitalWrite(44, LOW);  digitalWrite(47, HIGH); 
  digitalWrite(50, LOW);  digitalWrite(49, HIGH); 
  delay(DELAY_TIME);
#endif

#ifndef MICRO_STEP


#endif

}

void all_off(){
  // Even pins (High-side) HIGH to turn OFF
  // Odd pins (Low-side) LOW to turn OFF
  digitalWrite(44, HIGH); digitalWrite(45, LOW);
  digitalWrite(46, HIGH); digitalWrite(47, LOW);
  digitalWrite(48, HIGH); digitalWrite(49, LOW);
  digitalWrite(50, HIGH); digitalWrite(51, LOW);
}

void a_positive(){
  Serial.println("A pos");
  all_off(); 
  delayMicroseconds(10);
  
  digitalWrite(44, LOW);  // Phase A Left High-Side: ON (Inverted)
  digitalWrite(47, HIGH); // Phase A Right Low-Side: ON (Normal)
}

void a_negative(){
  Serial.println("A neg");
  all_off(); 
  delayMicroseconds(10);
  
  digitalWrite(46, LOW);  // Phase A Right High-Side: ON (Inverted)
  digitalWrite(45, HIGH); // Phase A Left Low-Side: ON (Normal)
}

void b_positive(){
  Serial.println("B pos");
  all_off(); 
  delayMicroseconds(10);
  
  digitalWrite(48, LOW);  // Phase B Left High-Side: ON (Inverted)
  digitalWrite(51, HIGH); // Phase B Right Low-Side: ON (Normal)
}

void b_negative(){
  Serial.println("B neg");
  all_off(); 
  delayMicroseconds(10);
  
  digitalWrite(50, LOW);  // Phase B Right High-Side: ON (Inverted)
  digitalWrite(49, HIGH); // Phase B Left Low-Side: ON (Normal)
}