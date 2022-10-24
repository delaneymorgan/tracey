#include <stdio.h>

#define TRACE_ON

#include "../includes/trace.h"

void YetAnotherFunction()
{
    TRACE_START();
    TRACE_CHECK("Arbitrary checkpoint");
    TRACE_END();
}

void AnotherFunction()
{
    TRACE_START();
    YetAnotherFunction();
    TRACE_SINGLE_CHECK("One Time Only");
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
    SomeFunction(54321);
    return 0;
}
