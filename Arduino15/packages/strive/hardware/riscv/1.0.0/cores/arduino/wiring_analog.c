#include "Arduino.h"
#include "wiring_analog.h"
#include "platform.h"


__BEGIN_DECLS


static int _readResolution = 10;
static int _writeResolution = 8;

static uint8_t pwm_enabled[VARIANT_NUM_PWM];
static int8_t pwm_enabled_pin[VARIANT_NUM_PIN];

void analogReadResolution(int res) {
	_readResolution = res;
}

void analogWriteResolution(int res) {
	_writeResolution = res;
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void analogWritePhase(uint32_t pin, uint32_t phase)
{
  int8_t pwm_num;
  
  if(pin >= variant_pin_map_size)
    return;

  pwm_num = variant_pin_map[pin].pwm_num;
  if(pwm_num > variant_pwm_size)
    {
      //TODO -- Not sure what this function is supposed to
      //        do exactly
    }
}
      
void analogOutputInit( void )
{
  
}

#if defined(STRIVE_1)
void analogWrite(uint32_t pin, uint32_t ulValue)
{

  // Arduino Creates a 50Hz signal by default

  uint32_t frequency_val = SystemCoreClock/500;


  volatile uint8_t pwm_num;
  volatile uint8_t pwm_cmp_num;
  volatile uint8_t pwm_bit_pos;
  uint32_t pwm_period;
  
  if (pin > variant_pin_map_size) {
    return;
  }

  pwm_num = variant_pin_map[pin].pwm_num;
  pwm_cmp_num = variant_pin_map[pin].pwm_cmp_num;
  pwm_bit_pos = variant_pin_map[pin].bit_pos;

  if (pwm_num > variant_pwm_size) {
    return;
  }

  pwm_period = (1 << _writeResolution) - 1;

  uint32_t pwm_val = map((ulValue > pwm_period) ? 0 : (pwm_period -  ulValue),1,pwm_period-1,0,frequency_val)-1;
  // This also sets the scale to 0.
   if (!pwm_enabled[pwm_num]) {


    *((volatile uint32_t*) (variant_pwm[pwm_num] + PWM_DTR))  = 1;
    *((volatile uint32_t*) (variant_pwm[pwm_num] + PWM_CTRL)) = 0; // Disable 
    *((volatile uint32_t*) (variant_pwm[pwm_num] + PWM_CTRL)) |= _BV(PWM_CTRL_CNTRST); // Reset Counter
    *((volatile uint32_t*) (variant_pwm[pwm_num] + PWM_CTRL)) = 0; // Counter Enable 
    *((volatile uint32_t*) (variant_pwm[pwm_num] + PWM_LRC)) = frequency_val; // Write LRC For Frequency
    *((volatile uint32_t*) (variant_pwm[pwm_num] + PWM_HRC))   =  pwm_val;
    //*((volatile uint32_t*) (variant_pwm[pwm_num] + PWM_CTRL))   = 0x80;
    *((volatile uint32_t*) (variant_pwm[pwm_num] + PWM_CTRL)) |= _BV(PWM_CTRL_OE);
    *((volatile uint32_t*) (variant_pwm[pwm_num] + PWM_CTRL)) |= _BV(PWM_CTRL_EN);
    //*((volatile uint32_t*) (variant_pwm[pwm_num] + PWM_CTRL))   = 0x209;
     pwm_enabled[pwm_num] = 1;
   }
  
 // if (!pwm_enabled_pin[pin]) {
    //#ifdef REMAP_ENABLED
    Remap(pwm_bit_pos,OUTPUT,pwm_cmp_num);
   // #endif
    pwm_enabled_pin[pin] = 1;
  //}

    // Set PWM Duty Cycle
    *((volatile uint32_t*) (variant_pwm[pwm_num] + PWM_HRC))   =  pwm_val;

}
#endif

#if defined(STRIVE_1alpha)

void analogWrite(uint32_t pin, uint32_t ulValue)
{
    if (pin >= variant_pin_map_size) return;

    uint8_t pwm_num = variant_pin_map[pin].pwm_num;
    uint8_t bit_pos = variant_pin_map[pin].bit_pos;

    if (pwm_num == 0 || pwm_num > variant_pwm_size) return;

    Remap(bit_pos, OUTPUT, PERIPHERAL);

    volatile uint32_t* PWM_BASE = (volatile uint32_t*)variant_pwm[pwm_num - 1];

    // --------------------------
    // 1) Auto divisor (simple)
    // --------------------------
    const uint32_t f_system = 50000000;      // 50 MHz
    const uint32_t target_pre = 1000000;     // aim for 1 MHz prescaled clock

    uint32_t divisor = f_system / target_pre;
    if (divisor & 1) divisor++;              // must be even
    if (divisor < 2) divisor = 2;
    if (divisor > 254) divisor = 254;

    // --------------------------
    // 2) Auto period
    // --------------------------
    const uint32_t desired_pwm_freq = 10000; // 10 kHz default
    uint32_t period = (f_system / (divisor * desired_pwm_freq)) - 1;

    // --------------------------
    // 3) Duty mapping (0–255 → 0–period)
    // --------------------------
    uint32_t duty = ((uint64_t)ulValue * period) / 255;
    if (duty > period) duty = period;

    // --------------------------
    // 4) Write registers
    // --------------------------
    PWM_BASE[0] = 22;       // Enable PWM
    PWM_BASE[3] = divisor;  // divisor
    PWM_BASE[2] = period;   // period
    PWM_BASE[1] = duty;     // duty
}



#endif




// Strive - 1 has 8 external ADC inputs 
uint32_t analogRead(uint32_t pin)
{
  return 0;
}

__END_DECLS
