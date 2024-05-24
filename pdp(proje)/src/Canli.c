#include <Canli.h>

Canli CanliOlustur(int sayisalDeger, int satirSayisi, int sutunSayisi)
{
    Canli this;
    this = (Canli)malloc(sizeof(struct CANLI));
    this->CanliYokEt = &CanliYokEt;
    this->EsitMi = &EsitMi;
    this->DegerGetir = &DegerGetir;

    this->sayisalDeger = sayisalDeger;
    this->satirSayisi = satirSayisi;
    this->sutunSayisi = sutunSayisi;
    this->bitki = NULL;
    this->bocek = NULL;
    this->pire = NULL;
    this->sinek = NULL;
    // this->CanliDegerKiyas = &CanliDegerKiyas;
    return this;
}

boolean EsitMi(const Canli this, const Canli dgr)
{
    if (this == NULL || dgr == NULL)
        return false;
    return this->sayisalDeger == dgr->sayisalDeger;
}
void CanliYokEt(const Canli this)
{
    if (this == NULL)
        return;
    if (this->bitki != NULL)
        this->bitki->CanliYokEt(this->bitki);
    else if (this->bocek != NULL)
        this->bocek->CanliYokEt(this->bocek);
    else if (this->pire != NULL)
        this->pire->CanliYokEt(this->pire);
    else if (this->sinek != NULL)
        this->sinek->CanliYokEt(this->sinek);
    free(this);
}
int DegerGetir(const Canli this)
{
    if (this == NULL)
        return 0;
    return this->sayisalDeger;
}
