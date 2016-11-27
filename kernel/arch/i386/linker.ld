/* This is the entry point for BoemiOS*/
ENTRY(_start)

SECTIONS {
	/* We load the kernel at 1M*/
	. = 1M;

	.text BLOCK(4096) : ALIGN(4096) {
		*(.multiboot) /* Load multiboot info */
		*(.text)
	}

	.data BLOCK(4096) : ALIGN(4096) {
		*(.data)
		*(.eh_frame)
	}

	.bss BLOCK(4096) : ALIGN(4096) {
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
		endkernel = .;
		endkernel = ALIGN(4096);
	}
}
