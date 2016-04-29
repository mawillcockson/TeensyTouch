/* For testing TeensyTouch implementation and its interaction with other
 * pin uses
 */

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
#include <IntervalTimer.h>
#include <Metro.h>

#define LED_PIN (1)

IntervalTimer led_timer;
bool led_val = false;

void toggle_led(void) {
    //digitalWrite(LED_PIN,led_val = !led_val);
    if (led_val = !led_val) {
        digitalWriteFast(LED_PIN,1);
    } else {
        digitalWriteFast(LED_PIN,0);
    }
    //Spn(led_val);
}

Metro pin_switch_metro = Metro(0);

void setup() {
    #ifdef TEENSYTOUCH_SERIAL_DEBUG
    // Serial
    Serial.begin(9600);
    delay(1000);
    #endif
    
    #ifdef TEENSYTOUCH_SERIAL_DEBUG
    interpret_setup_error_codes(
    #endif
    setup_tsi((PIN0_EN | PIN1_EN | PIN15_EN | PIN16_EN | PIN17_EN | PIN18_EN | PIN19_EN | PIN22_EN | PIN23_EN), // Pins to enable
              1,1,32,32,LPOSCCLK,0,1,HARDWARE_POLL,100000)
              #ifndef TEENSYTOUCH_SERIAL_DEBUG
              ;
              #endif
    #ifdef TEENSYTOUCH_SERIAL_DEBUG
    );
    #endif
    
    tsi_stop();
    
    pinMode(LED_PIN,OUTPUT);
    
    led_timer.begin(toggle_led,250000);
    led_timer.priority(255);
    
    pin_switch_metro.interval(5000);
}

void loop() {
    Sp(touchVal(0));
    tab;
    Sp(touchVal(1));
    tab;
    Sp(touchVal(15));
    tab;
    Sp(touchVal(16));
    tab;
    Sp(touchVal(17));
    tab;
    Sp(touchVal(18));
    tab;
    Sp(touchVal(19));
    tab;
    Sp(touchVal(22));
    tab;
    Sp(touchVal(23));
    Spn("\n");
    
    if (pin_switch_metro.check()) {
        Spn("Starting TSI");
        //tsi_start();
        setup_tsi(PIN1_EN,1,1,32,32,LPOSCCLK,0,1,HARDWARE_POLL,100000);
        //led_timer.begin(toggle_led,1000000);
    }
    
    delay(300);
}
