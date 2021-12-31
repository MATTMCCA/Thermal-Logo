/*
   Thermal Logo Code for Board REV_2 (Adafruit Itsy Bitsy 3v 8Mhz)
   MJM - 2021
*/

#define HOT    1
#define COLD   0
#define ACTIVE 0

#define COOL 0
#define HEAT 1

#define E2_OFFSET 5                         /* tune wire offset */

const int micro_pixle = 20;                 /* 20 upix per pix */
const int ms_delay    = 10;                 /* 10ms per E */
const int u_thold     = 10;                 /* heat limit, start to cool */
const int l_thold     = 5;                  /* cool, start to heat */

/* logo, replaces logic */
const int bmp_size  = 10;
const int bmp[3][bmp_size] = {
  {0, 1, 1, 1, 1, 0, 1, 1, 1, 1},
  {0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
  {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}
};

/* IO deff */
const int TRIGGER = 10;
const int EN_1    = 6;
const int EN_2    = 8;
const int EN_3    = 9;

int THERM_CNT[3]   = {      0,    0,    0};
int THERM[3]       = {   HEAT, HEAT, HEAT};

int SEQ[3][3]      = {
  // E1,   E2,   E3
  {COLD, COLD, COLD}, //state 1, E1
  {COLD, COLD, COLD}, //state 2, E2
  {COLD, COLD, COLD}  //state 3, E3
};

int cnt = 0, i = 0, e = 0, e2 = 0;

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
  button_check();
  state_seq();

  for (i = 0; i < 3; i++) {
    if (SEQ[i][i] == COLD) {
      THERM_CNT[i] = 0;
      THERM[i] = HEAT;
    } else {
      if ((THERM_CNT[i] >= u_thold) && (THERM[i] == HEAT)) THERM[i] = COOL;
      if ((THERM_CNT[i] <= l_thold) && (THERM[i] == COOL)) THERM[i] = HEAT;
      if (THERM[i] == HEAT)                                THERM_CNT[i]++;
      else                                                 THERM_CNT[i]--;
    }
  }

  /* may need to add the 4th state back */
  for (i = 0; i < 3; i++) {
    digitalWrite(EN_1, SEQ[i][0] & THERM[0]); /* E1 */
    digitalWrite(EN_2, SEQ[i][1] & THERM[1]); /* E2 */
    digitalWrite(EN_3, SEQ[i][2] & THERM[2]); /* E3 */
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
    cnt = THERM_CNT[0] = THERM_CNT[1] = THERM_CNT[2] = 0;
    THERM[0] = THERM[1] = THERM[2] = HEAT;
    delay(100); //poll button every ~100ms
  }
}

void state_seq(void) {
  e  = ((cnt)             / micro_pixle) % bmp_size; //mod prevent out of bounds indexing
  e2 = ((cnt + E2_OFFSET) / micro_pixle) % bmp_size; //mod prevent out of bounds indexing
  SEQ[0][0] = SEQ[1][1] = SEQ[2][2] = COLD;
  /* E1 *************************************************/
  if (bmp[0][e]  == 1)  SEQ[0][0] = HOT;
  /* E2 *************************************************/
  if (bmp[1][e2] == 1)  SEQ[1][1] = HOT;
  /* E3 *************************************************/
  if (bmp[2][e]  == 1)  SEQ[2][2] = HOT;
}
