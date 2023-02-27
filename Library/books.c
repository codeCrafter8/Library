#include "bilbioteka.h"

int book_id = 0; /** zmienna book_id okreslająca numer identyfikatora ksiazki. */

/** \brief Funkcja odczytuje dane z pliku "books.txt"
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *
 */
void create_books(struct books_pointers *books_p)
{
    FILE *file = fopen("books.txt", "r");
    struct books *current = NULL;
    if(NULL == file)
    {
        printf("Blad otwarcia pliku!");
        exit (1);
    }
    else
    {
        if(books_p->first == NULL)
        {
            books_p->first = (struct books *)malloc(sizeof(struct books));
            if(NULL != books_p->first)
            {
                fscanf(file,"%d %s %s %s %s %d %d",&books_p->first->id,books_p->first->title,books_p->first->year,books_p->first->author,books_p->first->genre,&books_p->first->copies,&books_p->first->numberofrentals);
                books_p->first->next = NULL;
                current = books_p->first;
                while(!feof(file))
                {
                    struct books *newbook = (struct books *)malloc(sizeof(struct books));
                    if(NULL != newbook)
                    {
                        fscanf(file,"%d %s %s %s %s %d %d\n",&newbook->id,newbook->title,newbook->year,newbook->author,newbook->genre,&newbook->copies,&newbook->numberofrentals);
                        current->next = newbook;
                        current = newbook;
                    }
                }
                books_p->last = current;
                book_id = books_p->last->id;
                current->next = NULL;
            }

        }
    }
    fclose(file);
}
/** \brief Funkcja wyswietla liste ksiazek.
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *
 */
void print_books(struct books_pointers books_p)
{
    if(books_p.first == NULL)
    {
        printf("Brak ksiazek do wyswietlenia.\n");
        return;
    }
    printf("%-4s %-25s %-7s %-20s %-15s %-15s\n","ID","TYTUL","ROK","AUTOR","GATUNEK","LICZBA EGZEMPLARZY");
    puts("~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~ ~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~");
    for(;books_p.first!=NULL;books_p.first=books_p.first->next)
    {
        printf("%-4d %-25s %-7s %-20s %-15s %-15d",books_p.first->id,books_p.first->title,books_p.first->year,books_p.first->author,books_p.first->genre,books_p.first->copies);
        puts("");
    }
    puts("");
}
/** \brief Funkcja sprawdza czy dane autora ksiazki zostaly podane poprawnie.
 *
 *  \param autor zmienna przechowujaca autora ksiazki.
 *  \return zwraca 1, gdy autor jest poprawny.
 *
 */
int check_author(char author[30])
{
    int counter = 0;
    for(int i = 0; i < strlen(author); i++)
    {
        if((author[i] >= 65 && author[i] <= 90) || (author[i] >= 97 && author[i] <= 122) || author[i] == 46 || author[i] == 32 || author[i] == 45)
            counter++;
    }
    if(counter == strlen(author))
        return 1;
    return 0;
}
/** \brief Funkcja sprawdza czy podany gatunek ksiazki zostal poprawnie zapisany.
 *
 *  \param genre zmienna przechowujaca gatunek ksiazki.
 *  \return zwraca 1, gdy gatunek jest poprawny.
 *
 */
int check_genre(char genre[30])
{
    int counter = 0;
    for(int i = 0; i < strlen(genre); i++)
    {
        if((genre[i] >= 65 && genre[i] <= 90) || (genre[i] >= 97 && genre[i] <= 122) || genre[i] == 32)
            counter++;
    }
    if(counter == strlen(genre))
        return 1;
    return 0;
}
/** \brief Funkcja sprawdza czy zostal podany poprawny rok wydania ksiazki.
 *
 *  \param year zmienna przechowujaca rok wydania ksiazki
 *  \return zwraca 1, gdy rok wydania ksiazki jest poprawny.
 *
 */
int check_year(char year[5])
{
    int counter = 0;
    for(int i = 0; i < strlen(year); i++)
    {
        if(year[i] >= 48 && year[i] <= 57)
            counter++;
    }
    if(counter == strlen(year))
        return 1;
    return 0;
}
/** \brief Funkcja umozliwia dodanie nowej ksiazki.
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *
 */
