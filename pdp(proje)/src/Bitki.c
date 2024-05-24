#include <Bitki.h>
#include <stdlib.h>

Bitki BitkiOlustur(int sayisalDeger, char *isim, int satirSayisi, int sutunSayisi)
{
    Bitki this;
    this = (Bitki)malloc(sizeof(struct BITKI));
    // İsim için bellek ayır ve kopyala
    this->isim = (char *)malloc(strlen(isim) + 1);
    if (this->isim == NULL)
    {
        // Bellek hatası
        free(this);
        return NULL;
    }
    strcpy(this->isim, isim);
    this->super = CanliOlustur(sayisalDeger, satirSayisi, sutunSayisi);
    this->super->gorunum = &BitkiGorunumu;
    this->super->isimDegis = &BitkiIsimDegis;
    this->CanliYokEt = &BitkiYokEt;

    return this;
}

char* BitkiGorunumu(void* this)
{
    return ((Bitki)this)->isim;
}

void BitkiIsimDegis(void* this, char* isim)
{
    free(((Bitki)this)->isim);
    ((Bitki)this)->isim = isim;
}

void BitkiYokEt(const Bitki this)
{
    if (this == NULL)
        return;
    free(this);
}