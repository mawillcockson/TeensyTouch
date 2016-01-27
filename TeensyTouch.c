/* This file is supposed to help with running the Touch Sense Input
 * module of the Teensy (3.2).
 */

#include <kinetis.h>
#include <pins_arduino.h>
#include <stdint.h>
#include <math.h>
//#include <stdlib.h>
//#include <Arduino.h>
//#include <WProgram.h>
//#include <usb_serial.h>

#if defined(KINETISK)
#define TSI_GENCS_LPCLKS_VAL    ((TSI0_GENCS << 3)  >> 31)
#define TSI_GENCS_LPCLKS(n)	    ((n) << 28)		// Valid values: {0,1}
#define TSI_GENCS_LPSCNITV_VAL  ((TSI0_GENCS << 4)  >> 28)
#define TSI_GENCS_NSCN_VAL      ((TSI0_GENCS << 8)  >> 27)
#define TSI_GENCS_PS_VAL        ((TSI0_GENCS << 13) >> 29)
#define TSI_GENCS_EOSF_VAL      ((TSI0_GENCS << 16) >> 31)
#define TSI_GENCS_EOSF_RST(n)   ((n) << 15)     // Resets the error flag // Valid values: {0,1}
#define TSI_GENCS_OUTRGF_VAL    ((TSI0_GENCS << 17) >> 31)
#define TSI_GENCS_OUTRGF_RST(n) ((n) << 14)     // Resets the error flag // Valid values: {0,1}
#define TSI_GENCS_EXTERF_VAL    ((TSI0_GENCS << 18) >> 31)
#define TSI_GENCS_EXTERF_RST(n) ((n) << 13)     // Resets the error flag // Valid values: {0,1}
#define TSI_GENCS_OVRF_VAL      ((TSI0_GENCS << 19) >> 31)
#define TSI_GENCS_OVRF_RST(n)   ((n) << 12)     // Resets the error flag // Valid values: {0,1}
#define TSI_GENCS_SCNIP_VAL     ((TSI0_GENCS << 22) >> 31)
#define TSI_GENCS_SWTS_VAL      ((TSI0_GENCS << 23) >> 31)
#define TSI_GENCS_TSIEN_VAL     ((TSI0_GENCS << 24) >> 31)
#define TSI_GENCS_TSIIE_VAL     ((TSI0_GENCS << 25) >> 31)
#define TSI_GENCS_ERIE_VAL      ((TSI0_GENCS << 26) >> 31)
#define TSI_GENCS_ESOR_VAL      ((TSI0_GENCS << 27) >> 31)
#define TSI_GENCS_ESOR(n)       ((n) << 4)      // Valid values: {0,1}
#define TSI_GENCS_STM_VAL       ((TSI0_GENCS << 30) >> 31)
#define TSI_GENCS_STM(n)        ((n) << 1)
#define TSI_GENCS_STPE_VAL      ((TSI0_GENCS << 31) >> 31)
#define TSI_GENCS_STPE(n)       ((n) /* << 0 */ ) // Valid values: {0,1}
#define TSI_SCANC_REFCHRG_VAL       ((TSI0_SCANC << 4)  >> 28)
#define TSI_SCANC_EXTCHRG_VAL       ((TSI0_SCANC << 12) >> 28)
#define TSI_SCANC_SMOD_VAL          ((TSI0_SCANC << 16) >> 24)
#define TSI_SCANC_AMCLKS_VAL        ((TSI0_SCANC << 27) >> 30)
#define TSI_SCANC_AMPSC_VAL         ((TSI0_SCANC << 29) >> 30)
#define TSI_PEN_LPSP_VAL        ((TSI0_PEN << 12) >> 28)
#define TSI_PEN_LPSP(n)         (((n) & 15) << 16)
/* Teensy:    16, ??, ??, ??, ??, 33, 17, 19, 18, 0,  1,  32, 25, 15, 22, 23 */
/* Chip:      35, 22, 23, 24, 25, 26, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45 */
/* Channel:   0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15 */
#define TSI_PEN_PEN15_VAL       ((TSI0_PEN << 16) >> 31)
#define TSI_PEN_PEN15_EN        (0x8000) // (1 << 15) // 23
#define PIN23_EN                (TSI_PEN_PEN15_EN)
#define TSI_PEN_PEN14_VAL       ((TSI0_PEN << 17) >> 31)
#define TSI_PEN_PEN14_EN        (0x4000) // (1 << 14) // 22
#define PIN22_EN                (TSI_PEN_PEN14_EN)
#define TSI_PEN_PEN13_VAL       ((TSI0_PEN << 18) >> 31)
#define TSI_PEN_PEN13_EN        (0x2000) // (1 << 13) // 15
#define PIN15_EN                (TSI_PEN_PEN13_EN)
#define TSI_PEN_PEN12_VAL       ((TSI0_PEN << 19) >> 31)
#define TSI_PEN_PEN12_EN        (0x1000) // (1 << 12) // 25
#define PIN25_EN                (TSI_PEN_PEN12_EN)
#define TSI_PEN_PEN11_VAL       ((TSI0_PEN << 20) >> 31)
#define TSI_PEN_PEN11_EN        (0x800) // (1 << 11)  // 32
#define PIN32_EN                (TSI_PEN_PEN11_EN)
#define TSI_PEN_PEN10_VAL       ((TSI0_PEN << 21) >> 31)
#define TSI_PEN_PEN10_EN        (0x400) // (1 << 10)  // 1
#define PIN1_EN                (TSI_PEN_PEN10_EN)
#define TSI_PEN_PEN9_VAL        ((TSI0_PEN << 22) >> 31)
#define TSI_PEN_PEN9_EN        (0x200) // (1 << 9)    // 0
#define PIN0_EN                (TSI_PEN_PEN9_EN)
#define TSI_PEN_PEN8_VAL        ((TSI0_PEN << 23) >> 31)
#define TSI_PEN_PEN8_EN        (0x100) // (1 << 8)    // 18
#define PIN18_EN                (TSI_PEN_PEN8_EN)
#define TSI_PEN_PEN7_VAL        ((TSI0_PEN << 24) >> 31)
#define TSI_PEN_PEN7_EN        (0x80) // (1 << 7)     // 19
#define PIN19_EN                (TSI_PEN_PEN7_EN)
#define TSI_PEN_PEN6_VAL        ((TSI0_PEN << 25) >> 31)
#define TSI_PEN_PEN6_EN        (0x40) // (1 << 6)     // 17
#define PIN17_EN                (TSI_PEN_PEN6_EN)
#define TSI_PEN_PEN5_VAL        ((TSI0_PEN << 26) >> 31)
#define TSI_PEN_PEN5_EN        (0x20) // (1 << 5)     // 33
#define PIN33_EN                (TSI_PEN_PEN4_EN)
#define TSI_PEN_PEN4_VAL        ((TSI0_PEN << 27) >> 31)
#define TSI_PEN_PEN4_EN        (0x10) // (1 << 4)     // ??
#define TSI_PEN_PEN3_VAL        ((TSI0_PEN << 28) >> 31)
#define TSI_PEN_PEN3_EN        (0x8) // (1 << 3)      // ??
#define TSI_PEN_PEN2_VAL        ((TSI0_PEN << 29) >> 31)
#define TSI_PEN_PEN2_EN        (0x4) // (1 << 2)      // ??
#define TSI_PEN_PEN1_VAL        ((TSI0_PEN << 30) >> 31)
#define TSI_PEN_PEN1_EN        (0x2) // (1 << 1)      // ??
#define TSI_PEN_PEN0_VAL        ((TSI0_PEN << 31) >> 31)
#define TSI_PEN_PEN0_EN        (0x1) // (1 << 0)      // 16
#define PIN16_EN                (TSI_PEN_PEN0_EN)
#define TSI_PEN_PEN_VALs        ((TSI0_PEN << 16) >> 16)
#define TSI_WUCNTR_VAL              ((TSI0_WUCNTR << 16) >> 16)
#define TSI0_CNTR1_CTN_VAL      ((TSI0_CNTR1        ) >> 16)
#define TSI0_CNTR1_CTN1_VAL     ((TSI0_CNTR1   << 16) >> 16) // 16
#define TSI0_CNTR3_CTN_VAL      ((TSI0_CNTR3        ) >> 16)
#define TSI0_CNTR3_CTN1_VAL     ((TSI0_CNTR3   << 16) >> 16)
#define TSI0_CNTR5_CTN_VAL      ((TSI0_CNTR5        ) >> 16) // 33
#define TSI0_CNTR5_CTN1_VAL     ((TSI0_CNTR5   << 16) >> 16)
#define TSI0_CNTR7_CTN_VAL      ((TSI0_CNTR7        ) >> 16) // 19
#define TSI0_CNTR7_CTN1_VAL     ((TSI0_CNTR7   << 16) >> 16) // 17
#define TSI0_CNTR9_CTN_VAL      ((TSI0_CNTR9        ) >> 16) // 0
#define TSI0_CNTR9_CTN1_VAL     ((TSI0_CNTR9   << 16) >> 16) // 18
#define TSI0_CNTR11_CTN_VAL     ((TSI0_CNTR11      ) >> 16) // 32
#define TSI0_CNTR11_CTN1_VAL    ((TSI0_CNTR11 << 16) >> 16) // 1
#define TSI0_CNTR13_CTN_VAL     ((TSI0_CNTR13     ) >> 16) // 15
#define TSI0_CNTR13_CTN1_VAL    ((TSI0_CNTR13 << 16) >> 16) // 25
#define TSI0_CNTR15_CTN_VAL     ((TSI0_CNTR15      ) >> 16) // 23
#define TSI0_CNTR15_CTN1_VAL    ((TSI0_CNTR15 << 16) >> 16) // 22
#define TSI_THRESHOLD_LTHH_VAL          ((TSI0_THRESHOLD      ) >> 16)
#define TSI_THRESHOLD_LTHH(n)           (((n) & 0xFFFF) << 16) // Valid values: {0,65535}
#define TSI_THRESHOLD_HTHH_VAL          ((TSI0_THRESHOLD << 16) >> 16)
#define TSI_THRESHOLD_HTHH(n)           ((n) & 0xFFFF) // Valid values: {0,65535}

