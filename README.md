### Bankomat
## TODO:
# ** >> Dodać podstawową klasę Bankomatu i dziedziczenie, **
	>> Tworzenie kont
        Metoda umożliwiająca tworzenie nowego konta bankowego.
        Parametry: dane klienta, początkowy depozyt itp.
        Zapisywanie danych konta w bazie danych.

    >> Sprawdzanie salda
        Metoda umożliwiająca sprawdzenie salda konta.
        Parametry: numer konta, dane uwierzytelniające.
        Zwracanie aktualnego salda konta.

    >> Wpłacanie pieniędzy
        Metoda umożliwiająca wpłacanie środków na konto.
        Parametry: numer konta, kwota wpłaty.
        Aktualizacja salda konta w bazie danych.

    >> Wypłacanie pieniędzy
        Metoda umożliwiająca wypłacanie środków z konta.
        Parametry: numer konta, kwota wypłaty.
        Sprawdzenie, czy saldo jest wystarczające, aktualizacja salda konta w bazie danych.

    >> Przelewy
        Metoda umożliwiająca dokonywanie przelewów między kontami.
        Parametry: numer konta nadawcy, numer konta odbiorcy, kwota przelewu.
        Sprawdzenie, czy saldo nadawcy jest wystarczające, aktualizacja salda obu kont w bazie danych.

    >> Generowanie raportów
        Metoda umożliwiająca generowanie raportów dotyczących operacji na koncie.
        Parametry: numer konta, zakres dat, typ raportu (np. miesięczny, kwartalny).
        Generowanie i zwracanie raportu w wybranym formacie.

    >> Historia transakcji
        Metoda umożliwiająca przeglądanie historii transakcji na koncie.
        Parametry: numer konta, zakres dat.
        Zwracanie listy transakcji dla wybranego okresu.

    >> Zarządzanie użytkownikami (administracja)
        Metody dla administratorów systemu, takie jak tworzenie, usuwanie i modyfikacja kont użytkowników.
        Parametry: dane użytkownika, poziom uprawnień itp.
        Zarządzanie rekordami użytkowników w bazie danych.

    >> Powiadomienia i alerty
        Metoda umożliwiająca konfigurowanie i wysyłanie powiadomień i alertów do użytkowników.
        Parametry: numer konta, typ powiadomienia (np. niskie saldo, duża transakcja).
        Mechanizm wysyłania powiadomień (np. email, SMS).

    >> Wsparcie dla wielu walut
        Metody umożliwiające zarządzanie kontami w różnych walutach.
        Parametry: numer konta, waluta, kwota.
        Przechowywanie i przeliczanie salda w różnych walutach.
# ** >> Wymyśleć jakieś klasy, **
    >> Standardowy klient
    >> Rodzic
    >> Konto dla dzieci
    >> Konto dla firm
    >> Konto dla Seniora
# ** >> Funkcja hashująca, aby zabezpieczyć dane, **
    >> Zabezpieczanie kont
        Metody związane z zabezpieczeniem kont, takie jak zmiana hasła, ustawianie pytania bezpieczeństwa itp.
        Parametry: numer konta, stare hasło, nowe hasło, odpowiedź na pytanie bezpieczeństwa itp.
        Aktualizacja danych uwierzytelniających w bazie danych.

    >> Logowanie i uwierzytelnianie użytkowników
        Metoda umożliwiająca logowanie użytkowników do systemu.
        Parametry: nazwa użytkownika, hasło.
        Sprawdzenie poprawności danych uwierzytelniających, zarządzanie sesjami użytkowników.
# ** >> Ogarnąć SQLite'a i interfejs graficzny. **