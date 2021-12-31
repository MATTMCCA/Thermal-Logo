#include <cstdio>

#define HOT    1
#define COLD   0
#define ACTIVE 0

#define COOL 0
#define HEAT 1

#define E2_OFFSET 5                         /* tune wire offset */

const int micro_pixle = 20;                 /* 20 upix per pix */

int THERM_CNT[3]   = {      0,    0,    0};
int     THERM[3]   = {   HEAT, HEAT, HEAT};

int SEQ[3][3]      = {
  // E1,   E2,   E3
  {COLD, COLD, COLD}, //state 1, E1
  {COLD, COLD, COLD}, //state 2, E2
  {COLD, COLD, COLD}  //state 3, E3
};

/* logo, replaces logic */
const int  bmp_size  = 10;
int bmp[3][bmp_size] = {
    {0, 1, 1, 1, 1, 0, 1, 1, 1, 1},
    {0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1}
};

int u_thold = 6; //heat limit, start to cool
int l_thold = 5; //cool, start to heat
int cnt = 0, i = 0, e = 0, e2 = 0;

void state_seq(void);

int main()
{
    printf("LOGO-TEST!\n");
    int upix_cnt = micro_pixle * bmp_size;
    int E1[upix_cnt] = {0x00};
    int E2[upix_cnt] = {0x00};
    int E3[upix_cnt] = {0x00};

    while(cnt < upix_cnt) {
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

      E1[cnt] = SEQ[0][0] & THERM[0];
      E2[cnt] = SEQ[1][1] & THERM[1];
      E3[cnt] = SEQ[2][2] & THERM[2];
      cnt++;
    }

    //display for visual inspection
    int *g[3] = {(int*)&E1, (int*)&E2, (int*)&E3};
    for(int j = 0; j < 3; j++) {
        int l = micro_pixle/2;
        if(j == 2 ) l*=3;
        for(int b = 0; b < l; b++) {
            printf("E%d: ", j+1);
            int *h = g[j];
            for(int u = 0; u < upix_cnt; u++) {
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
  e = ((cnt)              / micro_pixle) % bmp_size; //mod prevent out of bounds indexing
  e2 = ((cnt + E2_OFFSET) / micro_pixle) % bmp_size; //mod prevent out of bounds indexing
  SEQ[0][0] = SEQ[1][1] = SEQ[2][2] = COLD;
  /* E1 *************************************************/
  if(bmp[0][e] == 1)  SEQ[0][0] = HOT;
  /* E2 *************************************************/
  if(bmp[1][e2] == 1) SEQ[1][1] = HOT;
  /* E3 *************************************************/
  if(bmp[2][e] == 1)  SEQ[2][2] = HOT;
}



//100