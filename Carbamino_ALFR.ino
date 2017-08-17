#define MOTOR1_F 6      // Motor 1 forward
#define MOTOR1_R 9      // Motor 1 reverse
#define MOTOR2_F 3      // Motor 2 forward
#define MOTOR2_R 5      // Motor 2 reverse

#define M1_SPEED_DEFAULT 160   // Right default motor speed: 160
#define M2_SPEED_DEFAULT 160   // Left default motor speed : 160

#define M1_SPEED_3 140
#define M2_SPEED_3 140

#define M1_SPEED_2 100
#define M2_SPEED_2 100

#define M1_SPEED_1 80
#define M2_SPEED_1 80

#define M1_SPEED_0 0
#define M2_SPEED_0 0

int monitor_speedL = 0;
int monitor_speedR = 0;

int SENSOR_L = A3;
int SENSOR_R = A2;

int sensorL_val = 0;
int sensorR_val = 0;

String directionLR = "";

void printSensorVal(int, int);
void printSpeed(int, int);
void printDirectionLR(String);

void start(int, int);
void driveMotor(int, int);

void setup()
{
  delay(2000);
  Serial.begin(9600);

  pinMode(SENSOR_L, INPUT);
  pinMode(SENSOR_R, INPUT);
  
  pinMode(MOTOR1_F, OUTPUT);
  pinMode(MOTOR1_R, OUTPUT);
  pinMode(MOTOR2_F, OUTPUT);
  pinMode(MOTOR2_R, OUTPUT);
}

void loop()
{
  sensorL_val = analogRead(SENSOR_L);
  sensorR_val = analogRead(SENSOR_R);

  start(sensorL_val, sensorR_val);

  delay(0);
}

void printSensorVal(int sensorL_val, int sensorR_val)
{
  Serial.print("Sensor: ");
  Serial.print(sensorL_val);
  Serial.print("\t");
  Serial.println(sensorR_val);

  sensorL_val = 0;
  sensorR_val = 0;
}

void printSpeed(int monitor_speedL, int monitor_speedR)
{
  Serial.print("Speed : ");
  Serial.print(monitor_speedL);
  Serial.print("\t");
  Serial.println(monitor_speedR);

  monitor_speedL = 0;
  monitor_speedR = 0;
}

void printDirectionLR(String directionLR)
{
  Serial.print("Direction : ");
  Serial.println(directionLR);
  Serial.println("");

  directionLR = "";
}

void driveMotor(int monitor_speedL, int monitor_speedR)
{
  analogWrite(MOTOR1_F,monitor_speedL);      digitalWrite(MOTOR1_R,LOW);
  analogWrite(MOTOR2_F,monitor_speedR);      digitalWrite(MOTOR2_R,LOW);
}

void start(int sensorL_val, int sensorR_val)
{
  // case 1: วิ่งตรง Speed Default
  if      ( (sensorL_val >= 35 && sensorL_val <= 50) &&
            (sensorR_val >= 35 && sensorR_val <= 50) )
  {
    monitor_speedL = M1_SPEED_DEFAULT; // 160
    monitor_speedR = M2_SPEED_DEFAULT;

    directionLR = "Straight";

    printSensorVal(sensorL_val, sensorR_val);
    printSpeed(monitor_speedL, monitor_speedR);
    printDirectionLR(directionLR);
    
    driveMotor(monitor_speedL, monitor_speedR);
  }

  // case 2: ยกรถ  Speed 0
  else if ( (sensorL_val >= 940) &&
            (sensorR_val >= 940) )
  {
    monitor_speedL = M1_SPEED_0;       // 0
    monitor_speedR = M2_SPEED_0;

    directionLR = "Stop";

    printSensorVal(sensorL_val, sensorR_val);
    printSpeed(monitor_speedL, monitor_speedR);
    printDirectionLR(directionLR);

    driveMotor(monitor_speedL, monitor_speedR);
  }

  else // case เข้าโค้ง
  {
    // ----- เลี้ยวขวา : Sensor ซ้าย อ่านค่าได้ "น้อยกว่า" Sensor ขวา -----
    if      (sensorL_val < sensorR_val)
    {
      directionLR = "Turn Right";

      // เลี้ยวขวา Speed 3
      if      (sensorL_val >= 60 && sensorL_val <= 106)
      {
        monitor_speedL = 160;
        monitor_speedR = 70;

        printSensorVal(sensorL_val, sensorR_val);
        printSpeed(monitor_speedL, monitor_speedR);
        printDirectionLR(directionLR);
      }

      // เลี้ยวขวา Speed 2
      else if (sensorL_val >= 220 && sensorL_val <= 735)
      {
        monitor_speedL = 140;
        monitor_speedR = 40;

        printSensorVal(sensorL_val, sensorR_val);
        printSpeed(monitor_speedL, monitor_speedR);
        printDirectionLR(directionLR);
      }

      // เลี้ยวขวา Speed 1
      else if (sensorL_val >= 744 || sensorL_val <= 840)
      {
        monitor_speedL = 120;
        monitor_speedR = 20;

        printSensorVal(sensorL_val, sensorR_val);
        printSpeed(monitor_speedL, monitor_speedR);
        printDirectionLR(directionLR);
      }

      driveMotor(monitor_speedL, monitor_speedR);
    }

    // ----- เลี้ยวซ้าย : Sensor ซ้าย อ่านค่าได้ "มากกว่า" Sensor ขวา -----
    else if (sensorL_val > sensorR_val)
    {
      directionLR = "Turn Left";

      // เลี้ยวซ้าย Speed 3
      if      (sensorR_val >= 60 && sensorR_val <= 106)
      {
        monitor_speedL = 70;
        monitor_speedR = 160;

        printSensorVal(sensorL_val, sensorR_val);
        printSpeed(monitor_speedL, monitor_speedR);
        printDirectionLR(directionLR);
      }

      // เลี้ยวซ้าย Speed 2
      else if (sensorR_val >= 180 || sensorR_val <= 860)
      {
        monitor_speedL = 40;
        monitor_speedR = 140;

        printSensorVal(sensorL_val, sensorR_val);
        printSpeed(monitor_speedL, monitor_speedR);
        printDirectionLR(directionLR);
      }

      // เลี้ยวซ้าย Speed 1
      else if (sensorR_val >= 878 || sensorR_val <= 935)
      {
        monitor_speedL = 20;
        monitor_speedR = 120;

        printSensorVal(sensorL_val, sensorR_val);
        printSpeed(monitor_speedL, monitor_speedR);
        printDirectionLR(directionLR);
      }
      driveMotor(monitor_speedL, monitor_speedR);
    }

    // ----- อื่น ๆ -----
    else
    {
      monitor_speedL = 999;
      monitor_speedR = 999;

      directionLR = "ERROR!";

      printSensorVal(sensorL_val, sensorR_val);
      printSpeed(monitor_speedL, monitor_speedR);
      printDirectionLR(directionLR);
    }
  }
}