#define PIN33_VAL (TSI0_CNTR5_CTN_VAL)
#define PIN32_VAL (TSI0_CNTR11_CTN_VAL)
#define PIN25_VAL (TSI0_CNTR13_CTN1_VAL)
#define PIN23_VAL (TSI0_CNTR15_CTN_VAL)
#define PIN22_VAL (TSI0_CNTR15_CTN1_VAL)
#define PIN19_VAL (TSI0_CNTR7_CTN_VAL)
#define PIN18_VAL (TSI0_CNTR9_CTN1_VAL)
#define PIN17_VAL (TSI0_CNTR7_CTN1_VAL)
#define PIN16_VAL (TSI0_CNTR1_CTN1_VAL)
#define PIN15_VAL (TSI0_CNTR13_CTN_VAL)
#define PIN1_VAL (TSI0_CNTR11_CTN1_VAL)
#define PIN0_VAL (TSI0_CNTR9_CTN_VAL)
#endif

#if (!defined(TSI_PERIODIC))
#endif

#if (!defined(TSI_SOFTWARE))
#endif

#define noop {asm volatile ("nop");}
void wait(uint8_t num_adds_to_do) {
    __disable_irq();
    uint32_t counter;
    for (counter = 0; counter < num_adds_to_do; ++counter) {
        noop;
    }
    __enable_irq();
}

void tsi_stop(void) {
    //TSI0_GENCS = TSI0_GENCS & (~(TSI_GENCS_TSIEN | TSI_GENCS_TSIIE));
    TSI0_GENCS &= ~TSI_GENCS_TSIEN; // Turn TSI module off
    //wait(79);
}

void tsi_start(void) {
    *portConfigRegister(0) = PORT_PCR_MUX(0); // Need to figure out what this line does
    SIM_SCGC5 |= SIM_SCGC5_TSI;               // And this one, too
    //TSI0_GENCS = TSI0_GENCS | TSI_GENCS_TSIEN;
    TSI0_GENCS |= TSI_GENCS_TSIEN; // Enables TSI module
    wait(79);
}

#define tsi_start_scan {TSI0_GENCS |= TSI_GENCS_SWTS; wait(79);}

/* NOTE:
 * - The length of buff needs to be set based on the number of pins
 *   enabled, for space efficiency. Is it possible to do this without
 *   malloc() for the non-defines version?
 * - tsi_isr() needs to have a very efficient way of deciding what it
 *   needs to do:
 * - - If the GENCS[EOSF] flag is set, and that's it, then it needs to
 *     copy the result registers to buff, preferably with a Direct
 *     Memory Access (DMA)
 * - - If GENCS[EXTERF] is set, regardless of other flags, the current
 *     scan needs to be cut short (probably by disabling the TSI module)
 *     and a new scan needs to be started, in the same mode that the
 *     scan was started in.
 * ^--- Should this be the behaviour in the SOFTWARE_TRIGGER mode, or
 *      should error interrupts be disabled, and the scan let finish,
 *      regardless of what potential errors there may be?
 * - - Interrupts caused only by GENCS[OVRF] should be ignored.
 */

