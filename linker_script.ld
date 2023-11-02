MEMORY
{
	FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 512K
	RAM   (rwx)     : ORIGIN = 0x20000000, LENGTH = 64K
}

_stack = ORIGIN(RAM) + LENGTH(RAM);

ENTRY(Reset_Handler)

SECTIONS
{
	.isr_vector :
	{
		KEEP(*(.isr_vector))
		. = ALIGN(4);
	} > FLASH

	.text :
	{
		*(.text)
		. = ALIGN(4);
	} > FLASH

	.rodata :
	{
		*(.rodata)
		. = ALIGN(4);
	} > FLASH

	.data : AT ( ADDR(.text) + SIZEOF(.text) )
	{
		*(.data)
		. = ALIGN(4);
	} > RAM

	.bss :
	{
		*(.bss)
		. = ALIGN(4);
	} > RAM
}
