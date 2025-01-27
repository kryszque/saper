SPRAWOZDANIE JIMP1 projekt końcowy saper 

Autorzy: Kacper Kulesza 337580, Mateusz Krysiak 337576 gr 2 

Spis treści 

Podręcznik użytkowania…………………………………………………………………………………… 

Szczegóły implementacyjne………………………………………………………………………………

Podział pracy nad projektem………………………………………………………………………………… 

Podsumowanie………………………………………………………………………………………………….. 

Podręcznik użytkowania 

Kompilacja 

Nasz program kompiluje się za pomocą dedykowanego do tego pliku make, który  złączy wszystkie pliki źródłowe w wykonywalny. 

Wywołanie 

Program posiada dwie możliwe flagi wywołania. 

-n (normal mode) 

 rys 1. Przykładowe wywołanie w trybie normalnym na so windows. 

Program w tym trybie pozwala na klasyczną grę w sapera.  

Po następującym wywołaniu użytkownik zostanie poproszony o podanie poziomu trudności gry. Do wyboru istnieją cztery opcje; po wpisaniu ‘1’ – tryb łatwy (plansza 9x9 z dziesięcioma minami) , po wpisaniu ‘2’ – tryb średni (plansza 16x16 z czterdziestoma minami), po wpisaniu ‘3’ – tryb trudny (plansza 16x30 z dziewięćdziesięcioma dziewięcioma minami), po wpisaniu ‘4’ – tryb własny (dowolny rozmiar planszy i ilość min, po wybraniu tej opcji gracz zostanie poproszony o podanie rozmiaru planszy oraz ilości min).  

Po decyzji dotyczącej poziomu trudności rozpoczyna się gra – wyświetlona zostaje plansza i użytkowni zostaje poproszony o wykonanie pierwszego ruchu. Istnieją dwa możliwe ruchy f x y lub r x y, gdzie x i y to współrzędne na planszy a f i r to rodzaje ruchu, f – postawienie flagi na danym polu (postawienie flagi na polu bez miny równoznaczne jest z jego odkryciem), r – odkrycie danego pola. Po dokonaniu ruchu plansza zostaje zaktualizowana o wykonane posunięcie.  

W tym momencie następne ruchy przetwarzane są w sposób analogiczny do momentu odkrycia miny lub wszystkich pól bez nich, co jest równoznaczne z zakończeniem rozgrywki.  

W trakcie gry graczowi wyświetlane są uzyskane przez niego punkty, liczone według następującej formuły: pomnożenie liczby odsłoniętych pól x mnożnik, gdzie mnożnik to jest poziom trudności 1 - łatwy, 2 - normalny, 3 trudny (w przypadku planszy własnej przyjmujemy stały mnożnik równy 1). 

Po skończonej rozgrywce użytkownik proszony jest o podanie swojej nazwy, która później w pliku tabela_wyników.txt będzie go reprezentowała wraz z uzyskanym wynikiem.  

Następnie zostaje wyświetlone pięć najlepszych wyników i nazwy graczy w porządku malejącym. 

-f [plik] (file mode) 

 rys 1. Przykładowe wywołanie w trybie wczytywania z pliku na so Windows 

Program w tym trybie pozwala na sprawdzenie ruchów dla planszy zawartych w pliku podanego jako argument opcji.  

Program bez podania argumentu wywołania w postaci pliku nie uruchomi się! 

Obraz zawierający tekst, Czcionka, zrzut ekranu, książka

Opis wygenerowany automatycznierys 2. Przykładowa zawartość pliku z danymi o poprawnym formacie 

Aby program w trybie sczytywania z pliku działał poprawnie zachowany musi być ścisły format pliku źródłowego. Pierwsza w pliku musi znaleźć się plansza, w której pierwszy wiersz musi zawierać maksymalną długość wiersza. Plansza składa się z 0 i 1, gdzie 0 oznacza pole bez miny, natomiast 1 symbolizuje pole z miną.  Następne wiersze planszy mogą być krótsze (ale nie puste), brakujące miejsca automatycznie zostaną zastąpione przez 0 do uzyskania długości wiersza pierwszego.  

Po planszy musi nastąpić rozgraniczenie w postaci pustej linii.  

Następnie w pliku muszą znaleźć się ruchy w formacie txy, gdzie t – rodzaj ruchu, analogicznie jak w trybie normalnym f – postawienie flagi na danym polu, r – odkrycie danego pola, x i y współrzędne pola.  

Program po wywołaniu wypisze w terminalu pełną planszę (uzupełnioną zerami w brakujących miejscach) oraz sprawdzone ruchy – w przypadku niepoprawnego formatu posunięć lub współrzędnych wykraczających poza zakres planszy wyświetlony zostanie odpowiedni komunikat, dany ruch nie będzie brany pod uwagę.  

Następnie użytkownik dostanie informację o wyniku sprawdzenia oraz uzyskanych przez podane ruchy i dla danej planszy punktach. 

Możliwe są trzy scenariusze: 

Gra zakończyła się porażką – któryś z ruchów odkrył pole z miną 

