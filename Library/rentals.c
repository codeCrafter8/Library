#include "bilbioteka.h"

int rental_id = 0; /** zmienna rental_id okreslajaca numer identyfikatora. */

/** \brief Funkcja odczytuje dane z pliku "rentals.txt"
 *
 *  \param struct rentals_pointers zawiera wskazniki na wypozyczenie.
 *
 */
void create_rentals(struct rentals_pointers *rentals_p)
{
    FILE *file = fopen("rentals.txt", "r");
    struct rentals *current = NULL;
    if(NULL == file)
    {
        printf("Blad otwarcia pliku!");
        exit (1);
    }
    else
    {
        if(rentals_p->first == NULL)
        {
            rentals_p->first = (struct rentals *)malloc(sizeof(struct rentals));
            if(NULL != rentals_p->first)
            {
                fscanf(file,"%d %d %d %d %d %d %d %d %d",&rentals_p->first->id,&rentals_p->first->client_id,&rentals_p->first->book_id,&rentals_p->first->rental_date.day,
                       &rentals_p->first->rental_date.month,&rentals_p->first->rental_date.year,&rentals_p->first->return_date.day,&rentals_p->first->return_date.month,&rentals_p->first->return_date.year);
                rentals_p->first->next = NULL;
                current = rentals_p->first;
                while(!feof(file))
                {
                    struct rentals *newrental = (struct rentals *)malloc(sizeof(struct rentals));
                    if(NULL != newrental)
                    {
                        fscanf(file,"%d %d %d %d %d %d %d %d %d\n",&newrental->id,&newrental->client_id,&newrental->book_id,&newrental->rental_date.day,
                        &newrental->rental_date.month,&newrental->rental_date.year,&newrental->return_date.day,&newrental->return_date.month,&newrental->return_date.year);
                        current->next = newrental;
                        current = newrental;
                    }
                }
                rentals_p->last = current;
                rental_id = rentals_p->last->id;
                current->next = NULL;
            }

        }
    }
    fclose(file);
}
/** \brief Funkcja liczaca roznice pomiedzy dzisiejsza data a data oddania ksiazki.
 *
 *  \param data1 zmienna, informujaca o dzisiejszej dacie.
 *  \param data2 zmienna, informujaca o dacie oddana ksiazki.
 *
 */
