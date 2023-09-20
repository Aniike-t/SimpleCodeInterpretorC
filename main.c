#include <stdio.h>

// Define the bytecode instructions
typedef enum {
    LOAD_CONSTANT,
    ADD,
    PRINT,
    HALT,
} OpCode;

// Define a simple stack for our interpreter
#define STACK_SIZE 100
double stack[STACK_SIZE];
int stackTop = 0;

// The bytecode program
unsigned char bytecode[] = {
    LOAD_CONSTANT, 0,  // Load constant 10
    LOAD_CONSTANT, 1,  // Load constant 20
    ADD,               // Add the top two values on the stack
    PRINT,             // Print the result
    HALT,              // Halt the interpreter
};

// Constants for the bytecode program
double constants[] = {
    10.0,
    20.0,
};

int ip = 0;  // Instruction pointer

// Function to push a value onto the stack
void push(double value) {
    if (stackTop < STACK_SIZE) {
        stack[stackTop++] = value;
        printf("%lf \n",stack[stackTop-1]);
        printf("pushing \n\n");
    } else {
        printf("Stack overflow!\n");
    }
}

// Function to pop a value from the stack
double pop() {
    if (stackTop > 0) {
        printf("popping \n\n");
        printf("%lf \n",stack[stackTop]);
        return stack[--stackTop];
    } else {
        printf("Stack underflow!\n");
        return 0.0;
    }
}

int main() {
    while (1) {
        OpCode instruction = bytecode[ip++];
        switch (instruction) {
            case LOAD_CONSTANT: {
                int constantIndex = bytecode[ip++];
                double constantValue = constants[constantIndex];
                push(constantValue);
                break;
            }
            case ADD: {
                double b = pop();
                double a = pop();
                double result = a + b;
                push(result);
                break;
            }
            case PRINT: {
                double value = pop();
                printf("Result: %lf\n", value);
                break;
            }
            case HALT: {
                return 0;  // Exit the program
            }
        }
    }
    return 0;
}