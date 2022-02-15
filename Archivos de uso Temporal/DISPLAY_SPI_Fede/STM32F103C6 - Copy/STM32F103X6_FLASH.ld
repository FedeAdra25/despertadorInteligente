/*
 * In this linker script there is no heap available.
 * The stack start at the end of the ram segment.
 */


/*
 * Take a look in the "The GNU linker" manual, here you get
 * the following information about the "MEMORY":
 *
 * "The MEMORY command describes the location and size of 
 * blocks of memory in the target."
 */
MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 0x00008000
  RAM (rw) : ORIGIN = 0x20000000, LENGTH = 0x00002800
}

/*
 * And the "SECTION" is used for:
 *
 * "The SECTIONS command tells the linker how to map input
 * sections into output sections, and how to place the output
 * sections in memory.
 */
SECTIONS
{

   /*
    * The ".text" section is used for the code, and
    * read only (.rodata) data. Even the vectors (.vectors)
    * MUST be saved at the start of this section.
    */
   .text :
   {
      _stext = .;          /* Provide the name for the start of this section */
      
      CREATE_OBJECT_SYMBOLS
      KEEP(*(.vectors))
	  KEEP(*(.isr_vector))
      
      *(.text)
      *(.text.*)
	  
	  KEEP (*(.init))
            
      . = ALIGN(4);        /* Align the start of the rodata part */
      *(.rodata)
      *(.rodata.*)
      
      . = ALIGN(4);        /* Align the end of the section */
   } > FLASH = 0
   _etext = .;             /* Provide the name for the end of this section */
   
   
   /* used by the startup to initialize data */
   _sidata = LOADADDR(.data);
   /*
    * The ".data" section is used for initialized data
    * and for functions (.fastrun) which should be copied 
    * from flash to ram. This functions will later be
    * executed from ram instead of flash.
    */
   .data : AT (_etext)
   {
      . = ALIGN(4);        /* Align the start of the section */
      _sdata = .;          /* Provide the name for the start of this section */
      
      *(.data)
      *(.data.*)
      
      . = ALIGN(4);        /* Align the end of the section */
      _edata = .;          /* Provide the name for the end of this section */
   } > RAM
   

   /*
    * The ".bss" section is used for uninitialized data.
    * This section will be cleared by the startup code.
    */
   .bss :
   {
      . = ALIGN(4);        /* Align the start of the section */
      _sbss = .;           /* Provide the name for the start of this section */
      
      *(.bss)
      *(.bss.*)
      
      . = ALIGN(4);        /* Align the end of the section */
   } > RAM
   _ebss = .;              /* Provide the name for the end of this section */
   
   
   /* 
    * The ".stack" section is our stack.
    * Here this section starts at the end of the ram segment.
    */
   _estack = ORIGIN(RAM) + LENGTH(RAM);

}

/*** EOF **/