uint16_t buff[] = {1, // 0
                   1, // 1
                   1,
                   1,
                   1,
                   1,
                   1,
                   1,
                   1,
                   1,
                   1,
                   1,
                   1,
                   1,
                   1,
                   1, // 15
                   1, // 16
                   1, // 17
                   1, // 18
                   1, // 19
                   1,
                   1,
                   1, // 22
                   1, // 23
                   1,
                   1, // 25
                   1,
                   1,
                   1,
                   1,
                   1,
                   1,
                   1, // 32
                   1 // 33
                   };

uint32_t default_pin2cntr_val = 1;
/* This array holds pointers to the TSI0_CNTRn registers at the index corresponding to the Tensy pin for which they hold a capacitance value.
 * That is to say, at index 23 is the location in the chip's memory which holds Teensy pin 23's current capacitance value
 */
volatile uint32_t* pin2cntr[] = {(&TSI0_CNTR1 + 9), // 0
                        (&TSI0_CNTR1 + 10), // 1
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        (&TSI0_CNTR1 + 13), // 15
                        (&TSI0_CNTR1 + 0), // 16
                        (&TSI0_CNTR1 + 10), // 17
                        (&TSI0_CNTR1 + 8), // 18
                        (&TSI0_CNTR1 + 7), // 19
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        (&TSI0_CNTR1 + 14), // 22
                        (&TSI0_CNTR1 + 15), // 23
                        &default_pin2cntr_val,
                        (&TSI0_CNTR1 + 12), // 25
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        &default_pin2cntr_val,
                        (&TSI0_CNTR1 + 11), // 32
                        (&TSI0_CNTR1 + 5), // 33
                        };

/* Teensy:    33, 32, 25, 23, 22, 19, 18, 17, 16, 15, 1,  0 */
/* Channel:   5,  11, 12, 15, 14, 7,  8,  6,  0,  13, 10, 9 */

/* NOTE: Make an array of pointers to the result registers, and use that in both copy_to_buff, and in place of pin2buff[] */

void copy_to_buff(void) {
    /* Copy pin values directly from the registers into the buffer array */
    uint32_t i;
    for (i = 0; i < 33; ++i) {
        buff[i] = (*pin2cntr[i]);
    }
    /* NOTE: Skip the inefficient copying of values that don't need to
     * be copied---like index 27---and make both arrays 16 elements long
     */
}

void restart_tsi(void) {
    TSI0_GENCS &= (~TSI_GENCS_TSIEN); // Disable TSI module
    wait(7); // Wait for the module to be disabled
    TSI0_GENCS |= (TSI_GENCS_SWTS | TSI_GENCS_TSIEN); // Turn the module back on, and at the same time trigger a software scan; if the module is in periodic mode, this does nothing
    /* NOTE: Should the above line trigger a scan in SOFTWARE_TRIGGER
     * mode, or should it just let things continue without even
     * restarting the module?
     */
}

void do_nothing(void) {return;}

void (*(tsi_isr_jumptable[]))(void) = {*do_nothing, // Default: no flags set, but ISR is called???
                                       *copy_to_buff, // Just the End-of-Scan flag is set, so do the copy
                                       *restart_tsi, // Just the error flag is set, so restart the TSI module
                                       *restart_tsi // Restart the TSI module even if both flags are set, as it's pointless to copy at the end of a scan if there's an error
                                       }; // An array of pointers to functions taking void and returning void

void tsi0_isr(void) {
    /* This is the function that is run every time an interrupt is
     * triggered by the TSI module, regarless of what kind of interrupt
     * it was.
     * 
     * This function tries to efficiently decide what to do, and uses a
     * jump table to efficiently call a function to do that.
     */
    
    (*tsi_isr_jumptable[(TSI_GENCS_EOSF_VAL |
                        (TSI_GENCS_EXTERF_VAL << 1))])();
}

/* Teensy:                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, ... */
//uint8_t valid_pin_numbers[] = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1};
uint16_t touchVal(uint8_t pin) {
    //if ((pin < 34) && (valid_pin_numbers[pin])) { // Valid pin checking unnecessary as buff has 34 indices currently
    if (pin < 34) {
        return buff[pin];
    } else {
        return 0;
    }
}


typedef enum SETUP_ERROR_CODES {NORMAL,
                                OUT_OF_RANGE_VALUE,
                                OUT_OF_RANGE_VALUE_NSCN,
                                OUT_OF_RANGE_VALUE_PS,
                                OUT_OF_RANGE_VALUE_REFCHRG,
                                OUT_OF_RANGE_VALUE_EXTCHRG,
                                OUT_OF_RANGE_VALUE_AMCLKS,
                                OUT_OF_RANGE_VALUE_SMOD,
                                OUT_OF_RANGE_VALUE_AMPSC
} SETUP_ERROR_CODE;


#if defined(TEENSYTOUCH_DEFINES)
SETUP_ERROR_CODE setup_tsi(
    (uint16_t) pen_en, /* This is set up by OR-ing (|) together the
                        * PIN0_EN - PIN23_EN defines provided, and
                        * casting as uint16_t
                        */
    uint8_t number_of_scans, /* Defines the number of scans the TSI
                              * module should perform on each electrode
                              */
    uint8_t prescaler, /* Defines the value by which the TSI module's
                        * reference clock's frequency will be divided,
                        * as compared to the system clock
                        */
    ) {
    /* TSI module needs to be stopped/disabled in order to change some of its register values */
    tsi_stop();
    /* Next all flag bits are reset by writing 1 to them */
    TSI0_GENCS |= TSI_GENCS_EOSF_RST(1);   // Valid values: {0,1}
    TSI0_GENCS |= TSI_GENCS_OUTRGF_RST(1); // Valid values: {0,1}
    TSI0_GENCS |= TSI_GENCS_EXTERF_RST(1); // Valid values: {0,1}
    TSI0_GENCS |= TSI_GENCS_OVRF_RST(1);   // Valid values: {0,1}
    /* Haven't set up low-power modes yet, so this register bit is kept
     * sensible for non-low-power moder
     */
    TSI0_GENCS |= TSI_GENCS_ESOR(1);       // Valid values: {0,1}
    
    
    
}

#else
typedef enum ACTIVE_MODE_CLOCK_SOURCES {LPOSCCLK,  /* 1 kHz LPO clock, Low-Power OSC clock, or Bus clock */
                                MCGIRCLK,  /* Multipurpose Clock Generator Internal Reference Clock */
                                OSCERCLK  /* Clock provided by OSC module for peripheral use */
                                } ACTIVE_MODE_CLOCK_SOURCE;
typedef enum TSI_READ_MODES {HARDWARE_POLL,
                             SOFTWARE_POLL,
                             SOFTWARE_TRIGGER
                             } TSI_READ_MODE;

