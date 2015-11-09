# Zasady oceniania projektu
Przeklejam ze strony doktora Wytrębowicza, ku wygodzie i przestrodze.

## Punktacja

Maksymalnie można uzyskać 50 pkt.
Minimum wymagane do zaliczenia to 25 pkt.
Od 0 do 10 pkt. – za projekt wstępny i jego publiczną prezentację.
Od 0 do 15 pkt. – za przedstawienie działania zaplanowanych funkcji, w tym prezentacja przebiegu kompilacji, wykonania testów i scenariuszy demonstracyjnych.
Od 0 do 10 pkt. – za dokumentację projektu.
Od 0 do 5 pkt. – za jakość kodu.
Od 0 do 5 pkt. – za publiczną prezentację projektu.
Od 0 do 5 pkt. – za pracę w zespole, przydzielane przez lidera dla członków zespołu i przez prowadzącego dla lidera.
-5 pkt. – za niedotrzymanie terminu wysłania projektu wstępnego lub dokumentacji końcowej.

## Projekt wstępny

Projekt wstępny powinien określać:

    Treść zadania.
    Nazwę własną projektowanego systemu.
    Przyjęte założenia funkcjonalne i niefunkcjonalne.
    Podstawowe przypadki użycia.
    Wybrane środowisko sprzętowo-programowe (systemy operacyjne, biblioteki programistyczne) i narzędziowe (debugowanie, testowanie).
    Architekturę rozwiązania, tj. ilustrację i opis struktury logicznej systemu (koncepcyjnych bloków funkcjonalnych).
    Ewentualnie API modułów stanowiących bloki funkcjonalne.
    Sposób testowania.
    Sposób demonstracji rezultatów, tj. scenariusze testów akceptacyjnych do zaprezentowania przy odbiorze projektu.
    Podział prac w zespole.
    Adres projektu na serwerze kontroli wersji.

## Dokumentacja

Dokumentacja projektu powinna zawierać:
  1.  Zaktualizowany projekt wstępny.
  2.  Ilustrację i opis struktury implementacyjnej systemu (np. diagramy klas).
  3.  Definicję komunikatów:
       * ich strukturę (tj. typy parametrów) i sposób ich kodowania,
       * określenie kto jakie komunikaty odbiera i wysyła.
  4.  Opis zachowania poszczególnych podmiotów komunikacji, w tym:
       * jeżeli podmiot ten jest maszyną stanową, to należy podać graf automatu z warunkami przejść),
       * opis ewentualnych zegarów (timeout),
       * opis obsługi sytuacji błędnych,
       * przykładowe scenariusze komunikacji wyrażone np. w MSC lub w innych diagramach komunikatów.
  5.  Wnioski z wykonanego testowania.
  6.  Ewentualnie instrukcja instalacji i dezinstalacji stworzonego systemu.
  7.  Podsumowanie:
       * opis wyniesionych doświadczeń z realizacji projektu,
       * statystyki określające rozmiar stworzonych plików.
       * oszacowanie czasu poświęconego na realizację projektu w godzinach!

## Pliki projektu

Pliki zawierające projekt wstępny, dokumentację końcową, archiwum kodów źródłowych, muszą zawierać w nazwie nazwisko lidera projektu!
W nagłówku dokumentacji należy podać: tytuł dokumentu, autorów, datę sporządzenia! Dokumentacja powinna być napisana poprawną polszczyzną. Z dokumentacji powinno jasno wynikać kto co zrobił w projekcie.

Oczekuję, że pliki projektu składane będą na serwerze z systemem kontroli wersji (np. GitHub.com GitLab.com) i że otrzymam prawa do przeglądania kto, kiedy i jakie pliki umieszczał. Adres serwera z prawami dostępu chciałbym otrzymać razem z projektem wstępnym.
Pliki źródłowe powinny mieć w nagłówku metryczkę podającą w jednolity sposób co najmniej: nazwę projektu, autora (autorów), datę utworzenia.
