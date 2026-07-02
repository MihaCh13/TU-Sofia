#include <stdio.h>
#include <math.h>
// A MACRO to convert from degrees° to radians:
#define degrees_to_radians(degree_angle) ((degree_angle) * M_PI / 180.0)

void calculate_triangle_perimeter()
{
    float a, b, c; // sides
    float A, B, C; // angles°

    // Enter the triangle's 3ʳᵈ side:
    printf("Enter △ side (c): ");
    scanf("%f", &c); // 2

    // Enter the triangle's first two angles:
    printf("Enter △ angles (A & B): ");
    scanf("%f %f", &A, &B); // 30° 60°

    // Calculate the 3ʳᵈ angle:
    C = 180 - A - B; // C = 180° - 30° - 60° = 90°
    // Calculate the first two sides using the law of sines:
    // since the "sine" function accepts radians, we have to convert the degrees° to radians:
    a = c*sin(degrees_to_radians(A))/sin(degrees_to_radians(C)); // a = 2*sin(30°)/sin(90°) = 2*(1/2)/1 = 1/1 = 1
    b = c*sin(degrees_to_radians(B))/sin(degrees_to_radians(C)); // b = 2*sin(60°)/sin(90°) = 2*(√3/2)/1 = √3 ≈ 1.73

    printf("△ Sides: %.2f; %.2f; %.2f\n", a, b, c);
    // Calculate the triangle's perimeter:
    float perimeter = a + b + c; // 1 + 1.73 + 2 = 4.73
    // Print the perimeter:
    printf("△ Perimeter: %.2f.\n", perimeter);
}
