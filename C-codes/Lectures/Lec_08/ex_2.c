#include <stdio.h>
#include <string.h>


typedef struct {
    char brand[50];
    char model[50];
    float max_speed;
} Vehicle;


typedef struct {
    Vehicle vehicle;
    int wheels;
    float engine_capacity;
    float fuel_capacity;
    int passenger_capacity;
    float wing_span;
    float length;
} SpecificVehicle;


void compareSpeed(SpecificVehicle v1, SpecificVehicle v2) {
    printf("\nComparing %s %s and %s %s by max speed:\n", v1.vehicle.brand, v1.vehicle.model, v2.vehicle.brand, v2.vehicle.model);
    if (v1.vehicle.max_speed > v2.vehicle.max_speed) {
        printf("%s %s is faster with a speed of %.2f km/h\n", v1.vehicle.brand, v1.vehicle.model, v1.vehicle.max_speed);
    } else if (v1.vehicle.max_speed < v2.vehicle.max_speed) {
        printf("%s %s is faster with a speed of %.2f km/h\n", v2.vehicle.brand, v2.vehicle.model, v2.vehicle.max_speed);
    } else {
        printf("Both vehicles have the same max speed of %.2f km/h\n", v1.vehicle.max_speed);
    }
}

int main() {


    SpecificVehicle car = {
        .vehicle = {"Toyota", "Corolla", 180.0},
        .wheels = 4,
        .engine_capacity = 1.8,
        .fuel_capacity = 50.0,
        .passenger_capacity = 5,
        .wing_span = 0.0,
        .length = 0.0
    };

    SpecificVehicle motorbike = {
        .vehicle = {"Harley-Davidson", "Iron 883", 120.0},
        .wheels = 2,
        .engine_capacity = 0.9,
        .fuel_capacity = 12.0,
        .passenger_capacity = 2,
        .wing_span = 0.0,
        .length = 2.3
    };

    SpecificVehicle boat = {
        .vehicle = {"Yamaha", "242X", 80.0},
        .wheels = 0,
        .engine_capacity = 4.0,
        .fuel_capacity = 210.0,
        .passenger_capacity = 12,
        .wing_span = 0.0,
        .length = 7.4
    };

    SpecificVehicle airplane = {
        .vehicle = {"Boeing", "747", 900.0},
        .wheels = 8,
        .engine_capacity = 0.0,
        .fuel_capacity = 183380.0,
        .passenger_capacity = 416,
        .wing_span = 64.4,
        .length = 70.7
    };


    compareSpeed(car, motorbike);
    compareSpeed(boat, airplane);

    return 0;
}
