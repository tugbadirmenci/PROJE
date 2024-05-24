#include <Pire.h>

Pire PireOlustur(int sayisalDeger, char *isim, int satirSayisi, int sutunSayisi)
{
    Pire this;
    this = (Pire)malloc(sizeof(struct PIRE));
    this->isim = (char *)malloc(strlen(isim) + 1);
    if (this->isim == NULL)
    {
        // Bellek hatası
        free(this);
        return NULL;
    }
    strcpy(this->isim, isim);
    this->super = BocekOlustur(sayisalDeger, isim, satirSayisi, sutunSayisi);
    this->super->super->gorunum = &PireGorunumu;
    this->super->super->isimDegis = &PireIsimDegis;
    this->CanliYokEt = &PireYokEt;

    return this;
}

char* PireGorunumu(void* this)
{
    return ((Pire)this)->isim;
}

void PireIsimDegis(void* this, char* isim)
{
    free(((Pire)this)->isim);
    ((Pire)this)->isim = isim;
}

void PireYokEt(const Pire this)
{
    if (this == NULL)
        return;
    free(this);
}