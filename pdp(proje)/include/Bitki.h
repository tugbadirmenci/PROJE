#ifndef BITKI_H
#define BITKI_H

#include <Canli.h>

struct BITKI
{
    struct CANLI* super;
    char *isim;
    void (*CanliYokEt)(struct BITKI *);
};

typedef struct BITKI *Bitki;
Bitki BitkiOlustur(int, char *, int, int);
char* BitkiGorunumu(void*);
void BitkiIsimDegis(void*, char*);
void BitkiYokEt(const Bitki);

#endif
