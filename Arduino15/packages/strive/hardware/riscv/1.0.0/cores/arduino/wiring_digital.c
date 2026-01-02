// See LICENSE file for license details.
#if defined(STRIVE_1)
#include "Arduino.h"

__BEGIN_DECLS

static inline uint32_t _to_hw_pin(uint32_t pin)
{
    // If it's a normal Arduino pin number, map through variant.
    // If it's already a raw SoC pin number (>= variant size), pass through.
    if (pin < variant_pin_map_size) {
        return variant_pin_map[pin].bit_pos;
    }
    return pin;
}

void pinMode( uint32_t dwPin, uint32_t dwMode)
{
    uint32_t hwPin = _to_hw_pin(dwPin);
    #ifdef REMAP_ENABLED
    Remap((uint8_t)hwPin, (uint8_t)dwMode, GPIO);
    #endif

    #ifndef REMAP_ENABLED
    if (dwMode == OUTPUT)
    {
        GPIO_DIR|=1<<(hwPin);
    }
    else{
        GPIO_DIR &= ~(1<<(hwPin));
    }

    #endif

} 

void digitalWrite(uint32_t pin, uint32_t val)
{
    uint32_t hwPin = _to_hw_pin(pin);
    if(val)
    {
    GPIO_OUTPUT |= 1<<hwPin;  // BitSet
    }

    else
    {
    GPIO_OUTPUT &= ~(1<<hwPin);
    }

}

int digitalRead(uint32_t pin)
{
    int state;
    uint32_t hwPin = _to_hw_pin(pin);
    state = GPIO_INPUT & 1<<(hwPin);
    if (state)
    {
        return 1;
    }
    else{
        return 0;
    }
}

void Remap(uint8_t pin_number, uint8_t pin_dir, uint8_t x)
{

    typedef struct {
        unsigned int address;
        uint8_t pin;
    } PinMap;

const PinMap pin_mappings[] = {
    {REMAP_OUT_REG1, PIN0},
    {REMAP_OUT_REG1, PIN1},
    {REMAP_OUT_REG1, PIN2},
    {REMAP_OUT_REG1, PIN3},
    {REMAP_OUT_REG2, PIN4},
    {REMAP_OUT_REG2, PIN5},
    {REMAP_OUT_REG2, PIN6},
    {REMAP_OUT_REG2, PIN7},
    {REMAP_OUT_REG3, PIN8},
    {REMAP_OUT_REG3, PIN9},
    {REMAP_OUT_REG3, PIN10},
    {REMAP_OUT_REG3, PIN11},
    {REMAP_OUT_REG4, PIN12},
    {REMAP_OUT_REG4, PIN13},
    {REMAP_OUT_REG4, PIN14},
    {REMAP_OUT_REG4, PIN15},
    {REMAP_OUT_REG5, PIN16},
    {REMAP_OUT_REG5, PIN17},
    {REMAP_OUT_REG5, PIN18},
    {REMAP_OUT_REG5, PIN19},
    {REMAP_OUT_REG6, PIN20},
    {REMAP_OUT_REG6, PIN21},
    {REMAP_OUT_REG6, PIN22},
    {REMAP_OUT_REG6, PIN23},
    {REMAP_OUT_REG7, PIN24},
    {REMAP_OUT_REG7, PIN25},
    {REMAP_OUT_REG7, PIN26},
    {REMAP_OUT_REG7, PIN27},
    {REMAP_OUT_REG8, PIN28},
    {REMAP_OUT_REG8, PIN29},
    {REMAP_OUT_REG8, PIN30},
    {REMAP_OUT_REG8, PIN31}
};

    typedef struct {
        unsigned int address;
        uint8_t pin_offset;
    } PinMap_Input;

const PinMap_Input pin_mappings_input[] = {   
    {REMAP_IN_REG1, 0},
    {REMAP_IN_REG1, 8},
    {REMAP_IN_REG1, 16},
    {REMAP_IN_REG1, 24},
    {REMAP_IN_REG2, 0},
    {REMAP_IN_REG2, 8},
    {REMAP_IN_REG2, 16},
    {REMAP_IN_REG2, 24},
    {REMAP_IN_REG3, 0},
    {REMAP_IN_REG3, 8},
    {REMAP_IN_REG3, 16},
    {REMAP_IN_REG3, 24}
};

// Check if pin is in range of pins
if (pin_number > NUM_GPIO )
{
    return;
}

if (pin_dir == OUTPUT)
{
    //Set Direction register bit to 1
    uint32_t direction_reg_current = READ_Reg(DIR_REG_ADDR);
    uint32_t direction_reg_mask = 1 << pin_number;
    WRITE_Reg(DIR_REG_ADDR, direction_reg_current | direction_reg_mask);

    // Create Pin Mask
    uint32_t pin_mask = x << pin_mappings[pin_number].pin;

    //Read Current state of Pin Register and OR new pin_value to it
    uint32_t pin_value = READ_Reg(pin_mappings[pin_number].address) | pin_mask ;

    // Write Pin Value to Register
    WRITE_Reg(pin_mappings[pin_number].address, pin_value);
}

else if (pin_dir == INPUT)
{
    //Set Direction register bit to 0
    uint32_t direction_reg_current = READ_Reg(DIR_REG_ADDR);
    uint32_t direction_reg_mask = ~(1 << pin_number);
    WRITE_Reg(DIR_REG_ADDR, direction_reg_current & direction_reg_mask);

    // Create Pin Mask
    uint32_t pin_mask_input = pin_number << pin_mappings_input[x].pin_offset;

    //Read Current state of Pin Register and OR new pin_value to it
    uint32_t pin_value_input = READ_Reg(pin_mappings_input[x].address) | pin_mask_input ;

    // Write Pin Value to Register
    WRITE_Reg(pin_mappings_input[x].address, pin_value_input);
}
 
}

