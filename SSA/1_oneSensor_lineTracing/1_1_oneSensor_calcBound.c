#pragma config(Sensor, S1, c1, sensorEV3_color)
#pragma config(Sensor, S2, c2, sensorEV3_color)
#pragma config(Sensor, S3, c3, sensorEV3_color)
#pragma config(Motor, motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor, motorC, rm, tmotorEV3_Large, PIDControl, encoder)

int calcBound()
{
    int bound;
    int black = 0;
    int white = 0;

    for (int i = 0; i<5; i++){
        black+=getColorReflection(c2);
        sleep(10);
    }

    setMotorSpeed(lm, 0);
    setMotorSpeed(rm, 40);
    sleep(300);
    setMotorSpeed(lm, 0);
    setMotorSpeed(lm, 0);

    for (int i = 0; i<5; i++){
        white+=getColorReflection(c2);
        sleep(10);
    }

    bound = (white/10+black/10)/2;

    return bound;
}

task main()
{
    int gray = calcBound();
    displayBigTextLine(1, "%d", gray);
    sleep(5000);
}