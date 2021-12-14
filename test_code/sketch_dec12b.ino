/*
 * Thermal Test Code for Board
 * MJM - 2021
 */

int EN_1    = 10;
int EN_2    = 9;
int EN_3    = 11;
int PWM_PIN = 8;

int LED_STATE[3] = {1, 1, 1};

unsigned long previousMillis_A = 0;
int _state = 0;
int cnt = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(PWM_PIN, OUTPUT);
  pinMode(EN_1, OUTPUT);
  pinMode(EN_2, OUTPUT);
  pinMode(EN_3, OUTPUT);

  digitalWrite(PWM_PIN, 0); //off
  digitalWrite(EN_1,    1); //off
  digitalWrite(EN_2,    1); //off
  digitalWrite(EN_3,    1); //off

  delay(100);
  digitalWrite(PWM_PIN, 1); //on
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();

  /* E 1 */
  if (((cnt > 5) && (cnt < 45)) ||
      ((cnt > 55) && (cnt < 95)))
    LED_STATE[0] = 0;
  else
    LED_STATE[0] = 1;

  /* E 2 */
  if (((cnt > 0) && (cnt < 10))  ||
      ((cnt > 40) && (cnt < 50)) ||
      ((cnt > 80) && (cnt < 90)))
    LED_STATE[1] = 0;
  else
    LED_STATE[1] = 1;

  /* E 3 */
  if (((cnt > 5) && (cnt < 15))  ||
      ((cnt > 25) && (cnt < 35)) ||
      ((cnt > 45) && (cnt < 55)) ||
      ((cnt > 65) && (cnt < 75)) ||
      ((cnt > 85) && (cnt < 95)))
    LED_STATE[2] = 0;
  else
    LED_STATE[2] = 1;

  if (cnt > 180)
    cnt = 0;

  /********** state update, every 20ms **********/
  if (currentMillis - previousMillis_A >= 20) {
    previousMillis_A = currentMillis;

    digitalWrite(EN_3, 1);
    digitalWrite(EN_2, 1);
    digitalWrite(EN_1, 1);

    if (_state == 0)
      digitalWrite(EN_3, LED_STATE[2]);
    if (_state == 1)
      digitalWrite(EN_2, LED_STATE[1]);
    if (_state == 2)
      digitalWrite(EN_3, LED_STATE[2]);
    if (_state == 3)
      digitalWrite(EN_1, LED_STATE[0]);

    if (_state == 0) cnt++;
    _state = (_state + 1) % 4;    
  }

}













//line 100