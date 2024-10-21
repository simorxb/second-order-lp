#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LENGTH 200
#define TIME_STEP 0.1

struct Second_Order_Filter
{
    const float tau1;           // First time constant
    const float tau2;           // Second time constant
    const float T;              // Time step
    float y_k_1;                // Previous output
    float y_k_2;                // Output two steps ago
};

float Second_Order_Filter_Step(struct Second_Order_Filter *filter, float u_k)
{
    /* This function implements a second-order filter.
     *
     * Inputs:
     *   u_k: the current input to the filter
     *   filter: a pointer to a second-order filter struct containing the filter parameters
     *
     * Returns:
     *   y_k: the filtered output
     */

    float y_k; // Filtered output

    /* Calculate the filtered output using the second-order filter equation */
    y_k = (u_k + filter->tau1 * filter->tau2 * ((2 * filter->y_k_1) - filter->y_k_2) / (filter->T * filter->T) + 
           (filter->tau1 + filter->tau2) * (filter->y_k_1) / filter->T) / 
           (1 + (filter->tau1 * filter->tau2) / (filter->T * filter->T) + (filter->tau1 + filter->tau2) / filter->T);

    /* Update the filter's state for the next iteration */
    filter->y_k_2 = filter->y_k_1;
    filter->y_k_1 = y_k;

    return y_k;
}

int main()
{
    // Current simulation time
    float t = 0;

    // Iteration counter
    int i = 0;

    // Setpoint and output of the first control loop
    float y = 0;
    float u = 1;

    // Filter initialisation
    struct Second_Order_Filter second_order_filter = {1.0, 3.0, TIME_STEP, 0, 0};

    // Open a file for logging simulation data
    FILE *file = fopen("data.txt", "w");

    /* Implement iteration using a while loop */
    while(i < LENGTH)
    {
        
        // Execute the first control loop
        y = Second_Order_Filter_Step(&second_order_filter, u);

        // Log the current time and control loop values to the file
        fprintf(file, "%f %f %f\n", t, u, y);

        // Increment the time and iteration counter
        t = t + TIME_STEP;
        i = i + 1;
    }

    // Close the file and exit the program
    fclose(file);
    exit(0);
}
