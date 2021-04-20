SECTIONS{
    . = 0X41000000;
    .text :
    {
        start.o
        *(.text)
    }
    .rodata ALIGN(4) :
    {
        *(.rodata)
    }
    .data ALIGN(4) :
    {
        *(.data)
    }

    . = ALIGN(4);
    __bss_start = .;
    .bss ALIGN(4) :
    {
        *(.bss)
        *(.COMMON)
    }
    __bss_end = .;
}
