
#include <Bitki.h>
#include <Sinek.h>
#include <Pire.h>
#include <Habitat.h>
#include <Bocek.h>

void clearScreen();
void waitForInput(); // Yeni eklediğimiz fonksiyon

int main()
{
    Habitat habitat = habitatOlustur();
    int satir, sutun;
    elemeBaslat(habitat, "./doc/Veri.txt", &satir, &sutun);
 
    // Oyun başlamadan önce bir tuşa basılmasını bekleyin
    printf("Oyuna baslamak icin bir tusa basin...\n\n");
    waitForInput();

    oyunuBaslat(habitat, satir, sutun);
    habitatYokEt(habitat);

    return 0;
}
