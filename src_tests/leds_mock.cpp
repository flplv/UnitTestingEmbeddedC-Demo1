#include <CppUTestExt/MockSupport.h>

extern "C" void leds_toggle ()
{
    mock().actualCall("leds_toggle");
}



