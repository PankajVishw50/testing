#include <LiquidCrystal.h>

#include <Servo.h>

// C++ code
//

// Display PART
#define RS 11
#define RW 10
#define E  9
#define DB4 6
#define DB5 5
#define DB6 4
#define DB7 3

LiquidCrystal lcd(RS, RW, E, DB4, DB5, DB6, DB7);

// DC MOTOR PART
#define inp1 13
#define inp2 12
#define enA  A0
#define inp3 8
#define inp4 7
#define enB A1

// SERVO PART 
#define servoPin 2
Servo myservo;



int seconds = 0;
int play = 1;
int delay_interval = 2000;

String stations[4] = {"Ambala", "Panipat", "Sonipat", "Delhi"};
int station_data[][2] = {
	{0, 0},
	{110, 118},
	{150, 181},
	{190, 223}
};// {distance, Time}

//int station_data[][2] = {
	//{0, 0},
	//{110, 2},
	//{150, 4},
	//{190, 6}
//};


int total_stations = 3;
int current_station = 0;

void setup()
{
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  myservo.attach(servoPin);
  myservo.write(0);
  
  pinMode(inp1, OUTPUT);
  pinMode(inp2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(inp3, OUTPUT);
  pinMode(inp4, OUTPUT);
  pinMode(enB, OUTPUT);
  
}

void loop(){
  
  //start_greetings(delay_interval);
  //journey_info(delay_interval);
  
  
  while (current_station < total_stations){
    long journey_time =  next_station(0);
    Serial.println("Journey_time " + String(journey_time*1000));
    rotate_forward();
    delay(journey_time*1000);
    stop();
    delay(1*1000);
    open_gate();
    Serial.println("Gate opened");
    delay(10*1000);
    close_gate();
    delay(1*1000);
    Serial.println("Gate closed");
    stop();
    current_station++;
  }
  
  stop();
  current_station = 0;
  destination_info(delay_interval);
}



void rotate_forward(){
  int speed = 255;
  digitalWrite(inp1, HIGH);
  digitalWrite(inp2, LOW);
  
  digitalWrite(inp3, HIGH);
  digitalWrite(inp4, LOW);
  
  analogWrite(enA, speed);
  analogWrite(enB, speed);
 }

void stop(){
  digitalWrite(inp1, LOW);
  digitalWrite(inp2, LOW);
  digitalWrite(inp3, LOW);
  digitalWrite(inp4, LOW);
}

void open_gate(){
  for (int degree=0;degree<180;degree++){
    myservo.write(degree);
  }
}

void close_gate(){
  for (int degree=180;degree>0;degree--){
    myservo.write(degree);
  }
}



void start_greetings(int interval){
  lcd.clear();
  lcd.setCursor(0, 0);
  
  lcd.print("Welcome");
  lcd.setCursor(0,1);
  lcd.print("Train: Shatabadi exp.");
  delay(interval);
}

void journey_info(int interval){
  lcd.clear();
  lcd.setCursor(0,0);
  
  lcd.print("Journey");
  lcd.setCursor(0,1);
  lcd.print("Ambala to Delhi");
  delay(interval);
}

void destination_info(int interval){
  lcd.clear();
  lcd.setCursor(0,0);
  
  lcd.print("Final Destination");
  lcd.setCursor(0, 1);
  lcd.print("reached. ");
  delay(interval);
}

long next_station(int interval){
  
  long time = station_data[current_station+1][1]-station_data[current_station][1];
  
  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print("Next: ");
  lcd.print(stations[current_station+1]);

  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(time);

  lcd.setCursor(10, 1);
  lcd.print("KM:");
  lcd.print(station_data[current_station+1][0]-station_data[current_station][0]);
  
  
  delay(interval);
  return time;
}
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  