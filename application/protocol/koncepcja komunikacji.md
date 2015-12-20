# Koncepcja implementacji modułu komunikacyjnego

#### Klasa Socket

Prosty wrapper obiektowy dla socketów unixowych.

#### Klasa Ip i dziedziczące

Bardzo drobna klasa, przechowuje adres IP w postaci stringa przetrawialnego dla socketów unixowych. Generalnie zadaniem tej klasy jest sprawdzenie podczas wywołania konstruktora, czy podany adres jest poprawny.

Samo istnienie obiektu IP gwarantuje, że przechowywany w nim adres jest prawidłowy. Ponadto w prezencie dostajemy kontrolę typów, przeciążanie funkcji w zależności od wersji adresu i ochronę stringa przed modyfikacją.

#### Klasa Message

Idea jest prosta - klasa ta reprezentuje pojedynczy komunikat protokołu LOTC oraz udostępnia interfejs pozwalający na jego wygodne tworzenie i odczytywanie pól.

## Połączenia

Przez jedno "połączenie" rozumiemy wymianę komunikatów:

````
----REQ---> 
<---ACK---- 
<--OK/NOK--
----ACK--->
````

 - Po przesłaniu ostatniego komuniktu (ACK), połączenie jest zamykane.
 - Na raz może być otwarte tylko jedno połączenie (założenie protokołu - hosty nie wysyłają/przymują poleceń, nim nie zakończą przetwarzać poprzednich)

### Nawiązywanie połączeń

Każdy host nasłuchuje na porcie 55555 (na chwilę obecną). Oznacza to, że połączenie z innym hostem może zostać nawiązane za dwa sposoby - poprzez połączenie z portem 55555 drugiej strony (connect()) lub przyjęcie połączenia na własny port 55555 (accept()).

Nawiązanie połączenia oznacza utworzenie u hosta zasocjowanego gniazda, wykorzystywanego do wysyłania i odbierania komunikatów.

#### Klasa Connection

**UWAGA! Pliki klasy Connection na chwilę obecną zawierają wersję testową nieaktualnego, zarzuconego rozwiązania.**

Klasa Connection reprezentuje pojedyncze, nawiązane, otwarte połączenie. Obiekty tej klasy posiadają wskazanie na jeden zasocjowany socket związany z tym połączeniem. Poza realizacją komunikacji w obrębie swojego połączenia, klasa ta dba również o zachowanie odpowiedniej kolejności wysyłania komunikatów. Dla przykładu próba wysłania pod rząd dwóch komunikatów REQ zakończy się zgloszeniem wyjątku.

Czas życia obiektów Connection odpowiada czasowi trwania połączenia.

#### Klasa ConnectionManager

**Klasa jeszcze nie narodzona**

"Centrum dowodzenia" połączeniami. Singleton, przechowuje gniazdo nasłuchujące na porcie 55555, zarządza przyjmowaniem i nawiazywaniem połączeń, a także odpowiada za zarządzanie wątkami (jedno połączenie = jeden wątek). Pilnuje też, by z danym hostem nie nawiązać więcej niż jednego połączeni jednocześnie.

Klasa ta wystawia całość interfejsu mudułu komunikacyjnego protokołu LOTC. Nie ma potrzeby tworzenia własnych obiektów Socket lub Connection.

Obiekt tej klasy jest monitorem i gwarantuje bezpieczny dostęp współbieżny.
