# 🔐 C XOR Fájl Titkosító (File Encryptor)

> **50 Hét - 50 Nyelv Kihívás: 2. Hét (C Nyelv)**

Ez a projekt egy alacsony szintű, **C nyelvben írt titkosító alkalmazás**. Képes bármilyen fájlt (képet, videót, szöveget, futtatható állományt) olvashatatlanná tenni a **XOR (Kizáró VAGY)** bitművelet segítségével, illetve visszaállítani az eredeti állapotot.

---

## 🎯 A Működési Elv

A program nem szövegként, hanem **nyers bájtokként** (`rb` - read binary módban) kezeli a fájlokat. Ezért működik képeken és `.exe` fájlokon is anélkül, hogy tönkretenné azokat.

A titkosítás lelke a **XOR (bitwise exclusive OR)** művelet szimmetriája:
1.  `Adat` XOR `Kulcs` = `Titkosított Adat`
2.  `Titkosított Adat` XOR `Kulcs` = `Eredeti Adat`

Ez azt jelenti, hogy **ugyanaz a program végzi a titkosítást és a visszafejtést is.**

### 🧠 Smart File Naming (Okos Névkezelés)
A program automatikusan felismeri, hogy titkosítani vagy visszafejteni kell-e a fájl kiterjesztése alapján:

* **Titkosításkor:**
  Ha egy normál fájlt adsz meg (pl. `kep.jpg`), a program létrehoz egy titkosított verziót `.xor` kiterjesztéssel.
  * *Eredmény:* `kep.jpg.xor`

* **Visszafejtéskor:**
  Ha a fájl neve `.xor`-ra végződik, a program levágja ezt a kiterjesztést, és egy `_` jelet szúr be az eredeti név elé (hogy véletlenül se írja felül az eredeti forrásfájlt).
  * *Eredmény:* `kep_.jpg` (Ez a fájl már megnyitható lesz).

---

## 🛠️ Technológiák
A projekt során a C nyelv "szigorú" memóriakezelését és biztonsági funkcióit használtam:
* **Pointerek (`FILE *`):** Közvetlen hozzáférés a fájlrendszerhez.
* **Bináris I/O:** `fgetc` és `fputc` használata a bájtonkénti léptetéshez.
* **String Manipuláció:** `strrchr`, `strncpy` és pointer aritmetika használata a fájlnevek intelligens átalakításához.
* **Biztonság:** Buffer Overflow elleni alapvető védelem és a Visual Studio `_CRT_SECURE_NO_WARNINGS` makrójának kezelése.

---

## 🚀 Telepítés és Használat

### 1. Fordítás (Compilation)
A program forráskódja a `main.c` fájlban található.

**Visual Studio esetén:**
1. Hozz létre egy új "Console App" projektet.
2. Nevezd át a `.cpp` fájlt `main.c`-re.
3. Másold be a kódot és nyomj **F5**-öt.

**GCC (Linux/MinGW) esetén:**
```bash
gcc main.c -o encryptor
```

### 2. Használati Példák

#### A) Titkosítás
Indítsd el a programot, és add meg az eredeti fájlt.

```text
--- XOR Fajl Titkosito v3.0 (Smart Name) ---
Fajl neve: dokumentum.pdf
Kulcs: titkosjelszo

Feldolgozas alatt... (dokumentum.pdf -> dokumentum.pdf.xor)
SIKER! A muvelet befejezodott.
```

#### B) Visszafejtés
Add meg a titkosított (`.xor` végű) fájlt bemenetként.

```text
--- XOR Fajl Titkosito v3.0 (Smart Name) ---
Fajl neve: dokumentum.pdf.xor
Kulcs: titkosjelszo

Feldolgozas alatt... (dokumentum.pdf.xor -> dokumentum_.pdf)
SIKER! A muvelet befejezodott.
```
Az eredményül kapott `dokumentum_.pdf` tökéletesen megnyitható.

---

## ⚠️ Jogi és Biztonsági Nyilatkozat
Ez a szoftver oktatási célokat szolgál. A használt XOR titkosítás ismétlődő kulccsal (Vigenère-jellegű) **nem nyújt ipari szintű biztonságot**. Ne használd bankkártyaadatok vagy szigorúan titkos információk védelmére!
