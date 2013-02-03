
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdbool.h>

#define DIG_MAX 3
#define NUM_MAX 11

void showNumber(char dig, char num) {
  char nums[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111,
    0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111,
    0b01101111, 0b10000000};

  if (dig < DIG_MAX && num < NUM_MAX) {
    PORTB = 1 << dig;

    if (num == -1) {
      PORTD = 0b00000000;
    }
    else {
      PORTD = nums[num];
    }
  }
}

int main(void) {
  char currentNums[] = {-1, -1, -1};
  char n = 0, dig = 0;
  DDRB = 0b00000111;
  DDRD = 0b11111111;

  for (;;) {
    char i, l;

    currentNums[2] = currentNums[1];
    currentNums[1] = currentNums[0];
    currentNums[0] = n;

    for (i = 0; i < 100; i++) {
      for (l = 0; l < 3; l++) {
        showNumber(l, currentNums[l]);
        _delay_ms(3);
      }
    }

    if (++n >= NUM_MAX) n = 0;
    if (++dig >= 3) dig = 0;
  }

  return 0;
}
