OUTPUT_ARCH( "riscv" )

ENTRY( _start )

MEMORY
{
  ram (wxa!ri) : ORIGIN = 0x00000000, LENGTH = 64K
}

PHDRS
{
  rom_load PT_LOAD;
  ram_init PT_LOAD;
  ram_load PT_LOAD;
}

SECTIONS
{
  __stack_size = DEFINED(__stack_size) ? __stack_size : 4K;

  .init           :
  {
    KEEP (*(SORT_NONE(.init)))
  } > ram : ram_load

  .text           :
  {
    *(.text.unlikely .text.unlikely.*)
    *(.text.startup .text.startup.*)
    *(.text .text.*)
    *(.gnu.linkonce.t.*)
  } > ram : ram_load

  .fini           :
  {
    KEEP (*(SORT_NONE(.fini)))
  } > ram : ram_load

  PROVIDE (__etext = .);
  PROVIDE (_etext = .);
  PROVIDE (etext = .);

  .rodata         :
  {
    *(.rdata)
    *(.rodata .rodata.*)
    *(.gnu.linkonce.r.*)
  } > ram : ram_load

  . = ALIGN(8);

  .preinit_array  :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } > ram : ram_load

  .init_array     :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
    KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
    PROVIDE_HIDDEN (__init_array_end = .);
  } > ram : ram_load

  .fini_array     :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
    KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } > ram : ram_load

  .ctors          :
  {
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    /* We don't want to include the .ctor section from
       the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  } > ram : ram_load

  .dtors          :
  {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  } > ram : ram_load

  .lalign         :
  {
    . = ALIGN(8);
    PROVIDE( _data_lma = . );
  } > ram : ram_load

  .dalign         :
  {
    . = ALIGN(8);
    PROVIDE( _data = . );
  } > ram : ram_load

  .data          :
  {
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
  } > ram : ram_load

  .srodata        :
  {
    PROVIDE( _gp = . + 0x800 );
    *(.srodata.cst16)
    *(.srodata.cst8)
    *(.srodata.cst4)
    *(.srodata.cst2)
    *(.srodata .srodata.*)
  } > ram : ram_load

  .sdata          :
  {
    *(.sdata .sdata.*)
    *(.gnu.linkonce.s.*)
  } > ram : ram_load

  . = ALIGN(8);
  PROVIDE( _edata = . );
  PROVIDE( edata = . );

  PROVIDE( _fbss = . );
  PROVIDE( __bss_start = . );
  .bss            :
  {
    *(.sbss*)
    *(.gnu.linkonce.sb.*)
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(8);
  } > ram : ram_load

  . = ALIGN(8);
  PROVIDE( _end = . );
  PROVIDE( end = . );

  .stack ORIGIN(ram) + LENGTH(ram) - __stack_size :
  {
    PROVIDE( _heap_end = . );
    . = __stack_size;
    PROVIDE( _sp = . );
  } > ram : ram_load
}
