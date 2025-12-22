OUTPUT_ARCH( "riscv" )

ENTRY( _start )

MEMORY
{
  ram (wxa!ri) : ORIGIN = 0x00000000, LENGTH = 128K
}

PHDRS
{
  rom_load PT_LOAD;
  ram_init PT_LOAD;
  ram_load PT_LOAD;
}


/*----------------------------------------------------------------------*/
/* Sections                            */
/*----------------------------------------------------------------------*/

SECTIONS
{
  __stack_size = DEFINED(__stack_size) ? __stack_size : 4K;

  /* C++ constructor and destructor initialization */

  .text.init :
  {
    *(.text.init)
    . = ALIGN(8);
  } > ram : ram_load

  .text :
  {
    *(.text.unlikely .text.unlikely.*)
    *(.text.startup .text.startup.*)
    *(.text .text.*)
    *(.gnu.linkonce.t.*)
    . = ALIGN(4);
  } > ram : ram_load

  .fini :
  {
    KEEP (*(SORT_NONE(.fini)))
  } >ram : ram_load

  .rodata :
  {
    *(.rdata)
    *(.rodata .rodata.*)
    *(.gnu.linkonce.r.*)
  } > ram : ram_load

  .preinit_array :
  {
    PROVIDE_HIDDEN(__preinit_array_start = .);
    KEEP(*(.preinit_array))
    PROVIDE_HIDDEN(__preinit_array_end = .);
  } > ram : ram_load

  .init_array :
  {
    PROVIDE_HIDDEN(__init_array_start = .);
    KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
    KEEP(*(.init_array EXCLUDE_FILE(*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o) .ctors))
    PROVIDE_HIDDEN(__init_array_end = .);
  } > ram : ram_load

  .fini_array :
  {
    PROVIDE_HIDDEN(__fini_array_start = .);
    KEEP(*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
    KEEP(*(.fini_array EXCLUDE_FILE(*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o) .dtors))
    PROVIDE_HIDDEN(__fini_array_end = .);
  } > ram : ram_load

  .ctors :
  {
    KEEP(*crtbegin.o(.ctors))
    KEEP(*crtbegin?.o(.ctors))
    KEEP(*(EXCLUDE_FILE(*crtend.o *crtend?.o) .ctors))
    KEEP(*(SORT(.ctors.*)))
    KEEP(*(.ctors))
  } > ram : ram_load

  .dtors :
  {
    KEEP(*crtbegin.o(.dtors))
    KEEP(*crtbegin?.o(.dtors))
    KEEP(*(EXCLUDE_FILE(*crtend.o *crtend?.o) .dtors))
    KEEP(*(SORT(.dtors.*)))
    KEEP(*(.dtors))
  } > ram : ram_load

  .lalign :
  {
    . = ALIGN(4);
    PROVIDE(_data_lma = .);
  } > ram : ram_load

  .dalign :
  {
    . = ALIGN(4);
    PROVIDE(_data = .);
  } > ram : ram_load

  .data :
  {
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    . = ALIGN(8);
  } > ram : ram_load

  .srodata :
  {
    *(.srodata.cst16)
    *(.srodata.cst8)
    *(.srodata.cst4)
    *(.srodata.cst2)
    *(.srodata .srodata.*)
  } > ram : ram_load

  .sdata :
  {
    . = ALIGN(8);
    __global_pointer$ = . + 0x800;
    *(.sdata .sdata.*)
    *(.gnu.linkonce.s.*)
    . = ALIGN(8);
  } > ram : ram_load

  . = ALIGN(4);
  PROVIDE(_edata = .);
  PROVIDE(edata = .);

  PROVIDE(_fbss = .);
  PROVIDE(__bss_start = .);

  .bss :
  {
    *(.sbss .sbss.* .gnu.linkonce.sb.*)
    *(.scommon)
    *(.bss)
    . = ALIGN(8);
  } > ram : ram_load

  _end = .;

  /* Define heap section */
  .heap :
  {
    . = ALIGN(8);
    PROVIDE(_heap_start = .);
    . = . + 8K;  /* 32KB heap size - adjust as needed */
    PROVIDE(_heap_end = .);
  } > ram : ram_load

  .stack :
  {
    . = ALIGN(8);
    . = . + __stack_size;
    _sp = .;
  } > ram : ram_load
}
