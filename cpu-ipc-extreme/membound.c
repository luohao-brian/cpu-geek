	 #include <stdlib.h>
	 #include <emmintrin.h>
	 #include <stdio.h>
	 #include <signal.h>

	 char a = 1;

	 void memory_bound() {
	         register unsigned i=0;
	         register char b;

	         for (i=0;i<(1u<<24);i++) {
	                 // evict cacheline containing a
 	                 _mm_clflush(&a);
 	                 b = a;
	         }
	 }

	 int main() {
	         memory_bound();
	         return 0;
	 }

