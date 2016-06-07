#include "motor.h"
#include "astro.h"

byte tracking = TRACKING_OFF;

void Motor::setup(boolean a4988) {
  if (a4988) {
    this->stepperHa = new (Stepper::DRIVER, 10/*step*/, 11/*dir*/); 
    this->stepperHa->setMaxSpeed(1800.0);
    this->stepperHa->setAcceleration(6000.0);
     
    this->stepperDec = new Stepper(Stepper::DRIVER, 12/*step*/, 13/*dir*/); 
    this->stepperDec->setMaxSpeed(1800.0);
    this->stepperDec->setAcceleration(6000.0);
    
  } else {
    /*
    this->stepperHa = new Stepper(AccelStepper::HALF4WIRE, 10, 12, 11, 13);
    this->stepperHa->setMaxSpeed(1500.0);
    this->stepperHa->setAcceleration(2000.0);
    
    this->stepperDec = new Stepper(AccelStepper::HALF4WIRE, 14, 16, 15, 17);
    this->stepperDec->setMaxSpeed(1500.0);
    this->stepperDec->setAcceleration(2000.0);
    */
  }

  this->topHaSpeed = this->stepperHa->maxSpeed();
  this->topDecSpeed = this->stepperDec->maxSpeed();
  
  noInterrupts();
  TCCR1A = 0;// set entire TCCR2A register to 0
  TCCR1B = 0;// same for TCCR2B
  TCNT1  = 0;//initialize counter value to 0
  
  // set compare match register for 8khz increments
  OCR1A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
  //32Khz
  //OCR1A = 62;// = (16*10^6) / (8000*8) - 1 (must be <256)
  
  // turn on CTC mode
  TCCR1A |= (1 << WGM11);
  // Set CS21 bit for 8 prescaler
  TCCR1B |= (1 << CS11);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void Motor::loop() {
  AstronomicalObjectSelected objectSelected = astronomy.getSelected();
  
  if (tracking == TRACKING_FOLLOW && objectSelected.object.name[0]) {
    
    this->moveToHourAngle(astronomy.raToHa(objectSelected.object.ra));
    
    this->moveToDeclination(objectSelected.object.dec);
  }

  
}

void Motor::run() {
  this->stepperHa->run();
  this->stepperDec->run();
}

extern Motor motor;
ISR(TIMER1_COMPA_vect) {
  motor.run();
}

float Motor::getHourAngle() {
  return this->stepperHa->currentPosition() * STEPPER_RA_TO_ARCMILLIS;
}

float Motor::getDeclination() {
  return this->stepperDec->currentPosition() * STEPPER_DEC_TO_ARCMILLIS;
}


void Motor::setHaMaxSpeedPercent(float percent) {
  if (percent < 0) percent = 0;
  if (percent > 1) percent = 1;
  this->stepperHa->setMaxSpeed(this->topHaSpeed * percent);  
}

void Motor::setDecMaxSpeedPercent(float percent) {
  if (percent < 0) percent = 0;
  if (percent > 1) percent = 1;
  this->stepperDec->setMaxSpeed(this->topDecSpeed * percent);
}

void Motor::moveToHourAngle(float ha) {
  this->stepperHa->moveTo(ha / STEPPER_RA_TO_ARCMILLIS);
}

void Motor::moveToDeclination(float dec) {
  this->stepperDec->moveTo(dec / STEPPER_DEC_TO_ARCMILLIS);
}

float Motor::getMaxHaPerSecond() {
  return this->stepperHa->maxSpeed() * STEPPER_RA_TO_ARCMILLIS;
}

float Motor::getMaxDecPerSecond() {
  return this->stepperDec->maxSpeed() * STEPPER_DEC_TO_ARCMILLIS;
}

bool Motor::isHaRunning() {
  return this->stepperHa->isRunning();
}

bool Motor::isDecRunning() {
  return this->stepperDec->isRunning();
}

void Motor::clearRa(float ra) {
  this->stepperHa->setCurrentPosition(0);
}

void Motor::clearDec(float dec) {
  this->stepperDec->setCurrentPosition(0);
}

