void cpu_bound() {
    register unsigned i=0;
    for (i=0;i<(1u<<31);i++) {
        __asm__ ("nop\nnop\nnop");
    }
 }

 int main() {
    cpu_bound();
    return 0;
 }