void add_book(struct books_pointers *books_p)
{
     struct books *newbook = (struct books *)malloc(sizeof(struct books));
     if(NULL != newbook)
     {
         newbook->next = NULL;
         newbook->id = ++book_id;
         getchar();
         printf("Podaj tytul: ");
         gets(newbook->title);
         while(1){
         printf("Podaj rok:");
         char year[4];
         scanf("%s",year);
         if(check_year(year))
         {
             strcpy(newbook->year, year);
             break;
         }
         else
            printf("Niepoprawnie podano rok.\n");
         }
         getchar();
         while(1){
         printf("Podaj autora:");
         char author[30];
         gets(author);
         if(check_author(author))
         {
             strcpy(newbook->author, author);
             break;
         }
         else
            printf("Niepoprawnie podano autora.\n");
         }
         while(1){
         printf("Podaj gatunek:");
         char genre[30];
         gets(genre);
         if(check_genre(genre))
         {
             strcpy(newbook->genre, genre);
             break;
         }
         else
            printf("Niepoprawnie podano gatunek.\n");
         }
         printf("Podaj ilosc egzemplarzy:");
         scanf("%d",&newbook->copies);
         newbook->numberofrentals = 0;
         if(NULL == books_p->first)
            books_p->first = books_p->last = newbook;
         books_p->last->next = newbook;
         books_p->last = newbook;
         printf("ID ksiazki to: %d.\n",book_id);
     }
}
/** \brief Funkcja realizuje pytanie odnośnie kontynuacji.
 *
 *  \return zwraca 1 w razie kontunacji.
 *
 */
int book_question()
{
    while(1){
    printf("Czy chcesz kontynuowac?\n1 - tak\n2 - nie\n");
    int choice;
    scanf("%d",&choice);
    if(choice == 1)
        return 1;
    if(choice == 2)
        return 0;
    else
        printf("Nie ma takiej opcji.\n\n");}
}
/** \brief Funkcja umozliwia edycje ksiazki.
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *
 */
void edit_book(struct books_pointers *books_p)
{
    if(books_p->first == NULL)
    {
        printf("Brak ksiazek do edycji.\n");
        return;
    }
    printf("Podaj ID ksiazki, ktora chcesz edytowac: ");
    int id, choice;
    scanf("%d",&id);
    struct books *current = books_p->first;
    while(current->id != id)
    {
        current = current->next;
        if(current == NULL)
        {
            printf("Brak ksiazki o podanym ID.\n");
            return;
        }
    }
    system("cls");
    printf("Dane tej ksiazki:\n\n");
    printf("%-4s %-25s %-7s %-20s %-15s %-15s\n","ID","TYTUL","ROK","AUTOR","GATUNEK","LICZBA EGZEMPLARZY");
    puts("~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~ ~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~");
    printf("%-4d %-25s %-7s %-20s %-15s %-15d",current->id,current->title,current->year,current->author,current->genre,current->copies);
    puts("");
    puts("");
    if(book_question()){
    printf("Podaj, co chcesz edytowac:\n1 - tytul\n2 - rok\n3 - autor\n4 - gatunek\n5 - ilosc egzemplarzy\n");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        printf("Podaj nowy tytul:");
        getchar();
        gets(current->title);
        break;
    case 2:
        printf("Podaj nowy rok:");
        scanf("%s",current->year);
        break;
    case 3:
        printf("Podaj nowego autora:");
        getchar();
        gets(current->author);
        break;
    case 4:
        printf("Podaj nowy gatunek:");
        getchar();
        gets(current->genre);
        break;
    case 5:
        printf("Podaj nowa ilosc egzemplarzy:");
        scanf("%d",&current->copies);
        break;
    default:
        printf("Nie ma takiej opcji edycji.\n");
        break;
    }
    }
}
/** \brief Funkcja umozliwia usuniecie ksiazki.
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *
 */
