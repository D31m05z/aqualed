#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

int main() {
    if (wiringPiSetup () == -1)
        return 1;

    if(softPwmCreate(0, 0, 100)) {
        printf("error\n");
        return 1;
    }

    softPwmWrite(0, 1);

    for(;;);

    return 0;
}
