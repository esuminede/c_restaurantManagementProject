/*
        33. GRUP
        402505 - Emine Sude ASLAN
        422610 - Zehra ÖZÇÝRÝÞ
*/



#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

int ascilar[5] = {0,0,0,0,0};
int siparisSayisi = 0;

//musteri fonksiyonlari

void yemekListele();
void siparisVer();
void siparisDurumu();
void tumSiparisler();
void musteriKayit();

//satici fonksiyonlari
void yemekEkle();
void yemekGuncelle();
void yemekSil();
void siparisOnayla();
void gunlukRapor();
void gunlukRaporAl();
void gunlukRaporGoruntule();
void analizler();
void urunAnaliz();
void gunlukKazanc();
void aylikKazanc();
void donemKazanci();
void enCokTuketim();
int uygunAsciBul();

//giris islemleri
void kullanici();
void restoran();
void musteri();
int musteriDogrula(char* kullaniciAdi, char* sifre);

int main() {
    FILE* file = fopen("siparisler.txt", "r");
    if (file != NULL) {
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file)) {
            siparisSayisi++;
        }
        fclose(file);
    }

    kullanici();

    return 0;
}


//MUSTERI
void musteriKayit() {
    system("cls");

    char kullaniciAdi[50];
    char sifre[50];
    char ad[50];
    char soyad[50];
    char telefon[15];
    char email[50];

    printf("Kullanici adi: ");
    scanf("%s", kullaniciAdi);
    printf("Sifre: ");
    scanf("%s", sifre);
    printf("Ad: ");
    scanf("%s", ad);
    printf("Soyad: ");
    scanf("%s", soyad);
    printf("Telefon: ");
    scanf("%s", telefon);
    printf("Email: ");
    scanf("%s", email);

    FILE* file = fopen("musteriler.txt", "a");
    if (file == NULL) {
        printf("Musteri dosyasi acilamadi.\n");
        exit(1);
    }

    fprintf(file, "%s %s %s %s %s %s\n", kullaniciAdi, sifre, ad, soyad, telefon, email);
    fclose(file);

    printf("Musteri basariyla kaydedildi.\n\n Hosgeldiniz!", ad, soyad);
    usleep(7000000); // 5 saniye (5000000 mikrosaniye) bekler

}
void yemekListele()
 {
    system("cls");
    FILE *file = fopen("yemeklistesi.txt", "r");
    if (file == NULL) {
        printf("Yemek listesi dosyasi acilamadi.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char yemekAdi[50], durum[10];
    int fiyat, hazirlanmaSuresi;

    printf("Yemek Listesi:\n");
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %d %d %s", yemekAdi, &fiyat, &hazirlanmaSuresi, durum);
        if(strcmp(durum, "Degil")==1){
            printf("%s - %d TL - %d dk\n", yemekAdi, fiyat, hazirlanmaSuresi);
        }
    }
    fclose(file);
}
void siparisVer() {
    system("cls");
    char siparisID[20], yemekAdi[50], kullanici[20], asci[20];
    int fiyat, asciIndex;
    time_t now;
    char siparisZamani[20], hazirlanmaZamani[20];

    printf("Kullanici adi: ");
    scanf("%s", kullanici);

    sprintf(siparisID, "SIP_%06d", siparisSayisi + 1);
    siparisSayisi++;
    printf("Yemek adi: ");
    scanf("%s", yemekAdi);

    FILE* file = fopen("yemeklistesi.txt", "r");
    if (file == NULL) {
        system("cls");
        printf("Yemek listesi dosyasi acilamadi.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int yemekBulundu = 0, hazirlanmaSuresi = 0;
    while (fgets(line, sizeof(line), file)) {
        char mevcutYemekAdi[50], durum[15];
        int mevcutFiyat, mevcutHazirlanmaSuresi;
        sscanf(line, "%s %d %d %s", mevcutYemekAdi, &mevcutFiyat, &mevcutHazirlanmaSuresi, durum);
        if (strcmp(yemekAdi, mevcutYemekAdi) == 0 && strcmp(durum, "Mevcut") == 0) {
            fiyat = mevcutFiyat;
            hazirlanmaSuresi = mevcutHazirlanmaSuresi;
            yemekBulundu = 1;
            break;
        }
    }
    fclose(file);

    if (!yemekBulundu) {
        printf("Sectiginiz yemek mevcut degil.\n");
        return;
    }

    now = time(NULL);
    strftime(siparisZamani, 20, "%d.%m.%Y-%H:%M", localtime(&now));

    asciIndex = uygunAsciBul();
    sprintf(asci, "A%d", asciIndex);

    file = fopen("siparisler.txt", "a");
    if (file == NULL) {
        printf("Siparis dosyasi acilamadi.\n");
        exit(1);
    }
    fprintf(file, "%s %s %d %s OnayBekliyor %s %s\n", siparisID, yemekAdi, fiyat, siparisZamani, kullanici, asci);
    fclose(file);

    printf("Siparis basariyla verildi.\n");
}
void siparisDurumu()
{
    system("cls");
    char kullanici[20];
    printf("Kullanici adinizi girin: ");
    scanf("%s", kullanici);

    FILE *file = fopen("siparisler.txt", "r");
    if (file == NULL) {
        printf("Siparisler dosyasi acilamadi.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char musteri[20], siparisID[20], yemekAdi[50], siparisZamani[20], hazirlanmaZamani[20], asci[20];
    int fiyat;

    printf("Siparisleriniz:\n");
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s %d %s %s %s %s", siparisID, yemekAdi, &fiyat, siparisZamani, hazirlanmaZamani, musteri, asci);
        if (strcmp(kullanici, musteri) == 0 && ((strcmp(hazirlanmaZamani, "OnayBekliyor") == 0 )|| strcmp(hazirlanmaZamani, "Onaylandi") || strcmp(hazirlanmaZamani, "Reddedildi"))) {
            printf("Siparis ID: %s - Yemek: %s - Fiyat: %d TL - Siparis Zamani: %s - Hazirlanma Zamani: %s - Asci: %s\n", siparisID, yemekAdi, fiyat, siparisZamani, hazirlanmaZamani, asci);
        }
    }
    fclose(file);
}

void tumSiparisler() {
    system("cls");
    char kullaniciAdi[20];

    printf("Kullanici adinizi giriniz: ");
    scanf("%s", kullaniciAdi);

    FILE *file = fopen("siparisler.txt", "r");
    if (file == NULL) {
        printf("Siparisler dosyasi acilamadi.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    char siparisID[20], yemekAdi[50], siparisZamani[20], hazirlanmaZamani[20], kullanici[20], asci[20];
    int fiyat;
    int siparisVar = 0;

    printf("Tum Siparisleriniz:\n");
    printf("Siparis ID | Yemek Adi      | Fiyat | Siparis Zamani   | Hazirlanma Zamani | Asci\n");
    printf("---------------------------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s %d %s %s  %s %s", siparisID, yemekAdi, &fiyat, siparisZamani, hazirlanmaZamani, kullanici, asci);
        if (strcmp(kullaniciAdi, kullanici) == 0) {
            printf("%-10s | %-14s | %-5d | %-14s | %-17s | %-4s\n", siparisID, yemekAdi, fiyat, siparisZamani, hazirlanmaZamani, asci);
            siparisVar = 1;
        }
    }

    if (!siparisVar) {
        printf("Hic siparisiniz bulunmamaktadir.\n");
    }

    fclose(file);
}

//ASCI
void yemekEkle()
{
    system("cls");
    char yemekAdi[50], durum[10] = "Mevcut";
    int fiyat, hazirlanmaSuresi;

    printf("Yeni yemek adi: ");
    scanf("%s", yemekAdi);
    printf("Fiyat: ");
    scanf("%d", &fiyat);
    printf("Hazirlanma suresi (dk): ");
    scanf("%d", &hazirlanmaSuresi);
//    printf("Mevcudiyet: ");
//    scanf("%d", &durum);

    FILE *file = fopen("yemeklistesi.txt", "a");
    if (file == NULL) {
        printf("Yemek listesi dosyasi acilamadi.\n");
        exit(1);
    }

    fprintf(file, "%s %d %d %s\n", yemekAdi, fiyat, hazirlanmaSuresi, durum);
    fclose(file);

    printf("Yeni yemek basariyla eklendi.\n");
}
void yemekGuncelle()
{
    system("cls");
    FILE *file = fopen("yemeklistesi.txt", "r");
    if (file == NULL) {
        printf("Yemek listesi dosyasi acilamadi.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char yemekAdi[50], yeniYemekAdi[50], durum[10], yeniDurum[10];
    int fiyat, hazirlanmaSuresi;
    int yeniFiyat, yeniHazirlanmaSuresi;
    int yemekBulundu = 0;

    printf("Guncellenecek yemek adi: ");
    scanf("%s", yemekAdi);

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Geçici dosya açilamadi.\n");
        exit(1);
    }

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %d %d %s", yeniYemekAdi, &fiyat, &hazirlanmaSuresi, durum);
        if (strcmp(yemekAdi, yeniYemekAdi) == 0) {
            printf("Yeni yemek adi: ");
            scanf("%s", yeniYemekAdi);
            printf("Yeni fiyat: ");
            scanf("%d", &yeniFiyat);
            printf("Yeni hazirlanma suresi (dk): ");
            scanf("%d", &yeniHazirlanmaSuresi);
            printf("Yeni durum (Mevcut, Degil): ");
            scanf("%s", yeniDurum);
            fprintf(temp, "%s %d %d %s\n", yeniYemekAdi, yeniFiyat, yeniHazirlanmaSuresi, yeniDurum);
            yemekBulundu = 1;
        } else {
            fprintf(temp, "%s %d %d %s\n", yeniYemekAdi, fiyat, hazirlanmaSuresi, durum);
        }
    }
    fclose(file);
    fclose(temp);

    if (yemekBulundu) {
        remove("yemeklistesi.txt");
        rename("temp.txt", "yemeklistesi.txt");
        printf("Yemek basariyla guncellendi.\n");
    } else {
        remove("temp.txt");
        printf("Yemek bulunamadi.\n");
    }
}
void yemekSil()
{
    system("cls");
    FILE *file = fopen("yemeklistesi.txt", "r");
    if (file == NULL) {
        printf("Yemek listesi dosyasi acilamadi.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char yemekAdi[50], silinecekYemekAdi[50], durum[10];
    int fiyat, hazirlanmaSuresi;
    int yemekBulundu = 0;

    printf("Silinecek yemek adi: ");
    scanf("%s", silinecekYemekAdi);

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Geçici dosya acilamadi.\n");
        exit(1);
    }

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %d %d %s", yemekAdi, &fiyat, &hazirlanmaSuresi, durum);
        if (strcmp(silinecekYemekAdi, yemekAdi) == 0) {
            yemekBulundu = 1;
        } else {
            fprintf(temp, "%s %d %d %s\n", yemekAdi, fiyat, hazirlanmaSuresi, durum);
        }
    }
    fclose(file);
    fclose(temp);

    if (yemekBulundu) {
        remove("yemeklistesi.txt");
        rename("temp.txt", "yemeklistesi.txt");
        printf("Yemek basariyla silindi.\n");
    } else {
        remove("temp.txt");
        printf("Yemek bulunamadi.\n");
    }
}

void siparisOnayla()
{
    system("cls");
    FILE *file = fopen("siparisler.txt", "r");
    if (file == NULL) {
        printf("Siparisler dosyasi acilamadi.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char yemekAdi[50], siparisZamani[20], hazirlanmaZamani[20], kullanici[20], asci[20];
    char siparisID[20];
    int fiyat, secim, i = 0;
    int siparisBulundu = 0;

    printf("Onaylanabilir Siparisler:\n");
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s %d %s %s %s %s", siparisID, yemekAdi, &fiyat, siparisZamani, hazirlanmaZamani, kullanici, asci);
        if (strcmp(hazirlanmaZamani, "OnayBekliyor") == 0) {
            printf("%d. Siparis ID: %s - Yemek: %s - Kullanici: %s\n", i + 1, siparisID, yemekAdi, kullanici);
            i++;
        }
    }
    fclose(file);

    if (i == 0) {
        printf("Onaylanabilir siparis bulunamadi.\n");
        return;
    }

    printf("Onaylamak istediginiz siparisi secin: ");
    scanf("%d", &secim);
    int siparisSecimi = secim - 1; // dizi indexi 0'dan baþladýðý için

    printf("1: Onayla\n2: Reddet\n3: Siparis Hazir\n");
    printf("Seciminiz: ");
    scanf("%d", &secim);

    i = 0;
    file = fopen("siparisler.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Gecici dosya acilamadi.\n");
        exit(1);
    }

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s %d %s %s %s %s", siparisID, yemekAdi, &fiyat, siparisZamani, hazirlanmaZamani, kullanici, asci);
        if (i == siparisSecimi) {
            if (secim == 1) {
                strcpy(hazirlanmaZamani, "Onaylandi");
                fprintf(temp, "%s %s %d %s %s %s %s\n", siparisID, yemekAdi, fiyat, siparisZamani, hazirlanmaZamani, kullanici, asci);
            } else if (secim == 2) {
                strcpy(hazirlanmaZamani, "Reddedildi");
                fprintf(temp, "%s %s %d %s %s %s %s\n", siparisID, yemekAdi, fiyat, siparisZamani, hazirlanmaZamani, kullanici, asci);
            } else if (secim == 3) {
                time_t now = time(NULL);
                strftime(hazirlanmaZamani, 20, "%d.%m.%Y-%H:%M", localtime(&now));
                fprintf(temp, "%s %s %d %s %s %s %s\n", siparisID, yemekAdi, fiyat, siparisZamani, hazirlanmaZamani, kullanici, asci);
            }
            siparisBulundu = 1;
        } else {
            fprintf(temp, "%s %s %d %s %s %s %s\n", siparisID, yemekAdi, fiyat, siparisZamani, hazirlanmaZamani, kullanici, asci);
        }
        i++;
    }

    fclose(file);
    fclose(temp);

    if (siparisBulundu) {
        remove("siparisler.txt");
        rename("temp.txt", "siparisler.txt");
        printf("Siparis basariyla guncellendi.\n");
    } else {
        remove("temp.txt");
        printf("Gecersiz secim.\n");
    }
}

void gunlukRapor()
{
    system("cls");
    int secim;

    while (1) {
        printf("Gunluk Rapor Menusu:\n");
        printf("1. Gunluk Rapor Al\n");
        printf("2. Gunluk Rapor Goruntule\n");
        printf("3. Geri\n");
        printf("Seciminizi yapiniz: ");
        scanf("%d", &secim);
        system("cls");

        switch (secim) {
            case 1:
                gunlukRaporAl();
                break;
            case 2:
                gunlukRaporGoruntule();
                break;
            case 3:
                return;
            default:
                printf("Gecersiz secim. Tekrar deneyiniz.\n");
        }
    }
}
void urunAnaliz()
{
    system("cls");
    FILE *file = fopen("siparisler.txt", "r");
    if (file == NULL) {
        printf("Siparisler dosyasi acilamadi.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char siparisID[20], yemekAdi[50], siparisZamani[20], hazirlanmaZamani[20], kullanici[20], asci[20];
    int fiyat, yemekSayilari[100] = {0}, yemekFiyatlari[100] = {0};
    char yemekAdlari[100][50];
    int yemekAdet = 0, i;

    while(fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s %d %s %s %s %s", siparisID, yemekAdi, &fiyat, siparisZamani, hazirlanmaZamani, kullanici, asci);
        int bulunan = 0;
        for (i = 0; i < yemekAdet; i++) {
            if (strcmp(yemekAdi, yemekAdlari[i]) == 0) {
                yemekSayilari[i]++;
                yemekFiyatlari[i] += fiyat;
                bulunan = 1;
                break;
            }
        }
        if (!bulunan) {
            strcpy(yemekAdlari[yemekAdet], yemekAdi);
            yemekSayilari[yemekAdet] = 1;
            yemekFiyatlari[yemekAdet] = fiyat;
            yemekAdet++;
        }
    }
    fclose(file);

    printf("Siparis Analizleri:\n");
    for (i = 0; i < yemekAdet; i++) {
        printf("Yemek: %s - Siparis Sayisi: %d - Toplam Gelir: %d TL\n", yemekAdlari[i], yemekSayilari[i], yemekFiyatlari[i]);
    }
}
void asciSayisi()
{
    system("cls");
    int asciSayisi;
    printf("Asci sayisini belirleyin: ");
    scanf("%d", &asciSayisi);
    printf("Asci sayisi basariyla belirlendi: %d\n", asciSayisi);
}
void gunlukKazanc()
{
    system("cls");
    FILE *file = fopen("siparisler.txt", "r");
    if (file == NULL) {
        printf("Siparisler dosyasi acilamadi.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char siparisID[20], yemekAdi[50], siparisZamani[20], hazirlanmaZamani[20], kullanici[20], asci[20];
    int fiyat, toplamKazanc = 0;
    char tarih[11];

    printf("Gunluk kazancini ogrenmek istediginiz tarihi giriniz (GG.AA.YYYY): ");
    scanf("%s", tarih);

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s %d %s %s %s %s", siparisID, yemekAdi, &fiyat, siparisZamani, hazirlanmaZamani, kullanici, asci);
        if (strncmp(tarih, siparisZamani, 10) == 0) {
            toplamKazanc += fiyat;
        }
    }
    fclose(file);

    printf("Gunluk Kazanc (%s): %d TL\n", tarih, toplamKazanc);
}
void aylikKazanc()
{
    system("cls");
    FILE *file = fopen("siparisler.txt", "r");
    if (file == NULL) {
        printf("Siparisler dosyasi acilamadi.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char siparisID[20], yemekAdi[50], siparisZamani[20], hazirlanmaZamani[20], kullanici[20], asci[20];
    int fiyat, toplamKazanc = 0;
    char ay[8];

    printf("Aylik kazancini ogrenmek istediginiz ayi giriniz (AA.YYYY): ");
    scanf("%s", ay);

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s %d %s %s %s %s", siparisID, yemekAdi, &fiyat, siparisZamani, hazirlanmaZamani, kullanici, asci);
        if (strncmp(ay, siparisZamani + 3, 7) == 0) {
            toplamKazanc += fiyat;
        }
    }
    fclose(file);

    printf("Aylik Kazanc (%s): %d TL\n", ay, toplamKazanc);
}
void donemKazanci()
{
    system("cls");
    FILE *file = fopen("siparisler.txt", "r");
    if (file == NULL) {
        printf("Siparisler dosyasi acilamadi.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char siparisID[20], yemekAdi[50], siparisZamani[20], hazirlanmaZamani[20], kullanici[20], asci[20];
    int fiyat, toplamKazanc = 0;
    int donem, yil, secilenYil;

    printf("Donemlik kazanci ogrenmek istediginiz yili giriniz: ");
    scanf("%d", &secilenYil);
    system("cls");

    printf("Donemlik kazanci ogrenmek istediginiz donemi seciniz:\n");
    printf("1. Bahar (Ocak - Nisan)\n");
    printf("2. Yaz (Mayis - Agustos)\n");
    printf("3. Sonbahar (Eylul - Aralik)\n");
    printf("4. Kis (Ocak - Mart)\n");
    printf("Seciminizi yapiniz: ");
    scanf("%d", &donem);

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s %d %s %s %s %s", siparisID, yemekAdi, &fiyat, siparisZamani, hazirlanmaZamani, kullanici, asci);
        int ay, siparisYili;
        sscanf(siparisZamani + 3, "%d", &ay); // Ayý al
        sscanf(siparisZamani + 6, "%d", &siparisYili); // Yýlý al

        if (siparisYili == secilenYil) {
            switch (donem) {
                case 1: // Bahar (Ocak - Nisan)
                    if (ay >= 1 && ay <= 4) {
                        toplamKazanc += fiyat;
                    }
                    break;
                case 2: // Yaz (Mayis - Agustos)
                    if (ay >= 5 && ay <= 8) {
                        toplamKazanc += fiyat;
                    }
                    break;
                case 3: // Sonbahar (Eylul - Aralik)
                    if (ay >= 9 && ay <= 12) {
                        toplamKazanc += fiyat;
                    }
                    break;
                case 4: // Kis (Ocak - Mart)
                    if (ay >= 1 && ay <= 3) {
                        toplamKazanc += fiyat;
                    }
                    break;
                default:
                    printf("Gecersiz secim.\n");
                    fclose(file);
                    return;
            }
        }
    }
    fclose(file);

    switch (donem) {
        case 1:
            printf("%d Bahar Donemi Kazanci: %d TL\n", secilenYil, toplamKazanc);
            break;
        case 2:
            printf("%d Yaz Donemi Kazanci: %d TL\n", secilenYil, toplamKazanc);
            break;
        case 3:
            printf("%d Sonbahar Donemi Kazanci: %d TL\n", secilenYil, toplamKazanc);
            break;
        case 4:
            printf("%d Kis Donemi Kazanci: %d TL\n", secilenYil, toplamKazanc);
            break;
    }
}

void enCokTuketim()
{
    system("cls");
    FILE *file = fopen("siparisler.txt", "r");
    if (file == NULL) {
        printf("Siparisler dosyasi acilamadi.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char siparisID[20], yemekAdi[50], siparisZamani[20], hazirlanmaZamani[20], kullanici[20], asci[20];
    int fiyat, yemekSayilari[100] = {0}, yemekFiyatlari[100] = {0};
    char yemekAdlari[100][50];
    int yemekAdet = 0, i;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s %d %s %s %s %s", siparisID, yemekAdi, &fiyat, siparisZamani, hazirlanmaZamani, kullanici, asci);
        int bulunan = 0;
        for (i = 0; i < yemekAdet; i++) {
            if (strcmp(yemekAdi, yemekAdlari[i]) == 0) {
                yemekSayilari[i]++;
                yemekFiyatlari[i] += fiyat;
                bulunan = 1;
                break;
            }
        }
        if (!bulunan) {
            strcpy(yemekAdlari[yemekAdet], yemekAdi);
            yemekSayilari[yemekAdet] = 1;
            yemekFiyatlari[yemekAdet] = fiyat;
            yemekAdet++;
        }
    }
    fclose(file);

    int enCokTuketilenIndex = 0;
    for (i = 1; i < yemekAdet; i++) {
        if (yemekSayilari[i] > yemekSayilari[enCokTuketilenIndex]) {
            enCokTuketilenIndex = i;
        }
    }

    printf("En Cok Tuketilen Yemek: %s - Siparis Sayisi: %d - Toplam Gelir: %d TL\n", yemekAdlari[enCokTuketilenIndex], yemekSayilari[enCokTuketilenIndex], yemekFiyatlari[enCokTuketilenIndex]);
}
void analizler()
{
    system("cls");
    int secim;

    while (1) {
        printf("Analizler Menusu:\n");
        printf("1. Gunluk Kazanc\n");
        printf("2. Aylik Kazanc\n");
        printf("3. Donem Kazanci\n");
        printf("4. En Cok Tuketim\n");
        printf("5. Urun Analizi\n");
        printf("6. Geri\n");
        printf("Seciminizi yapiniz: ");
        scanf("%d", &secim);
        system("cls");

        switch (secim) {
            case 1:
                gunlukKazanc();
                break;
            case 2:
                aylikKazanc();
                break;
            case 3:
                donemKazanci();
                break;
            case 4:
                enCokTuketim();
                break;
            case 5:
                urunAnaliz();
            case 6:
                return; // Geri
            default:
                printf("Gecersiz secim. Tekrar deneyiniz.\n");
        }
    }
}
int musteriDogrula(char* kullaniciAdi, char* sifre) {
    FILE* file = fopen("musteriler.txt", "r");
    if (file == NULL) {
        printf("Musteri dosyasi acilamadi.\n");
        return 0;
    }

    char fileKullaniciAdi[50];
    char fileSifre[50];
    char fileAd[50];
    char fileSoyad[50];
    char fileTelefon[15];
    char fileEmail[50];

    while (fscanf(file, "%s %s %s %s %s %s", fileKullaniciAdi, fileSifre, fileAd, fileSoyad, fileTelefon, fileEmail) != EOF) {
        if (strcmp(fileKullaniciAdi, kullaniciAdi) == 0 && strcmp(fileSifre, sifre) == 0) {
            fclose(file);
            return 1;  // Doğrulama başarılı
        }
    }

    fclose(file);
    return 0;  // Doğrulama başarısız
}
void musteri()
{
    int secim;
    char kullaniciAdi[50];
    char sifre[50];

    printf("Kullanici adi: ");
    scanf("%s", kullaniciAdi);
    printf("Sifre: ");
    scanf("%s", sifre);

    if (musteriDogrula(kullaniciAdi, sifre)) {
        printf("Musteri girisi basarili.\n");
 while (1) {
        printf("Musteri Menusu:\n");
        printf("1. Yemek Listele\n");
        printf("2. Siparis Ver\n");
        printf("3. Siparis Durumu\n");
        printf("4. Tum Siparislerim\n");
        printf("5. Geri\n");
        printf("Seciminizi yapiniz: ");
        scanf("%d", &secim);
        system("cls");

        switch (secim) {
            case 1:
                yemekListele();
                break;
            case 2:
                siparisVer();
                break;
            case 3:
                siparisDurumu();
                break;
            case 4:
                tumSiparisler();
                break;
            case 5:
                printf("Afiyet Olsun.\n\n");
                return; // Geri
            default:
                printf("Gecersiz secim. Tekrar deneyiniz.\n");
        }
    }    } else {
        printf("Gecersiz kullanici adi veya sifre.\n");
    }
}
void restoran()
{
    system("cls");
    char kullaniciAdi[20];
    char sifre[20];
    int secim;

    printf("Kullanici Adi: ");
    scanf("%s", kullaniciAdi);
    printf("Sifre: ");
    scanf("%s", sifre);

    if (strcmp(kullaniciAdi, "r") == 0 && strcmp(sifre, "1") == 0) {
        while (1) {
            printf("Asci Menusu:\n");
            printf("1. Yemek Ekle\n");
            printf("2. Yemek Guncelle\n");
            printf("3. Yemek Sil\n");
            printf("4. Siparis Onayla\n");
            printf("5. Gunluk Rapor\n");
            printf("6. Analizler\n");
            printf("7. Geri\n");
            printf("Seciminizi yapiniz: ");
            scanf("%d", &secim);
            system("cls");

            switch (secim) {
                case 1:
                    yemekEkle();
                    break;
                case 2:
                    yemekGuncelle();
                    break;
                case 3:
                    yemekSil();
                    break;
                case 4:
                    siparisOnayla();
                    break;
                case 5:
                    gunlukRapor();
                    break;
                case 6:
                    analizler();
                    break;
                case 7:
                    printf("Kolay Gelsin.\n");
                    return; // Geri
                default:
                    printf("Gecersiz secim. Tekrar deneyiniz.\n");
            }
        }
    } else {
        printf("Yanlis kullanici adi veya sifre.\n");
    }
}
void kullanici()
{
    system("cls");
    int secim;

    while (1) {
        system("cls");
        printf("07 ESNAFIM'dasiniz.\n");
        printf("Kullanici Tipini Seciniz:\n");
        printf("1. Musteri\n");
        printf("2. Asci\n");
        printf("3. Yeni Musteri Kayit\n");
        printf("4. Cikis\n");
        printf("Seciminizi yapiniz: ");
        scanf("%d", &secim);

        system("cls");

        switch (secim) {
            case 1:
                musteri();
                break;
            case 2:
                restoran();
                break;
            case 3:
                musteriKayit();
                break;
            case 4:
                exit(0);
            default:
                system("cls");
                printf("Gecersiz secim. Tekrar deneyiniz.\n");
        }
    }
}
void gunlukRaporAl()
{
    system("cls");
    FILE *file = fopen("siparisler.txt", "r");
    if (file == NULL) {
        printf("Siparisler dosyasi acilamadi.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    char siparisID[20], yemekAdi[50], siparisZamani[20], hazirlanmaZamani[20], kullanici[20], asci[20];
    int fiyat;
    char tarih[11];

    printf("Gunluk rapor almak istediginiz tarihi giriniz (GG.AA.YYYY): ");
    scanf("%s", tarih);

    char raporDosyaAdi[30];
    snprintf(raporDosyaAdi, sizeof(raporDosyaAdi), "gunluk_rapor_%s.txt", tarih);

    FILE *raporDosyasi = fopen(raporDosyaAdi, "w");
    if (raporDosyasi == NULL) {
        system("cls");
        printf("Gunluk rapor dosyasi olusturulamadi.\n");
        fclose(file);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s %d %s %s %s %s", siparisID, yemekAdi, &fiyat, siparisZamani, hazirlanmaZamani, kullanici, asci);
        if (strncmp(tarih, siparisZamani, 10) == 0) {
            fprintf(raporDosyasi, "%s %s %d %s %s %s %s\n", siparisID, yemekAdi, fiyat, siparisZamani, hazirlanmaZamani, kullanici, asci);
        }
    }

    fclose(file);
    fclose(raporDosyasi);
    system("cls");
    printf("Gunluk rapor basariyla olusturuldu: %s\n", raporDosyaAdi);
}

void gunlukRaporGoruntule()
 {
    system("cls");
    char tarih[11];
    char raporDosyaAdi[30];

    printf("Goruntulemek istediginiz gunluk raporun tarihini giriniz (GG.AA.YYYY): ");
    scanf("%s", tarih);

    snprintf(raporDosyaAdi, sizeof(raporDosyaAdi), "gunluk_rapor_%s.txt", tarih);

    FILE *raporDosyasi = fopen(raporDosyaAdi, "r");
    if (raporDosyasi == NULL) {
        system("cls");
        printf("Gunluk rapor dosyasi acilamadi: %s\n", raporDosyaAdi);
        return;
    }

    char line[MAX_LINE_LENGTH];
    printf("Gunluk Rapor (%s):\n", tarih);
    printf("Siparis ID | Yemek Adi      | Fiyat | Siparis Zamani   | Hazirlanma Zamani | Kullanici  | Asci\n");
    printf("---------------------------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), raporDosyasi)) {
        char siparisID[20], yemekAdi[50], siparisZamani[20], hazirlanmaZamani[20], kullanici[20], asci[20];
        int fiyat;
        sscanf(line, "%s %s %d %s %s %s %s", siparisID, yemekAdi, &fiyat, siparisZamani, hazirlanmaZamani, kullanici, asci);
        printf("%-10s | %-14s | %-5d | %-14s | %-17s | %-9s | %-4s\n", siparisID, yemekAdi, fiyat, siparisZamani, hazirlanmaZamani, kullanici, asci);
    }

    fclose(raporDosyasi);
}

int uygunAsciBul()
{
    system("cls");

    int minIndex = -1;
    srand(time(NULL));

    minIndex = rand() % 5;
    return minIndex;
}
