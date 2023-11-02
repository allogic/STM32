extern int _stack;

// Define the Reset_Handler function, which is the entry point after reset
void Reset_Handler(void);

// Main function prototype
int main(void);

// Vector table
__attribute__((section(".isr_vector"))) void* g_pfnVectors[] = {
    (void*)&_stack, // The stack pointer after reset
    Reset_Handler,    // Reset handler
};

// Reset handler
void Reset_Handler(void) {
    // Copy data from Flash to RAM (if used)
    // Initialize the C library (e.g., set up global constructors, if using C++)
    // Initialize hardware (e.g., clock configuration, GPIO, etc.)

    // Call the main function
    main();

    // In case the main function returns, you can either hang or go to an error state
    while (1);
}

// Main application entry point
int main(void) {
    // Your application code goes here

    // Example: Toggle an LED (assuming GPIO is configured)
    // while (1) {
    //     // Toggle LED
    //     // Delay for a while
    // }
    return 0;
}