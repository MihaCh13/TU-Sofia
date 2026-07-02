#include <stdio.h>
# include <math.h>

void calculate_triangle_area()
{
    // Declare variables for the triangle's sides:
    float first_side, second_side, third_side;
    // Enter values for the sides:
    printf("Enter △ sides: ");
    scanf("%f %f %f", &first_side, &second_side, &third_side); // 6 8 10
    // Print the sides, just in case:
    printf("△ Sides: %.2f, %.2f, %.2f.\n", first_side, second_side, third_side);
    // Calculate the half-perimeter:
    float half_perimeter = (first_side + second_side + third_side)/2;

    printf("△ Half-Perimeter: %.2f.\n", half_perimeter);
    // Calculate the triangle's area using Heron's formula:
    float area = sqrt(half_perimeter*(half_perimeter - first_side)*(half_perimeter - second_side)*(half_perimeter - third_side));

    // Print the triangle's area:
    printf("△ Area: %.2f.\n", area);
}