Gra zakończyła się zwycięstwem – wszystkie pole bez min zostały odkryte bądź oznaczone flagą, przy równoczesnym braku odkrycia pól z minami. 

Gra nierozstrzygnięta – żaden z podanych ruchów nie odkrył miny, ale nie odkryły one również wszystkich pól bez nich.  

 

Szczegóły implementacyjne 

Program realizowany był na dwóch systemach operacyjnych Windows 10 i środowisku Visual Studio Code oraz Linux w dystrybucji Debian w środowisku Neovim. Powstał przy użyciu systemu kontroli wersji git, a repozytorium istnieje na serwerze GitHub. 

Gałąź interface 

Plik main.c 

Zawiera wszystkie funkcje zdefiniowane w pozostałych plikach oraz interface użytkownika. Sprawdza poprawność argumentów wywołania za pomocą prostych warunków jak np. Obraz zawierający tekst, zrzut ekranu, Czcionka, linia

Opis wygenerowany automatycznie  

Rys 2. warunek sprawdzający poprawność argumentów wywołania. 

Zbiera informacje podane przez użytkownika, na podstawie wybranej opcji i instrukcji switch case przekazuje je do odpowiednich funkcji funkcji np. 
Obraz zawierający tekst, zrzut ekranu, Czcionka

Opis wygenerowany automatycznie rys 3. konstrukcja switch case z wyborem poziomu gry 

Zawiera zdefiniowane wszystkie makra programu. 

Obraz zawierający tekst, zrzut ekranu, Czcionka

Opis wygenerowany automatycznie rys 4. makra programu w pliku main.c 

 

Pliki users.c i users.h 

Pliki users.c i users.h odpowiedzialne są za zarządzanie użytkownikami gry. Zawierają funkcje dopisujące graczy z ich wynikami do pliku oraz wypisującą top 5 wyników. 

Dane najpierw wpisywane są do pliku za pomcą funkcji add_usr(), wykorzystującej fprintf(). Następnie plik jest ponownie otwierany w funkcji display_lisy(), która sczytuje informacje o graczach z pliku za pomocą fgets() i na ich podstawie tworzy listę wskaźników na struktury user, zdefiniowanej w sposób następujący: 

Obraz zawierający tekst, Czcionka, zrzut ekranu, linia

Opis wygenerowany automatycznie rys 5. Struktura user 

Przekazanie wskaźników odbywa się za pomocą funkcji strndup(), napisanej w pliku users.c, która tworzy kopie podanego wskaźnika.  

Następnie lista jest sortowana malejąco po polu char *score za pomocą funkcji qsort() i wyświetlone zostaje top 5 wyników.  

 

Gałąź file_mode 

Pliki file_mode.h i file_mode.h 

File_mode.c oraz file_mode.h odpowiedzialne są z sczytanie informacji (planszy oraz ruchów) z pliku podanego jako argument wywołania programu. Plik źródłowy musi mieć określony format opisany w -f [plik] (file mode). Dane o planszy sczytywane są z przez funkcję read_board(), która wykorzystuje getline() (napisana w file_mode.c) do czytania pliku. Tworzy listę jednowymiarową struktur Cell reprezentującą planszę.  
Obraz zawierający tekst, Czcionka, zrzut ekranu, design

Opis wygenerowany automatycznie rys 6. Struktura Cell zdefiniowana w board.h, używana również w gałęzi board, przechowująca informacje o pojedynczej komórce.  

Przechowywanie planszy w liście jednowymiarowej jest optymalnym rozwiązaniem, w porównaniu z przechowywaniem planszy w macierzy. Funkcja zwraca wskaźnik na pierwszy element listy. 

Sczytywanie ruchów z pliku odbywa się za pomocą funkcji read_moves(), która czyta plik w sposób analogiczny do read_board(), z tą różnicą, że tworzy listę struktur Move reprezentujących ruchy.  

Obraz zawierający tekst, Czcionka, zrzut ekranu

Opis wygenerowany automatycznie rys 7. Struktura Move zdefiniowana w file_mode.h przechowująca informacje o pojedynczym ruchu. 

Funkcja zwraca wskaźnik na pierwszy element listy. 

Funkcje print_read_board() i print_read_moves() odpowiedzialne są za wypisywanie sczytanych planszy i ruchów w terminalu. 

Funkcja free_read_moves(), zwalnia przydzieloną pamięć dla stringów move_skip w strukturach Move. 

Funkcja solve(), przechodzi przez listę struktur Move i na podstawie zawartych w nich danych zmienia odpowiednie pola w strukturze Cell. Jeśli przy odkrywaniu pola natrafi na komórkę z bombą od razu zwraca 0, co oznacza przegraną. Jeśli skończy tablicę ruchów i nie natrafi na minę przechodzi przez całą tablicę zmienionych struktur Cell i liczy ile pól bez min zostało odkrytych. W przypadku odkrycia wszystkich, zwraca 1 – zwycięstwo, jeśli nie wszystkie, zwraca 2 – gra nierozstrzygnięta.  

 

