//Serial
#define Sp(a)   (Serial.print(a))
#define Spn(a)  (Serial.println(a))
#define Sph(a)  (Serial.print(a,HEX))
#define Sphn(a) (Serial.println(a,HEX))
#define Spb(a)  (Serial.print(a,BIN))
#define Spbn(a) (Serial.println(a,BIN))
#define tab     (Sp("\t"))
#define nl      (Sp("\n"))
#define serial_on (true)

#define noop {asm volatile ("nop");}
#define stop {while (1) {continue;}}

#define GPIO_BITBAND_ADDR(reg, bit) (((uint32_t)&(reg) - 0x40000000) * 32 + (bit) * 4 + 0x42000000)

void setup() {
    //Serial
    Serial.begin(9600);
    delay(1000);
    
    Sp("portConfigRegister(0): ");Sphn((uint32_t)portConfigRegister(0));
    Sp("portConfigRegister(1): ");Sphn((uint32_t)portConfigRegister(1));
    Sp("PORT_PCR_MUX(0): ");Spbn(PORT_PCR_MUX(0));
    Sp("PORT_PCR_MUX(1): ");Spbn(PORT_PCR_MUX(1));
    for (uint32_t i = 0; i < 34; ++i) {
        Sp("portModeRegister("+String(i)+"): ");Sphn((uint32_t)portModeRegister(i));
    }
    Sp("portOutputRegister(0): ");Sphn((uint32_t)portOutputRegister(0));
    Sp("GPIO_BITBAND_ADDR(CORE_PIN2_PORTREG, CORE_PIN2_BIT): ");Sphn(GPIO_BITBAND_ADDR(CORE_PIN2_PORTREG, CORE_PIN2_BIT));
    Sp("portOutputRegister(2): ");Sphn((uint32_t)portOutputRegister(2));
    //digitalWrite
}

void loop() {
    Spn("\n\nStopped");
    stop;
}
