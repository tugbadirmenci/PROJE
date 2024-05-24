#include "Habitat.h"
#include <Bocek.h>
#include <Bitki.h>
#include <Sinek.h>
#include <Pire.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

Habitat habitatOlustur()
{
    Habitat this;
    this = (Habitat)malloc(sizeof(struct HABITAT));
    this->elemeBaslat = &elemeBaslat;

    List list = NULL;
    this->sayac = 0;
    this->listSize = 0;
    this->listCapacity = 0;
    //this->elemeSonrasi = &elemeSonrasi;
    //this->yoket = &elemeYokEt;
    return this;
};

void habitataEkle(Habitat habitat, int canliDeger, int satirSayisi, int sutunSayisi)
{
    if (canliDeger >= 1 && canliDeger <= 9)
    {
        Bitki b = BitkiOlustur(canliDeger, "B", satirSayisi, sutunSayisi);
        b->super->bitki = b;
        habitat->list[habitat->sayac] = b->super;
        habitat->listSize++;
        //printf("%s ", b->isim);
    }
    else if (canliDeger >= 10 && canliDeger <= 20)
    {
        Bocek c = BocekOlustur(canliDeger, "C", satirSayisi, sutunSayisi);
        c->super->bocek = c;
        habitat->list[habitat->sayac] = c->super;
        habitat->listSize++;
        //printf("%s ", c->isim);
    }
    else if (canliDeger >= 21 && canliDeger <= 50)
    {
        Sinek s = SinekOlustur(canliDeger, "S", satirSayisi, sutunSayisi);
        s->super->super->sinek = s;
        habitat->list[habitat->sayac] = s->super->super;
        habitat->listSize++;
        //printf("%s ", s->isim);
    }
    else if (canliDeger >= 51 && canliDeger <= 99)
    {
        Pire p = PireOlustur(canliDeger, "P", satirSayisi, sutunSayisi);
        p->super->super->pire = p;
        habitat->list[habitat->sayac] = p->super->super;
        habitat->listSize++;
        //printf("%s ", p->isim);
    }
    habitat->sayac++;
}

void elemeBaslat(Habitat this, const char *dosyaAdi, int* ptr1, int* ptr2)
{
    FILE *dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL)
    {
        printf("Dosya acilamadi.\n");
        return;
    }
    int canliDeger, canliSayisi;
    canliSayisi = 0;
    while (fscanf(dosya, "%d\n", &canliDeger) != EOF)
    {
        canliSayisi++;
    }
    rewind(dosya);

    char satir[(canliSayisi*2)+canliSayisi+2];
    int satirSayisi = 0;
    while (fgets(satir, ((canliSayisi*2)+canliSayisi+2), dosya) != NULL)
    {
        satirSayisi++;
    }
    rewind(dosya);

    int sutunSayisi = 0;
    sutunSayisi = canliSayisi / satirSayisi;
    *ptr1 = satirSayisi;
    *ptr2 = sutunSayisi;
    this->list = (List)malloc(sizeof(Canli) * satirSayisi * sutunSayisi);
    this->listCapacity = satirSayisi * sutunSayisi;
    int x = 0; int y = 0;
    while (fscanf(dosya, "%d\n", &canliDeger) != EOF)
    {
        if (y == sutunSayisi)
        {
            y = 0;
            x++;
        }
        habitataEkle(this, canliDeger, x, y);
        y++;
    }
    this->sayac = 0;

    for(int i=0; i<satirSayisi; i++)
    {
        for(int j=0; j<sutunSayisi; j++)
        {
            int sira = i * sutunSayisi + j;

            boolean bitkiKontrol = bitkiMi(this->list[sira]);
            boolean bocekKontrol = bocekMi(this->list[sira]);
            boolean pireKontrol = pireMi(this->list[sira]);
            boolean sinekKontrol = sinekMi(this->list[sira]);

            if (bitkiKontrol == true)
                printf("%s ", this->list[sira]->gorunum(this->list[sira]->bitki));
            else if (bocekKontrol == true)
                printf("%s ", this->list[sira]->gorunum(this->list[sira]->bocek));
            else if (pireKontrol == true)
                printf("%s ", this->list[sira]->gorunum(this->list[sira]->pire));
            else if (sinekKontrol == true)
                printf("%s ", this->list[sira]->gorunum(this->list[sira]->sinek));
        }
        printf("\n");
    }
    printf("\n");
}

