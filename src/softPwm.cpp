#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <signal.h>

struct LED {
	LED()
        : r(100)
        , g(100)
        , b(100)
        , w(100)
       	{}

    int r;
    int g;
    int b;
    int w;
};

std::vector<int> gGPIO = { 0, 2, 3, 4 };

void reset(const std::vector<int>& GPIO) {
    for(size_t i = 0; i < GPIO.size(); i++) {
        softPwmWrite(GPIO[i], 0);
    }
}

void SIGINT_handler(int s) {
    printf("Caught signal %d\n", s);
    softPwmWrite(0, 0);
    softPwmWrite(2, 0);
    softPwmWrite(3, 0);
    softPwmWrite(4, 0);
    exit(1);
}

int main() {
    LED led;
    LED led_prev;

    signal(SIGINT, SIGINT_handler);

    if(gGPIO.size() < 4) {
        printf("You need to define 4 GPIO pin for softPWM.\n");
        return 1;
    }

    // initialize wiring PI
    if (wiringPiSetup () == -1) {
        return 1;
    }

    // create soft PWM control
    for(size_t i = 0; i < gGPIO.size(); i++) {
	int ret = softPwmCreate(gGPIO[i], 0, 100);
        if(ret != 0) {
            printf("GPIO: %d error : %d\n", gGPIO[i], ret);
            return 1;
        }   
    }

    // setup
    for(size_t i = 0; i< gGPIO.size(); i++) {
        softPwmWrite(gGPIO[i], 50);
    }

    for(;;) {
	char c = getchar();
	if(c == 'r') {
            printf("r- [%d]\n", --led.r);
	} else if(c == 'R') {
            printf("r+ [%d]\n", ++led.r);
	} else if(c == 'g') {
            printf("g- [%d]\n", --led.g);
	} else if(c == 'G') {
            printf("g+ [%d]\n", ++led.g);
	} else if(c == 'b') {
            printf("b- [%d]\n", --led.b);
	} else if(c == 'B') {
            printf("b+ [%d]\n", ++led.b);
	} else if(c == 'w') {
            printf("w- [%d]\n", --led.w);
	} else if(c == 'W') {
            printf("w+ [%d]\n", ++led.w);
	} else if(c == 'z') {
            led.r = led.g = led.b = led.w = 0;
	} else if(c == 'm') {
            led.r = led.g = led.b = led.w = 100;
	} else if(c == 's') {
	    printf("R=%d G=%d B=%d W=%d\n", led.r, led.g, led.b, led.w);
	} else if(c == 'q') {
            break;
	}

	if(led.r != led_prev.r) {
            softPwmWrite(gGPIO[0], led.r);
	}

	if(led.g != led_prev.g) {
            softPwmWrite(gGPIO[1], led.g);
	}

	if(led.b != led_prev.b) {
            softPwmWrite(gGPIO[2], led.b);
	}

	if(led.w != led_prev.w) {
            softPwmWrite(gGPIO[3], led.w);
	}

	led_prev = led;
    }

    reset(gGPIO);

    return 0;
}
