# Koncepcja implementacji modułu komunikacyjnego

#### Klasa Socket

Prosty wrapper obiektowy dla socketów unixowych.

#### Klasa Ip i dziedziczące

Bardzo drobna klasa, przechowuje adres Ip w postaci stringa przetrawialnego dla socketów unixowych. Generalnie zadaniem tej klasy jest sprawdzenie podczas wywołania konstruktora, czy podany adres jest poprawny.

Samo istnienie obiektu Ip gwarantuje, że przechowywany w nim adres jest prawidłowy. Ponadto w prezencie dostajemy kontrolę typów, przeciążanie funkcji w zależności od wersji adresu i ochronę stringa przed modyfikacją.

Klasy Ip udostępniają operator porównania (mniejszy niż), ale służy on jedynie do ustalenia **jakiegokolwiek** porządku w zbiorze adresów, co jest potrzebne w strukturach uporządkowanych typu map. Porównanie adresów Ip zwraca wynik porównania ich zapisów bitowych z sieciowym porządkiem bajtów. Nie mam pojęcia jak to się ma do "naturalnego" porządku typu 10.10.10.10 < 10.10.10.11, więc sugeruję nie używać tego operatora.

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

Klasa Connection reprezentuje pojedyncze, nawiązane połączenie. Obiekty tej klasy posiadają wskazanie na jeden zasocjowany socket związany z tym połączeniem. Poza realizacją komunikacji w obrębie swojego połączenia, klasa ta dba również o zachowanie odpowiedniej kolejności wysyłania komunikatów. Dla przykładu próba wysłania pod rząd dwóch komunikatów REQ zakończy się zgloszeniem wyjątku.

Czas życia obiektów Connection odpowiada czasowi trwania połączenia.

#### Klasa ConnectionManager

"Centrum dowodzenia" połączeniami. Singleton, przechowuje gniazdo nasłuchujące na porcie 55555, zarządza przyjmowaniem i nawiazywaniem połączeń. Każde połączenie trzymane jest w mapie z IP jako kluczem. Z danym hostem nie można nawiązać więcej niż jednego połączenia jednocześnie.

ConnectionManager wystawia całość interfejsu modułu komunikacyjnego protokołu LOTC. Nie ma potrzeby tworzenia własnych obiektów Socket lub Connection.

Obiekt tej klasy jest monitorem i gwarantuje bezpieczny dostęp współbieżny.

**Uwagi co do metod:**

send() - jeśli z danym adresem IP nie ma otwartego połączenia, jest ono automatycznie tworzone.  
receive() - jeśli z danym adresem IP nie ma otwartego połączenia, metoda ta czeka na utworzenie połączenia poprzez funkcję nasłuchującą.

remove() - usuwa adres IP (i powiązane polączenie) z mapy
send() i receive() automatycznie dodają nowy adres IP do mapy, jeśli nie znajdą w niej klucza odpowiadającego argumentowi wywołania. Nie ma potrzeby (ani możliwości :^) ) wcześniejszego zgłaszania adresów.


