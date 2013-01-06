#include "common.h"

#include "atags.h"
#include "gpio.h"
#include "textcons.h"
#include "interrupt.h"
#include "string.h"
#include "timer.h"

//To do: peripheral read/write barriers!

void kmain(uint r0, uint system_type, AtagHeader* atags) {
	gpio_set_output(16);
	gpio_set(16);
	//interrupt_init();
	//enable_irqs();
	//enable_irq(cpu_timer);
	bool status = init_console();
	if(status) {
		process_atags(atags);
	}
}
