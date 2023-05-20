#ifdef _WIN32
    #include <Windows.h>
#endif  // _WIN32

#include <stdio.h>

#define TRACE_ON

#include "../includes/trace.h"

void YetAnotherFunction( const char* param)
{
    TRACE_START( "param: %s", param);
    TRACE_CHECK("Arbitrary checkpoint");
    TRACE_ON_CHANGE("param: %s", param);
    TRACE_END();
}

void AnotherFunction()
{
    TRACE_START();
    YetAnotherFunction( "fred");
    YetAnotherFunction( "fred");
    YetAnotherFunction( "fred");
    YetAnotherFunction( "fred");
    YetAnotherFunction( "joe");
    YetAnotherFunction( "joe");
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
    printf("tracey-gcc Start\n");
    SomeFunction(12345);
    SomeFunction(54321);
    return 0;
}
