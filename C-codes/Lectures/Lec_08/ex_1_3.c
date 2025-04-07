#include <stdio.h>


typedef struct {
    float x, y, z;
} Point;


float sqrt_custom(float number) {
    if (number == 0) return 0;  
    float guess = number / 2.0f;  
    float epsilon = 0.00001f;  

   
    while (1) {
        float temp = guess;
        guess = (guess + number / guess) / 2.0f;
        if (temp - guess < epsilon && temp - guess > -epsilon) {
            break;  
        }
    }
    return guess;
}


float distance(Point p1, Point p2) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float dz = p2.z - p1.z;
    return sqrt_custom(dx * dx + dy * dy + dz * dz);  
}


void calculateTriangleSides(Point p1, Point p2, Point p3) {
    float side1 = distance(p1, p2);
    float side2 = distance(p2, p3);
    float side3 = distance(p1, p3);

    printf("Sides of the triangle:\n");
    printf("Side 1: %.2f\n", side1);
    printf("Side 2: %.2f\n", side2);
    printf("Side 3: %.2f\n", side3);
}

int main() {
    Point points[3];  
    int i;

    for(i = 0; i < 3; i++) {
        printf("Enter the coordinates for point %d (x, y, z): ", i+1);
        scanf("%f %f %f", &points[i].x, &points[i].y, &points[i].z);
    }

    printf("\nCalculating the sides of the triangle formed by the entered points:\n");
    calculateTriangleSides(points[0], points[1], points[2]);

    return 0;
}