void delete_book(struct books_pointers *books_p)
{
    if(books_p->first == NULL)
    {
        printf("Brak ksiazek do usuniecia.\n");
        return;
    }
    printf("Podaj ID ksiazki, ktora chcesz usunac: ");
    int id;
    scanf("%d",&id);
    struct books *current = books_p->first;
    struct books *prev;
    while(current->id != id)
    {
        prev = current;
        current = current->next;
        if(current == NULL)
        {
            printf("Brak ksiazki o podanym ID.\n");
            return;
        }
    }
    system("cls");
    printf("Dane tej ksiazki:\n\n");
    printf("%-4s %-25s %-7s %-20s %-15s %-15s\n","ID","TYTUL","ROK","AUTOR","GATUNEK","LICZBA EGZEMPLARZY");
    puts("~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~ ~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~");
    printf("%-4d %-25s %-7s %-20s %-15s %-15d",current->id,current->title,current->year,current->author,current->genre,current->copies);
    puts("");
    puts("");
    if(book_question()){
    if(current == books_p->first)
    {
        books_p->first = current->next;
        free(current);
        current = NULL;
    }
    else
    {
        prev->next = current->next;
        free(current);
        current = NULL;
    }
    }
}
/** \brief Funkcja realizuje pytania odnosnie sortowania ksiazek.
 *
 *  \return zwraca 1, gdy sortowanie ma byc rosnace, -1 gdy malejace.
 *
 */
int sort_question()
{
    printf("Podaj, czy chcesz sortowac rosnaco czy malejaco:\n1-rosnaco\n2-malejaco\n");
    int choice;
    scanf("%d",&choice);
    if(choice == 1)
        return 1;
    else if(choice == 2)
        return -1;
    else
        printf("Nie ma takiej opcji.\n");
}
/** \brief Funkcja realizuje zamiane danych dwoch elementow.
 *
 */
void swap_books(struct books *current, struct books *current2)
{
    int pom_ID, pom_copies, pom_numberofrentals;
    char pom_title[30], pom_author[30], pom_genre[30], pom_year[5];
    pom_ID = current->id;

    strcpy(pom_title,current->title);
    strcpy(pom_year, current->year);
    strcpy(pom_author,current->author);
    strcpy(pom_genre,current->genre);
    pom_copies = current->copies;
    pom_numberofrentals = current->numberofrentals;

    strcpy(current->title,current2->title);
    strcpy(current->year,current2->year);
    strcpy(current->author,current2->author);
    strcpy(current->genre,current2->genre);
    current->copies = current2->copies;
    current->numberofrentals = current2->numberofrentals;
    current->id = current2->id;

    strcpy(current2->title,pom_title);
    strcpy(current2->year, pom_year);
    strcpy(current2->author,pom_author);
    strcpy(current2->genre,pom_genre);
    current2->copies = pom_copies;
    current2->numberofrentals = pom_numberofrentals;
    current2->id = pom_ID;
}
/** \brief Funkcja realizuje sortowanie ksiazek wedlug tytulu.
 *
 *  \param type_of_sort zmienna, ktora okresla sposob sortowania.
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *
 */
void sort_by_title(int type_of_sort, struct books_pointers *books_p)
{
    if(books_p->first == NULL)
    {
        printf("Brak ksiazek do posortowania.");
        return;
    }
    for(books_p->current = books_p->first; books_p->current->next != NULL; books_p->current = books_p->current->next)
    {
        for(books_p->current2 = books_p->current->next; books_p->current2 != NULL; books_p->current2 = books_p->current2->next)
        {
            if(strcmp(books_p->current->title,books_p->current2->title) == type_of_sort)
                swap_books(books_p->current, books_p->current2);
        }

    }
}
/** \brief Funkcja realizuje sortowanie ksiazek wedlug autora.
 *
 *  \param type_of_sort zmienna, ktora okresla sposob sortowania.
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *
 */
void sort_by_author(int type_of_sort, struct books_pointers *books_p)
{
    if(books_p->first == NULL)
    {
        printf("Brak ksiazek do posortowania.");
        return;
    }
    for(books_p->current = books_p->first; books_p->current != NULL; books_p->current = books_p->current->next)
    {
        for(books_p->current2 = books_p->current->next; books_p->current2 != NULL; books_p->current2 = books_p->current2->next)
        {
            if(strcmp(books_p->current->author,books_p->current2->author)==type_of_sort)
                swap_books(books_p->current,books_p->current2);
        }

    }
}
/** \brief Funkcja realizuje sortowanie ksiazek wedlug gatunku.
 *
 *  \param type_of_sort zmienna, ktora okresla sposob sortowania.
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *
 */
