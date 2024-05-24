#ifndef SINEK_H
#define SINEK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Bocek.h>

struct SINEK
{
    struct BOCEK* super;
    char *isim;
    void (*CanliYokEt)(struct SINEK *);
};

typedef struct SINEK *Sinek;
Sinek SinekOlustur(int, char *, int, int);
char* SinekGorunumu(void*);
void SinekIsimDegis(void*, char*);
void SinekYokEt(const Sinek);

#endif
