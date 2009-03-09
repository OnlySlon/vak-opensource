/*
 * Copyright (C) 2005 Serge Vakulenko, <vak@cronyx.ru>
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You can redistribute this file and/or modify it under the terms of the GNU
 * General Public License (GPL) as published by the Free Software Foundation;
 * either version 2 of the License, or (at your discretion) any later version.
 * See the accompanying file "COPYING" for more details.
 */
#include "io.h"
#include "io2313.h"

/* ���� �� ������ ������. */
unsigned char button_pressed;
unsigned char button_disabled;

/* ������ ���������� �� �������� - � ��������� �����. */
extern unsigned char *pic_table [];

/*
 * �������������� �������� - ��� ������ 4 MHz.
 */
void usleep (unsigned char usec)
{
	do {
		/* ����� ������ ����� �� ����.
		 * ��� ����� ������ �� ��������� � �������,
		 * ���� ���� �������� �������. */
		asm volatile ("nop");
	} while (--usec);
}

/*
 * �������������� ��������.
 */
void msleep (unsigned char msec)
{
	do {
		usleep (250);
		usleep (250);
		usleep (250);
		usleep (250);
	} while (--msec);
}

/*
 * ����������� ������ ������� � ������� ���������� �����������.
 */
void frame (unsigned char *data, int msec)
{
	unsigned char i;

	/* ����� ������ �� ����������, ��� �������
	 * � ������ 0 � � ������� 1 (PORTB=0, PORTD=1). */
	while (msec > 0) {
		for (i=0; i<7; ++i) {
			/* ������ ������ ����� i � ������� 1 ������������. */
			outb (~(1 << i), PORTB);
			outb (readb (data + i), PORTD);
			msleep (1);
		}
		msec -= 7;

		/* ����� ������ ������������ ������ - ���� B7. */
		if (testb (7, PINB)) {
			/* ������ �� ������. */
			if (button_disabled)
				button_disabled = 0;
		} else {
			/* ������ ������. */
			if (! button_disabled) {
				button_pressed = 1;
				return;
			}
		}
	}
}

/*
 * ����������� ������������������ ��������.
 */
void show (unsigned char *data)
{
	while (readb (data) != 0xff) {
		/* ������ ���� ������������ 125 �����������. */
		frame (data, 125);
		if (button_pressed)
			return;
		data += 7;
	}
}

int main ()
{
	/* ����� �������. */
	int n = 0;

	/*
	 * ������������� ����������� ������ �����-������:
	 * D0-D6 - ����� - ������� 1-7.
	 * B0-B6 - ����� - ������ 7-1.
	 * B7 - ���� - ������ ������������ ������.
	 */
	outb (0x7f, DDRB);
	outb (0x7f, DDRD);

	for (;;) {
		show (pic_table [n]);

		/* ���� ���� ������ ������ - ������ �������. */
		if (button_pressed) {
			++n;
			if (! pic_table [n])
				n = 0;

			/* ����� ������������ ��������� ������� �� ������,
			 * ���� ��� �� ����� ������. ����� �� ����
			 * �������� ������������. */
			button_disabled = 1;
			button_pressed = 0;
		}
	}
}
