#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(10, 9); // RX, TX

// Output pins for the motors
int IN1 =5;
int IN2 = 6;
int IN3 = 4;
int IN4 = 3;
int Speed = 204;

// output pin for the pump
int PUMP1 = 11;
int PUMP2 = 12;
int EN = 13;

// Received data via bluetooth
char data;
char check_data;
int stop_pressed = 0;
int btVal;

void setup() {
 // Declare output?
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(PUMP1, OUTPUT);
  pinMode(PUMP2, OUTPUT);
  pinMode(EN, OUTPUT);
// Initial output value (during initialization?)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(PUMP1, LOW);
  digitalWrite(PUMP2, LOW);
  digitalWrite(EN, LOW);
//Set the baud rate to your Bluetooth module.
  Bluetooth.begin(9600);
  Serial.begin(9600); 
  Serial.println("Waiting for command..."); 
}

void loop()
{
 while (Bluetooth.available())
 {  
  {  
      data = Bluetooth.read();
      Serial.print(data);             
  } 
    
    //btVal = (data.toInt());
    //Serial.print("BlueTooth Value ");
    //Serial.println(btVal);    



  switch (data) 
   {
      case 'F':                                
        //Serial.println("Forward");
        forward();
        Bluetooth.println("On!");
        break;

      case 'B':                 
       //Serial.println("Reverse");
        reverse();
        break;

      case 'L':         
       //Serial.println("Left");
        left();
        break;
        
      case 'R':                     
        //Serial.println("Right");
        right();
        break;
      
      case 'G':                     
        //Serial.println("Right");
        //right();
        break;
       
      case 'I':                     
        //Serial.println("Right");
        //right();
        break;

      case 'H':                     
        //Serial.println("Right");
        //right();
        break;

      case 'J':                     
        //Serial.println("Right");
        //right();
        break;
        
      case 'S':                                            
        //Serial.println("Stop");
        stoprobot();
        break;  

      case 'W':                                            
        //Serial.println("Stop");
        pumpON();
        break;
      
      case 'w':                                            
        //Serial.println("Stop");
        pumpOFF();
        break;
    
      case '':  // Put button character for path A in ''
        // Actual path needs calibration
        // Plant 1
        left();
        delay(2000);
        forward();
        delay(5000);
        reverse_left();
        delay(2000);
        forward();
        delay(1000);
        // Put code for the arm movement?
        pumpON();
        delay(5000);
        pumpOFF();

        // Check if the stop button is pressed during previous actions
        // is there a better way? Buttons pushed while running delays might result in buffer overflow
        while (Bluetooth.available()) {
          check_data = Bluetooth.read();
          if (check_data == 'S') {  // Emergency stop
            stop_pressed = 1;
            break;
          }
        }
        if (stop_pressed == 1) {
          stop_pressed = 0;
          break;
        }
        
        // Code to check if path A button pressed again to pause???

        // Plant 2
        reverse();
        delay(1000);
        reverse_left();
        delay(3000);
        forward();
        delay(2000);
        left();
        delay(3000);
        forward();
        delay(1000);
        // Put code for the arm movement?
        pumpON();
        delay(5000);
        pumpOFF();

        // Check again if stop button is pressed...

        // Plant 3, etc....

        break;

  }

 } 
 
                                                              
   if (Bluetooth.available() < 0)                              
    {
     //Serial.println("No Bluetooth Data ");          
    }
  
}

void forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void reverse()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void stoprobot()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void pumpON()
{
  digitalWrite(PUMP1, HIGH);
  digitalWrite(PUMP2, LOW);
  digitalWrite(EN, HIGH);
}

void pumpOFF()
{
  digitalWrite(PUMP1, LOW);
  digitalWrite(PUMP2, LOW);
  digitalWrite(EN, LOW);
}

void reverse_left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void reverse_right()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
