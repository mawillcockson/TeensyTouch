/* This file is supposed to help with running the Touch Sense Input
 * module of the Teensy (3.2).
 */

#include <kinetis.h>
#include <pins_arduino.h>

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
#define TSI_PEN_PEN15_VAL       ((TSI0_PEN << 16) >> 31)
#define TSI_PEN_PEN15_EN        (0x8000) // (1 << 15)
#define TSI_PEN_PEN14_VAL       ((TSI0_PEN << 17) >> 31)
#define TSI_PEN_PEN14_EN        (0x4000) // (1 << 14)
#define TSI_PEN_PEN13_VAL       ((TSI0_PEN << 18) >> 31)
#define TSI_PEN_PEN13_EN        (0x2000) // (1 << 13)
#define TSI_PEN_PEN12_VAL       ((TSI0_PEN << 19) >> 31)
#define TSI_PEN_PEN12_EN        (0x1000) // (1 << 12)
#define TSI_PEN_PEN11_VAL       ((TSI0_PEN << 20) >> 31)
#define TSI_PEN_PEN11_EN        (0x800) // (1 << 11)
#define TSI_PEN_PEN10_VAL       ((TSI0_PEN << 21) >> 31)
#define TSI_PEN_PEN10_EN        (0x400) // (1 << 10)
#define TSI_PEN_PEN9_VAL        ((TSI0_PEN << 22) >> 31)
#define TSI_PEN_PEN9_EN        (0x200) // (1 << 9)
#define TSI_PEN_PEN8_VAL        ((TSI0_PEN << 23) >> 31)
#define TSI_PEN_PEN8_EN        (0x100) // (1 << 8)
#define TSI_PEN_PEN7_VAL        ((TSI0_PEN << 24) >> 31)
#define TSI_PEN_PEN7_EN        (0x80) // (1 << 7)
#define TSI_PEN_PEN6_VAL        ((TSI0_PEN << 25) >> 31)
#define TSI_PEN_PEN6_EN        (0x40) // (1 << 6)
#define TSI_PEN_PEN5_VAL        ((TSI0_PEN << 26) >> 31)
#define TSI_PEN_PEN5_EN        (0x20) // (1 << 5)
#define TSI_PEN_PEN4_VAL        ((TSI0_PEN << 27) >> 31)
#define TSI_PEN_PEN4_EN        (0x10) // (1 << 4)
#define TSI_PEN_PEN3_VAL        ((TSI0_PEN << 28) >> 31)
#define TSI_PEN_PEN3_EN        (0x8) // (1 << 3)
#define TSI_PEN_PEN2_VAL        ((TSI0_PEN << 29) >> 31)
#define TSI_PEN_PEN2_EN        (0x4) // (1 << 2)
#define TSI_PEN_PEN1_VAL        ((TSI0_PEN << 30) >> 31)
#define TSI_PEN_PEN1_EN        (0x2) // (1 << 1)
#define TSI_PEN_PEN0_VAL        ((TSI0_PEN << 31) >> 31)
#define TSI_PEN_PEN0_EN        (0x1) // (1 << 0)
#define TSI_PEN_PEN_VALs        ((TSI0_PEN << 16) >> 16)
#define TSI_WUCNTR_VAL              ((TSI0_WUCNTR << 16) >> 16)
#define TSI0_CNTR1_CTN_VAL      ((TSI0_CNTR1        ) >> 16)
#define TSI0_CNTR1_CTN1_VAL     ((TSI0_CNTR1   << 16) >> 16)
#define TSI0_CNTR3_CTN_VAL      ((TSI0_CNTR3        ) >> 16)
#define TSI0_CNTR3_CTN1_VAL     ((TSI0_CNTR3   << 16) >> 16)
#define TSI0_CNTR5_CTN_VAL      ((TSI0_CNTR5        ) >> 16)
#define TSI0_CNTR5_CTN1_VAL     ((TSI0_CNTR5   << 16) >> 16)
#define TSI0_CNTR7_CTN_VAL      ((TSI0_CNTR7        ) >> 16)
#define TSI0_CNTR7_CTN1_VAL     ((TSI0_CNTR7   << 16) >> 16)
#define TSI0_CNTR9_CTN_VAL      ((TSI0_CNTR9        ) >> 16)
#define TSI0_CNTR9_CTN1_VAL     ((TSI0_CNTR9   << 16) >> 16)
#define TSI0_CNTR11_CTN_VAL     ((TSI0_CNTR11      ) >> 16)
#define TSI0_CNTR11_CTN1_VAL    ((TSI0_CNTR11 << 16) >> 16)
#define TSI0_CNTR13_CTN_VAL     ((TSI0_CNTR13     ) >> 16)
#define TSI0_CNTR13_CTN1_VAL    ((TSI0_CNTR13 << 16) >> 16)
#define TSI0_CNTR15_CTN_VAL     ((TSI0_CNTR15      ) >> 16)
#define TSI0_CNTR15_CTN1_VAL    ((TSI0_CNTR15 << 16) >> 16)
#define TSI_THRESHOLD_LTHH_VAL          ((TSI0_THRESHOLD      ) >> 16)
#define TSI_THRESHOLD_LTHH(n)           (((n) & 0xFFFF) << 16) // Valid values: {0,65535}
#define TSI_THRESHOLD_HTHH_VAL          ((TSI0_THRESHOLD << 16) >> 16)
#define TSI_THRESHOLD_HTHH(n)           ((n) & 0xFFFF) // Valid values: {0,65535}
#endif

#if (!defined(TSI_PERIODIC))
#endif

#if (!defined(TSI_SOFTWARE))
#endif

void tsi_stop(void) {
    TSI0_GENCS = TSI0_GENCS & (~(TSI_GENCS_TSIEN | TSI_GENCS_TSIIE));
}

void tsi_start(void) {
    *portConfigRegister(0) = PORT_PCR_MUX(0); // Need to figure out what this line does
    SIM_SCGC5 |= SIM_SCGC5_TSI;               // And this one, too
    TSI0_GENCS = TSI0_GENCS | TSI_GENCS_TSIEN;
}
