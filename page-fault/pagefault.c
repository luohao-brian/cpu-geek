/*
 * Page fault microbenchmark.
 * 
 * Build with:
 *
 * gcc -O2 -o page_fault page_fault.c
 *
 * Copyright (C) 2009 Anton Blanchard <anton@au.ibm.com>, IBM
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define PAGES (10*1024)

int main()
{
	unsigned long pgsize = getpagesize();
	unsigned long length = pgsize * PAGES;
	unsigned long i;

	while (1) {
		char *c = mmap(NULL, length, PROT_READ|PROT_WRITE,
			       MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
		if (c == MAP_FAILED) {
			perror("mmap");
			exit(1);
		}

		for (i = 0; i < length; i += pgsize)
			c[i] = 0;

		munmap(c, length);
	}
}
