#include <CppUTestExt/MockSupport.h>

extern "C" void leds_toggle (int j)
{
    mock().actualCall("leds_toggle");
}



