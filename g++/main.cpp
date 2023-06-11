#ifdef _WIN32
#include <Windows.h>
#endif  // _WIN32

#include <iostream>

#define TRACE_ON

#include "../trace/trace.h"


class SomeClass {
public:
    SomeClass();

    void method1(const std::string& name) const;
    int method2( const std::string& param) const;
private:
    int m_number;
};

SomeClass::SomeClass()
{
    TRACE_START();
    m_number = 12345;
    TRACE_CHECK("Arbitrary checkpoint");
    TRACE_END();
}

void SomeClass::method1(const std::string& name) const {
    TRACE_START("name: %s", name.c_str());
    method2("fred");
    method2("fred");
    method2("fred");
    method2("fred");
    method2("joe");
    method2("joe");
    method2("joe");
    method2("joe");
    TRACE_END();
}

int SomeClass::method2( const std::string& param) const {
    TRACE_START();
    int ret = m_number * 2;
    TRACE_ON_CHANGE("param: %s", param.c_str());
    TRACE_END("ret: %d", ret);
    return ret;
}

void YetAnotherFunction()
{
    TRACE_START();
    SomeClass classy;
    classy.method1("fred");
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
    TRACE_SINGLE_CHECK("One Time Only");
    TRACE_END();
}

int main() {
    std::cout << "tracey-cpp Start" << std::endl;
    SomeFunction(12345);
    SomeFunction(54321);
    return 0;
}