SETUP_ERROR_CODE setup_tsi(
    uint16_t pen_en, /* This is set up by OR-ing (|) together the
                        * PIN0_EN - PIN23_EN defines provided, and
                        * casting as uint16_t
                        */
    uint8_t number_of_scans, /* Defines the number of scans the TSI
                              * module should perform on each electrode.
                              * Valid value: 1 - 32
                              */
    uint8_t prescaler, /* Defines the value by which the TSI module's
                        * reference clock's frequency will be divided,
                        * as compared to the system clock.
                        * Valid values: 1 - 128, by powers of 2
                        *   (e.g. 2^(0), 2^(1), 2^(2), ...)
                        */
    uint8_t reference_current, /* Defines the reference oscillator
                                * charging current, which when raised,
                                * makes the electrode charge faster, but
                                * also makes it less sensitive to finer
                                * differences in capacitance.
                                * Valid values: Even numbers 2 - 32
                                *   (e.g. 2, 4, 6, ...) in microAmps
                                */
    uint8_t electrode_current, /* Defines how much current the current
                                * source provides to charge the
                                * oscillator conneced to the
                                * electrode/pin.
                                * Valid values: Even numbers 2 - 32
                                *   (e.g. 2, 4, 6, ...) in microAmps
                                */
    ACTIVE_MODE_CLOCK_SOURCE am_clock_source, /* Sets the active mode
                                               * clock source, which
                                               * doesn't seem to have a
                                               * large affect on the
                                               * results of the
                                               * measurement at the
                                               * moment. More testing is
                                               * needed.
                                               */
    uint8_t scan_modulus, /* Determines the interval between scan
                           * triggers in active/polling mode
                           * NOTE: unclear how specifically this works
                           */
    uint8_t am_prescaler, /* Same as the prescaler, except for the
                           * am_clock_cource clock selection
                           */
    /* Instead of picking the software/hardware triggering, it's set up by picking the mode in the last argument */
    TSI_READ_MODE tsi_read_mode) {
    /* TSI module needs to be stopped/disabled in order to change some of its register values */
    tsi_stop();
    /* Next all flag bits are reset by writing 1 to them */
    TSI0_GENCS |= TSI_GENCS_EOSF_RST(1);   // Valid values: {0,1}
    TSI0_GENCS |= TSI_GENCS_OUTRGF_RST(1); // Valid values: {0,1}
    TSI0_GENCS |= TSI_GENCS_EXTERF_RST(1); // Valid values: {0,1}
    TSI0_GENCS |= TSI_GENCS_OVRF_RST(1);   // Valid values: {0,1}
    /* Haven't set up low-power modes yet, so these register bits are
     * kept sensible for non-low-power mode
     */
    /* End-of-scan interrupt instead of out-of-range */
    TSI0_GENCS |= TSI_GENCS_ESOR(1);       // Valid values: {0,1}
    /* Stop TSI module in low-power modes instead of running it in all */
    TSI0_GENCS |= TSI_GENCS_STPE(1);       // Valid values: {0,1}
    
    
    /* Checking and then using passed arguments one by one */
    TSI0_PEN |= pen_en; // However it was OR-ed together is how it's going to look in the register
    
    if ((number_of_scans > 32) || (number_of_scans < 1)) {
        return OUT_OF_RANGE_VALUE_NSCN;
    } else {
        TSI0_GENCS |= TSI_GENCS_NSCN(number_of_scans - 1); // Subtract 1 so that it falls in the valid range of 00000-11111
    }
    
    uint32_t valid_prescaler = 0;
    uint32_t i;
    for (i = 0; i < 7; ++i) {
        if (prescaler == pow(2,i)) {
            valid_prescaler = 1;
            break;
        }
    }
    
    if (valid_prescaler) {
        //uint8_t prescaler_value = (uint8_t)(log(prescaler)/log(2)); // Takes the log to base 2 of the number, so that we get 0-7 again
        //TSI0_GENCS |= TSI_GENCS_PS(prescaler_value);
        TSI0_GENCS |= TSI_GENCS_PS((uint8_t)(log(prescaler)/log(2)));
    } else {
        return OUT_OF_RANGE_VALUE_PS;
    }
    
    if ((reference_current < 33) && ((reference_current % 2) == 0)) {
        ///* Shift back to 0 - 15 scale */
        //uint8_t reference_current_shifted = (reference_current - 2)/2; // 2*(0 through 15) + 2 == reference current in microAmps
        ///*                                        reference current in register---^ */
        TSI0_SCANC |= TSI_SCANC_REFCHRG((reference_current - 2)/2);
    } else {
        return OUT_OF_RANGE_VALUE_REFCHRG;
    }
    
    if ((electrode_current < 33) && ((electrode_current % 2) == 0)) {
        ///* Shift back to 0 - 15 scale */
        //uint8_t electrode_current_shifted = (electrode_ecurrent - 2)/2; // 2*(0 through 15) + 2 == electrode current in microAmps
        ///*                                        electrode current in register---^ */
        TSI0_SCANC |= TSI_SCANC_EXTCHRG((electrode_current - 2)/2);
    } else {
        return OUT_OF_RANGE_VALUE_EXTCHRG;
    }
    
    switch (am_clock_source) {
        case LPOSCCLK: TSI0_SCANC |= TSI_SCANC_AMCLKS(0);
        case MCGIRCLK: TSI0_SCANC |= TSI_SCANC_AMCLKS(1);
        case OSCERCLK: TSI0_SCANC |= TSI_SCANC_AMCLKS(2);
        default: return OUT_OF_RANGE_VALUE_AMCLKS;
    }
    
    /* The type definition for SMOD already limits what values can be
     * passed to within the scope of accepted values
     */
    TSI0_SCANC |= TSI_SCANC_SMOD(scan_modulus);
    
    uint32_t valid_am_prescaler = 0;
    //uint32_t i; // Already defined
    for (i = 0; i < 7 /* Largest it can be is 128 == 2^7 */; ++i) {
        if (am_prescaler == pow(2,i)) {
            valid_am_prescaler = 1;
            break;
        }
    }
    
    if (valid_am_prescaler) {
        //uint8_t am_prescaler_value = (uint8_t)(log(am_prescaler)/log(2)); // Takes the log to base 2 of the number, so that we get 0-7 again
        //TSI0_GENCS |= TSI_GENCS_PS(am_prescaler_value);
        TSI0_SCANC |= TSI_SCANC_AMPSC((uint8_t)(log(am_prescaler)/log(2)));
    } else {
        return OUT_OF_RANGE_VALUE_AMPSC;
    }
    
    switch (tsi_read_mode) {
        case HARDWARE_POLL: {
            /* This mode sets up the TSI module for optimal scanning in
             * the background, interrupting only to cope with errors,
             * and to copy to the buffer.
             * 
             * NOTE: Set SCANC[SMOD] and SCANC[AMCLKS] based on testing
             * and number of pins enabled
             * 
             * Test if a pin is enabled by looking at the data pointed
             * to by a specific bit's memory register in the PEN register
             */
            TSI0_GENCS |= TSI_GENCS_STM(1); // Periodical scan
            /* Enable interrupts */
            TSI0_GENCS |= TSI_GENCS_TSIIE; // Enable TSI interrupt module
            TSI0_GENCS |= TSI_GENCS_ERIE;  // Enable error interupts
            
            break;
        }
        case SOFTWARE_POLL: {
            /* This won't work like this, as this would need to tell tsi0_isr() that it needs to resart the scan at the end of each scan */
            
            break;
        }
        case SOFTWARE_TRIGGER: {
            
            break;
        }
    }
    
    NVIC_ENABLE_IRQ(IRQ_TSI); // Enable all interrupts to fire off interrupt service routines (ISRs)
    tsi_start(); // Start the TSI module
    return NORMAL;
}
#endif

