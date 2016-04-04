// Serial
#define Sp(a)  (Serial.print(a))
#define Spn(a) (Serial.println(a))
#define tab    (Sp("\t"))
#define nl     (Sp("\n"))
#define serial_on (true)

#define noop {asm volatile ("nop");}
#define stop {while (1) {continue;}}

#include <kinetis.h>
#define TEENSYTOUCH_SERIAL_DEBUG
#include <TeensyTouch.h>

void setup() {
    #ifdef TEENSYTOUCH_SERIAL_DEBUG
    // Serial
    Serial.begin(9600);
    delay(1000);
    #endif
    
    interpret_setup_error_codes(
    setup_tsi((PIN1_EN | PIN15_EN | PIN16_EN | PIN17_EN | PIN18_EN | PIN19_EN | PIN22_EN | PIN23_EN), // Pins to enable
              1, // number of scans
              1, // prescaler
              32, // reference charge
              32, // external charge
              LPOSCCLK, // active mode clock source
              0, // scan modulus
              1, // active mode prescaler
              HARDWARE_POLL,
              100000 // buffer update interval
              )
              //;
    );
}

uint32_t loop_num = 0;

unsigned long start_time;
unsigned long end_time;

// As global variables so the memory is preallocated (?)
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
    #define reps (10) // Number of repititions for the timing loops
    
    start_time = micros();
    for (uint16_t count = 0; count < reps; ++count) {
        // 9 blank noops for comparison
        noop;
        noop;
        noop;
        noop;
        noop;
        noop;
        noop;
        noop;
        noop;
    }
    end_time = micros();
    unsigned long blank_loop_time = (end_time - start_time);
    
    // Should these be static?
    int pin0;
    int pin1;
    int pin15;
    int pin16;
    int pin17;
    int pin18;
    int pin19;
    int pin22;
    int pin23;
    
    // As local variables
    start_time = micros();
    for (uint16_t count = 0; count < reps; ++count) {
        pin0 = touchVal(0);
        pin1 = touchVal(1);
        pin15 = touchVal(15);
        pin16 = touchVal(16);
        pin17 = touchVal(17);
        pin18 = touchVal(18);
        pin19 = touchVal(19);
        pin22 = touchVal(22);
        pin23 = touchVal(23);
    }
    end_time = micros();
    unsigned long local_loop_time = (end_time - start_time);
    
    // As global variables
    start_time = micros();
    for (uint16_t count = 0; count < reps; ++count) {
        gpin0 = touchVal(0);
        gpin1 = touchVal(1);
        gpin15 = touchVal(15);
        gpin16 = touchVal(16);
        gpin17 = touchVal(17);
        gpin18 = touchVal(18);
        gpin19 = touchVal(19);
        gpin22 = touchVal(22);
        gpin23 = touchVal(23);
    }
    end_time = micros();
    unsigned long global_loop_time = (end_time - start_time);
    
    // Assigned in loop
    start_time = micros();
    for (uint16_t count = 0; count < reps; ++count) {
        int apin0 = touchVal(0);
        int apin1 = touchVal(1);
        int apin15 = touchVal(15);
        int apin16 = touchVal(16);
        int apin17 = touchVal(17);
        int apin18 = touchVal(18);
        int apin19 = touchVal(19);
        int apin22 = touchVal(22);
        int apin23 = touchVal(23);
    }
    end_time = micros();
    unsigned long assigned_loop_time = (end_time - start_time);
    
    // ISRs themselves
    start_time = micros();
    for (uint16_t count = 0; count < reps; ++count) {
        copy_to_buff();
        restart_tsi();
    }
    end_time = micros();
    unsigned long isrs_loop_time = (end_time - start_time);
    
    //Sp("Blank loop: ");Spn(blank_loop_time);
    //Sp("Local var loop:    ");Sp(local_loop_time);Sp("  ");Spn(local_loop_time - blank_loop_time);
    //Sp("Global var loop:   ");Sp(global_loop_time);Sp("  ");Spn(global_loop_time - blank_loop_time);
    //Sp("Assigned var loop: ");Sp(assigned_loop_time);Sp("  ");Spn(assigned_loop_time - blank_loop_time);
    
    Sp("Blank loop: ");Spn(blank_loop_time/float(reps));
    Sp("Local var loop:    ");Sp(local_loop_time/float(reps));Sp("  ");Spn((local_loop_time - blank_loop_time)/float(reps));
    Sp("Global var loop:   ");Sp(global_loop_time/float(reps));Sp("  ");;Spn((global_loop_time - blank_loop_time)/float(reps));
    Sp("Assigned var loop: ");Sp(assigned_loop_time/float(reps));Sp("  ");Spn((assigned_loop_time - blank_loop_time)/float(reps));
    Sp("ISRs themselves:   ");Sp(isrs_loop_time/float(reps));Sp("  ");Spn((isrs_loop_time - blank_loop_time)/float(reps));
    
    /* Do something with values so they don't get optimized away by compiler */
    //nl;
    //Spn("Avg pin val:");
    //Spn((pin0 + gpin0 + pin1 + gpin1 + pin15 + gpin15 + pin16 + gpin16 + 
       //pin17 + gpin17 + pin18 + gpin18 + pin19 + gpin19 + pin22 +
       //gpin22 + pin23 + gpin23)/float(18)
       //);
    //nl;
    
    /* Pretty format the results */
    nl;
    Sp("Local");tab;Spn("Global");
    Sp(pin0);tab;Spn(gpin0);
    Sp(pin1);tab;Spn(gpin1);
    Sp(pin15);tab;Spn(gpin15);
    Sp(pin16);tab;Spn(gpin16);
    Sp(pin17);tab;Spn(gpin17);
    Sp(pin18);tab;Spn(gpin18);
    Sp(pin19);tab;Spn(gpin19);
    Sp(pin22);tab;Spn(gpin22);
    Sp(pin23);tab;Spn(gpin23);
    nl;
    
    if (loop_num >= 5) {
        pinMode(20,OUTPUT);
        digitalWrite(20,HIGH);
    }
    
    ++loop_num;
    delay(700);
}


