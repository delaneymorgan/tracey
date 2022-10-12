# tracey
A simple trace macro which can be controlled by individual modules, or if brave, the entire program.

(c) Delaney & Morgan Computing 2009-2010.
<admin@delaneymorgan.com.au>
Anyone is free to copy this software as is, or modified as long as this attribution remains. i.e. no complicated licences, no lawyers, and no restrictions. Just use it, enjoy it, and relax. We won't hassle you about it if you don't hassle us.

### To use:
#### In client module:
```
#define TRACE_ON
#include "include/trace.h
```

#### In client functions/methods:
```
SomeClass::SomeClass()
{
    TRACE_START();
    m_number = 12345;
    TRACE_CHECK("Arbitrary checkpoint");
    TRACE_END();
}

int myDouble( int num)
{
	TRACE_START( "num: %d", num);
	int ret = 2 * num;
	TRACE_END( "ret: %d", ret);
	return ret;
}
```

#### To disable:
```
//#define TRACE_ON
```