#if defined(TEENSYTOUCH_SERIAL_DEBUG)

#define Sp(a)   (Serial.print(a))
#define Spn(a)  (Serial.println(a))
#define Spnb(a) (Serial.println(a,BIN))
#define nl      (Serial.print("\n"))
#define tab     (Serial.print("\t"))

void print_touch_register_values(void) {
    // Teensy: 16, ??, ??, ??, ??, 33, 17, 19, 18, 0, 1,  32, 25, 15, 22, 23
    // Chip:   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
    
    // Teensy: 33, 32, 25, 23, 22, 19, 18, 17, 16, 15, 1,  0
    // Chip:   5,  11, 12, 15, 14, 7,  8,  6,  0,  13, 10, 9
    Sp("pin 33: ");Spnb(TSI0_CNTR5_CTN_VAL);
    Sp("pin 32: ");Spnb(TSI0_CNTR11_CTN_VAL);
    Sp("pin 25: ");Spnb(TSI0_CNTR13_CTN1_VAL);
    Sp("pin 23: ");Spn(TSI0_CNTR15_CTN_VAL);
    Sp("pin 22: ");Spn(TSI0_CNTR15_CTN1_VAL);
    Sp("pin 19: ");Spn(TSI0_CNTR7_CTN_VAL);
    Sp("pin 18: ");Spn(TSI0_CNTR9_CTN1_VAL);
    Sp("pin 17: ");Spn(TSI0_CNTR7_CTN1_VAL);
    Sp("pin 16: ");Spn(TSI0_CNTR1_CTN1_VAL);
    Sp("pin 15: ");Spn(TSI0_CNTR13_CTN_VAL);
    Sp("pin 1:  ");Spn(TSI0_CNTR11_CTN1_VAL);
    Sp("pin 0:  ");Spn(TSI0_CNTR9_CTN_VAL);
}

typedef enum PRINT_MODES {ALL_REGISTERS,
                          CONCAT_ALL,
                          CONCAT_PINS,
                          JUST_PINS,
                          JUST_COUNTERS} PRINT_MODE;

