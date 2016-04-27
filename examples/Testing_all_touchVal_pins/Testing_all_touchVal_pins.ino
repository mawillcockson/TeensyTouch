// Serial
#define Sp(a)  (Serial.print(a))
#define Spn(a) (Serial.println(a))
#define tab    (Sp("\t"))
#define nl     (Sp("\n"))
#define serial_on (true)

#define noop {asm volatile ("nop");}
#define stop {while (1) {continue;}}

#define TEENSYTOUCH_SERIAL_DEBUG
#include <TeensyTouch.h>

void setup() {
    #ifdef TEENSYTOUCH_SERIAL_DEBUG
    // Serial
    Serial.begin(9600);
    delay(1000);
    #endif
    
    interpret_setup_error_codes(
    setup_tsi((PIN0_EN | PIN1_EN | PIN15_EN | PIN16_EN | PIN17_EN | PIN18_EN | PIN19_EN | PIN22_EN | PIN23_EN), // Pins to enable
              1, // number of scans
              1, // prescaler
              32, // reference charge
              32, // external charge
              LPOSCCLK, // active mode clock source
              0, // scan modulus
              1, // active mode prescaler
              HARDWARE_POLL,
              100000 // buffer update interval (us)
              )
              //;
    );
}

unsigned long start_time;
unsigned long end_time;

int gpin0;
int gpin1;
int gpin15;
int gpin16;
int gpin17;
int gpin18;
int gpin19;
int gpin22;
int gpin23;

void loop() {
    gpin0 = touchVal(0);
    gpin1 = touchVal(1);
    gpin15 = touchVal(15);
    gpin16 = touchVal(16);
    gpin17 = touchVal(17);
    gpin18 = touchVal(18);
    gpin19 = touchVal(19);
    gpin22 = touchVal(22);
    gpin23 = touchVal(23);
    
    /* Pretty format the results */
    nl;
    Spn("Global");
    Sp("p0:\t");Spn(gpin0);
    Sp("p1:\t");Spn(gpin1);
    Sp("p15:\t");Spn(gpin15);
    Sp("p16:\t");Spn(gpin16);
    Sp("p17:\t");Spn(gpin17);
    Sp("p18:\t");Spn(gpin18);
    Sp("p19:\t");Spn(gpin19);
    Sp("p22:\t");Spn(gpin22);
    Sp("p23:\t");Spn(gpin23);
    nl;
    
    delay(700);
}

