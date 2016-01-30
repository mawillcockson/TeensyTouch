/* Author: Matthew Willcockson
 * Description: A group of functions and utilities to help fleh out the
 * TSI capabilities presented by the Teensy 3.2 in kinetis.h
 */
 
#ifndef TEENSYTOUCH_H
#ifdef KINETISK
#define TEENSYTOUCH_H

#include <kinetis.h>
#include <pins_arduino.h>
#include <stdint.h>
#include <math.h>
//#include <Print.h>
#include <HardwareSerial.h>
//#include <SoftwareSerial.h>
//#include <stdlib.h>
#include <Arduino.h>
//#include <WProgram.h>
//#include <usb_serial.h>
#include <IntervalTimer.h>


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


#define tsi_start_scan {TSI0_GENCS |= TSI_GENCS_SWTS; wait(79);}

/* A function that waits without using a timer.
 * NOTE: Please make this better
 */
void wait(uint32_t num_adds_to_do);

/* Starts the TSI module
 * NOTE: Figure out the magic in the first two lines of this function
 */
void tsi_start(void);

/* Disables the TSI module */
void tsi_stop(void);

/* This function is as basic as you can get:
 *   It checks if the pin to be read is less than 34, and then returns
 *   that pin's value from the buffer.
 */
uint16_t touchVal(uint8_t pin);

/* Lists return values of the setup_tsi() function as types */
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

/* Lists the Active Mode Clock Sources */
typedef enum ACTIVE_MODE_CLOCK_SOURCES {LPOSCCLK,  /* 1 kHz LPO clock, Low-Power OSC clock, or Bus clock */
                                MCGIRCLK,  /* Multipurpose Clock Generator Internal Reference Clock */
                                OSCERCLK  /* Clock provided by OSC module for peripheral use */
} ACTIVE_MODE_CLOCK_SOURCE;

/* Lists the different modes of operation available with the TSI module
 * NOTE: Under consideration for how the function should be designed,
 * and if it needs this 
 */
typedef enum TSI_READ_MODES {HARDWARE_POLL,
                             SOFTWARE_POLL,
                             SOFTWARE_TRIGGER
} TSI_READ_MODE;

/* Lists the different modes of operation for a function that prints
 * debugging info
 */
typedef enum PRINT_MODES {ALL_REGISTERS,
                          CONCAT_ALL,
                          CONCAT_SOME,
                          JUST_PINS,
                          JUST_COUNTERS
} PRINT_MODE;



/* This function can be called any time to change the operating
 * parameters of the TSI module.
 * 
 * I'm still trying to figure out how to provide:
 *  - Efficiently and dynamically allocating buffer arrays for the pin
 *    capacitance measurement results
 *  - Modifying the tsi0_isr() ISR so that it doesn't needlessly check for conditions which it doesn't need to deal with */
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
    TSI_READ_MODE tsi_read_mode,
    unsigned long interval_time /* The amount of time between buffer
                                 * updates in microseconds
                                 */
    );

#ifdef TEENSYTOUCH_SERIAL_DEBUG
#define Sp(a)  (Serial.print(a))
#define Spn(a) (Serial.println(a))
#define tab    (Sp("\t"))
#define nl     (Sp("\n"))

#define noop {asm volatile ("nop");}
#define pause_stop {while (true) {continue;}}

void print_tsi_register_values(PRINT_MODE print_mode);
void interpret_setup_error_codes(SETUP_ERROR_CODE error_number);

/* Only temporarily exposed */
void copy_to_buff(void);
void restart_tsi(void);
//extern volatile uint32_t num_interrupt_calls;
#endif // ifdef TEENSYTOUCH_SERIAL_DEBUG

#endif // ifdef KINETISK
#endif // ifndef TEENSYTOUCH_H