void print_tsi_register_values(PRINT_MODE print_mode) {
    switch (print_mode) {
        case ALL_REGISTERS: {
            /* Print out all TSI-related port values in detailed form */
            nl;
            Spn("TSI port values");
            nl;
            Sp("General Control and Status Register (TSI0_GENCS): ");Spnb(TSI0_GENCS);
            Sp("    Low-Power Mode Clock Source Selection (TSI_GENCS_LPCLKS):        ");Spnb(TSI_GENCS_LPCLKS_VAL);
            Sp("    Low-Power Mode Scan Interval (TSI_GENCS_LPSCNITV):               ");Spnb(TSI_GENCS_LPSCNITV_VAL);
            Sp("    Number of Consecutive Scane Per Electrode (TSI_GENCS_NSCN):      ");Spnb(TSI_GENCS_NSCN_VAL);
            Sp("    Electrode Oscillator Prescaler (TSI_GENCS_PS):                   ");Spnb(TSI_GENCS_PS_VAL);
            Sp("    End of Scan Flag (TSI_GENCS_EOSF):                               ");Spnb(TSI_GENCS_EOSF_VAL);
            Sp("    Out of Range Flag (TSI_GENCS_OUTRGF):                            ");Spnb(TSI_GENCS_OUTRGF_VAL);
            Sp("    External Electrode Error Occured (TSI_GENCS_EXTERF):             ");Spnb(TSI_GENCS_EXTERF_VAL);
            Sp("    Overrun Error Flag (TSI_GENCS_OVRF):                             ");Spnb(TSI_GENCS_OVRF_VAL);
            Sp("    Scan In Progress Status (TSI_GENCS_SCNIP):                       ");Spnb(TSI_GENCS_SCNIP_VAL);
            Sp("    Software Trigger Start (TSI_GENCS_SWTS):                         ");Spnb(TSI_GENCS_SWTS_VAL);
            Sp("    Touch Sensing Input Module Enable (TSI_GENCS_TSIEN):             ");Spnb(TSI_GENCS_TSIEN_VAL);
            Sp("    Touch Sensing Input Interrupt Module Enable (TSI_GENCS_TSIIE):   ");Spnb(TSI_GENCS_TSIIE_VAL);
            Sp("    Error Interrupt Enable (TSI_GENCS_ERIE):                         ");Spnb(TSI_GENCS_ERIE_VAL);
            Sp("    End-Of-Scan or Out-Of-Range Interrupt Select (TSI_GENCS_ESOR):   ");Spnb(TSI_GENCS_ESOR_VAL);
            Sp("    Scan Trigger Mode (TSI_GENCS_STM):                               ");Spnb(TSI_GENCS_STM_VAL);
            Sp("    TSI STOP Enable while in low-power modes (TSI_GENCS_STPE):       ");Spnb(TSI_GENCS_STPE_VAL);
            Spn("SCAN Control Register (TSI0_SCANC): ");Spnb(TSI0_SCANC);
            Sp("    Ref OSC Charge Current Select (TSI_SCANC_REFCHRG):               ");Spnb(TSI_SCANC_REFCHRG_VAL);
            Sp("    External OSC Charge Current Select (TSI_SCANC_EXTCHRG):          ");Spnb(TSI_SCANC_EXTCHRG_VAL);
            Sp("    Scan Module [Modulus] (TSI_SCANC_SMOD):                          ");Spnb(TSI_SCANC_SMOD_VAL);
            Sp("    Active Mode Clock Source (TSI_SCANC_AMCLKS):                     ");Spnb(TSI_SCANC_AMCLKS_VAL);
            Sp("    Active Mode Prescaler (TSI_SCANC_AMPSC):                         ");Spnb(TSI_SCANC_AMPSC_VAL);
            Spn("Pin Enable Register (TSI0_PEN): ");Spnb(TSI0_PEN);
            Sp("    Low-Power Scan Pin (TSI_PEN_LPSP_VAL):                           ");Spnb(TSI_PEN_LPSP_VAL);
            Sp("    Touch Sensing Input Pin Enable Register 15 (TSI_PEN_PEN15):      ");Spnb(TSI_PEN_PEN15_VAL);
            Sp("    Touch Sensing Input Pin Enable Register 14 (TSI_PEN_PEN14):      ");Spnb(TSI_PEN_PEN14_VAL);
            Sp("    Touch Sensing Input Pin Enable Register 13 (TSI_PEN_PEN13):      ");Spnb(TSI_PEN_PEN13_VAL);
            Sp("    Touch Sensing Input Pin Enable Register 12 (TSI_PEN_PEN12):      ");Spnb(TSI_PEN_PEN12_VAL);
            Sp("    Touch Sensing Input Pin Enable Register 11 (TSI_PEN_PEN11):      ");Spnb(TSI_PEN_PEN11_VAL);
            Sp("    Touch Sensing Input Pin Enable Register 10 (TSI_PEN_PEN10):      ");Spnb(TSI_PEN_PEN10_VAL);
            Sp("    Touch Sensing Input Pin Enable Register 9 (TSI_PEN_PEN9):        ");Spnb(TSI_PEN_PEN9_VAL);
            Sp("    Touch Sensing Input Pin Enable Register 8 (TSI_PEN_PEN8):        ");Spnb(TSI_PEN_PEN8_VAL);
            Sp("    Touch Sensing Input Pin Enable Register 7 (TSI_PEN_PEN7):        ");Spnb(TSI_PEN_PEN7_VAL);
            Sp("    Touch Sensing Input Pin Enable Register 6 (TSI_PEN_PEN6):        ");Spnb(TSI_PEN_PEN6_VAL);
            Sp("    Touch Sensing Input Pin Enable Register 5 (TSI_PEN_PEN5):        ");Spnb(TSI_PEN_PEN5_VAL);
            Sp("    Touch Sensing Input Pin Enable Register 4 (TSI_PEN_PEN4):        ");Spnb(TSI_PEN_PEN4_VAL);
            Sp("    Touch Sensing Input Pin Enable Register 3 (TSI_PEN_PEN3):        ");Spnb(TSI_PEN_PEN3_VAL);
            Sp("    Touch Sensing Input Pin Enable Register 2 (TSI_PEN_PEN2):        ");Spnb(TSI_PEN_PEN2_VAL);
            Sp("    Touch Sensing Input Pin Enable Register 1 (TSI_PEN_PEN1):        ");Spnb(TSI_PEN_PEN1_VAL);
            Sp("    Touch Sensing Input Pin Enable Register 0 (TSI_PEN_PEN0):        ");Spnb(TSI_PEN_PEN0_VAL);
            Spn("Wake-Up Channel Counter Register (TSI0_WUCNTR): ");Spnb(TSI0_WUCNTR);
            Sp("    Touch Sensing Wake-Up Channel 16-bit Counter Value (TSI_WUCNTR): ");Spnb(TSI_WUCNTR_VAL);
            Spn("Counter Register [15] (TSI0_CNTR15) :");Spnb(TSI0_CNTR1);
            Sp("    Touch Sensing Channel 1 16-bit Counter Value (pin 23):           ");Spn(TSI0_CNTR15_CTN_VAL);
            Sp("    Touch Sensing Channel 0 16-bit Counter Value (pin 22):           ");Spn(TSI0_CNTR15_CTN1_VAL);
            Spn("Counter Register [13] (TSI0_CNTR13): ");Spnb(TSI0_CNTR3);
            Sp("    Touch Sensing Channel 1 16-bit Counter Value (pin 15):           ");Spnb(TSI0_CNTR13_CTN_VAL);
            Sp("    Touch Sensing Channel 0 16-bit Counter Value (pin 25):           ");Spnb(TSI0_CNTR13_CTN1_VAL);
            Spn("Counter Register [11] (TSI0_CNTR11): ");Spnb(TSI0_CNTR5);
            Sp("    Touch Sensing Channel 1 16-bit Counter Value (pin 32):           ");Spnb(TSI0_CNTR11_CTN_VAL);
            Sp("    Touch Sensing Channel 0 16-bit Counter Value (pin 1):            ");Spnb(TSI0_CNTR11_CTN1_VAL);
            Spn("Counter Register [9] (TSI0_CNTR9): ");Spnb(TSI0_CNTR7);
            Sp("    Touch Sensing Channel 1 16-bit Counter Value (pin 0):            ");Spnb(TSI0_CNTR9_CTN_VAL);
            Sp("    Touch Sensing Channel 0 16-bit Counter Value (pin 18):           ");Spnb(TSI0_CNTR9_CTN1_VAL);
            Spn("Counter Register [7] (TSI0_CNTR7): ");Spnb(TSI0_CNTR9);
            Sp("    Touch Sensing Channel 1 16-bit Counter Value (pin 19):           ");Spnb(TSI0_CNTR7_CTN_VAL);
            Sp("    Touch Sensing Channel 0 16-bit Counter Value (pin 17):           ");Spnb(TSI0_CNTR7_CTN1_VAL);
            Spn("Counter Register [5] (TSI0_CNTR5): ");Spnb(TSI0_CNTR11);
            Sp("    Touch Sensing Channel 1 16-bit Counter Value (pin 33):           ");Spnb(TSI0_CNTR5_CTN_VAL);
            Sp("    Touch Sensing Channel 0 16-bit Counter Value (pin ??):           ");Spnb(TSI0_CNTR5_CTN1_VAL);
            Spn("Counter Register [3] (TSI0_CNTR3): ");Spnb(TSI0_CNTR13);
            Sp("    Touch Sensing Channel 1 16-bit Counter Value (pin ??):           ");Spnb(TSI0_CNTR3_CTN_VAL);
            Sp("    Touch Sensing Channel 0 16-bit Counter Value (pin ??):           ");Spnb(TSI0_CNTR3_CTN1_VAL);
            Spn("Counter Register [1] (TSI0_CNTR1): ");Spnb(TSI0_CNTR15);
            Sp("    Touch Sensing Channel 1 16-bit Counter Value (pin ??):           ");Spnb(TSI0_CNTR1_CTN_VAL);
            Sp("    Touch Sensing Channel 0 16-bit Counter Value (pin 16):           ");Spnb(TSI0_CNTR1_CTN1_VAL);
            Spn("Low-Power Channel Threshold Register (TSI0_THRESHOLD): ");Spnb(TSI0_THRESHOLD);
            Sp("    Touch Sensing Channel Low Threshold Value:                       ");Spnb(TSI_THRESHOLD_LTHH_VAL);
            Sp("    Touch Sensing Channel High Threshold Value:                      ");Spnb(TSI_THRESHOLD_HTHH_VAL);
            nl;
        }
        case CONCAT_ALL: {
            /* Print out all TSI-related port values in compact form */
            nl;
            Spn("TSI port values");
            nl;
            Spnb(TSI0_GENCS);
            Spnb(TSI0_SCANC);
            Spnb(TSI0_PEN);
            Spnb(TSI0_WUCNTR);
            Spnb(TSI0_CNTR1);
            Spnb(TSI0_CNTR3);
            Spnb(TSI0_CNTR5);
            Spnb(TSI0_CNTR7);
            Spnb(TSI0_CNTR9);
            Spnb(TSI0_CNTR11);
            Spnb(TSI0_CNTR13);
            Spnb(TSI0_CNTR15);
            Spnb(TSI0_THRESHOLD);
            nl;
        }
        case CONCAT_PINS: {
            /* Print out all TSI-related port values with pins concatenated */
            nl;
            Spn("TSI port values");
            nl;
            Sp("General Control and Status Register (TSI0_GENCS): ");Spnb(TSI0_GENCS);
            Sp("    Low-Power Mode Clock Source Selection (TSI_GENCS_LPCLKS):        ");Spnb(TSI_GENCS_LPCLKS_VAL);
            Sp("    Low-Power Mode Scan Interval (TSI_GENCS_LPSCNITV):               ");Spnb(TSI_GENCS_LPSCNITV_VAL);
            Sp("    Number of Consecutive Scane Per Electrode (TSI_GENCS_NSCN):      ");Spnb(TSI_GENCS_NSCN_VAL);
            Sp("    Electrode Oscillator Prescaler (TSI_GENCS_PS):                   ");Spnb(TSI_GENCS_PS_VAL);
            Sp("    End of Scan Flag (TSI_GENCS_EOSF):                               ");Spnb(TSI_GENCS_EOSF_VAL);
            Sp("    Out of Range Flag (TSI_GENCS_OUTRGF):                            ");Spnb(TSI_GENCS_OUTRGF_VAL);
            Sp("    External Electrode Error Occured (TSI_GENCS_EXTERF):             ");Spnb(TSI_GENCS_EXTERF_VAL);
            Sp("    Overrun Error Flag (TSI_GENCS_OVRF):                             ");Spnb(TSI_GENCS_OVRF_VAL);
            Sp("    Scan In Progress Status (TSI_GENCS_SCNIP):                       ");Spnb(TSI_GENCS_SCNIP_VAL);
            Sp("    Software Trigger Start (TSI_GENCS_SWTS):                         ");Spnb(TSI_GENCS_SWTS_VAL);
            Sp("    Touch Sensing Input Module Enable (TSI_GENCS_TSIEN):             ");Spnb(TSI_GENCS_TSIEN_VAL);
            Sp("    Touch Sensing Input Interrupt Module Enable (TSI_GENCS_TSIIE):   ");Spnb(TSI_GENCS_TSIIE_VAL);
            Sp("    Error Interrupt Enable (TSI_GENCS_ERIE):                         ");Spnb(TSI_GENCS_ERIE_VAL);
            Sp("    End-Of-Scan or Out-Of-Range Interrupt Select (TSI_GENCS_ESOR):   ");Spnb(TSI_GENCS_ESOR_VAL);
            Sp("    Scan Trigger Mode (TSI_GENCS_STM):                               ");Spnb(TSI_GENCS_STM_VAL);
            Sp("    TSI STOP Enable while in low-power modes (TSI_GENCS_STPE):       ");Spnb(TSI_GENCS_STPE_VAL);
            Spn("SCAN Control Register (TSI0_SCANC): ");Spnb(TSI0_SCANC);
            Sp("    Ref OSC Charge Current Select (TSI_SCANC_REFCHRG):               ");Spnb(TSI_SCANC_REFCHRG_VAL);
            Sp("    External OSC Charge Current Select (TSI_SCANC_EXTCHRG):          ");Spnb(TSI_SCANC_EXTCHRG_VAL);
            Sp("    Scan Module [Modulus] (TSI_SCANC_SMOD):                          ");Spnb(TSI_SCANC_SMOD_VAL);
            Sp("    Active Mode Clock Source (TSI_SCANC_AMCLKS):                     ");Spnb(TSI_SCANC_AMCLKS_VAL);
            Sp("    Active Mode Prescaler (TSI_SCANC_AMPSC):                         ");Spnb(TSI_SCANC_AMPSC_VAL);
            Spn("Pin Enable Register (TSI0_PEN): ");Spnb(TSI0_PEN);
            Sp("    Low-Power Scan Pin (TSI_PEN_LPSP_VAL):                           ");Spnb(TSI_PEN_LPSP_VAL);
            Sp("    Values of Pin Enable registers:                                  ");Spnb(TSI_PEN_PEN_VALs);
            Spn("Wake-Up Channel Counter Register (TSI0_WUCNTR): ");Spnb(TSI0_WUCNTR);
            Sp("    Touch Sensing Wake-Up Channel 16-bit Counter Value (TSI_WUCNTR): ");Spnb(TSI_WUCNTR_VAL);
            Spn("Counter Register [15] (TSI0_CNTR15) :");Spnb(TSI0_CNTR1);
            Spn("Counter Register [13] (TSI0_CNTR13): ");Spnb(TSI0_CNTR3);
            Spn("Counter Register [11] (TSI0_CNTR11): ");Spnb(TSI0_CNTR5);
            Spn("Counter Register [9] (TSI0_CNTR9): ");Spnb(TSI0_CNTR7);
            Spn("Counter Register [7] (TSI0_CNTR7): ");Spnb(TSI0_CNTR9);
            Spn("Counter Register [5] (TSI0_CNTR5): ");Spnb(TSI0_CNTR11);
            Spn("Counter Register [3] (TSI0_CNTR3): ");Spnb(TSI0_CNTR13);
            Spn("Counter Register [1] (TSI0_CNTR1): ");Spnb(TSI0_CNTR15);
            Spn("Low-Power Channel Threshold Register (TSI0_THRESHOLD): ");Spnb(TSI0_THRESHOLD);
            Sp("    Touch Sensing Channel Low Threshold Value:                       ");Spnb(TSI_THRESHOLD_LTHH_VAL);
            Sp("    Touch Sensing Channel High Threshold Value:                      ");Spnb(TSI_THRESHOLD_HTHH_VAL);
            nl;
        }
        case JUST_PINS: {
            nl;
            Spn("Pin Enable Register (TSI0_PEN) Pin Enable bits:");
            nl;
            Sp("Touch Sensing Input Pin Enable Register 15 (TSI_PEN_PEN15): ");Spnb(TSI_PEN_PEN15_VAL);
            Sp("Touch Sensing Input Pin Enable Register 14 (TSI_PEN_PEN14): ");Spnb(TSI_PEN_PEN14_VAL);
            Sp("Touch Sensing Input Pin Enable Register 13 (TSI_PEN_PEN13): ");Spnb(TSI_PEN_PEN13_VAL);
            Sp("Touch Sensing Input Pin Enable Register 12 (TSI_PEN_PEN12): ");Spnb(TSI_PEN_PEN12_VAL);
            Sp("Touch Sensing Input Pin Enable Register 11 (TSI_PEN_PEN11): ");Spnb(TSI_PEN_PEN11_VAL);
            Sp("Touch Sensing Input Pin Enable Register 10 (TSI_PEN_PEN10): ");Spnb(TSI_PEN_PEN10_VAL);
            Sp("Touch Sensing Input Pin Enable Register 9 (TSI_PEN_PEN9):   ");Spnb(TSI_PEN_PEN9_VAL);
            Sp("Touch Sensing Input Pin Enable Register 8 (TSI_PEN_PEN8):   ");Spnb(TSI_PEN_PEN8_VAL);
            Sp("Touch Sensing Input Pin Enable Register 7 (TSI_PEN_PEN7):   ");Spnb(TSI_PEN_PEN7_VAL);
            Sp("Touch Sensing Input Pin Enable Register 6 (TSI_PEN_PEN6):   ");Spnb(TSI_PEN_PEN6_VAL);
            Sp("Touch Sensing Input Pin Enable Register 5 (TSI_PEN_PEN5):   ");Spnb(TSI_PEN_PEN5_VAL);
            Sp("Touch Sensing Input Pin Enable Register 4 (TSI_PEN_PEN4):   ");Spnb(TSI_PEN_PEN4_VAL);
            Sp("Touch Sensing Input Pin Enable Register 3 (TSI_PEN_PEN3):   ");Spnb(TSI_PEN_PEN3_VAL);
            Sp("Touch Sensing Input Pin Enable Register 2 (TSI_PEN_PEN2):   ");Spnb(TSI_PEN_PEN2_VAL);
            Sp("Touch Sensing Input Pin Enable Register 1 (TSI_PEN_PEN1):   ");Spnb(TSI_PEN_PEN1_VAL);
            Sp("Touch Sensing Input Pin Enable Register 0 (TSI_PEN_PEN0):   ");Spnb(TSI_PEN_PEN0_VAL);
            nl;
        }
        case JUST_COUNTERS: {
            print_touch_register_values();
        }
    }
}

