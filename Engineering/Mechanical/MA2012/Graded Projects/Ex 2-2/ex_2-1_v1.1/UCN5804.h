/*
  UCN5804.h - Library for Stepper Driver
  Pins (numbered anti-clockwise from upper left):
  1: OUTPUT_B
  2: K_BD
  3: OUTPUT_D
  4: GND
  5: GND
  6: OUTPUT_C
  7: K_AC
  8: OUTPUT_A
  9: ONE-PHASE
  10: HALF-STEP
  11: STEP INPUT
  12: GND
  13: GND
  14: DIRECTIOn
  15: OUTPUT ENABLE
  16: SUPPLY
  Created by Lim Zhen Yi
*/

#ifndef UCN5804_h
#define UCN5804_h

#define tA          1           //micro, min data set up time
#define tB          1           //micro, min data hold time
#define tC          3           //micro, min step input pulse width

class UCN5804
{
  private:
    int _mode;
    int _direction;
    int _stepDelay;
    int _numberOfSteps;
  protected:
    int _dirPin;
    int _stepPin;
    int _halfPin;
    int _phasePin;
  public:
    UCN5804(int, int, int, int, int);
    void setMode(int);
    void setSpeed(long);
    void step(int);
};

#endif
