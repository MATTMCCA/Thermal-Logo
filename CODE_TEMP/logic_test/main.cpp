#include <cstdio>

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

int u_thold = 6; //heat limit, start to cool
int l_thold = 5;  //cool, start to heat
int cnt     = 0;
int i       = 0;

void state_seq(void);

int main()
{
    printf("LOGO-TEST!\n");

    int cell_cnt = cell * 19;
    int E1[cell_cnt] = {0x00};
    int E2[cell_cnt] = {0x00};
    int E3[cell_cnt] = {0x00};

    while(cnt < cell_cnt)
    {
      state_seq();
      for (int i = 0; i < 3; i++) {
        if (SEQ[i][i] == COLD) {
          THERM_CNT[i] = 0;
          THERM[i] = HEAT;
        }
      }

      for (i = 0; i < 3; i++) {
        if ((THERM_CNT[i] >= u_thold) && (THERM[i] == HEAT)) THERM[i] = COOL;
        if ((THERM_CNT[i] <= l_thold) && (THERM[i] == COOL)) THERM[i] = HEAT;

        if (THERM[i] == HEAT) THERM_CNT[i]++;
        else                  THERM_CNT[i]--;
      }

      E1[cnt] = SEQ[0][0] & THERM[0];
      E2[cnt] = SEQ[1][1] & THERM[1];
      E3[cnt] = SEQ[2][2] & THERM[2];
      cnt++;
    }

    //display
    int *g[3] = {(int*)&E1, (int*)&E2, (int*)&E3};
    for(int j = 0; j < 3; j++) {
        int l = cell;
        if(j == 2 ) l*=3;
        for(int b = 0; b < l; b++) {
            printf("E%d: ", j+1);
            int *h = g[j];
            for(int u = 0; u < cell_cnt; u++) {
                if(h[u] == 1) printf("#");
                else          printf(".");
            }
            printf("\n");
        }
    }
    return 0;
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
  if (((cnt > (1  * cell)) && (cnt < (3  * cell)))  || //shifted for test
      ((cnt > (9  * cell)) && (cnt < (11 * cell)))  || //shifted for test
      ((cnt > (17 * cell)) && (cnt < (19 * cell))))    //shifted for test
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