void sort_by_genre(int type_of_sort, struct books_pointers *books_p)
{
    if(books_p->first == NULL)
    {
        printf("Brak ksiazek do posortowania.");
        return;
    }
    for(books_p->current = books_p->first; books_p->current != NULL; books_p->current = books_p->current->next)
    {
        for(books_p->current2 = books_p->current->next; books_p->current2 != NULL; books_p->current2 = books_p->current2->next)
        {
            if(strcmp(books_p->current->genre,books_p->current2->genre)==type_of_sort)
                swap_books(books_p->current,books_p->current2);
        }
    }
}
/** \brief Funkcja realizuje sortowanie ksiazek wedlug roku ich wydania.
 *
 *  \param type_of_sort zmienna, ktora okresla sposob sortowania.
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *
 */
void sort_by_year(int type_of_sort, struct books_pointers *books_p)
{
    if(books_p->first == NULL)
    {
        printf("Brak ksiazek do posortowania.");
        return;
    }
    for(books_p->current = books_p->first; books_p->current->next != NULL; books_p->current = books_p->current->next)
    {
        for(books_p->current2 = books_p->current->next; books_p->current2 != NULL; books_p->current2 = books_p->current2->next)
        {
            if(strcmp(books_p->current->year, books_p->current2->year) == type_of_sort)
                swap_books(books_p->current, books_p->current2);
        }
    }
}
/** \brief Funkcja realizuje sortowanie ksiazek wedlug ilosci dostepnych egrzemplarzy.
 *
 *  \param type_of_sort zmienna, ktora okresla sposob sortowania.
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *
 */
void sort_by_copies(int type_of_sort, struct books_pointers *books_p)
{
    if(books_p->first == NULL)
    {
        printf("Brak ksiazek do posortowania.");
        return;
    }
    for(books_p->current = books_p->first; books_p->current != NULL; books_p->current = books_p->current->next)
    {
        for(books_p->current2 = books_p->current->next; books_p->current2 != NULL; books_p->current2 = books_p->current2->next)
        {
            if(books_p->current->copies > books_p->current2->copies && type_of_sort == 1)
               swap_books(books_p->current, books_p->current2);
            if(books_p->current->copies < books_p->current2->copies && type_of_sort == -1)
                swap_books(books_p->current, books_p->current2);
        }
    }
}
/** \brief Funkcja przedstawia menu sortowania ksiazek.
 *
 */
void sort_books()
{
    int choice;
    printf("Wybierz pole, po ktorym chcesz sortowac:\n1 - tytul\n2 - rok\n3 - autor\n4 - gatunek\n5 - ilosc egzemplarzy\n6 - wyjscie do menu\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            sort_by_title(sort_question(), &pointers_b);
            system("cls");
            print_books(pointers_b);
            break;
        case 2:
            sort_by_year(sort_question(),&pointers_b);
            system("cls");
            print_books(pointers_b);
            break;
        case 3:
            sort_by_author(sort_question(),&pointers_b);
            system("cls");
            print_books(pointers_b);
            break;
        case 4:
            sort_by_genre(sort_question(),&pointers_b);
            system("cls");
            print_books(pointers_b);
            break;
        case 5:
            sort_by_copies(sort_question(),&pointers_b);
            system("cls");
            print_books(pointers_b);
            break;
        case 6:
            return main();
        default:
            printf("Nie ma takiej opcji.");
            break;
        }

}
/** \brief Funkcja z menu wyszukiwania ksiazek.
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *
 */
void find_book(struct books_pointers books_p)
{
    printf("Podaj pole, po ktorym chcesz wyszukac ksiazke\n1 - ID\n2 - tytul\n3 - rok\n4 - autor\n5 - gatunek\n6 - ilosc egzemplarzy\n");
    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        printf("Podaj ID: ");
        int id;
        scanf("%d",&id);
        find_book_by_id(books_p, id);
        break;
    case 2:
        printf("Podaj tytul: ");
        char title[30];
        scanf("%s",title);
        find_book_by_title(books_p, title);
        break;
    case 3:
        printf("Podaj rok: ");
        char year[5];
        scanf("%s",year);
        find_book_by_year(books_p,year);
        break;
    case 4:
        printf("Podaj autora: ");
        char author[30];
        scanf("%s",author);
        find_book_by_author(books_p,author);
        break;
    case 5:
        printf("Podaj gatunek: ");
        char genre[30];
        scanf("%s",genre);
        find_book_by_genre(books_p,genre);
        break;
    case 6:
        printf("Podaj ilosc egzemplarzy: ");
        int copies;
        scanf("%d",&copies);
        find_book_by_copies(books_p, copies);
        break;
    default:
        printf("Nie ma takiej opcji.\n");
        break;
    }
}
/** \brief Funkcja wyszukujaca ksiazke po jej numerze id.
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *  \param id zmienna, ktora zawiera numer identyfikatora.
 *
 */
