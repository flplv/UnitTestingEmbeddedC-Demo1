/******************************************************************************
 * Software UART example for MSP430.
 *
 * Stefan Wendler
 * sw@kaltpost.de
 * http://gpio.kaltpost.de
 *
 * Echos back each character received enclosed in square brackets "[" and "]".
 * Use /dev/ttyACM0 at 9600 Bauds (and 8,N,1).
 ******************************************************************************/

#include <msp430.h>
#include <stdint.h>

#include "uart.h"
#include "echo.h"

static void platform_init()
{
    WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
    BCSCTL1 = CALBC1_1MHZ;     // Set range
    DCOCTL = CALDCO_1MHZ;      // SMCLK = DCO = 1MHz

    uart_init();
    __enable_interrupt();
}

int main(void)
{

    platform_init();
    echo_init();

    while (1)
    {
        echo_periodic();
    }
}
