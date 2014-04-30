/*
 * File:   Timers.h
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 30 avril 2014, 14:10
 */

void InitTMR1(void)
{
TMR1 = 0; // Reset timer counter
T1CONbits.TON = 0; // Turn off timer 1
T1CONbits.TSIDL = 0; // Continue operation during sleep
T1CONbits.TGATE = 0; // Gated timer accumulation disabled
T1CONbits.TCS = 0; // use Tcy as source clock
T1CONbits.TCKPS = 2; // Tcy / 64 as input clock
PR1 = 1728; // Interrupt period = 0.0075 sec with a 64 prescaler
IFS0bits.T1IF = 0; // Clear timer 1 interrupt flag
IEC0bits.T1IE = 1; // Enable timer 1 interrupts
T1CONbits.TON = 1; // Turn on timer 1
return;
}
