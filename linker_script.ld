MEMORY
{
	FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
	RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
}

g_flash = ORIGIN(FLASH);
g_ram = ORIGIN(RAM);
g_stack = ORIGIN(RAM) + LENGTH(RAM);

ENTRY(reset_handler)

SECTIONS
{
	.rovector :
	{
		KEEP(*(.rovector))
		. = ALIGN(4);
	} > FLASH

	.vector :
	{
		KEEP(*(.vector))
		. = ALIGN(4);
	} > RAM AT > FLASH

	.text :
	{
		*(.text)
		*(.text*)
		. = ALIGN(4);
	} > FLASH

	.rodata :
	{
		*(.rodata)
		*(.rodata*)
		. = ALIGN(4);
	} > FLASH

	.data :
	{
		*(.data)
		*(.data*)
		. = ALIGN(4);
	} > RAM AT > FLASH

	.bss :
	{
		__bss_start__ = .;
		*(.bss)
		*(.bss*)
		. = ALIGN(4);
		FILL(0)
		__bss_end__ = .;
	} > RAM
}
