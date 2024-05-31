# Bankomat

## Opis
Bankomat to projekt systemu bankowego umożliwiający zarządzanie kontami bankowymi oraz wykonywanie różnorodnych operacji finansowych. System obsługuje tworzenie kont, sprawdzanie salda, wpłaty i wypłaty, przelewy, generowanie raportów, przeglądanie historii transakcji, zarządzanie użytkownikami, powiadomienia, wsparcie dla wielu walut oraz zabezpieczenia kont.

## Funkcjonalności

### Tworzenie kont
- Metoda umożliwiająca tworzenie nowego konta bankowego.
- Parametry: dane klienta, początkowy depozyt itp.
- Zapisywanie danych konta w bazie danych.

### Sprawdzanie salda
- Metoda umożliwiająca sprawdzenie salda konta.
- Parametry: numer konta, dane uwierzytelniające.
- Zwracanie aktualnego salda konta.

### Wpłacanie pieniędzy
- Metoda umożliwiająca wpłacanie środków na konto.
- Parametry: numer konta, kwota wpłaty.
- Aktualizacja salda konta w bazie danych.

### Wypłacanie pieniędzy
- Metoda umożliwiająca wypłacanie środków z konta.
- Parametry: numer konta, kwota wypłaty.
- Sprawdzenie, czy saldo jest wystarczające, aktualizacja salda konta w bazie danych.

### Przelewy
- Metoda umożliwiająca dokonywanie przelewów między kontami.
- Parametry: numer konta nadawcy, numer konta odbiorcy, kwota przelewu.
- Sprawdzenie, czy saldo nadawcy jest wystarczające, aktualizacja salda obu kont w bazie danych.

### Generowanie raportów
- Metoda umożliwiająca generowanie raportów dotyczących operacji na koncie.
- Parametry: numer konta, zakres dat, typ raportu (np. miesięczny, kwartalny).
- Generowanie i zwracanie raportu w wybranym formacie.

### Historia transakcji
- Metoda umożliwiająca przeglądanie historii transakcji na koncie.
- Parametry: numer konta, zakres dat.
- Zwracanie listy transakcji dla wybranego okresu.

### Zarządzanie użytkownikami (administracja)
- Metody dla administratorów systemu, takie jak tworzenie, usuwanie i modyfikacja kont użytkowników.
- Parametry: dane użytkownika, poziom uprawnień itp.
- Zarządzanie rekordami użytkowników w bazie danych.

### Powiadomienia i alerty
- Metoda umożliwiająca konfigurowanie i wysyłanie powiadomień i alertów do użytkowników.
- Parametry: numer konta, typ powiadomienia (np. niskie saldo, duża transakcja).
- Mechanizm wysyłania powiadomień (np. email, SMS).

### Wsparcie dla wielu walut
- Metody umożliwiające zarządzanie kontami w różnych walutach.
- Parametry: numer konta, waluta, kwota.
- Przechowywanie i przeliczanie salda w różnych walutach.

### Klasy użytkowników
- Standardowy klient
- Rodzic
- Konto dla dzieci
- Konto dla firm
- Konto dla seniora

### Zabezpieczenia
- Funkcja hashująca dla zabezpieczenia danych.
- Zabezpieczanie kont: zmiana hasła, ustawianie pytania bezpieczeństwa itp.
- Logowanie i uwierzytelnianie użytkowników: nazwa użytkownika, hasło, zarządzanie sesjami użytkowników.

