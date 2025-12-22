#if defined(STRIVE_1alpha)
// Strivealpha_SPI.h  (public header, no #ifdef here)
#include <Arduino.h>
#include <stdint.h>
#include "platform.h" // must be on include path

// types kept same
typedef uint64_t u64_t;

#define __I  volatile
#define __O  volatile
#define __IO volatile

// register struct unchanged
typedef struct {
  union {
    __IO uint64_t SPCR;
    struct {
      __IO uint64_t SPR      : 2;
      __IO uint64_t CPHA     : 1;
      __IO uint64_t CPOL     : 1;
      __IO uint64_t MSTR     : 1;
      __IO uint64_t reserved : 1;
      __IO uint64_t SPE      : 1;
      __IO uint64_t SPIE     : 1;
    } SPCR_b;
  };

  union {
    __IO uint64_t SPSR;
    struct {
      __I uint64_t RFEMPTY  : 1;
      __I uint64_t RFFULL   : 1;
      __I uint64_t WFEMPTY  : 1;
      __I uint64_t WFFULL   : 1;
      __I uint64_t reserved : 2;
      __IO uint64_t WCOL    : 1;
      __IO uint64_t SPIF    : 1;
    } SPSR_b;
  };

  union {
    __O uint64_t SPDR_w_buff;
    __I uint64_t SPDR_r_buff;
    struct { __O uint64_t data : 8; } SPDR_w_buff_b;
    struct { __I uint64_t data : 8; } SPDR_r_buff_b;
  };

  union {
    __IO uint64_t SPER;
    struct {
      __IO uint64_t ESPR     : 2;
      __IO uint64_t reserved : 4;
      __IO uint64_t ICNT     : 2;
    } SPER_b;
  };

  union {
    __IO uint64_t SSR;
    struct { __IO uint64_t SS : 1; } SSR_b;
  };

} SPI_Registers;

// Expose globals (declarations only)
extern SPI_Registers* SPI1;
extern SPI_Registers* SPI2;
extern SPI_Registers* SPI3;
extern SPI_Registers* SPI4;
extern SPI_Registers* SPI5;
extern SPI_Registers* SPI6;

// function prototypes (unchanged logic)
int spiInit(SPI_Registers* spitx_ctrl, bool master_mode = true);

int spiMasterWriteSequence(SPI_Registers* spitx_ctrl, u64_t* data, u64_t data_size, SPI_Registers* spitx_ctrl2);
int master_slave_tx(SPI_Registers* spitx_ctrl, u64_t* data, u64_t data_size);
int transfer(SPI_Registers* spitx_ctrl, u64_t* data, u64_t data_size, SPI_Registers* spitx_ctrl2,u64_t no_trans,u64_t csh, u64_t dummy_cycles);
int spiMasterRead(SPI_Registers* spitx_ctrl, u64_t* data, u64_t data_size) ;
int spiSlavePoll(SPI_Registers* spitx_ctrl, u64_t* out_buf, u64_t max_count);
int setSPIMasterSlaveMode(SPI_Registers* spi_base_ptr, bool master_mode);
#endif