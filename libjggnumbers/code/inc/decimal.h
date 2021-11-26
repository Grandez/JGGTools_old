/*
* C version
* Use one struct
*/

#ifndef __DECIMAL_C__
#define __DECIMAL_C__

typedef struct __decimal {
    long znumber;
    long scale;
} decimal;

decimal *decimalChar (char *str);

#ifdef __cplusplus
extern "C" {
#endif



decimal *decimalFloat (float f);
decimal *decimalDouble(double f);
decimal *decimalLong  (long l);
decimal *decimalInt   (int i);
char*    decimalToChar        (decimal *dec);
char*    decimalToCharRounded (decimal *dec, int scale);   
float    decimalToFloat       (decimal *dec);
double   decimalToDouble      (decimal *dec);
long     decimalToFloor       (decimal *dec);
long     decimalToCeil        (decimal *dec);
decimal* decimalRound         (decimal *dec, int scale);

decimal* decimalAdd              (const decimal *a, const decimal *b);
decimal* decimalSubtract         (const decimal *a, const decimal *b);
decimal* decimalMultiply         (const decimal *a, const decimal *b);
decimal* decimalDivide           (const decimal *a, const decimal *b);

decimal* decimalAddInteger       (const decimal *a, long   value);
decimal* decimalSubtractInteger  (const decimal *a, long   value);
decimal* decimalMultiplyInteger  (const decimal *a, long   value);
decimal* decimalDivideInteger    (const decimal *a, long   value);
decimal* decimalAddFloat         (const decimal *a, double value);
decimal* decimalSubtractFloat    (const decimal *a, double value);
decimal* decimalMultiplyFloat    (const decimal *a, double value);
decimal* decimalDivideFloat      (const decimal *a, double value);

char decimalEQ (const decimal *a, const decimal *b);
char decimalNE (const decimal *a, const decimal *b);
char decimalGT (const decimal *a, const decimal *b);
char decimalGE (const decimal *a, const decimal *b);
char decimalLT (const decimal *a, const decimal *b);
char decimalLE (const decimal *a, const decimal *b);

#ifdef __cplusplus
}
#endif
#endif

