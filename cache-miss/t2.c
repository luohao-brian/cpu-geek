#include <stdlib.h>
#define MISS 39321600

int main(){
    int *p = (int*)malloc(MISS * sizeof(int));
    int i;
    for(i=0; i<MISS; i++) {
        p[i] = 1;
    }
}