int get_date_difference(struct date date1, struct date date2)
{
    int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int dat1 = 0;
    for(int i = 1; i <= date1.year - 1; i++)
    {
        if(((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0))
            dat1 += 366;
        else
            dat1 += 365;
    }
    dat1 += date1.day;
    for(int i = 0; i < date1.month - 1; i++)
    {
        dat1 += month_days[i];
    }
    if((((date1.year % 4 == 0) && (date1.year % 100 != 0)) || (date1.year % 400 == 0))&& date1.month > 2)
        dat1+=1;


    int dat2 = 0;
    for(int i = 1; i <= date2.year - 1; i++)
    {
        if(((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0))
            dat2 += 366;
        else
            dat2 += 365;
    }
    dat2 += date2.day;
    for(int i = 0; i < date2.month - 1; i++)
    {
        dat2 += month_days[i];
    }
    if((((date2.year % 4 == 0) && (date2.year % 100 != 0)) || (date2.year % 400 == 0)) && date2.month > 2)
        dat2+=1;

    return dat1 - dat2;
}
/** \brief Funkcja wyswietlajaca wypozyczenie ksiazki wraz ze wszystkimi informacjami.
 *
 *  \param struct rentals_pointers zawiera wskazniki na wypozyczenie.
 *  \param struct clients_pointers zawiera wskazniki na klientow.
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *
 */
void print_rentals(struct rentals_pointers rentals_p, struct clients_pointers clients_p, struct books_pointers books_p)
{
    if(rentals_p.first == NULL)
    {
        printf("Brak wypozyczen do wyswietlenia.\n");
        return;
    }

    time_t today;
    time(&today);
    struct tm *today_time;
    today_time = localtime(&today);

    struct date today_date;
    today_date.day = today_time -> tm_mday;
    today_date.month = today_time -> tm_mon + 1;
    today_date.year = today_time -> tm_year + 1900;

    char name[30];
    char surname[30];
    char title[30];



    for(;rentals_p.first!=NULL;rentals_p.first=rentals_p.first->next)
    {
        struct clients *current1 = clients_p.first;
        while(current1->id != rentals_p.first->client_id)
        {
               current1 = current1->next;
        }
        strcpy(name, current1->name);
        strcpy(surname, current1->surname);

        struct books *current2 = books_p.first;
        while(current2->id != rentals_p.first->book_id)
        {
            current2 = current2->next;
        }
        strcpy(title, current2->title);

        int difference = get_date_difference(today_date, rentals_p.first->return_date);
        if(difference <= 0)
        {
            printf("%-4s %-15s %-20s %-20s %-20s %-20s\n","ID","ID KLIENTA","IMIE","NAZWISKO", "ID KSIAZKI", "TYTUL KSIAZKI");
            printf("%-4d %-15d %-20s %-20s %-20d %-20s\n\n",rentals_p.first->id,rentals_p.first->client_id,name, surname, rentals_p.first->book_id, title);
            printf("%-20s %-15s %-8s\n","DATA WYPOZYCZENIA","DATA ZWROTU","KARA");
            printf("%d.%d.%d \t     %d.%d.%d\t     BRAK\n",rentals_p.first->rental_date.day, rentals_p.first->rental_date.month,rentals_p.first->rental_date.year,
            rentals_p.first->return_date.day, rentals_p.first->return_date.month,rentals_p.first->return_date.year);
        }
        else
        {
            printf("%-4s %-15s %-20s %-20s %-20s %-20s\n","ID","ID KLIENTA","IMIE","NAZWISKO","ID KSIAZKI", "TYTUL KSIAZKI");
            printf("%-4d %-15d %-20s %-20s %-20d %-20s\n\n",rentals_p.first->id,rentals_p.first->client_id,name, surname, rentals_p.first->book_id, title);
            printf("%-20s %-15s %-8s\n","DATA WYPOZYCZENIA","DATA ZWROTU","KARA");
            printf("%d.%d.%d \t     %d.%d.%d\t     %d ZL\n",rentals_p.first->rental_date.day, rentals_p.first->rental_date.month,rentals_p.first->rental_date.year,
            rentals_p.first->return_date.day, rentals_p.first->return_date.month,rentals_p.first->return_date.year, 2 * difference);
        }
        puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        puts("");
    }
    puts("");

}
/** \brief Funkcja sprawdzajaca czy jest klient o podanym numerze identyfikatora.
 *
 *  \param struct clients_pointers zawiera wskazniki na klientow.
 *  \return zwraca 1, gdy istnieje dany klient.
 *
 */
int check_if_client_id(int id, struct clients_pointers clients_p)
{
    clients_p.current = clients_p.first;
    while(clients_p.current->id != id)
    {
        clients_p.current = clients_p.current->next;
        if(clients_p.current == NULL)
        {
            printf("Brak klienta o podanym ID.\n");
            return 0;
        }
    }
    return 1;
}
/** \brief Funkcja sprawdzajaca czy jest ksiazka o podanym numerze identyfikatora.
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *  \return zwraca 1, gdy istnieje dana ksiazka.
 *
 */
int check_if_book_id(int id, struct books_pointers books_p)
{
    books_p.current = books_p.first;
    while(books_p.current->id != id)
    {
        books_p.current = books_p.current->next;
        if(books_p.current == NULL)
        {
            printf("Brak ksiazki o podanym ID.\n");
            return 0;
        }
    }
    return 1;
}
/** \brief Funkcja zwraca informacje o ilosci egzemplarzy ksiazki.
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *  \return zwraca liczbe ezgemplarzy ksiazki.
 *
 */
int get_book_copies(int id, struct books_pointers books_p)
{
    books_p.current = books_p.first;
    int copies;
    while(books_p.current->id != id)
    {
        books_p.current = books_p.current->next;
    }
    copies = books_p.current->copies;
    return copies;
}
/** \brief Funkcja ktora informuje o ilosci wypozyczen danej ksiazki.
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *  \param zmienna id numer identyfikatora.
 *  \return zwraca liczbe wypozyczen ksiazki.
 *
 */
int get_book_numberofrentals(int id, struct books_pointers books_p)
{
    books_p.current = books_p.first;
    int numberofrentals;
    while(books_p.current->id != id)
    {
        books_p.current = books_p.current->next;
    }
    numberofrentals = books_p.current->numberofrentals;
    return numberofrentals;
}
/** \brief Funkcja zwiekszajaca liczbe wypozyczen ksiazki.
 *
 *  \param struct books_pointers zawiera wskazniki na ksiazki.
 *  \param zmienna id numer identyfikatora.
 *
 */
void add_to_number_of_rental(int id, struct books_pointers *books_p)
{
    struct books *current = books_p->first;
    while(current->id != id)
    {
        current = current->next;
    }
    current->numberofrentals++;
}
/** \brief Funkcja umozliwia dodanie nowego wypozyczenia.
 *
 *  \param struct rentals_pointers zawiera wskazniki na wypozyczenie.
 *
 */
void add_rental(struct rentals_pointers *rentals_p)
{
    struct rentals *newrental = (struct rentals *)malloc(sizeof(struct rentals));
    int client_id, book_id;
    if(NULL != newrental)
    {
        newrental->next = NULL;
        newrental->id = ++rental_id;
        printf("Podaj ID klienta: ");
        scanf("%d", &client_id);
        if(check_if_client_id(client_id, pointers))
            newrental->client_id = client_id;
        else
            return;
        printf("Podaj ID ksiazki: ");
        scanf("%d", &book_id);
        if(check_if_book_id(book_id, pointers_b))
            newrental->book_id = book_id;
        else
            return;
        if(get_book_copies(book_id,pointers_b) - get_book_numberofrentals(book_id,pointers_b) <= 0)
        {
            printf("Ksiazki o podanym ID nie ma juz w bibliotece.\n");
            rental_id--;
            return;
        }
         printf("Podaj dzien wypozyczenia ksiazki: ");
         scanf("%d",&newrental->rental_date.day);
         printf("Podaj miesiac wypozyczenia ksiazki: ");
         scanf("%d",&newrental->rental_date.month);
         printf("Podaj rok wypozyczenia ksiazki: ");
         scanf("%d",&newrental->rental_date.year);
         printf("Podaj dzien oddania ksiazki: ");
         scanf("%d",&newrental->return_date.day);
         printf("Podaj miesiac oddania ksiazki: ");
         scanf("%d",&newrental->return_date.month);
         printf("Podaj rok oddania ksiazki: ");
         scanf("%d",&newrental->return_date.year);
         if(NULL == rentals_p->first)
            rentals_p->first = rentals_p->last = newrental;
         rentals_p->last->next = newrental;
         rentals_p->last = newrental;
         add_to_number_of_rental(book_id, &pointers_b);
    }
}
/** \brief Funkcja zmiejszajaca ilosc wypozyczen ksiazki.
 *
 *  \param struct rentals_pointers zawiera wskazniki na wypozyczenie.
 *  \param zmienna id numer identyfikatora.
 *
 */
void reduce_number_of_rental(int id, struct books_pointers *books_p)
{
    struct books *current = books_p->first;
    while(current->id != id)
    {
        current = current->next;
    }
    current->numberofrentals--;
}
/** \brief Funkcja umozliwia usuniecie wypozyczenia.
 *
 *  \param struct rentals_pointers zawiera wskazniki na wypozyczenie.
 *
 */
void delete_rental(struct rentals_pointers *rentals_p)
{
    if(rentals_p->first == NULL)
    {
        printf("Brak wypozyczen do usuniecia.\n");
        return;
    }
    printf("Podaj ID wypozyczenia, ktore chcesz usunac: ");
    int id;
    scanf("%d",&id);
    struct rentals *current = rentals_p->first;
    struct rentals *prev;
    while(current->id != id)
    {
        prev = current;
        current = current->next;
        if(current == NULL)
        {
            printf("Brak wypozyczenia o podanym ID.\n");
            return;
        }
    }
    reduce_number_of_rental(current->book_id, &pointers_b);
    if(current == rentals_p->first)
    {
        rentals_p->first = current->next;
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
/** \brief Funkcja zapisujaca dane do pliku "rentals.txt".
 *
 *  \param struct rentals_pointers zawiera wskazniki na wypozyczenie.
 *
 */
void print_rentals_to_file(struct rentals_pointers rentals_p)
{
    FILE *file = fopen("rentals.txt","w");
    if(file == NULL)
    {
        printf("Blad otwarcia pliku do zapisu.");
        exit(1);
    }
    else
    {
        if(rentals_p.first == NULL)
        {
            printf("Brak wypozyczen do zapisania.\n");
            return;
        }
        for(;rentals_p.first!=NULL;rentals_p.first=rentals_p.first->next)
        {
            fprintf(file,"%d %d %d %d %d %d %d %d %d\n",rentals_p.first->id,rentals_p.first->client_id,rentals_p.first->book_id,rentals_p.first->rental_date.day,
                       rentals_p.first->rental_date.month,rentals_p.first->rental_date.year,rentals_p.first->return_date.day,rentals_p.first->return_date.month,rentals_p.first->return_date.year);
        }
        fclose(file);
    }
}
/** \brief Funkcja przedstawia menu wyboru dostepnych operacji.
 *
 */
void choose_rental_operation()
{
    int choice = 0;
    while(choice != 5)
    {
        printf("Wybierz operacje:\n1 - wyswietlenie wypozyczen\n2 - dodanie wypozyczenia\n3 - usuniecie wypozyczenia\n4 - zapis wypozyczen i powrot do glownego menu\n");
        scanf("%d", &choice);
        {
            switch(choice)
            {
            case 1:
                system("cls");
                print_rentals(pointers_r, pointers, pointers_b);
                break;
            case 2:
                system("cls");
                add_rental(&pointers_r);
                break;
            case 3:
                system("cls");
                delete_rental(&pointers_r);
                break;
            case 4:
                system("cls");
                print_rentals_to_file(pointers_r);
                return main();
                break;
            default:
                printf("Nie ma takiej opcji.\n");
                break;
            }
        }
    }
}

