#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h> // String műveletekhez

int main() {
    char fajlnev[200];      // Megnöveltük a biztonság kedvéért
    char kimeneti_nev[200];
    char kulcs[100];

    FILE* bemenet = NULL;
    FILE* kimenet = NULL;

    printf("--- XOR Fajl Titkosito v3.0 (Smart Name) ---\n");

    // 1. Adatbekérés
    printf("Fajl neve: ");
    scanf("%s", fajlnev);
    printf("Kulcs: ");
    scanf("%s", kulcs);

    // 2. Bemenet megnyitása
    bemenet = fopen(fajlnev, "rb");
    if (bemenet == NULL) {
        printf("HIBA: Nem talalom a bemeneti fajlt!\n");
        return 1;
    }

    // 3. OKOS NÉVGENERÁLÁS (Az új logika) 🧠
    // Megnézzük, hogy ".xor"-ra végződik-e a fájlnév
    char* kiterjesztes = strrchr(fajlnev, '.'); // Megkeressük az utolsó pontot
    int xor_mod = 0; // 0 = Titkosítás, 1 = Visszafejtés

    // Ha van pont, és utána "xor" van írva...
    if (kiterjesztes != NULL && strcmp(kiterjesztes, ".xor") == 0) {
        xor_mod = 1;
    }

    if (xor_mod == 0) {
        // --- TITKOSÍTÁS MÓD ---
        // Nincs ott a .xor, tehát most titkosítunk.
        // Egyszerűen hozzáfűzzük a végére.
        sprintf(kimeneti_nev, "%s.xor", fajlnev);
    }
    else {
        // --- VISSZAFEJTÉS MÓD ---
        // Ott van a .xor, tehát le kell venni, és beékelni a "_"-t.

        char temp_nev[200];
        // 1. lépés: Levágjuk a ".xor" végét (4 karakter)
        int eredeti_hossz = strlen(fajlnev) - 4;
        strncpy(temp_nev, fajlnev, eredeti_hossz);
        temp_nev[eredeti_hossz] = '\0'; // Lezárjuk a szöveget (fontos!)
        // Most a temp_nev pl: "kep.jpg"

        // 2. lépés: Megkeressük a kiterjesztést (pl. .jpg) a levágott névben
        char* pont_helye = strrchr(temp_nev, '.');

        if (pont_helye != NULL) {
            // Van kiterjesztés (pl. kep.jpg) -> Cél: kep_.jpg

            // Kiszámoljuk, hol van a pont:
            int nev_hossza_pontig = pont_helye - temp_nev; // Pointer aritmetika

            // Bemásoljuk a nevet a pontig ("kep")
            strncpy(kimeneti_nev, temp_nev, nev_hossza_pontig);
            kimeneti_nev[nev_hossza_pontig] = '\0'; // Lezárás

            // Hozzáfűzzük az alsóvonást ("kep_")
            strcat(kimeneti_nev, "_");

            // Hozzáfűzzük az eredeti kiterjesztést ("kep_.jpg")
            strcat(kimeneti_nev, pont_helye);
        }
        else {
            // Nincs kiterjesztés (pl. "titkos_file") -> Cél: titkos_file_
            sprintf(kimeneti_nev, "%s_", temp_nev);
        }
    }

    // 4. Kimenet megnyitása
    kimenet = fopen(kimeneti_nev, "wb");
    if (kimenet == NULL) {
        printf("HIBA: Nem tudom letrehozni a '%s' fajlt!\n", kimeneti_nev);
        fclose(bemenet);
        return 1;
    }

    printf("Feldolgozas alatt... (%s -> %s)\n", fajlnev, kimeneti_nev);

    // 5. A MAG (XOR Ciklus - Változatlan)
    int karakter;
    int kulcs_index = 0;
    int kulcs_hossz = strlen(kulcs);

    while ((karakter = fgetc(bemenet)) != EOF) {
        int titkositott_karakter = karakter ^ kulcs[kulcs_index];
        fputc(titkositott_karakter, kimenet);

        kulcs_index++;
        if (kulcs_index == kulcs_hossz) {
            kulcs_index = 0;
        }
    }

    // 6. Takarítás
    fclose(bemenet);
    fclose(kimenet);

    printf("\nSIKER! A muvelet befejezodott.\n");
    printf("Letrejott fajl: %s\n", kimeneti_nev);

    return 0;
}