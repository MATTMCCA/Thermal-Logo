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

#define COOL 0
#define HEAT 1

const int cell     = 10; /* 10 cells per pix */
const int ms_delay = 10; /* 10ms per E */

int THERM_CNT[3]   = {      0,    0,    0};
int THERM[3]       = {   HEAT, HEAT, HEAT};

int SEQ[3][3]      = {
  // E1,   E2,   E3
  {COLD, COLD, COLD}, //state 1, E1
  {COLD, COLD, COLD}, //state 2, E2
  {COLD, COLD, COLD}  //state 3, E3
};

int TRIGGER = 10;
/* !!DOUBLE CHECK ORDER!! */
int EN_1    = 6;
int EN_2    = 8;
int EN_3    = 9;

int u_thold = 10; //heat limit, start to cool
int l_thold = 5;  //cool, start to heat

int cnt     = 0;
int i       = 0;

void state_seq(void);
void button_check(void);

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIGGER,      INPUT);
  pinMode(EN_1,         OUTPUT);
  pinMode(EN_2,         OUTPUT);
  pinMode(EN_3,         OUTPUT);
  /****************************************************/
  digitalWrite(EN_1,    COLD); //off
  digitalWrite(EN_2,    COLD); //off
  digitalWrite(EN_3,    COLD); //off
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  /****************************************************/
  button_check();
  state_seq();
  /****************************************************/

  for (int i = 0; i < 3; i++)
    if (SEQ[i][i] == COLD) {
      THERM_CNT[i] = 0;
      THERM[i] = HEAT;
    }

  for (i = 0; i < 3; i++) {
    if ((THERM_CNT[i] >= u_thold) && (THERM[i] == HEAT)) THERM[i] = COOL;
    if ((THERM_CNT[i] <= l_thold) && (THERM[i] == COOL)) THERM[i] = HEAT;

    if (THERM[i] == HEAT) THERM_CNT[i]++;
    else                  THERM_CNT[i]--;
  }

  for (i = 0; i < 3; i++) {    
    digitalWrite(EN_1, SEQ[i][0] & THERM[0]); //E1
    digitalWrite(EN_2, SEQ[i][1] & THERM[1]); //E2
    digitalWrite(EN_3, SEQ[i][2] & THERM[2]); //E3
    delay(ms_delay);
  }
  
  cnt++;  
}

void button_check(void) {
  /* loop while !active */  
  while (digitalRead(TRIGGER) == !ACTIVE) {
    digitalWrite(EN_3, COLD);
    digitalWrite(EN_2, COLD);
    digitalWrite(EN_1, COLD);
    THERM_CNT[0] = THERM_CNT[1] = THERM_CNT[2] = 0;
        THERM[0] =     THERM[1] =     THERM[2] = HEAT;
    cnt = 0;
    delay(100);
  }
}

/* WORK LOGO LOGIC */
void state_seq(void) {
  /* E1 *************************************************/
  if (((cnt > (1  * cell)) && (cnt < (9  * cell))) ||
      ((cnt > (11 * cell)) && (cnt < (19 * cell))))
    SEQ[0][0] = HOT;
  else
    SEQ[0][0] = COLD;
  /* E2 *************************************************/
  if (((cnt > (0  * cell)) && (cnt < (2  * cell)))  ||
      ((cnt > (8  * cell)) && (cnt < (10 * cell)))  ||
      ((cnt > (16 * cell)) && (cnt < (18 * cell))))
    SEQ[1][1] = HOT;
  else
    SEQ[1][1] = COLD;
  /* E3 *************************************************/
  if (((cnt > (1  * cell)) && (cnt < (3  * cell)))  ||
      ((cnt > (5  * cell)) && (cnt < (7  * cell)))  ||
      ((cnt > (9  * cell)) && (cnt < (11 * cell)))  ||
      ((cnt > (13 * cell)) && (cnt < (15 * cell)))  ||
      ((cnt > (17 * cell)) && (cnt < (19 * cell))))
    SEQ[2][2] = HOT;
  else
    SEQ[2][2] = COLD;
}


//130
