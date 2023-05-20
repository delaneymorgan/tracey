# tracey
A simple trace macro which can be controlled by individual modules, or if brave, the entire program.

(c) Delaney & Morgan Computing.
<admin@delaneymorgan.com.au>
Anyone is free to copy this software as is, or modified as long as this attribution remains. i.e. no complicated licences, no lawyers, and no restrictions. Just use it, enjoy it, and relax. We won't hassle you about it if you don't hassle us.

### Why?:
These macros are handy for revealing the code sequence in situations
where stepping through the code with a debugger is not practical.
i.e. in a real-time application.

### Why not?
These macros will increase code size, and perhaps that's a factor in your situation.

Also, these macros will have an impact on performance.

Finally, Heisenberg's conundrum applies.
Observing behaviour may change the behaviour.
Especially true in real-time applications.

### What's left:
I haven't experimented with using trace with many threads running.
The output could be confusing.
Thread-tidy stdout probably requires a shared mutex (at least for c programs)
which would probably introduce latencies between threads.

### To use:

#### In client module:

Bracket the start and end of functions/methods with TRACE_START and TRACE_END respectively.
Anything in-between, use TRACE_CHECK.

TRACE_END works better if each function/method has a single exit.

If you only want to see an item the first time, use TRACE_SINGLE_CHECK.
Once it has performed its trace, it will not do it again.

If you are only interested in a condition which has changed, use TRACE_ON_CHANGE.
This trace will only display if the message has changed.

```c++
#define TRACE_ON
#include "include/trace.h
```

#### In client functions/methods:
```c++
SomeClass::SomeClass()
{
    TRACE_START();
    m_number = 12345;
    TRACE_CHECK("Arbitrary checkpoint");
    TRACE_SINGLE_CHECK("Only shown once, even if called several times");
    TRACE_END();
}

int myDouble( int num)
{
    TRACE_START( "num: %d", num);
    TRACE_ON_CHANGE( "num: %d", num);       // will only display if num changes
    int ret = 2 * num;
    TRACE_END( "ret: %d", ret);
    return ret;
}
```

#### To disable:
```c++
//#define TRACE_ON
```


#### Sample output:
Each line states whether the context is starting or ending a function,
checking an item, or if an item has changed.

The number in brackets is the thread id, followed by the filepath,
the function name or signature, line number,
and then the message that was passed into the trace macro.

```text
tracey-gcc Start
Starting (6192)/home/craig/project/tracey/gcc/main.c::SomeFunction:30 number: 12345
Starting (6192)/home/craig/project/tracey/gcc/main.c::AnotherFunction:17 
Starting (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:9 param: fred
Check (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:10 Arbitrary checkpoint
Change (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:11 param: fred 
Ending (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:12 
Starting (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:9 param: fred
Check (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:10 Arbitrary checkpoint
Ending (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:12 
Starting (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:9 param: fred
Check (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:10 Arbitrary checkpoint
Ending (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:12 
Starting (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:9 param: fred
Check (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:10 Arbitrary checkpoint
Ending (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:12 
Starting (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:9 param: joe
Check (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:10 Arbitrary checkpoint
Change (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:11 param: joe 
Ending (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:12 
Starting (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:9 param: joe
Check (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:10 Arbitrary checkpoint
Ending (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:12 
Check (6192)/home/craig/project/tracey/gcc/main.c::AnotherFunction:24 One Time Only
Ending (6192)/home/craig/project/tracey/gcc/main.c::AnotherFunction:25 
Ending (6192)/home/craig/project/tracey/gcc/main.c::SomeFunction:32 
Starting (6192)/home/craig/project/tracey/gcc/main.c::SomeFunction:30 number: 54321
Starting (6192)/home/craig/project/tracey/gcc/main.c::AnotherFunction:17 
Starting (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:9 param: fred
Check (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:10 Arbitrary checkpoint
Change (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:11 param: fred 
Ending (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:12 
Starting (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:9 param: fred
Check (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:10 Arbitrary checkpoint
Ending (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:12 
Starting (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:9 param: fred
Check (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:10 Arbitrary checkpoint
Ending (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:12 
Starting (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:9 param: fred
Check (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:10 Arbitrary checkpoint
Ending (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:12 
Starting (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:9 param: joe
Check (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:10 Arbitrary checkpoint
Change (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:11 param: joe 
Ending (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:12 
Starting (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:9 param: joe
Check (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:10 Arbitrary checkpoint
Ending (6192)/home/craig/project/tracey/gcc/main.c::YetAnotherFunction:12 
Ending (6192)/home/craig/project/tracey/gcc/main.c::AnotherFunction:25 
Ending (6192)/home/craig/project/tracey/gcc/main.c::SomeFunction:32 
```