void find_book_by_id(struct books_pointers books_p, int id)
{
    books_p.current = books_p.first;
    while(books_p.current->id != id)
        {
            books_p.current = books_p.current->next;
            if(books_p.current == NULL){
                printf("Brak ksiazki o podanym ID.\n");
                return;
            }
        }
    printf("%-4s %-25s %-7s %-20s %-15s %-15s\n","ID","TYTUL","ROK","AUTOR","GATUNEK","LICZBA EGZEMPLARZY");
    puts("~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~ ~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~");
    printf("%-4d %-25s %-7s %-20s %-15s %-15d",books_p.current->id,books_p.current->title,books_p.current->year,books_p.current->author,books_p.current->genre,books_p.current->copies);
    puts("");
}
/** \brief Funkcja wyszukuj¹ca ksiazke po jej tytule.
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *  \param title zmienna, ktora zawiera tytul.
 *
 */
void find_book_by_title(struct books_pointers books_p, char title[30])
{
    books_p.current = books_p.first;
    books_p.current = NULL;
        for(;books_p.first!=NULL;books_p.first=books_p.first->next)
        {
            if(strcmp(books_p.first->title,title) == 0){
                printf("%-4s %-25s %-7s %-20s %-15s %-15s\n","ID","TYTUL","ROK","AUTOR","GATUNEK","LICZBA EGZEMPLARZY");
                puts("~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~ ~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~");
                printf("%-4d %-25s %-7s %-20s %-15s %-15d",books_p.first->id,books_p.first->title,books_p.first->year,books_p.first->author,books_p.first->genre,books_p.first->copies);
                puts("");
                books_p.current = books_p.first;
            }
        }
    if(books_p.current == NULL){
        printf("Brak ksiazki o podanym tytule.\n");
        return;
    }
}
/** \brief Funkcja wyszukuj¹ca ksiazke po jej roku wydania.
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *  \param year zmienna,ktora podaje rok wydania ksiazki
 *
 */
void find_book_by_year(struct books_pointers books_p, char year[5])
{
    books_p.current = books_p.first;
    books_p.current = NULL;
        for(;books_p.first!=NULL;books_p.first=books_p.first->next)
        {
            if((strcmp(books_p.first->year,year)==0)){
                printf("%-4s %-25s %-7s %-20s %-15s %-15s\n","ID","TYTUL","ROK","AUTOR","GATUNEK","LICZBA EGZEMPLARZY");
                puts("~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~ ~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~");
                printf("%-4d %-25s %-7s %-20s %-15s %-15d",books_p.first->id,books_p.first->title,books_p.first->year,books_p.first->author,books_p.first->genre,books_p.first->copies);
                puts("");
                books_p.current = books_p.first;
            }
        }
    if(books_p.current == NULL){
        printf("Brak ksiazki o podanym roku.\n");
        return;
    }
}
/** \brief Funkcja wyszukuj¹ca ksiazke po jej autorze.
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *  \param autor zmienna,ktora przechowuje autora ksiazki.
 *
 */
void find_book_by_author(struct books_pointers books_p, char author[30])
{
    books_p.current = books_p.first;
    books_p.current = NULL;
        for(;books_p.first!=NULL;books_p.first=books_p.first->next)
        {
            if(strcmp(books_p.first->author,author) == 0){
                printf("%-4s %-25s %-7s %-20s %-15s %-15s\n","ID","TYTUL","ROK","AUTOR","GATUNEK","LICZBA EGZEMPLARZY");
                puts("~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~ ~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~");
                printf("%-4d %-25s %-7s %-20s %-15s %-15d",books_p.first->id,books_p.first->title,books_p.first->year,books_p.first->author,books_p.first->genre,books_p.first->copies);
                puts("");
                books_p.current = books_p.first;
            }
        }
    if(books_p.current == NULL){
        printf("Brak ksiazki o podanego autora.\n");
        return;
    }
}
/** \brief Funkcja wyszukujaca ksiazke po jej gatunku.
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *  \param genre zmienna,ktora przechowuje gatunek ksiazki.
 *
 */
