/*
   Thermal Logo Code for Board REV_2
   MJM - 2021

   Board = Adafruit Itsy Bitsy 3v 8Mhz

   NOTE:
     Logic may need work, idk about the thermal control.
*/

#define HOT    1
#define COLD   0
#define ACTIVE 0

/* 10 cells per pix */
const int cell     = 10; //cell width

/* 10ms per E */
const int ms_delay = 10; //strobe time

//const int decay    = cell;      //??
//const int decay    = cell * 2;  //??
const int decay    = cell / 2;    //??

int LED_STATE[3]   = {COLD, COLD, COLD};
int KOOL[3]        = { HOT,  HOT,  HOT};
int STATE_THERM[3] = {   0,    0,    0};

int TRIGGER = 10;
/* !!DOUBLE CHECK ORDER!! */
int EN_1    = 6;
int EN_2    = 8;
int EN_3    = 9;

int _state  = 0;
int cnt     = 0;

void state_seq(void);
void button_check(void);

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIGGER,      INPUT);
  pinMode(EN_1,         OUTPUT);
  pinMode(EN_2,         OUTPUT);
  pinMode(EN_3,         OUTPUT);

  digitalWrite(EN_1,    COLD); //off
  digitalWrite(EN_2,    COLD); //off
  digitalWrite(EN_3,    COLD); //off
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  button_check();
  /****************************************************/
  state_seq();
  /****************************************************/
  if (_state == 0) {
    digitalWrite(EN_2, COLD);
    digitalWrite(EN_1, COLD);
    digitalWrite(EN_3, LED_STATE[2] & KOOL[2]);   // HOT & HOT = HOT | HOT & COLD = COLD
  }
  if (_state == 1) {
    digitalWrite(EN_3, COLD);
    digitalWrite(EN_1, COLD);
    digitalWrite(EN_2, LED_STATE[1] & KOOL[1]);
    if (STATE_THERM[1] > decay) KOOL[1]++;        //strobe period becomes 1/2 after decay is hit
  }
  if (_state == 2) {
    digitalWrite(EN_2, COLD);
    digitalWrite(EN_1, COLD);
    digitalWrite(EN_3, LED_STATE[2] & KOOL[2]);
    if (STATE_THERM[2] > decay) KOOL[2]++;        //strobe period becomes 1/2 after decay is hit
  }
  if (_state == 3) {
    digitalWrite(EN_3, COLD);
    digitalWrite(EN_2, COLD);
    digitalWrite(EN_1, LED_STATE[0] & KOOL[0]);
    if (STATE_THERM[0] > decay) KOOL[0]++;        //strobe period becomes 1/2 after decay is hit
    cnt++; //cnt advance, last state
  }
  _state = (_state + 1) % 4;
  delay(ms_delay);
}

void button_check(void) {
  /* loop while !active */
  while (digitalRead(TRIGGER) == !ACTIVE) {
    digitalWrite(EN_3, COLD);
    digitalWrite(EN_2, COLD);
    digitalWrite(EN_1, COLD);
    delay(100);
  }
}

/* WORK LOGO LOGIC */
void state_seq(void) {
  /******************************************************/
  /* E1 */
  if (((cnt > (1  * cell)) && (cnt < (9  * cell))) ||
      ((cnt > (11 * cell)) && (cnt < (19 * cell))))
  {
    LED_STATE[0] = HOT;
    STATE_THERM[0]++;
  }
  else
  {
    STATE_THERM[0] = 0;
    LED_STATE[0]   = COLD;
    KOOL[0]        = HOT;
  }
  /******************************************************/
  /* E2 */
  if (((cnt > (0  * cell)) && (cnt < (2  * cell)))  ||
      ((cnt > (8  * cell)) && (cnt < (10 * cell)))  ||
      ((cnt > (16 * cell)) && (cnt < (18 * cell))))
  {
    LED_STATE[1] = HOT;
    STATE_THERM[1]++;
  }
  else
  {
    STATE_THERM[1] = 0;
    LED_STATE[1]   = COLD;
    KOOL[1]        = HOT;
  }
  /******************************************************/
  /* E3 */
  if (((cnt > (1  * cell)) && (cnt < (3  * cell)))  ||
      ((cnt > (5  * cell)) && (cnt < (7  * cell)))  ||
      ((cnt > (9  * cell)) && (cnt < (11 * cell)))  ||
      ((cnt > (13 * cell)) && (cnt < (15 * cell)))  ||
      ((cnt > (17 * cell)) && (cnt < (19 * cell))))
  {
    LED_STATE[2] = HOT;
    STATE_THERM[2]++;
  }
  else
  {
    STATE_THERM[2] = 0;
    LED_STATE[2]   = COLD;
    KOOL[2]        = HOT;
  }
  /******************************************************/
}


// line 150