void test_all_writable_tsi_registers(void) {
    TSI0_GENCS = uint32_t(0); // Disable TSI module and interrupt to be able to change register values
    // Can't set first range of bits, as they're reserved
    TSI0_GENCS |= TSI_GENCS_LPCLKS(1);     // Valid values: {0,1}
    TSI0_GENCS |= TSI_GENCS_LPSCNITV(15);  // Valid values: {0,15}
    TSI0_GENCS |= TSI_GENCS_NSCN(31);      // Valid values: {0,31}
    TSI0_GENCS |= TSI_GENCS_PS(7);         // Valid values: {0,7}
    TSI0_GENCS |= TSI_GENCS_EOSF_RST(1);   // Valid values: {0,1}
    TSI0_GENCS |= TSI_GENCS_OUTRGF_RST(1); // Valid values: {0,1}
    TSI0_GENCS |= TSI_GENCS_EXTERF_RST(1); // Valid values: {0,1}
    TSI0_GENCS |= TSI_GENCS_OVRF_RST(1);   // Valid values: {0,1}
    // Reserved range
    // SCNIP is read-only
    // Don't want to make SWTS a 1 yet
    // Don't want to enable module yet
    // Don't want to enable TSI interrupts yet
    // Don't want to have error interrupts enabled either
    TSI0_GENCS |= TSI_GENCS_ESOR(1);       // Valid values: {0,1}
    // Reserved
    TSI0_GENCS |= TSI_GENCS_STM(1);        // Valid values: {0,1}
    TSI0_GENCS |= TSI_GENCS_STPE(1);       // Valid values: {0,1}
    TSI0_GENCS |= TSI_GENCS_SWTS;
    TSI0_GENCS |= TSI_GENCS_TSIIE; // Turning this and the following two on may cause interrupts to fire
    TSI0_GENCS |= TSI_GENCS_ERIE;  // NOTE: disable interrupts at the beginning of this function, and then return the NVIC or global mask to its original state at the end, right after returning all TSI registers to their original states
    TSI0_GENCS |= TSI_GENCS_TSIEN;

    TSI0_SCANC = uint32_t(0);
    TSI0_SCANC |= TSI_SCANC_REFCHRG(15);   // Valid values: {0,15}
    TSI0_SCANC |= TSI_SCANC_EXTCHRG(15);   // Valid values: {0,15}
    TSI0_SCANC |= TSI_SCANC_SMOD(255);     // Valid values: {0,255}
    TSI0_SCANC |= TSI_SCANC_AMCLKS(2);     // Valid values: {0,2}
    TSI0_SCANC |= TSI_SCANC_AMPSC(7);      // Valid values: {0,7}
    
    TSI0_PEN = uint32_t(0);
    TSI0_PEN |= TSI_PEN_LPSP(15);          // Valid values: {0,15}
    TSI0_PEN |= TSI_PEN_PEN15_EN;
    TSI0_PEN |= TSI_PEN_PEN14_EN;
    TSI0_PEN |= TSI_PEN_PEN13_EN;
    TSI0_PEN |= TSI_PEN_PEN12_EN;
    TSI0_PEN |= TSI_PEN_PEN11_EN;
    TSI0_PEN |= TSI_PEN_PEN10_EN;
    TSI0_PEN |= TSI_PEN_PEN9_EN;
    TSI0_PEN |= TSI_PEN_PEN8_EN;
    TSI0_PEN |= TSI_PEN_PEN7_EN;
    TSI0_PEN |= TSI_PEN_PEN6_EN;
    TSI0_PEN |= TSI_PEN_PEN5_EN;
    TSI0_PEN |= TSI_PEN_PEN4_EN;
    TSI0_PEN |= TSI_PEN_PEN3_EN;
    TSI0_PEN |= TSI_PEN_PEN2_EN;
    TSI0_PEN |= TSI_PEN_PEN1_EN;
    TSI0_PEN |= TSI_PEN_PEN0_EN;
    
    // Can't write to any counting registers
    
    TSI0_THRESHOLD = uint32_t(0);
    TSI0_THRESHOLD |= TSI_THRESHOLD_LTHH(65535); // Valid values: {0,65535}
    TSI0_THRESHOLD |= TSI_THRESHOLD_HTHH(0xFFFF); // Valid values: {0,65535}
}

void interpret_setup_error_codes(SETUP_ERROR_CODE error_number) { // NOTE: Complete this for all error codes
    switch(error_number) {
        case NORMAL: {Spn("Normal");break;}
        case OUT_OF_RANGE_VALUE: {Spn("A value passed as an argument was not within its valid range");break;}
    }
}
#endif
