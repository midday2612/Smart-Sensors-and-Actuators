#pragma config(Sensor, S1, ts, sensorEV3_Touch)
#pragma config(Sensor, S2, gs, sensorEV3_Gyro)
#pragma config(Sensor, S3, cs, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4, ss, sensorEV3_Ultrasonic)
#pragma config(Motor, motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor, motorC, rm, tmotorEV3_Large, PIDControl, encoder)

#define Black 1
#define Blue 2
#define Green 3
#define Yellow 4
#define Red 5
#define White 6
#define Brown 7

float speed = 5;
int c[8] = {0,0,0,0,0,0,0,0};
int tmpcolor, color=0;
int std = 7;
int finish_line;
int start_val=0;
float t;
int count = 0;


void go(float s)
{
   setMotorSpeed(lm, s);
   setMotorSpeed(rm, s);
}

void encodergo(int how, float sp){
    int enc_dgree = (int)(360.0*how/17.58);

      resetMotorEncoder(lm);
      //displayBigTextLine(9, "e = %d", getMotorEncoder(lm));
      while(abs(getMotorEncoder(lm))<enc_dgree){


      //displayBigTextLine(11, "e = %d", getMotorEncoder(lm));

        setMotorSpeed(lm, sp);
        setMotorSpeed(rm, sp);
     }
     go(0);
      sleep(2000);
}




void pointTurn_1(float speed)
{

      int initval = getGyroDegrees(gs);
      int s = initval - 82;
      while(1)
      {
       int lm_speed = -(speed);
       int rm_speed = speed;
       setMotorSpeed(lm, lm_speed);
       setMotorSpeed(rm, rm_speed);
       int interval = getGyroDegrees(gs);
       
       if (interval ==s)
       {
         go(0);
         sleep(1000);
         break;
       }
   }
}


void pointTurn1(float speed)
{

      int initval = getGyroDegrees(gs);
      int s = initval + 82;
      while(1)
      {
       int lm_speed = (speed);
       int rm_speed = -(speed);
       setMotorSpeed(lm, lm_speed);
       setMotorSpeed(rm, rm_speed);
       int interval = getGyroDegrees(gs);
       
       if (interval ==s)
       {
         go(0);
         sleep(1000);
         break;
       }
   }
}



void obs(float dist, int count, float speed){
        //dist = getUsDistance(ss);
        //displayBigTextLine(9, "d = %2f", dist);
        if (dist<10.0){
        encodergo(10, -(speed/2));
        pointTurn1(speed/2);
        encodergo(5*count, speed/2);
        pointTurn1(speed/2);
     }
     else if (dist < 30.0){
        playSound(soundBeepBeep);
        sleep(300);
        go(speed/2);
        sleep(1000);
     }

}

void redline(int count, float speed){
        pointTurn_1(speed/2);
        encodergo(5*count, speed/2);
        pointTurn_1(speed/2);
}


void checking(void){
   while(1)
      {

               tmpcolor = getColorName(cs);
               displayBigTextLine(4, "tmpcolor = %d %d", tmpcolor, start_val);
               //displayBigTextLine(6, "arr = %d %d %d %d", c[0], c[1], c[2],c[3]);
               //displayBigTextLine(8, "arr = %d %d %d ",c[4],c[5], c[6]);

               if (tmpcolor == Black)
                  {
                     c[1]++;
                     sleep(100);
                     if (c[1]>std)
                        {
                           color = Black;
                           displayBigTextLine(2, "color = %d", color);
                           for (int i = 0 ; i< 8; i++)
                              {
                                 c[i] = 0;
                              }

                           break;
                        }
                     }

      if (tmpcolor == Blue) {
         c[2]++;
         sleep(100);
         if (c[2]>std){
         color = Blue;
         displayBigTextLine(2, "color = %d", color);

         for (int i = 0 ; i< 8; i++){
               c[i] = 0;
         }
         break;
      }
   }
      if (tmpcolor == Green){
         c[3]++;
         sleep(100);
         if (c[3]>std){
         color = Green;
         displayBigTextLine(2, "color = %d", color);
         for (int i = 0 ; i< 8; i++){
               c[i] = 0;
         }
            break;
         }
      }


      if (tmpcolor == White) {
         c[6]++;
         sleep(100);
         if (c[6]>std){
         color = White;
         displayBigTextLine(2, "color = %d", color);
         for (int i = 0 ; i< 8; i++){
               c[i] = 0;
            }
            break;
         }
      }

      if (tmpcolor == Red)
         {
            c[5]++;
            sleep(100);
            if (c[5]>std)
               {
               color = Red;
               displayBigTextLine(2, "color = %d", color);
               for (int i = 0 ; i< 8; i++)
                  {
                        c[i] = 0;
                  }
               break;
               }
         }


   if (tmpcolor == Brown) {
         c[7]++;
         sleep(100);
         if (c[7]>std){
         color = Blue;
         displayBigTextLine(2, "color = %d", color);

         for (int i = 0 ; i< 8; i++){
               c[i] = 0;
         }
         break;
      }
   }

   if (tmpcolor == Yellow) {
      c[4]++;
      sleep(100);
      if (c[4]>std){
      color = Yellow;
      displayBigTextLine(2, "color = %d", color);
      for (int i = 0 ; i< 8; i++)
         {
            c[i] = 0;
         }
      break;
   }
}
}
}
task main()
{
      while(getTouchValue(ts) == 0){}
      while(getTouchValue(ts) == 1){}



      while(1){

      displayBigTextLine(7, "count = %d", count);

      go(speed);
      checking();
      float dist = getUSDistance(ss);
      obs(dist, count, speed);

         if(start_val==0 && ((color == Yellow )|| (color == Green) || (color == Black)||(color == Brown)))
      {
         finish_line = color;
         setLEDColor(ledGreen);
         start_val++;
         clearTimer(T1);

         //displayBigTextLine(1, "color = %d", color);
         displayBigTextLine(11, "f = %d", finish_line);
             clearTimer(T1);
      }

         if(finish_line== color)
      {
         start_val++;
      }
      if(( finish_line== color) && (start_val>2))
      {
         go(0);
         sleep(500);
         break;
      }
   if (color == Red){
      go(0);
      sleep(500);
      redline(count, speed);
   }
   if (color == Black){
      count++;
   }

   if (color == Blue){
      if(count>0)
            {
          for(int i = 0; i<count; i++)
             {
             playSound(soundBeepBeep);
             sleep(300);
             }
        }
       else
         {
          playSound(soundBeepBeep);
          sleep(300);
             }
   }


    if (count>=10) {
           go(0);
           sleep(500);
         break;
    }
}

t=time1[T1];
displayBigTextLine (14, "record = %.2f sec", t/1000);
sleep(10000);

}