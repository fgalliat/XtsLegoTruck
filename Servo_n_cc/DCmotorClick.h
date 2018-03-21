#ifndef __DCMOTORCLICK_H_____
#define __DCMOTORCLICK_H_____ 1

/**********************************
 *  DC motor Click board from     *
 *  MikroElectronika // 5v Driven *
 * Xtase - fgalliat        @2015  *
 **********************************/

  #define DBUG Serial.println

  int __PWM_MOTOR_PIN = -1;
  int __SL1_MOTOR_PIN = -1;
  int __SL2_MOTOR_PIN = -1;
  
  #define _minMotorPwr 65
  #define _maxMotorPwr 255
  bool _reversed = false;

  void DCMOTORCLICK_Init(int pwmPin, int sel1Pin, int sel2Pin) {
    __PWM_MOTOR_PIN = pwmPin;
    __SL1_MOTOR_PIN = sel1Pin;
    __SL2_MOTOR_PIN = sel2Pin;
    
    pinMode(__PWM_MOTOR_PIN, OUTPUT); // DC click PWM
    pinMode(__SL1_MOTOR_PIN, OUTPUT); // DC click SEL1
    pinMode(__SL2_MOTOR_PIN, OUTPUT); // DC click SEL2

    digitalWrite(__PWM_MOTOR_PIN, LOW);
    digitalWrite(__SL1_MOTOR_PIN, LOW);
    digitalWrite(__SL2_MOTOR_PIN, LOW);
  }

  void __DCMOTORCLICK_turn(unsigned char power, bool reverse);

  /** power goes from 0 to 100 */
  void DCMOTORCLICK_turnForward(unsigned char power) {
    __DCMOTORCLICK_turn(power, false);
  }

  /** power goes from 0 to 100 */  
  void DCMOTORCLICK_turnBackward(unsigned char power) {
    __DCMOTORCLICK_turn(power, true);
  }

  void DCMOTORCLICK_stop() {
    __DCMOTORCLICK_turn(0, _reversed);
  }
  
  void DCMOTORCLICK_brake() {
    // TODO
  }


  /** power goes from 0 to 100 */
  void __DCMOTORCLICK_turn(unsigned char power, bool reverse) {
    if ( __PWM_MOTOR_PIN < 0 ) { DBUG("DC Motor Click : Not initialised"); return; }
    if ( __PWM_MOTOR_PIN < 3 ) { DBUG("DC Motor Click : WRONG initialised"); return; }

    _reversed = reverse;
    digitalWrite(__SL2_MOTOR_PIN, _reversed ? HIGH : LOW );

    unsigned char speed = 0;
    if ( power > 100 ) { power = 100; }
    if ( power > 0 ) {
      speed = _minMotorPwr + ( power * (_maxMotorPwr - _minMotorPwr) / 100 );
    }
    
    analogWrite( __PWM_MOTOR_PIN,  speed );
  }



#endif
