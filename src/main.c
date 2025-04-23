#include <stdio.h>
#include <unistd.h>
#include "../include/traffic_light.h"

int main(){
    struct TrafficLight signal;

    initTrafficLight(&signal);

    while(1){
        displayTrafficLight(&signal);
        sleep(signal.duration);
        updateTrafficLight(&signal);
    }


    return 0;
}