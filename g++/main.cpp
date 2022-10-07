#include <iostream>

#define TRACE_ON

#include "../includes/trace.h"


class SomeClass {
public:
    SomeClass();

    void method1(const std::string& name) const;
    int method2() const;
private:
    int m_number;
};

SomeClass::SomeClass()
{
    TRACE_START();
    m_number = 12345;
    TRACE_END();
}

void SomeClass::method1(const std::string& name) const {
    TRACE_START("name: %s", name.c_str());
    method2();
    TRACE_END();
}

int SomeClass::method2() const {
    TRACE_START();
    int ret = m_number * 2;
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
    TRACE_END();
}

int main() {
    std::cout << "Tracey Start" << std::endl;
    SomeFunction(12345);
    return 0;
}
