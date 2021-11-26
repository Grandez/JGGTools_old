#include "stdlib.h"
#include "config.h"

#include "decimal.h"
#include "decimal.hpp"

#ifdef _WIN32
#pragma warning( disable : 6011 )
#endif

using namespace NST;

decimal *_createDecimal(Decimal value) {
   decimal *dec = (decimal *) malloc(sizeof(decimal));
   dec->znumber = value.getIntPart();
   dec->scale   = value.getDecPart();
   return dec;
}
decimal *_mergeDecimal(Decimal d1, decimal* d2) {
   d2->znumber = d1.getIntPart();
   d2->scale   = d1.getDecPart();
   return d2;
}
Decimal _makeDecimal  (const decimal *dec) { return Decimal(dec->znumber, dec->scale); }
Decimal _makeDecimal  (decimal *dec)    { return Decimal(dec->znumber, dec->scale); }

extern "C" decimal *decimalChar  (const char *str) { return _createDecimal(Decimal(str)); }
decimal *decimalFloat (float  f)         { return _createDecimal(Decimal(f));   }
decimal *decimalDouble(double d)         { return _createDecimal(Decimal(d));   }
decimal *decimalLong  (long   l)         { return _createDecimal(Decimal(l));   }
decimal *decimalInt   (int    i)         { return _createDecimal(Decimal(i));   }
char*    decimalToChar        (decimal *dec) { return _makeDecimal(dec).toChar();   }
float    decimalToFloat       (decimal *dec) { return _makeDecimal(dec).toFloat();  }
double   decimalToDouble      (decimal *dec) { return _makeDecimal(dec).toDouble(); }
long     decimalToFloor       (decimal *dec) { return _makeDecimal(dec).toFloor();  }
long     decimalToCeil        (decimal *dec) { return _makeDecimal(dec).toCeil();   }
char*    decimalToCharRounded (decimal *dec, int scale) { return _makeDecimal(dec).toCharRounded(scale); }
decimal* decimalRound         (decimal *dec, int scale) { 
return _createDecimal(_makeDecimal(dec).round(scale));         
}

decimal* decimalAdd                  (decimal *a, const decimal *b) {
   Decimal d1 = _makeDecimal(a);
   Decimal d2 = _makeDecimal((decimal *) b);
   return _createDecimal(d1.add(d1, d2));
}
decimal* decimalSubtract             (decimal *a, const decimal *b) {
   Decimal d1 = _makeDecimal(a);
   Decimal d2 = _makeDecimal((decimal *) b);
   return _createDecimal(d1.subtract(d1, d2));
}
decimal* decimalMultiply             (decimal *a, const decimal *b) {
   Decimal d1 = _makeDecimal(a);
   Decimal d2 = _makeDecimal((decimal *) b);
   return _createDecimal(d1.multiply(d1, d2));
}
decimal* decimalDivide               (decimal *a, const decimal *b) {
   Decimal d1 = _makeDecimal(a);
   Decimal d2 = _makeDecimal((decimal *) b);
   return _createDecimal(d1.divide(d1, d2));
}

char decimalEQ (const decimal *a, const decimal *b) {
   Decimal d1 = _makeDecimal(a);
   Decimal d2 = _makeDecimal(b);
   return (d1 == d2) ? 0xFF : 0x00; 
}
char decimalNE (const decimal *a, const decimal *b) {
   Decimal d1 = _makeDecimal(a);
   Decimal d2 = _makeDecimal(b);
   return (d1 != d2) ? 0xFF : 0x00; 
}
char decimalGT (const decimal *a, const decimal *b) {
   Decimal d1 = _makeDecimal(a);
   Decimal d2 = _makeDecimal(b);
   return (d1 > d2) ? 0xFF : 0x00; 
}
char decimalGE (const decimal *a, const decimal *b) {
   Decimal d1 = _makeDecimal(a);
   Decimal d2 = _makeDecimal(b);
   return (d1 >= d2) ? 0xFF : 0x00; 
}
char decimalLT (const decimal *a, const decimal *b) {
   Decimal d1 = _makeDecimal(a);
   Decimal d2 = _makeDecimal(b);
   return (d1 < d2) ? 0xFF : 0x00; 
}
char decimalLE (const decimal *a, const decimal *b) {
   Decimal d1 = _makeDecimal(a);
   Decimal d2 = _makeDecimal(b);
   return (d1 <= d2) ? 0xFF : 0x00; 
}

decimal* decimalAddInteger       (decimal *a, long   value) {
   Decimal d1 = _makeDecimal(a);
   return _mergeDecimal(d1 += value, a);
}
decimal* decimalSubtractInteger  (decimal *a, long   value){
   Decimal d1 = _makeDecimal(a);
   return _mergeDecimal(d1 -= value, a);
}
decimal* decimalMultiplyInteger  (decimal *a, long   value){
   Decimal d1 = _makeDecimal(a);
   return _mergeDecimal(d1 *= value, a);
}
decimal* decimalDivideInteger    (decimal *a, long   value){
   Decimal d1 = _makeDecimal(a);
   return _mergeDecimal(d1 /= value, a);
}
decimal* decimalAddFloat         (decimal *a, double value){
   Decimal d1 = _makeDecimal(a);
   return _mergeDecimal(d1 += value, a);
}
decimal* decimalSubtractFloat    (decimal *a, double value){
   Decimal d1 = _makeDecimal(a);
   return _mergeDecimal(d1 -= value, a);
}
decimal* decimalMultiplyFloat    (decimal *a, double value){
   Decimal d1 = _makeDecimal(a);
   return _mergeDecimal(d1 *= value, a);
}
decimal* decimalDivideFloat      (decimal *a, double value){
   Decimal d1 = _makeDecimal(a);
   return _mergeDecimal(d1 /= value, a);
}