__END_DECLS
#endif

// See LICENSE file for license details.
#if defined(STRIVE_1alpha)
#include "Arduino.h"
__BEGIN_DECLS

static inline uint32_t _to_hw_pin(uint32_t pin)
{
    // If it's a normal Arduino pin number, map through variant.
    // If it's already a raw SoC pin number (>= variant size), pass through.
    if (pin < variant_pin_map_size) {
        return variant_pin_map[pin].bit_pos;
    }
    return pin;
}

void pinMode( uint32_t dwPin, uint32_t dwMode)
{
    uint32_t hwPin = _to_hw_pin(dwPin);
    #ifdef REMAP_ENABLED
    Remap((uint8_t)hwPin, (uint8_t)dwMode, GPIO);
    #endif

    #ifndef REMAP_ENABLED
    if (dwMode == OUTPUT)
    {
        GPIO_DIR|=1<<(hwPin);
    }
    else{
        GPIO_DIR &= ~(1<<(hwPin));
    }

    #endif

} 

// void digitalWrite(uint32_t pin, uint32_t val)
// {
//     if(val)
//     {
//     GPIO_OUTPUT |= 1<<pin;  // BitSet
//     }

//     else
//     {
//     GPIO_OUTPUT &= ~(1<<pin);
//     }

// }

// int digitalRead(uint32_t pin)
// {
//     int state;
//     state = GPIO_INPUT & 1<<(pin);
//     if (state)
//     {
//         return 1;
//     }
//     else{
//         return 0;
//     }
// }

