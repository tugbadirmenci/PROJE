#include <Sinek.h>

Sinek SinekOlustur(int sayisalDeger, char *isim, int satirSayisi, int sutunSayisi)
{
    Sinek this;
    this = (Sinek)malloc(sizeof(struct SINEK));
    this->isim = (char *)malloc(strlen(isim) + 1);
    if (this->isim == NULL)
    {
        // Bellek hatası
        free(this);
        return NULL;
    }
    strcpy(this->isim, isim);
    this->super = BocekOlustur(sayisalDeger, isim, satirSayisi, sutunSayisi);
    this->super->super->gorunum = &SinekGorunumu;
    this->super->super->isimDegis = &SinekIsimDegis;
    this->CanliYokEt = &SinekYokEt;
    
    return this;
};

char* SinekGorunumu(void* this)
{
    return ((Sinek)this)->isim;
}

void SinekIsimDegis(void* this, char* isim)
{
    free(((Sinek)this)->isim);
    ((Sinek)this)->isim = isim;
}

void SinekYokEt(const Sinek this)
{
    if (this == NULL)
        return;
    free(this);
}