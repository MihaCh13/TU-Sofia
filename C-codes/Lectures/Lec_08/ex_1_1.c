#include <stdio.h>
#include <math.h>


typedef struct {
    float x, y, z;
} Point;


float distance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
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

    Point points[] = {
        {0, 0, 0},
        {3, 0, 0},
        {0, 4, 0},
        {1, 1, 1}
    };


    printf("Calculating the sides of the triangle made out of the points 1, 2 and 3:\n");
    calculateTriangleSides(points[0], points[1], points[2]);

    return 0;
}
