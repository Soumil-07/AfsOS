#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/system.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

/* Updates the VGA cursor position to the current index */
void terminal_update_csr() {
    uint16_t temp = terminal_row * VGA_WIDTH + terminal_column;

    /* write the higher and lower byte of the VGA index position to indices 14 and 15 of the CRT Control Register */
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);

        terminal_update_csr();
}

void terminal_putchar(char c) {
    unsigned char uc = c;

    // Handle character output and terminal_row/column modification
    switch(c) {
      case '\n':
        terminal_row++;
        terminal_column = 0;
        break;

      default:
        terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
        terminal_column++;
    }

    // Handle validation on terminal_column before terminal_row, since the logic in terminal_column can update terminal_row
    if(terminal_column >= VGA_WIDTH) {
          terminal_column = 0;
          terminal_row++;
    }

    // Handle validating terminal_row, and scrolling the screen upwards if necessary.
    if(terminal_row >= VGA_HEIGHT) {
        // You shouldn't need terminal_print_error() since you are handling the case where terminal_row >= VGA_HEIGHT
        // terminal_print_error();

        // What does this line do? Appears to set the 16th character of the 16th row to the same value as the 5th character of the 1st row.
        // terminal_buffer[(15 * VGA_WIDTH) + 15] = terminal_buffer[(0 * VGA_WIDTH) + 4];

        size_t i, j;
        for(i = 0; i < VGA_WIDTH-1; i++) {
            for(j = VGA_HEIGHT-2; j > 0; j--) {
                terminal_buffer[(j * VGA_WIDTH) + i] = terminal_buffer[((j+1) * VGA_WIDTH) + i];
            }               
        }

        // Also clear out the bottom row
        for(i = 0; i < VGA_WIDTH-1; i++) {
            terminal_putentryat(' ', terminal_color, i, VGA_HEIGHT-1);
        }

        terminal_row = VGA_HEIGHT-1;
    }
}


void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}
