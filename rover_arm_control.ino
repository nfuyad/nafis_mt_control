#include <IBT.h>

IBT base(0, 1);
IBT shoulder(2, 3);
IBT elbow(4, 5);
IBT wrist(7, 6);
IBT wrist_twist(8, 9);
IBT claw(10, 11);
IBT solenoid(12, 13);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()){
    String recievedstring= Serial.readString();

    float values[6];
        int index = 0;
        char *ptr = strtok((char*)recievedstring.c_str(), ",");
        while (ptr != NULL && index < 6) {
            values[index] = atof(ptr);
            ptr = strtok(NULL, ",");
            index++;
        }


    if(values[0]!= 0.0){float base_value= map(values[0], -300, 300, -200, 200);   base.setRawSpeed(base_value); }
    if(values[1]!= 0.0){float shoulder_value= map(values[1], -300, 300, -200, 200);   shoulder.setRawSpeed(shoulder_value);}
    if(values[2]!= 0.0){float elbow_value= map(values[2], -300, 300, -200, 200);    elbow.setRawSpeed(elbow_value);}
    if(values[3]!= 0.0){float wrist_value= map(values[3], -300, 300, -200, 200);    wrist.setRawSpeed(wrist_value);}
    if(values[4]!= 0.0){float wrist_twist_value= map(values[4], -300, 300, -200, 200);    wrist_twist.setRawSpeed(wrist_twist_value);}
    if(values[5]!= 0.0){float claw_value= map(values[5], -300, 300, -200, 200);   claw.setRawSpeed(claw_value);}




    
    
    
    
    
    


    


    
    

    
    }

}
