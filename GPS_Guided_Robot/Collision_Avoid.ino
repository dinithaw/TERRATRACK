
// void Ping(){
//   if (pingOn == true) {
//     myservo.attach(9); 
//     StopCar();
//     delay(1500);

//     for (pos = 20; pos <= 60; pos += 1) {
//       myservo.write(pos);
//       delay(25);
//     }

//   } else if (pingOn == false) {
//     for (pos = 60; pos >= 20; pos -= 1) {
//       myservo.write(pos);
//       delay(25);
//     }
//     myservo.detach();
//   }
// }

// void pingToggle()                                         // Turns Collision avoidance on/ off
//  {
//   if (pingOn == true) {
//     pingOn = false;
//     Serial1.print("Collision Avoidance OFF");
//   }
//     else if (pingOn == false) {
//     pingOn = true;
//     Serial1.print("Collision Avoidance ON");
//   }
  
//  }


void pingToggle(){
  StopCar();
  myservo.attach(9);
  delay(1000);

  for (pos = 20; pos <= 60; pos += 1) {
  myservo.write(pos);
  delay(10);
  }
  Serial1.print("Sensor Arm Engaged!");

  myservo.detach();
  delay(5000);
  
  myservo.attach(9);
  delay(100);

  for (pos = 60; pos >= 20; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
    Serial1.print("Sensor Arm Disengaged!");
    myservo.detach();

  
}



// void Ping()
// { 
//   currentMillis = millis();
  
//  if ((currentMillis - previousMillis >= interval) && (pingOn == true)) 
//  {
//   previousMillis = currentMillis;
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(5);
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);

//   pinMode(echoPin, INPUT);
//   duration = pulseIn(echoPin, HIGH);
  
//   int inches = (duration / 2) / 74;                       // convert the time into a distance
//   Ping_distance == inches;  
 
//     if ((inches < 12) && (blueToothVal != 5))
//       {
//         Serial1.print("Crash! ");
//         Serial1.println(inches);
//         Reverse();                                        // Quick reverse to Stop quickly
//         delay(100);
//         StopCar();   
//         blueToothVal = 5;                                 // Set bluetooth value to "Stop"
//       } 
  
//   }       // end if statement
 
// }         // end Ping()


