MEMORY
{
	FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
	RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
}

__flash__ = ORIGIN(FLASH);
__ram__   = ORIGIN(RAM);
__stack__ = ORIGIN(RAM) + LENGTH(RAM);

ENTRY(reset_handler)

SECTIONS
{
	.vector :
	{
		__vector_start__ = .;
		KEEP(*(.vector))
		. = ALIGN(4);
		__vector_end__ = .;
	} > RAM AT > FLASH

	__vector_init__ = LOADADDR(.vector);

	.text :
	{
		__text_start__ = .;
		*(.text)
		*(.text*)
		. = ALIGN(4);
		*(.rodata)
		*(.rodata*)
		. = ALIGN(4);
		__text_end__ = .;
	} > FLASH

	.data :
	{
		__data_start__ = .;
		*(.data)
		*(.data*)
		. = ALIGN(4);
		__data_end__ = .;
	} > RAM AT > FLASH

	__data_init__ = LOADADDR(.data);

	.bss :
	{
		__bss_start__ = .;
		*(.bss)
		*(.bss*)
		. = ALIGN(4);
		__bss_end__ = .;
	} > RAM
}