void digitalWrite(uint32_t pin, uint32_t val)
{
    uint32_t hwPin = _to_hw_pin(pin);
    volatile uint32_t* gpio_out;

    if (hwPin < 32)
        gpio_out = (volatile uint32_t*)(GPIO1_BASE_ADDR + 0x04);
    else if (hwPin < 64)
        gpio_out = (volatile uint32_t*)(GPIO2_BASE_ADDR + 0x04);
    else if (hwPin <= 93)
        gpio_out = (volatile uint32_t*)(GPIO3_BASE_ADDR + 0x04);
    else
        return; // invalid pin

    uint32_t bit = hwPin % 32;

    if (val)
        *gpio_out |= (1 << bit);
    else
        *gpio_out &= ~(1 << bit);
}

int digitalRead(uint32_t pin)
{
    uint32_t hwPin = _to_hw_pin(pin);
    volatile uint32_t* gpio_in;

    if (hwPin < 32)
        gpio_in = (volatile uint32_t*)(GPIO1_BASE_ADDR + 0x00);
    else if (hwPin < 64)
        gpio_in = (volatile uint32_t*)(GPIO2_BASE_ADDR + 0x00);
    else if (hwPin <= 93)
        gpio_in = (volatile uint32_t*)(GPIO3_BASE_ADDR + 0x00);
    else
        return 0; // invalid pin

    uint32_t bit = hwPin % 32;

    return ((*gpio_in & (1 << bit)) != 0) ? 1 : 0;
}



void Remap(uint8_t pin_number, uint8_t pin_dir, uint8_t peripheral)
{
    uint32_t dir_addr = 0;
    uint32_t cfg_addr = 0;
    uint8_t dir_bit = 0;
    uint8_t cfg_bit = 0;

    // --- Direction register (banked every 32 pins) ---
    if (pin_number < 32) {
        dir_addr = 0x8000B100;
        dir_bit  = pin_number;
    } else if (pin_number < 64) {
        dir_addr = 0x8000B104;
        dir_bit  = pin_number - 32;
    } else if (pin_number <= 93) {
        dir_addr = 0x8000B108;
        dir_bit  = pin_number - 64;
    } else return; // invalid

    // --- Config register (grouped irregularly) ---
    if (pin_number >= 32 && pin_number <= 38) {
        cfg_addr = 0x8000B00C; cfg_bit = pin_number - 32; // config_reg_2
    } else if (pin_number >= 39 && pin_number <= 51) {
        cfg_addr = 0x8000B004; cfg_bit = (pin_number - 39) +10 ; // config_reg_4
    } else if (pin_number >= 52 && pin_number <= 63) {
        cfg_addr = 0x8000B000; cfg_bit = pin_number - 52; // config_reg_3
    } else if (pin_number >= 64 && pin_number <= 83) {
        cfg_addr = 0x8000B000; cfg_bit = pin_number - 64; // config_reg_3 (bank3)
    } else if (pin_number >= 84 && pin_number <= 93) {
        cfg_addr = 0x8000B004; cfg_bit = pin_number - 84; // config_reg_4 (bank3)
    } else if (pin_number < 32) {
        cfg_addr = 0x8000B008; cfg_bit = pin_number;      // config_reg_1
    } else return;

    // --- Read current values ---
    uint32_t dir = READ_Reg(dir_addr);
    uint32_t cfg = READ_Reg(cfg_addr);

    // --- Apply mode logic ---
    if (peripheral == GPIO) {
        if (pin_dir == INPUT) {
            dir &= ~(1 << dir_bit);   // 0 = input
            cfg &= ~(1 << cfg_bit);   // 0 = GPIO
        } else {
            dir |= (1 << dir_bit);    // 1 = output
            cfg &= ~(1 << cfg_bit);   // 0 = GPIO
        }
    } 
    else { // PERIPHERAL/ALT
    if (pin_dir == OUTPUT)
        dir |= (1 << dir_bit);        // TX or output
    else
        dir &= ~(1 << dir_bit);       // RX or input
    cfg |= (1 << cfg_bit);            // 1 = peripheral
}

    // --- Write back ---
    WRITE_Reg(dir_addr, dir);
    WRITE_Reg(cfg_addr, cfg);
}

__END_DECLS
#endif
