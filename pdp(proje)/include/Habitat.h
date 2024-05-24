#include <Bocek.h>
#include <Bitki.h>
#include <Sinek.h>
#include <Pire.h>

typedef Canli* List;

struct HABITAT
{
    
void (*elemeSonrasi)(struct HABITAT*);
void (*elemeBaslat)(struct HABITAT*, const char *, int*, int*);
void (*yoket)(struct HABITAT*);

    
    List list;
    int sayac;
    int listSize;
    int listCapacity;
};

typedef struct HABITAT *Habitat;

Habitat habitatOlustur();
void elemeSonrasi(Habitat);
void elemeBaslat(Habitat, const char *dosyaAdi, int*, int*);
boolean bitkiMi(const Canli);
boolean bocekMi(const Canli);
boolean pireMi(const Canli);
boolean sinekMi(const Canli);
void elemeYokEt(Habitat);
void clearScreen();
void waitForInput();
void oyunuBaslat(Habitat, int, int);
void habitatYokEt(Habitat);