#ifndef CANLI_H
#define CANLI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Bitki.h"
#include "Bocek.h"
#include "Pire.h"
#include "Sinek.h"

typedef enum
{
    false,
    true
} boolean;

struct CANLI
{
    int sayisalDeger;
    int (*DegerGetir)(struct CANLI *);
    // void (*CanliDegerKiyas)(struct CANLI *, struct CANLI *);
    void (*CanliYokEt)(struct CANLI *);
    boolean (*EsitMi)(struct CANLI *, struct CANLI *);
    char* (*gorunum)(void*); // void*
    void (*isimDegis)(void*, char*);
    int satirSayisi;
    int sutunSayisi;
    struct BITKI* bitki;
    struct BOCEK* bocek;
    struct PIRE* pire;
    struct SINEK* sinek;
};

typedef struct CANLI *Canli;

Canli CanliOlustur(int, int, int);
int DegerGetir(const Canli);
boolean EsitMi(const Canli, const Canli);
void CanliDegerKiyas(const Canli, const Canli);
void CanliYokEt(const Canli);

#endif
