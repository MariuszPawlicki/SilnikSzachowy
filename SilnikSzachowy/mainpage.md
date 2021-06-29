@mainpage Strona główna projektu
@tableofcontents

Autor: Mariusz Pawlicki

Obranym przeze mnie tematem projektu na przedmiocie ZAP 2 - projekt, było stworzenie Silnika Szachowego w języku c++. Poniżej postaram się przybliżyć założenia i cele projektu, a także opisać jego strukturę i wyjaśnić jego obsługę.

@section sub1sec1 Czym jest silnik szachowy?
Silnik szachowy jest programem potrafiącym analizować zadaną pozycję szachową pod kątem znalezienia najlepszego według algorytmu ruchu. Moja wersja programu używa w tym celu algorytmu MinMax polegającego na utworzeniu drzewa poszukiwań pozycji wynikowych z pozycji zadanej na określoną głębokość, a następnie przeprowadzeniu oceny statycznej uzyskanych pozycji wynikowych. Na tej podstawie wybiera on taki ruch, który w najgorszym wypadku (przeciwnik wybierający najlepsze dla niego ruchy) doprowadzi do jak najlepszej, dla strony wykonującej ruch, pozycji.

@section sub1sec2 Obsługa programu
@subsection sub1subsec1 Krok 1
Po uruchomieniu program prosi o podanie pozycji początkowej w postaci notacji szachowej FEN (notacja tekstowa). W przypadku nie podania żadnej pozycji program wczyta pozycję szachową wyjściową.

@subsection sub1subsec2 Krok 2
Następnie program wydrukuje wczytaną pozycję i spyta czy dla ułatwienia podać listę wszystkich możliwych do wykonania ruchów. Odpowiedzi należy udzielić poprzez wpisanie T (tak), lub N (nie), oraz zatwierdzenie ENTEREM.

@subsection sub1subsec3 Krok 3
Dalej program zapyta się czy użytkownik chce wyświetlić najlepszy ruch proponowany przez algorytm (tryb analizy), lub nie (tryb wolnej rozgrywki). Odpowiedzi udziela się w sposób opisany powyżej.

@subsection sub1subsec4 Krok 4
W przypadku odpowiedzi pozytywnej program poprosi jeszcze o podanie głębokości drzewa poszukiwań, która powinna znajdować się w zakresie <1, 4> (im większa podana wartość, tym dokładniejsza analiza i lepsze ruchy)

@subsection sub1subsec5 Krok 5
Na koniec należy podać ruch do wykonania (w notacji komputerowej prostej np. e2e4 e2 - pole z, e4 - pole na) i program po jego wykonaniu zacznie funkcjonować jak przy podaniu nowej pozycji będącej wynikiem zadanego ruchu w pozycji poprzedniej.

@section sub1sec3 Struktura programu
Działanie programu rozpoczyna się w funkcji main, gdzie poza zleceniem początkowego wczytania kodu FEN wszystkie inne wywołania funkcji odbywają się w pętli wykonującej się do momentu zakończenia rozgrywki (mata, lub remisu).

Program po przepisaniu zadanej pozycji w formie tekstowej przerabia ją na wygodną do obsługi zagnieżdżoną strukturę danych. Najważniejszą jej częścią jest jednokierunkowa dynamiczna ListaFigur zawierająca figury opisane jako typ (znak), oraz pole (kordynaty rząd-kolumna). Taki zapis planszy w teori jest wydajniejszy od statycznej tablicy 64 znaków.

Następnie dedykowana do tego funkcja żąda od wszystkich zapisanych w liście figur zwrócenia pól na jakie mogą się one poruszyć (robią to poprzez ich funkcje wewnętrzne). Zwrócone ruchy są jeszcze weryfikowane i kompilowane w jednokierunkową dynamiczną ListęRuchów.

Na koniec funkcja MinMax mając możliwość odnalezienia możliwych do wykonania ruchów w zadanej pozycji tworzy drzewo poszukiwań (z użyciem usprawnienia alfa-beta) na zadaną przez użytkownika głębokość i po jej uzyskaniu wywołuje funkcję przeprowadzającą ocenę statyczną pozycji wynikowych poprzez odjęcie od sumy przyjętych wag figur białych wagi figur czarnych. Funkcja ta zwraca również uwagę na to jak "aktywne" pola objęły dane figury, oraz ile łącznie figur znajduje się na szachownicy. Mając te dane algorytm MinMax'u wraz z usprawnieniem alfa-beta dokonuje wyboru najlepszego do wykonania ruchu i zwraca go wraz z oceną.