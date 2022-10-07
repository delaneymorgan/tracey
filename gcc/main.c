#include <stdio.h>

#define TRACE_ON

#include "../includes/trace.h"

void YetAnotherFunction()
{
    TRACE_START();
    TRACE_END();
}

void AnotherFunction()
{
    TRACE_START();
    YetAnotherFunction();
    TRACE_END();
}

void SomeFunction(int number)
{
    TRACE_START("number: %d", number);
    AnotherFunction();
    TRACE_END();
}

int main() {
    printf("Tracey Start\n");
    SomeFunction(12345);
    return 0;
}