Gałąź board 

Plik board.c 

Ten plik definiuje funkcje związane z tworzeniem, zarządzaniem i wyświetlaniem planszy. 

Kluczowe funkcje: 

Cell* create_board(int row, int col): Alokuje pamięć na planszę o rozmiarze row x col i zwraca wskaźnik do niej. 

void free_board(Cell* board): Zwalnia pamięć przydzieloną dla planszy. 

void initialize_board(Cell* board, int row, int col): Inicjalizuje wszystkie komórki planszy jako puste. 

void clear_console(): Czyści konsolę, działając na Windows i UNIX/Linux. 

void print_board(Cell* board, int row, int col): Wyświetla aktualny stan planszy w konsoli, uwzględniając widoczność pól, flagi i bomby. 

void generate_bombs(Cell* board, int bombnum, int row, int col): Rozmieszcza losowo bombnum bomb na planszy. 

int is_valid(Cell* board, int max_cols, int row, int col): Sprawdza, czy dana komórka jest odpowiednia do umieszczenia bomby. 

int count_adjacent_bombs(Cell* board, int row, int col, int max_row, int max_col): Liczy bomby wokół danej komórki. 

void check_for_bombs(Cell* board, int max_row, int max_col): Oznacza komórki planszy liczbą bomb w sąsiedztwie. 

 

2. Plik board.h 

Ten plik nagłówkowy deklaruje strukturę Cell oraz prototypy funkcji z pliku board.c. 

Kluczowe elementy: 

Struktura Cell: 

int bomb: 1 oznacza, że komórka zawiera bombę. 

char num: Liczba bomb w sąsiedztwie (lub 'B' dla bomby). 

int flag: Flaga oznaczająca, że gracz oznaczył komórkę. 

int visible: Oznacza, czy komórka jest widoczna. 

 

3. Plik engine.c 

Ten plik zarządza logiką gry i interakcjami użytkownika. 

Kluczowe funkcje: 

int is_game_over(Cell* board, int max_row, int max_col): Sprawdza, czy gra się zakończyła (odkrycie bomby lub odsłonięcie wszystkich pól). 

void set_multiplier(int level): Ustawia mnożnik punktowy na podstawie poziomu trudności. 

void update_board_on_first_move(Cell* board, int row, int col, int max_row, int max_col): Aktualizuje planszę, aby pierwsze kliknięcie nigdy nie kończyło gry. 

void reveal_whole_map(Cell* board, int max_col, int max_row): Odsłania całą planszę. 

int count_score(int moves): Oblicza wynik na podstawie liczby ruchów i mnożnika. 

void reveal(Cell* board, int row, int col, int max_col, int max_row): Odkrywa pole (rekurencyjnie, jeśli sąsiaduje z pustymi polami). 

void move(Cell* board, int x, int y, int max_col, int max_row, char order): Wykonuje ruch gracza (r dla odkrycia pola, f dla dodania/usunięcia flagi). 

int game(Cell* board, int max_col, int max_row, int total_bombs): Główna pętla gry, obsługująca logikę ruchów, wyświetlanie planszy i obliczanie wyniku. 

 

Podział pracy w zespole 

Nasze repozytorium na GitHubie zawiera 4 gałęzie reprezentujące różne części programu. 

 rys  lista branchy w repozytorium na GitHubie 

Następujące gałęzie zawierają następujące części programu: 

Gałąź master – główna gałąź, zawiera całość programu. 

Gałąź interface – zawiera plik main.c z wywoływaniem funkcji oraz cały interface użytkownika oraz pliki users.c i users.h, które odpowiedzialne są za funkcje związane z dopisywaniem użytkowników do tabeli wyników oraz wyświetlanie top5 wyników. 

Gałąź file_mode – zawiera pliki file_mode.c i file_mode.h, które w pełni obsługują tryb sczytywania z pliku. 

Gałąź board – zawiera pliki board.c, board.h, engine.c oraz engine.h odpowiedzialne za pełną obsługę trybu normalnego gry.  

Podział prac był następujący: 

Kacper Kulesza – branch board 

Mateusz Krysiak – branche interface i file_mode 

Ponadto wszelkie nieścisłości, koncepty, wykorzystane algorytmy, rozwiązania oraz ogólny zarys projektu w pełni ustalaliśmy wspólnie.  

Podsumowanie 

Projekt był wymagający lecz pozwolił nam spiąć i zastosować w praktyce wszystkiego czego nauczyliśmy się w tym semestrze na JIMP1. Nasz program jest w pełni funkcjonalny i spełnia wszystkie założenia. Czas pracy to około tydzień. Największe problemy sprawiły nam poprawne sczytywanie danych do dalszego przetwarzania i manipulacji z plików oraz funkcja odpowiedzialna za dawanie gwarancji, że nie trafimy na bombę w pierwszym ruchu.  
Źródła:  
https://www.geeksforgeeks.org/ 
https://stackoverflow.com/ 
https://chatgpt.com/ 
https://claude.ai/ 
https://cpp0x.pl/ 
https://www.ibm.com/ 