void oyunuBaslat(Habitat habitat, int satirSayisi, int sutunSayisi) {
    // Oyun başlatma işlemleri
    // Oyun başlatılıyor mesajı
    // Ana oyun döngüsü

    Canli kazanan = NULL;    
    while (habitat->listSize > 1) {
        clearScreen(); // Ekranı temizle

        // Canlılar arasındaki mücadele ve yeme işlemleri
        for (int i = 0; i < habitat->listSize; i++) {
            char* isim = "";
            boolean bitkiKontrol = bitkiMi(habitat->list[i]);
            boolean bocekKontrol = bocekMi(habitat->list[i]);
            boolean pireKontrol = pireMi(habitat->list[i]);
            boolean sinekKontrol = sinekMi(habitat->list[i]);
            if (bitkiKontrol == true)
                isim = habitat->list[i]->gorunum(habitat->list[i]->bitki);
            else if (bocekKontrol == true)
                isim = habitat->list[i]->gorunum(habitat->list[i]->bocek);
            else if (pireKontrol == true)
                isim = habitat->list[i]->gorunum(habitat->list[i]->pire);
            else if (sinekKontrol == true)
                isim = habitat->list[i]->gorunum(habitat->list[i]->sinek);

            boolean kirilsinMi = false;
            if (isim[0] == 'B') { // Bitki ise
                for (int j = i+1; j < habitat->listSize; j++) {
                    kirilsinMi = false; // silinebilir
                    bitkiKontrol = bitkiMi(habitat->list[j]);
                    bocekKontrol = bocekMi(habitat->list[j]);
                    pireKontrol = pireMi(habitat->list[j]);
                    sinekKontrol = sinekMi(habitat->list[j]);
                    if (bitkiKontrol == true)
                        isim = habitat->list[j]->gorunum(habitat->list[j]->bitki);
                    else if (bocekKontrol == true)
                        isim = habitat->list[j]->gorunum(habitat->list[j]->bocek);
                    else if (pireKontrol == true)
                        isim = habitat->list[j]->gorunum(habitat->list[j]->pire);
                    else if (sinekKontrol == true)
                        isim = habitat->list[j]->gorunum(habitat->list[j]->sinek);
                    
                    if (isim[0] == 'S') { // Sinek'i yiyor
                        habitat->list[j]->isimDegis(habitat->list[j]->sinek, "X");
                    } else if (isim[0] == 'P') { // Pire'yi yiyor
                        habitat->list[j]->isimDegis(habitat->list[j]->pire, "X");
                    }
                    else {
                        if (isim[0] == 'C') { // Bitki yenir
                            habitat->list[i]->isimDegis(habitat->list[i]->bitki, "X");
                            i = j-1;
                            kirilsinMi = true;
                        } else if (isim[0] == 'B') {
                            int mesafeIlk = abs(habitat->list[i]->satirSayisi - satirSayisi) + abs(habitat->list[i]->sutunSayisi - sutunSayisi);
                            int mesafeIkinci = abs(habitat->list[j]->satirSayisi - satirSayisi) + abs(habitat->list[j]->sutunSayisi - sutunSayisi);
                            if (habitat->list[i]->sayisalDeger > habitat->list[j]->sayisalDeger ||
                                (habitat->list[i]->sayisalDeger == habitat->list[j]->sayisalDeger &&
                                    mesafeIlk > mesafeIkinci)) {
                                habitat->list[j]->isimDegis(habitat->list[j]->bitki, "X"); // Yenilen canlı ölüp X oluyor
                            } else {
                                habitat->list[i]->isimDegis(habitat->list[i]->bitki, "X");
                                i = j-1;
                                kirilsinMi = true;
                            }
                        }
                    }

                    for(int i=0; i<satirSayisi; i++)
                    {
                        for(int j=0; j<sutunSayisi; j++)
                        {
                            int sira = i * sutunSayisi + j;

                            boolean bitkiKontrol = bitkiMi(habitat->list[sira]);
                            boolean bocekKontrol = bocekMi(habitat->list[sira]);
                            boolean pireKontrol = pireMi(habitat->list[sira]);
                            boolean sinekKontrol = sinekMi(habitat->list[sira]);

                            if (bitkiKontrol == true)
                                printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->bitki));
                            else if (bocekKontrol == true)
                                printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->bocek));
                            else if (pireKontrol == true)
                                printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->pire));
                            else if (sinekKontrol == true)
                                printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->sinek));
                        }
                        printf("\n");
                    }
                    clearScreen();
                    printf("\n"); // bunlar da silinebilir system cls yapınca anlamı yok

                    if (kirilsinMi == true)
                        break;
                }
            } else if (isim[0] == 'C') { // Bocek ise, diğer koşullar da benzer şekilde kontrol edilir
                for (int j = i+1; j < habitat->listSize; j++) {
                    kirilsinMi = false;
                    bitkiKontrol = bitkiMi(habitat->list[j]);
                    bocekKontrol = bocekMi(habitat->list[j]);
                    pireKontrol = pireMi(habitat->list[j]);
                    sinekKontrol = sinekMi(habitat->list[j]);
                    if (bitkiKontrol == true)
                        isim = habitat->list[j]->gorunum(habitat->list[j]->bitki);
                    else if (bocekKontrol == true)
                        isim = habitat->list[j]->gorunum(habitat->list[j]->bocek);
                    else if (pireKontrol == true)
                        isim = habitat->list[j]->gorunum(habitat->list[j]->pire);
                    else if (sinekKontrol == true)
                        isim = habitat->list[j]->gorunum(habitat->list[j]->sinek);
                    
                    if (isim[0] == 'B') { // Bitki'yi yiyor
                        habitat->list[j]->isimDegis(habitat->list[j]->bitki, "X");
                    } else if (isim[0] == 'P') { // Pire'yi yiyor
                        habitat->list[j]->isimDegis(habitat->list[j]->pire, "X");
                    }
                    else {
                        if (isim[0] == 'S') {
                            habitat->list[i]->isimDegis(habitat->list[i]->bocek, "X");
                            i = j-1;
                            kirilsinMi = true;
                        } else if (isim[0] == 'C') {
                            int mesafeIlk = abs(habitat->list[i]->satirSayisi - satirSayisi) + abs(habitat->list[i]->sutunSayisi - sutunSayisi);
                            int mesafeIkinci = abs(habitat->list[j]->satirSayisi - satirSayisi) + abs(habitat->list[j]->sutunSayisi - sutunSayisi);
                            if (habitat->list[i]->sayisalDeger > habitat->list[j]->sayisalDeger ||
                                (habitat->list[i]->sayisalDeger == habitat->list[j]->sayisalDeger &&
                                    mesafeIlk > mesafeIkinci)) {
                                habitat->list[j]->isimDegis(habitat->list[j]->bocek, "X"); // Yenilen canlı ölüp X oluyor
                            } else {
                                habitat->list[i]->isimDegis(habitat->list[i]->bocek, "X");
                                i = j-1;
                                kirilsinMi = true;
                            }
                        }
                    }

                    for(int i=0; i<satirSayisi; i++)
                    {
                        for(int j=0; j<sutunSayisi; j++)
                        {
                            int sira = i * sutunSayisi + j;

                            boolean bitkiKontrol = bitkiMi(habitat->list[sira]);
                            boolean bocekKontrol = bocekMi(habitat->list[sira]);
                            boolean pireKontrol = pireMi(habitat->list[sira]);
                            boolean sinekKontrol = sinekMi(habitat->list[sira]);

                            if (bitkiKontrol == true)
                                printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->bitki));
                            else if (bocekKontrol == true)
                                printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->bocek));
                            else if (pireKontrol == true)
                                printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->pire));
                            else if (sinekKontrol == true)
                                printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->sinek));
                        }
                        printf("\n");
                    }
                    clearScreen();
                    printf("\n");

                    if (kirilsinMi == true)
                        break;
                }
            } else if (isim[0] == 'S') { // Sinek ise, diğer koşullar da benzer şekilde kontrol edilir
                for (int j = i+1; j < habitat->listSize; j++) {
                    kirilsinMi = false;
                    bitkiKontrol = bitkiMi(habitat->list[j]);
                    bocekKontrol = bocekMi(habitat->list[j]);
                    pireKontrol = pireMi(habitat->list[j]);
                    sinekKontrol = sinekMi(habitat->list[j]);
                    if (bitkiKontrol == true)
                        isim = habitat->list[j]->gorunum(habitat->list[j]->bitki);
                    else if (bocekKontrol == true)
                        isim = habitat->list[j]->gorunum(habitat->list[j]->bocek);
                    else if (pireKontrol == true)
                        isim = habitat->list[j]->gorunum(habitat->list[j]->pire);
                    else if (sinekKontrol == true)
                        isim = habitat->list[j]->gorunum(habitat->list[j]->sinek);
                    
                    if (isim[0] == 'C') { // Bocek'i yiyor
                        habitat->list[j]->isimDegis(habitat->list[j]->bocek, "X");
                    } else if (isim[0] == 'P') {
                        habitat->list[j]->isimDegis(habitat->list[j]->pire, "X");
                    }
                    else {
                        if (isim[0] == 'B') {
                            habitat->list[i]->isimDegis(habitat->list[i]->sinek, "X");
                            i = j-1;
                            kirilsinMi = true;
                        } else if (isim[0] == 'S') {
                            int mesafeIlk = abs(habitat->list[i]->satirSayisi - satirSayisi) + abs(habitat->list[i]->sutunSayisi - sutunSayisi);
                            int mesafeIkinci = abs(habitat->list[j]->satirSayisi - satirSayisi) + abs(habitat->list[j]->sutunSayisi - sutunSayisi);
                            if (habitat->list[i]->sayisalDeger > habitat->list[j]->sayisalDeger ||
                                (habitat->list[i]->sayisalDeger == habitat->list[j]->sayisalDeger &&
                                    mesafeIlk > mesafeIkinci)) {
                                habitat->list[j]->isimDegis(habitat->list[j]->sinek, "X"); // Yenilen canlı ölüp X oluyor
                            } else {
                                habitat->list[i]->isimDegis(habitat->list[i]->sinek, "X");
                                i = j-1;
                                kirilsinMi = true;
                            }
                        }
                    }

                    for(int i=0; i<satirSayisi; i++)
                    {
                        for(int j=0; j<sutunSayisi; j++)
                        {
                            int sira = i * sutunSayisi + j;

                            boolean bitkiKontrol = bitkiMi(habitat->list[sira]);
                            boolean bocekKontrol = bocekMi(habitat->list[sira]);
                            boolean pireKontrol = pireMi(habitat->list[sira]);
                            boolean sinekKontrol = sinekMi(habitat->list[sira]);

                            if (bitkiKontrol == true)
                                printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->bitki));
                            else if (bocekKontrol == true)
                                printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->bocek));
                            else if (pireKontrol == true)
                                printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->pire));
                            else if (sinekKontrol == true)
                                printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->sinek));
                        }
                        printf("\n");
                    }
                    clearScreen();
                    printf("\n");

                    if (kirilsinMi == true)
                        break;
                }
            } else if (isim[0] == 'P') { // Pire ise, diğer koşullar da benzer şekilde kontrol edilir
                for (int j = i+1; j < habitat->listSize; j++) {
                    kirilsinMi = false;
                    bitkiKontrol = bitkiMi(habitat->list[j]);
                    bocekKontrol = bocekMi(habitat->list[j]);
                    pireKontrol = pireMi(habitat->list[j]);
                    sinekKontrol = sinekMi(habitat->list[j]);
                    if (bitkiKontrol == true)
                        isim = habitat->list[j]->gorunum(habitat->list[j]->bitki);
                    else if (bocekKontrol == true)
                        isim = habitat->list[j]->gorunum(habitat->list[j]->bocek);
                    else if (pireKontrol == true)
                        isim = habitat->list[j]->gorunum(habitat->list[j]->pire);
                    else if (sinekKontrol == true)
                        isim = habitat->list[j]->gorunum(habitat->list[j]->sinek);
                   
                    if (isim[0] == 'C') { // Pire yenir
                        habitat->list[i]->isimDegis(habitat->list[i]->pire, "X");
                        i = j-1;
                        kirilsinMi = true; 
                    } else if (isim[0] == 'S') {
                        habitat->list[i]->isimDegis(habitat->list[i]->pire, "X");
                        i = j-1;
                        kirilsinMi = true; 
                    } else if (isim[0] == 'B') {
                        habitat->list[i]->isimDegis(habitat->list[i]->pire, "X");
                        i = j-1;
                        kirilsinMi = true;
                    }
                    else {
                        int mesafeIlk = abs(habitat->list[i]->satirSayisi - satirSayisi) + abs(habitat->list[i]->sutunSayisi - sutunSayisi);
                        int mesafeIkinci = abs(habitat->list[j]->satirSayisi - satirSayisi) + abs(habitat->list[j]->sutunSayisi - sutunSayisi);
                        if (habitat->list[i]->sayisalDeger > habitat->list[j]->sayisalDeger ||
                            (habitat->list[i]->sayisalDeger == habitat->list[j]->sayisalDeger &&
                                mesafeIlk > mesafeIkinci)) {
                            habitat->list[j]->isimDegis(habitat->list[j]->pire, "X"); // Yenilen canlı ölüp X oluyor
                        } else {
                            habitat->list[i]->isimDegis(habitat->list[i]->pire, "X");
                            i = j-1;
                            kirilsinMi = true;
                        }
                    }

                    for(int i=0; i<satirSayisi; i++)
                    {
                        for(int j=0; j<sutunSayisi; j++)
                        {
                            int sira = i * sutunSayisi + j;

                            boolean bitkiKontrol = bitkiMi(habitat->list[sira]);
                            boolean bocekKontrol = bocekMi(habitat->list[sira]);
                            boolean pireKontrol = pireMi(habitat->list[sira]);
                            boolean sinekKontrol = sinekMi(habitat->list[sira]);

                            if (bitkiKontrol == true)
                                printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->bitki));
                            else if (bocekKontrol == true)
                                printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->bocek));
                            else if (pireKontrol == true)
                                printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->pire));
                            else if (sinekKontrol == true)
                                printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->sinek));
                        }
                        printf("\n");
                    }
                    clearScreen();
                    printf("\n");

                    if (kirilsinMi == true)
                        break;
                }
            }
        }

        // Canlıları ekrana yazdırır
        for(int i=0; i<satirSayisi; i++)
        {
            for(int j=0; j<sutunSayisi; j++)
            {
                int sira = i * sutunSayisi + j;

                boolean bitkiKontrol = bitkiMi(habitat->list[sira]);
                boolean bocekKontrol = bocekMi(habitat->list[sira]);
                boolean pireKontrol = pireMi(habitat->list[sira]);
                boolean sinekKontrol = sinekMi(habitat->list[sira]);

                if (bitkiKontrol == true)
                    printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->bitki));
                else if (bocekKontrol == true)
                    printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->bocek));
                else if (pireKontrol == true)
                    printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->pire));
                else if (sinekKontrol == true)
                    printf("%s ", habitat->list[sira]->gorunum(habitat->list[sira]->sinek));
            }
            printf("\n");
        }

        // Ölü canlıları listeden çıkar
        int k = 0;
        for (int i = 0; i < habitat->listSize; i++) {
            char* isim = "";
            boolean bitkiKontrol = bitkiMi(habitat->list[i]);
            boolean bocekKontrol = bocekMi(habitat->list[i]);
            boolean pireKontrol = pireMi(habitat->list[i]);
            boolean sinekKontrol = sinekMi(habitat->list[i]);
            if (bitkiKontrol == true)
                isim = habitat->list[i]->gorunum(habitat->list[i]->bitki);
            else if (bocekKontrol == true)
                isim = habitat->list[i]->gorunum(habitat->list[i]->bocek);
            else if (pireKontrol == true)
                isim = habitat->list[i]->gorunum(habitat->list[i]->pire);
            else if (sinekKontrol == true)
                isim = habitat->list[i]->gorunum(habitat->list[i]->sinek);
            if (isim[0] != 'X')
                kazanan = habitat->list[i];
        }
        habitat->listSize = 1;
    }

    // Kazananı bul ve ekrana yazdır
    boolean bitkiKontrol = bitkiMi(kazanan);
    boolean bocekKontrol = bocekMi(kazanan);
    boolean pireKontrol = pireMi(kazanan);
    boolean sinekKontrol = sinekMi(kazanan);

    if (bitkiKontrol == true)
        printf("Kazanan: %s : (%d, %d)\n", kazanan->gorunum(kazanan->bitki), kazanan->satirSayisi, kazanan->sutunSayisi);
    else if (bocekKontrol == true)
        printf("Kazanan: %s : (%d, %d)\n", kazanan->gorunum(kazanan->bocek), kazanan->satirSayisi, kazanan->sutunSayisi);
    else if (pireKontrol == true)
        printf("Kazanan: %s : (%d, %d)\n", kazanan->gorunum(kazanan->pire), kazanan->satirSayisi, kazanan->sutunSayisi);
    else if (sinekKontrol == true)
        printf("Kazanan: %s : (%d, %d)\n", kazanan->gorunum(kazanan->sinek), kazanan->satirSayisi, kazanan->sutunSayisi);
    kazanan = NULL;
}

void clearScreen() {
    // Ekran temizleme işlemi
    system("cls"); 
}

void waitForInput() {
    // Tuşa basılmasını bekleme işlemi
    getch(); // Bir tuşa basılmasını bekler
}


boolean bitkiMi(const Canli this)
{
    return this->bitki != NULL;
}

boolean bocekMi(const Canli this)
{
    return this->bocek != NULL;
}

boolean pireMi(const Canli this)
{
    return this->pire != NULL;
}

boolean sinekMi(const Canli this)
{
    return this->sinek != NULL;
}

void habitatYokEt(Habitat this)
{
    if (this != NULL) {
        if (this->list != NULL) {
            for(int i=0; i<this->listCapacity; i++) {
                this->list[i]->CanliYokEt(this->list[i]);
            }
            free(this->list);
        }
        free(this);
    }
}