void find_book_by_genre(struct books_pointers books_p, char genre[30])
{
    books_p.current = books_p.first;
    books_p.current = NULL;
        for(;books_p.first!=NULL;books_p.first=books_p.first->next)
        {
            if(strcmp(books_p.first->genre,genre) == 0){
                printf("%-4s %-25s %-7s %-20s %-15s %-15s\n","ID","TYTUL","ROK","AUTOR","GATUNEK","LICZBA EGZEMPLARZY");
                puts("~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~ ~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~");
                printf("%-4d %-25s %-7s %-20s %-15s %-15d",books_p.first->id,books_p.first->title,books_p.first->year,books_p.first->author,books_p.first->genre,books_p.first->copies);
                puts("");
                books_p.current = books_p.first;
            }
        }
    if(books_p.current == NULL){
        printf("Brak ksiazki o podanym tytule.\n");
        return;
    }
}
/** \brief Funkcja wyszukujaca ksiazke po ilosci egzemplarzy.
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *  \param copies zmienna, ktora przechowuje ilosci egzemplarzy.
 *
 */
void find_book_by_copies(struct books_pointers books_p, int copies)
{
    books_p.current = books_p.first;
    books_p.current = NULL;
        for(;books_p.first!=NULL;books_p.first=books_p.first->next)
        {
            if(books_p.first->copies == copies){
                printf("%-4s %-25s %-7s %-20s %-15s %-15s\n","ID","TYTUL","ROK","AUTOR","GATUNEK","LICZBA EGZEMPLARZY");
                puts("~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~ ~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~");
                printf("%-4d %-25s %-7s %-20s %-15s %-15d",books_p.first->id,books_p.first->title,books_p.first->year,books_p.first->author,books_p.first->genre,books_p.first->copies);
                puts("");
                books_p.current = books_p.first;
            }
        }
    if(books_p.current == NULL){
        printf("Brak ksiazki o podanej liczbie egzemplarzy.\n");
        return;
    }
}
/** \brief Funkcja zapisujaca dane do pliku "books.txt".
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *
 */
void print_books_to_file(struct books_pointers books_p)
{
    FILE *file = fopen("books.txt","w");
    if(file == NULL)
    {
        printf("Blad otwarcia pliku do zapisu.");
        exit(1);
    }
    else
    {
        if(books_p.first == NULL)
        {
            printf("Brak ksiazek do zapisania.\n");
            return;
        }
        for(;books_p.first!=NULL;books_p.first=books_p.first->next)
        {
            fprintf(file,"%d %s %s %s %s %d %d\n",books_p.first->id,books_p.first->title,books_p.first->year,books_p.first->author,books_p.first->genre,books_p.first->copies, books_p.first->numberofrentals);
        }
        fclose(file);
    }
}
/** \brief Funkcja przedstawia menu wyboru dostepnych operacji.
 *
 */
void choose_books_operation()
{
    int choice = 0;
    while(choice != 5)
    {
        printf("Wybierz operacje:\n1 - wyswietlenie ksiazek\n2 - dodanie ksiazki\n3 - edycja ksiazki\n4 - usuniecie ksiazki\n5 - sortowanie ksiazek\n"
               "6 - wyszukiwanie ksiazek\n7 - zapis ksiazek i powrot do glownego menu\n");
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            system("cls");
            print_books(pointers_b);
            break;
        case 2:
            system("cls");
            add_book(&pointers_b);
            break;
        case 3:
            system("cls");
            edit_book(&pointers_b);
            break;
        case 4:
            system("cls");
            delete_book(&pointers_b);
            break;
        case 5:
            system("cls");
            sort_books(&pointers_b);
            break;
        case 6:
            system("cls");
            find_book(pointers_b);
            break;
        case 7:
            system("cls");
            return main();
            break;
        default:
            printf("Nie ma takiej opcji.\n");
            break;
        }
    }
}
