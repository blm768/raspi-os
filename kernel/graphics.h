#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "common.h"

#include "timer.h"

#include "barrier.h"

typedef ubyte color_rgb[3];
typedef ubyte color_rgba[4];

typedef struct {
	uint width, height;
	color_rgb* data;
} Bitmap;

typedef struct {
	uint width, height;
	uint vWidth, vHeight;
	volatile uint pitch;
	uint depth;
	uint x, y;
	color_rgb* volatile buffer;
	volatile size_t size;
} __attribute__((__aligned__(16))) FramebufferInfo;

typedef struct {
	uint box: 4;
	uint code: 28;
} Message;

/*
typdedef struct {
	volatile Message send;
	uint padding[3];
	volatile Message peek;
	volatile uint sender;
	volatile uint status;
	volatile uint config;
	volatile uint send;
} Mailbox;
*/

#define MAIL_RECV   (*(volatile uint*)0x2000B880)
#define MAIL_PEEK   (*(volatile uint*)0x2000B890)
#define MAIL_SEND   (*(volatile uint*)0x2000B8A0)
#define MAIL_STATUS (*(volatile uint*)0x2000B898)

static inline volatile int get_send_status() {
	return MAIL_STATUS & (1 << 31);
};

static inline void send_message(uint mBox, uint msg) {
	//peripheral_memory_barrier();
	while(get_send_status()) {}
	MAIL_SEND = mBox | msg;
}

static inline int get_recv_status() {
	return MAIL_STATUS & (1 << 30);
}

//To do: move.
static inline void busy_wait(uint usecs) {
	cpu_timer_set(usecs);
	cpu_timer_start();
	while(!cpu_timer_done()) {}
	cpu_timer_ack();
}

static inline uint recv_message(uint mBox) {
	uint msg;
	//peripheral_memory_barrier();
	do {
		while(get_recv_status()) {}
		msg = MAIL_RECV;
	} while((msg & 0xF) != mBox);
	return msg & ~0xF;
}

Bitmap get_framebuffer(size_t width, size_t height);

void blit(Bitmap src, Bitmap dest, uint x, uint y);

#endif
