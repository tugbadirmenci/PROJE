#ifndef BOCEK_H
#define BOCEK_H

#include <Canli.h>

struct BOCEK
{
    struct CANLI* super;
    char *isim;
    void (*CanliYokEt)(struct BOCEK *);
};

typedef struct BOCEK *Bocek;
Bocek BocekOlustur(int, char *, int, int);
char* BocekGorunumu(void*);
void BocekIsimDegis(void*, char*);
void BocekYokEt(const Bocek);

#endif
