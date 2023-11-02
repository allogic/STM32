/* Linker script for STM32 microcontrollers */

/* Define the memory regions */
MEMORY
{
  FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 512K
  RAM   (rwx)     : ORIGIN = 0x20000000, LENGTH = 64K
}

/* Stack and heap memory (optional) */
_stack = ORIGIN(RAM) + LENGTH(RAM);

/* Define the entry point (reset handler) */
ENTRY(Reset_Handler)

/* Sections of the program */
SECTIONS
{
  /* The vector table located at the beginning of flash */
  .isr_vector :
  {
    KEEP(*(.isr_vector))    /* Interrupt vectors */
    . = ALIGN(4);
  } >FLASH

  /* Program code */
  .text :
  {
    *(.text)               /* Application code */
    . = ALIGN(4);
  } >FLASH

  /* Read-only data */
  .rodata :
  {
    *(.rodata)             /* Read-only data */
    . = ALIGN(4);
  } >FLASH

  /* Data section */
  .data : AT ( ADDR(.text) + SIZEOF(.text) )
  {
    *(.data)               /* Initialized data */
    . = ALIGN(4);
  } >RAM

  /* BSS section */
  .bss :
  {
    *(.bss)                /* Uninitialized data */
    . = ALIGN(4);
  } >RAM
}