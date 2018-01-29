#define X_MIN_PIN           3
#ifndef X_MAX_PIN
#define X_MAX_PIN         2
#endif
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_CS_PIN           53

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_CS_PIN           49

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_CS_PIN           40

int button_x, button_y, button_z, kranc_x_flag = 0, kranc_y_flag = 0, kranc_z_flag = 0, a, kroki_x = 0, kroki_y = 0, kroki_z = 0;
char s[40];
uint8_t s_len = 0;
String txtMsg;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  //Serial.setTimeout(100);
  pinMode(Y_MAX_PIN, INPUT);
  pinMode(Z_MAX_PIN, INPUT);
  pinMode(X_MAX_PIN, INPUT);

  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(X_CS_PIN, OUTPUT);

  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Y_CS_PIN, OUTPUT);

  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);
  pinMode(Z_CS_PIN, OUTPUT);

  digitalWrite(Y_MAX_PIN, HIGH);
  digitalWrite(Z_MAX_PIN, HIGH);
  digitalWrite(X_MAX_PIN, HIGH);

  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  digitalWrite(Z_ENABLE_PIN, LOW);

  digitalWrite(X_CS_PIN, HIGH);
  digitalWrite(Y_CS_PIN, HIGH);
  digitalWrite(Z_CS_PIN, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  button_y = digitalRead(Y_MAX_PIN);
  button_z = digitalRead(Z_MAX_PIN);
  button_x = digitalRead(X_MAX_PIN);

  while (Serial.available())
  {

    s[s_len++] = Serial.read();
    if (s[s_len - 1] == '\r' || s[s_len - 1] == '\n') {
      s[s_len - 1] = 0;
      sscanf(s, "x=%d y=%d z=%d a", &kroki_x, &kroki_y, &kroki_z);
      s_len = 0;
    }

  }


  if (button_x)
  {
    kranc_x_flag = 1;
    kroki_x = -100;
  }
  if (button_y)
  {
    kranc_y_flag = 1;
    kroki_y = -100;
  }
  if (button_z)
  {
    kranc_z_flag = 1;
    kroki_z = -100;
  }
  step_xyz_up();
  step_xyz_down();

}

void step_xyz_up()
{
  digitalWrite(X_DIR_PIN, LOW);
  digitalWrite(Y_DIR_PIN, LOW);
  digitalWrite(Z_DIR_PIN, LOW);
  if (kranc_x_flag == 0)
  {
    if (kroki_x > 0)
    {
      digitalWrite(X_STEP_PIN, HIGH);
      kroki_x = kroki_x - 1;
    }
  }
  else
  {
    steps_down();
    kranc_x_flag = 0;
  }
  if (kranc_y_flag == 0)
  {
    if (kroki_y > 0)
    {
      digitalWrite(Y_STEP_PIN, HIGH);
      kroki_y = kroki_y - 1;
    }
  }
  else
  {
    steps_down();
    kranc_y_flag = 0;
  }
  if (kranc_z_flag == 0)
  {
    if (kroki_z > 0)
    {
      digitalWrite(Z_STEP_PIN, HIGH);
      kroki_z = kroki_z - 1;
    }
  }
  else
  {
    steps_down();
    kranc_z_flag = 0;
  }
  delayMicroseconds(200);
  digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  delayMicroseconds(200);
}

void step_xyz_down()
{
  digitalWrite(X_DIR_PIN, HIGH);
  digitalWrite(Y_DIR_PIN, HIGH);
  digitalWrite(Z_DIR_PIN, HIGH);
  if (kranc_x_flag == 0 && kroki_x < 0)
  {
    digitalWrite(X_STEP_PIN, HIGH);
    kroki_x = kroki_x + 1;
  }
  if (kranc_y_flag == 0 && kroki_y < 0)
  {
    digitalWrite(Y_STEP_PIN, HIGH);
    kroki_y = kroki_y + 1;
  }
  if (kranc_z_flag == 0 && kroki_z < 0)
  {
    digitalWrite(Z_STEP_PIN, HIGH);
    kroki_z = kroki_z + 1;
  }
  delayMicroseconds(200);
  digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  delayMicroseconds(200);
}

void steps_down()
{
  if (kranc_x_flag == 1) digitalWrite(X_DIR_PIN, HIGH);
  if (kranc_y_flag == 1) digitalWrite(Y_DIR_PIN, HIGH);
  if (kranc_z_flag == 1) digitalWrite(Z_DIR_PIN, HIGH);
  if (kroki_x < 0)
  {
    digitalWrite(X_STEP_PIN, HIGH);
    kroki_x = kroki_x + 1;
  }
  if (kroki_y < 0)
  {
    digitalWrite(Y_STEP_PIN, HIGH);
    kroki_y = kroki_y + 1;
  }
  if (kroki_z < 0)
  {
    digitalWrite(Z_STEP_PIN, HIGH);
    kroki_z = kroki_z + 1;
  }
  delayMicroseconds(200);
  digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  delayMicroseconds(200);
}


