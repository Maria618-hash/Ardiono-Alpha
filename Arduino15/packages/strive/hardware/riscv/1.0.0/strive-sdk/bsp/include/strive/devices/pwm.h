// See LICENSE for license details.

#ifndef _SIFIVE_PWM_H
#define _SIFIVE_PWM_H

/* Register offsets */

#define PWM_CFG   0x00
#define PWM_COUNT 0x08
#define PWM_S     0x10
#define PWM_CMP0  0x20
#define PWM_CMP1  0x24
#define PWM_CMP2  0x28
#define PWM_CMP3  0x2C

/* Constants */

#define PWM_CFG_SCALE       0x0000000F
#define PWM_CFG_STICKY      0x00000100
#define PWM_CFG_ZEROCMP     0x00000200
#define PWM_CFG_DEGLITCH    0x00000400
#define PWM_CFG_ENALWAYS    0x00001000
#define PWM_CFG_ONESHOT     0x00002000
#define PWM_CFG_CMP0CENTER  0x00010000
#define PWM_CFG_CMP1CENTER  0x00020000
#define PWM_CFG_CMP2CENTER  0x00040000
#define PWM_CFG_CMP3CENTER  0x00080000
#define PWM_CFG_CMP0GANG    0x01000000
#define PWM_CFG_CMP1GANG    0x02000000
#define PWM_CFG_CMP2GANG    0x04000000
#define PWM_CFG_CMP3GANG    0x08000000
#define PWM_CFG_CMP0IP      0x10000000
#define PWM_CFG_CMP1IP      0x20000000
#define PWM_CFG_CMP2IP      0x40000000
#define PWM_CFG_CMP3IP      0x80000000


#define PWM_CNTR    0x00
#define PWM_HRC     0x04
#define PWM_LRC     0x08
#define PWM_CTRL    0x0c
#define PWM_DTR     0x10
#define PWM_CTR     0x14

#define PWM_CTRL_EN     0   //EN When set, RPTC_CNTR can be incremented
#define PWM_CTRL_ECLK   1   // ECLK When set, ptc_ecgt signal is used to increment 
                            //RPTC_CNTR. When cleared, system clock is used instead.
#define PWM_CTRL_NEC    2   //NEC 
                            // When set, ptc_ecgt increments on negative edge and gates 
                            // on low period. 
                            // When cleared, ptc_ecgt increments on positive edge and 
                            // gates on high period. 
                            // This bit has effect only on ‘gating’ function of ptc_ecgt when 
                            // RPTC_CTRL[ECLK] bit is cleared.
#define PWM_CTRL_OE     3   //Inverted value of this bit is reflected on the ptc_oen signal. It 
                            //is used to enable PWM output driver.
#define PWM_CTRL_SINGLE 4   // SINGLE 
                            // When set, RPTC_CNTR is not incremented anymore after it 
                            // reaches value equal to the RPTC_LRC value. When cleared, 
                            // RPTC_CNTR is restarted after it reaches value in the 
                            // RPTC_LCR register
#define PWM_CTRL_INTE   5   // INTE
                            // When set, PTC asserts an interrupt when RPTC_CNTR value is 
                            // equal to the value of RPTC_LRC or RPTC_HRC. When cleared, 
                            // interrupts are masked
#define PWM_CTRL_INT    6   //INT
                            // When read, this bit represents pending interrupt. When it is 
                            // set, an interrupt is pending. When this bit is written with ‘1’, 
                            // interrupt request is cleared.
#define PWM_CTRL_CNTRST 7   //CNTRRST
                            // When set, RPTC_CNTR is under reset. When cleared, normal 
                            // operation of the counter is allowed
#define PWM_CTRL_CAPTE  8   //When set, ptc_capt signal can be used to capture RPTC_CNTR 
                            // into RPTC_LRC or RPTC_HRC registers. Into which 
                            // reference/capture register capture occurs depends on edge 
                            // of the ptc_capt signal. When cleared, capture function is 
                            // masked
#define PWM_CTRL_MODE   9   //When setting mode bit, different modes can be selected.




#endif /* _SIFIVE_PWM_H */
