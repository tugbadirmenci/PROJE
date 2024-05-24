#include <Bocek.h>

Bocek BocekOlustur(int sayisalDeger, char *isim, int satirSayisi, int sutunSayisi)
{
    Bocek this;
    this = (Bocek)malloc(sizeof(struct BOCEK));
    this->isim = (char *)malloc(strlen(isim) + 1);
    if (this->isim == NULL)
    {
        // Bellek hatası
        free(this);
        return NULL;
    }
    strcpy(this->isim, isim);
    this->super = CanliOlustur(sayisalDeger, satirSayisi, sutunSayisi);
    this->super->gorunum = &BocekGorunumu;
    this->super->isimDegis = &BocekIsimDegis;
    this->CanliYokEt = &BocekYokEt;

    return this;
}

char* BocekGorunumu(void* this)
{
    return ((Bocek)this)->isim;
}

void BocekIsimDegis(void* this, char* isim)
{
    free(((Bocek)this)->isim);
    ((Bocek)this)->isim = isim;
}

void BocekYokEt(const Bocek this)
{
    if (this == NULL)
        return;
    free(this);
}