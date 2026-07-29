
void setup() {
  Serial.begin(9600);
  //Phase A Left Side
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  //Phase A Right Side
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  //Phase B Left Side
  pinMode(48, OUTPUT);
  pinMode(49, OUTPUT);
  //Phase B Right Side
  pinMode(50, OUTPUT);
  pinMode(51, OUTPUT);

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


}

void all_off(){
  // Even pins (High-side) HIGH to turn OFF
  // Odd pins (Low-side) LOW to turn OFF
  digitalWrite(44, HIGH); digitalWrite(45, LOW);
  digitalWrite(46, HIGH); digitalWrite(47, LOW);
  digitalWrite(48, HIGH); digitalWrite(49, LOW);
  digitalWrite(50, HIGH); digitalWrite(51, LOW);
}
