#ifndef PIRE_H
#define PIRE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Bocek.h>

struct PIRE
{
    struct BOCEK* super;
    char *isim;
    void (*CanliYokEt)(struct PIRE *);
};

typedef struct PIRE *Pire;
Pire PireOlustur(int, char *, int, int);
char* PireGorunumu(void*);
void PireIsimDegis(void*, char*);
void PireYokEt(const Pire);

#endif
