#include "common.h"

#include "console.h"
#include "platform/current/console.h"
#include "cpu/current/interrupt.h"
#include "memory.h"
#include "string.h"

#ifndef KMAIN_ARGS
	#define KMAIN_ARGS
#endif

void kmain(KMAIN_ARGS) {
	//interrupt_init();
	//enable_irqs();
	//enable_irq(cpu_timer);
	bool status = init_console();
	if(status) {
		write("Testing...\n");
		//process_atags(atags);
		//init_page_allocators();
	} else {
		//To do: error handling.
	}
}
