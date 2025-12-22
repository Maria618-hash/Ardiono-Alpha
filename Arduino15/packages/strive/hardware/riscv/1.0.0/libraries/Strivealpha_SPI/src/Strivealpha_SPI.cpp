#include "Strivealpha_SPI.h"
#include <stdint.h>
#define SPI_MODE_OFFSET 0xC0

#if defined(STRIVE_1alpha)

SPI_Registers* SPI1 = (SPI_Registers*)SPI1_ACCEL_BASE_ADDR;
SPI_Registers* SPI2 = (SPI_Registers*)SPI2_ACCEL_BASE_ADDR;
SPI_Registers* SPI3 = (SPI_Registers*)SPI3_ACCEL_BASE_ADDR;
SPI_Registers* SPI4 = (SPI_Registers*)SPI4_ACCEL_BASE_ADDR;
SPI_Registers* SPI5 = (SPI_Registers*)SPI5_ACCEL_BASE_ADDR;
SPI_Registers* SPI6 = (SPI_Registers*)SPI6_ACCEL_BASE_ADDR;

#endif

// Set master or slave mode for the SPI based on its SPI_Registers pointer
int setSPIMasterSlaveMode(SPI_Registers *spi_base_ptr, bool master_mode)
{
    if (spi_base_ptr == NULL)
        return -1;

    volatile uint32_t *mode_reg =
        (volatile uint32_t *)((uintptr_t)spi_base_ptr + SPI_MODE_OFFSET);

    *mode_reg = master_mode ? 1 : 0;

    return 0;
}

int spiInit(SPI_Registers* spitx_ctrl, bool master_mode)
{
  spitx_ctrl->SPER_b.ICNT = 1; // make icnt = 1
  spitx_ctrl->SPER_b.ESPR = 0; // make icnt = 0 
  spitx_ctrl->SPCR_b.SPIE = 0; // no interrupt
   spitx_ctrl->SPCR_b.MSTR = master_mode ? 1 : 0; // set master = 1
  spitx_ctrl->SPCR_b.CPOL = 1; // for polarity
  spitx_ctrl->SPCR_b.CPHA = 1; // c-phase
  spitx_ctrl->SPCR_b.SPR  = 0; // to set the clock
  spitx_ctrl->SPCR_b.SPE  = 1; //
  return 0;
}

// Port of your master_slave_tx2
int spiMasterWriteSequence(SPI_Registers* spitx_ctrl, u64_t* data, u64_t data_size, SPI_Registers* spitx_ctrl2)
{
    uint64_t data_index = 0;
    uint64_t read_cnt = 0;

    spitx_ctrl->SSR_b.SS = 1;
    spitx_ctrl->SPDR_w_buff_b.data = data[data_index];
    data_index = data_index + 1;

    while(1 & (data_index <data_size)){
        spitx_ctrl->SSR_b.SS = 1;
        spitx_ctrl->SPDR_w_buff_b.data = data[data_index];
        data_index = data_index + 1;
        while(spitx_ctrl->SPSR_b.WFEMPTY == 0){
        spitx_ctrl->SSR_b.SS = 1;
        }

        if(data_index == 4 || data_index == 13 ){

          spitx_ctrl->SSR_b.SS = 0;

        }
        
        // CPOL=CPHA=0 and CS for read commands
        if(data_index == 4){
          
          spitx_ctrl->SPCR_b.CPOL = 0; // for polarity
          spitx_ctrl->SPCR_b.CPHA = 0; // c-phase
          spitx_ctrl2->SPCR_b.CPOL = 0; // for polarity
          spitx_ctrl2->SPCR_b.CPHA = 0; // c-phase

        }

    }
        return 0;   

  }
  
// Port of your master_rx
int spiMasterRead(SPI_Registers* spitx_ctrl, u64_t* data, u64_t data_size){

  volatile u64_t data_index = 0;
  while(1 & (data_index <data_size)){
    spitx_ctrl->SSR_b.SS = 1;
    spitx_ctrl->SPDR_w_buff_b.data = 0;
   
    while(spitx_ctrl->SPSR_b.RFEMPTY == 1){
        spitx_ctrl->SSR_b.SS = 1;
        
    }
    spitx_ctrl->SSR_b.SS = 0;
    data[data_index] = spitx_ctrl->SPDR_r_buff_b.data;      
    data_index = data_index + 1;


  }
  return 0;

}



// Test Sequences for master_slave_tx
int master_slave_tx(SPI_Registers* spitx_ctrl, u64_t* data, u64_t data_size)
{
    uint64_t data_index = 0;

    spitx_ctrl->SSR_b.SS = 1;
    spitx_ctrl->SPDR_w_buff_b.data = data[data_index];
    data_index = data_index + 1;


    while(1 & (data_index <data_size)){
      //if(spitx_ctrl->SPDR_b.txf_e_ind == 1){
        spitx_ctrl->SSR_b.SS = 1;
        spitx_ctrl->SPDR_w_buff_b.data = data[data_index];
        data_index = data_index + 1;
        while(spitx_ctrl->SPSR_b.WFEMPTY == 0){
        spitx_ctrl->SSR_b.SS = 1;
        }
        if(spitx_ctrl->SPSR_b.WFEMPTY == 1){
            spitx_ctrl->SSR_b.SS = 0;
        }

    }
  return 0;
}

int transfer(SPI_Registers* spitx_ctrl, u64_t* data, u64_t data_size, SPI_Registers* spitx_ctrl2,u64_t no_trans,u64_t csh, u64_t dummy_cycles){
  
    u64_t data_index = 0;
    u64_t read_cnt = 0;

    spitx_ctrl->SSR_b.SS = 1;
    spitx_ctrl->SPDR_w_buff_b.data = data[data_index];
    data_index = data_index + 1;

    while(1 & (data_index <data_size)){
        spitx_ctrl->SSR_b.SS = 1;
        spitx_ctrl->SPDR_w_buff_b.data = data[data_index];
        data_index = data_index + 1;
        while(spitx_ctrl->SPSR_b.WFEMPTY == 0){
        spitx_ctrl->SSR_b.SS = 1;
        }

        // CS high after each write command
        if(data_index <= (no_trans*csh +4)) {
          if(data_index % csh == 4) {
            spitx_ctrl->SSR_b.SS = 0;
          }

        }
        // CS high after each read command
        else{
          read_cnt= read_cnt+1;
          if((read_cnt % (csh+(dummy_cycles/8))) == 0) {
              spitx_ctrl->SSR_b.SS = 0;
            }
        }
        
        // CPOL=CPHA=0 for read commands
        if(data_index == ((no_trans*csh)+4) ){
          
          spitx_ctrl->SPCR_b.CPOL = 0; // for polarity
          spitx_ctrl->SPCR_b.CPHA = 0; // c-phase
          spitx_ctrl2->SPCR_b.CPOL = 0; // for polarity
          spitx_ctrl2->SPCR_b.CPHA = 0; // c-phase
        }

    }
  return 0;
}
// Port of your spiSlavePoll
int spiSlavePoll(SPI_Registers* spitx_ctrl, u64_t* out_buf, u64_t max_count) {
  if (!spitx_ctrl || !out_buf || max_count == 0) return -1;
  u64_t idx = 0;
  while (idx < max_count) {
    if (spitx_ctrl->SPSR_b.RFEMPTY == 0) {
      out_buf[idx++] = spitx_ctrl->SPDR_r_buff_b.data;
    } else {
      break;
    }
  }
  return (int)idx;
}

