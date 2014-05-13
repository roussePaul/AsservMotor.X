/*
 * File:   PID.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 7 mai 2014, 10:14
 */

#include "../dsPIC33F/h/p33FJ128MC802.h"
#include "../peripheral_30F_24H_33F/Generic.h"
#include "../peripheral_30F_24H_33F/timer.h"
#include "QEI.h"
#include "UART.h"
#include "PWM.h"
#include "PID.h"


#include <dsp.h>

/*
Variable Declaration required for each PID controller in your application
*/
/* Declare a PID Data Structure named, PID1 and PID2 */
tPID PID1,PID2;
/* The fooPID data structure contains a pointer to derived coefficients in X-space and */
/* pointer to controler state (history) samples in Y-space. So declare variables for the */
/* derived coefficients and the controller history samples */
fractional abcCoefficient1[3] __attribute__ ((section (".xbss, bss, xmemory")));
fractional controlHistory1[3] __attribute__ ((section (".ybss, bss, ymemory")));

fractional abcCoefficient2[3] __attribute__ ((section (".xbss, bss, xmemory")));
fractional controlHistory2[3] __attribute__ ((section (".ybss, bss, ymemory")));
/* The abcCoefficients referenced by the fooPID data structure */
/* are derived from the gain coefficients, Kp, Ki and Kd */
/* So, declare Kp, Ki and Kd in an array */
fractional kCoeffs1[] = {0,0,0};
fractional kCoeffs2[] = {0,0,0};

/*
Main function demonstrating the use of PID(), PIDInit() and PIDCoeffCalc()
functions from DSP library in MPLAB C30 v3.00 and higher
*/
int initPIDs(void)
{
/*
Step 1: Initialize the PID data structure, PID
*/
        PID1.abcCoefficients = &abcCoefficient1[0];    /*Set up pointer to derived coefficients */
        PID1.controlHistory = &controlHistory1[0];     /*Set up pointer to controller history samples */
        PIDInit(&PID1);                               /*Clear the controler history and the controller output */
	kCoeffs1[0] = Q15(1.0);
	kCoeffs1[1] = Q15(0.0);
	kCoeffs1[2] = Q15(0.0);
        PIDCoeffCalc(&kCoeffs1[0], &PID);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */

        PID2.abcCoefficients = &abcCoefficient2[0];    /*Set up pointer to derived coefficients */
        PID2.controlHistory = &controlHistory2[0];     /*Set up pointer to controller history samples */
        PIDInit(&PID2);                               /*Clear the controler history and the controller output */
	kCoeffs2[0] = Q15(1.0);
	kCoeffs2[1] = Q15(0.0);
	kCoeffs2[2] = Q15(0.0);
        PIDCoeffCalc(&kCoeffs2[0], &PID2);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */

}
void setConsignePIDs(float vg, float vd)
{

        PID1.controlReference = Q15(vg) ;           /*Set the Reference Input for your controller */

        PID2.controlReference = Q15(vd) ;           /*Set the Reference Input for your controller */

}

void runPIDs(){

        PID1.measuredOutput = Q15(v1) ;
        PID2.measuredOutput = Q15(v2) ;

        PID(&PID1);                           /*Call the PID controller using the new measured input */
        PID(&PID2);                           /*Call the PID controller using the new measured input */
                                                /*The user may place a breakpoint on "PID(&fooPID)", halt the debugger,*/
                                                /*tweak the measuredOutput variable within the watch window */
                                                /*and then run the debugger again */
}
