    #if defined(STRIVE_1)

    #define GPIO            15
    #define SPI_CS          1    
    #define SPI_MOSI        2
    #define SPI_SCL         3
    #define PWM1            4
    #define PWM2            5
    #define PWM_N_PTC4      6
    #define PWM_P_PTC4      7
    #define PWM_N_PTC3      8
    #define PWM_P_PTC3      9
    #define PWM_N_PTC2      10
    #define PWM_P_PTC2      11
    #define PWM_N_PTC1      12   
    #define PWM_P_PTC1      13
    #define O_UART2_TX      14
	
    #define SPI_MISO            0   
    #define GATE_CLK_PAD_I3     1
    #define GATE_CLK_PAD_I2     2
    #define GATE_CLK_PAD_I 	    3
    #define CAPT_PAD_I4 	    4
    #define CAPT_PAD_I3         5  
    #define CAPT_PAD_I2         6
    #define CAPT_PAD_I          7
    #define EXT_INT3            8
    #define EXT_INT2            9
    #define EXT_INT             10
    #define I_UART2_RX          11

    #define REMAP_OUT_REG1 (REMAP_BASE_ADDR)
    #define REMAP_OUT_REG2 (REMAP_BASE_ADDR+0x04)
    #define REMAP_OUT_REG3 (REMAP_BASE_ADDR+0x08)
    #define REMAP_OUT_REG4 (REMAP_BASE_ADDR+0x0c)
    #define REMAP_OUT_REG5 (REMAP_BASE_ADDR+0x10)
    #define REMAP_OUT_REG6 (REMAP_BASE_ADDR+0x14)
    #define REMAP_OUT_REG7 (REMAP_BASE_ADDR+0x18)
    #define REMAP_OUT_REG8 (REMAP_BASE_ADDR+0x1c)
    #define REMAP_IN_REG1  (REMAP_BASE_ADDR+0x24)
    #define REMAP_IN_REG2  (REMAP_BASE_ADDR+0x28)
    #define REMAP_IN_REG3  (REMAP_BASE_ADDR+0x2c)

    #define PIN0 0
    #define PIN1 8
    #define PIN2 16
    #define PIN3 24
    #define PIN4 0
    #define PIN5 8
    #define PIN6 16
    #define PIN7 24
    #define PIN8 0
    #define PIN9 8
    #define PIN10 16
    #define PIN11 24
    #define PIN12 0
    #define PIN13 8
    #define PIN14 16
    #define PIN15 24
    #define PIN16 0
    #define PIN17 8
    #define PIN18 16
    #define PIN19 24
    #define PIN20 0
    #define PIN21 8
    #define PIN22 16
    #define PIN23 24
    #define PIN24 0
    #define PIN25 8
    #define PIN26 16
    #define PIN27 24
    #define PIN28 0
    #define PIN29 8
    #define PIN30 16
    #define PIN31 24

    #endif
    #if defined(STRIVE_1alpha)

    #define UART0_BASE_ADDR   UART1_BASE_ADDR
#define GPIO_BASE_ADDR    GPIO1_BASE_ADDR
#define NUM_GPIO          32
#define DIR_REG_ADDR      (GPIO_BASE_ADDR + 0x08)

// UART peripheral IDs for Remap()
#define GPIO        0
#define PERIPHERAL  1



#define REMAP_OUT_REG1 0
#define REMAP_OUT_REG2 0
#define REMAP_OUT_REG3 0
#define REMAP_OUT_REG4 0
#define REMAP_OUT_REG5 0
#define REMAP_OUT_REG6 0
#define REMAP_OUT_REG7 0
#define REMAP_OUT_REG8 0
#define REMAP_IN_REG1  0
#define REMAP_IN_REG2  0
#define REMAP_IN_REG3  0

#define PIN0  0
#define PIN1  1
#define PIN2  2
#define PIN3  3
#define PIN4  4
#define PIN5  5
#define PIN6  6
#define PIN7  7
#define PIN8  8
#define PIN9  9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15
#define PIN16 16
#define PIN17 17
#define PIN18 18
#define PIN19 19
#define PIN20 20
#define PIN21 21
#define PIN22 22
#define PIN23 23
#define PIN24 24
#define PIN25 25
#define PIN26 26
#define PIN27 27
#define PIN28 28
#define PIN29 29
#define PIN30 30
#define PIN31 31
    #define PWM_N_PTC1      57
    #define PWM_P_PTC1      58
    #define PWM_N_PTC2      59
    #define PWM_P_PTC2      60
    #define PWM_N_PTC3      61
    #define PWM_P_PTC3      62
    #define PWM_N_PTC4      63
    #define PWM_P_PTC4      64
    #define PWM_N_PTC5      65
    #define PWM_P_PTC5      66
    #define PWM_N_PTC6      67
    #define PWM_P_PTC6      68
    #define PWM_N_PTC7      69
    #define PWM_P_PTC7      70
    #define PWM_N_PTC8      71
    #define PWM_P_PTC8      72
    #define PWM_N_PTC9      73
    #define PWM_P_PTC9      74
    #define PWM_N_PTC10     75
    #define PWM_P_PTC10     76
    #define PWM_N_PTC11     77
    #define PWM_P_PTC11     78
    #define PWM_N_PTC12     79
    #define PWM_P_PTC12     80
    #define PWM_N_PTC13     81
    #define PWM_P_PTC13     82
    #define PWM_N_PTC14     83
    #define PWM_P_PTC14     84

    #endif