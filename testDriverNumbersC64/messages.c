#include <stdio.h>
#include <stdlib.h>
#include "stdarg.h"
#include "messages.h"

void test(char *fmt, ...) {
   va_list args;
   va_start(args, fmt);
   vprintf(fmt, args);
   va_end(args);
}
void check(decimal *dec, long ent, long fract) {
    if (dec->znumber != ent) {
        printf("KO\t Fail in integer. Expected %ld - Found %ld\n", dec->znumber, ent);
        exit(1);
    }
    if (dec->scale != fract) {
        printf("KO\t Fail in decimal. Expected %ld - Found %ld\n", dec->scale, fract);
        exit(1);
    }
    printf("OK\n");
}
