#include "bilbioteka.h"

int client_id = 0; /**< zmienna client_id okreslajaca numer identyfikatora klienta. */

/** \brief Funkcja odczytuje dane z pliku "clients.txt"
 *
 *  \param struct clients_pointers zawiera wskazniki na klientow.
 *
 */
void create_clients(struct clients_pointers *clients_p)
{
    FILE *file = fopen("clients.txt", "r");
    struct clients *current = NULL;
    if(NULL == file)
    {
        printf("Blad otwarcia pliku!");
        exit (1);
    }
    else
    {
        if(clients_p->first == NULL)
        {
            clients_p->first = (struct clients *)malloc(sizeof(struct clients));
            if(NULL != clients_p->first)
            {
                fscanf(file, "%d %s %s %s %s",&clients_p->first->id,clients_p->first->surname,clients_p->first->name,clients_p->first->phone_number,clients_p->first->email);
                clients_p->first->next = NULL;
                current = clients_p->first;
                while(!feof(file))
                {
                    struct clients *newclient = (struct clients *)malloc(sizeof(struct clients));
                    if(NULL != newclient)
                    {
                        fscanf(file, "%d %s %s %s %s\n",&newclient->id,newclient->surname,newclient->name,newclient->phone_number,newclient->email);
                        current->next = newclient;
                        current = newclient;
                    }

                }
                clients_p->last = current;
                client_id = clients_p->last->id;
                current->next = NULL;
            }
        }
    }
    fclose(file);
}
/** \brief Funkcja wyswietla dane klientow.
 *
 *  \param struct clients_pointers zawiera wskazniki na klientow.
 *
 */
void print_clients(struct clients_pointers clients_p)
{
    if(clients_p.first == NULL)
    {
        printf("Brak klientow do wyswietlenia.\n");
        return;
    }
    printf("%-4s %-25s %-15s %-15s %-15s\n","ID","NAZWISKO","IMIE","NUMER TELEFONU","EMAIL");
    puts("~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~");
    for(;clients_p.first!=NULL;clients_p.first=clients_p.first->next)
    {
        printf("%-4d %-25s %-15s %-15s %-15s",clients_p.first->id,clients_p.first->surname,clients_p.first->name,clients_p.first->phone_number,clients_p.first->email);
        puts("");
    }
    puts("");
}
/** \brief Funkcja sprawdza czy podane nazwisko klienta jest prawidlowo zapisane.
 *
 *  \param surname zmienna przechowujaca imie lub nazwisko klienta.
 *  \return zwraca 1, gdy imie lub nazwisko klienta jest poprawne.
 *
 */
int check_surname(char surname[30])
{
    int licznik = 0;
    for(int i = 0; i < strlen(surname); i++)
    {
        if((surname[i] >= 65 && surname[i] <= 90) || (surname[i] >= 97 && surname[i] <= 122) || (surname[i] == 45))
            licznik++;
    }
    if(licznik == strlen(surname))
        return 1;
    return 0;
}
/** \brief Funkcja sprawdza czy podany numer telefonu jest poprawny.
 *
 *  \param surname zmienna przechowujaca numer telefonu klienta.
 *  \return zwraca 1, gdy numer telefonu klienta jest poprawny.
 *
 */
int check_number(char number[10])
{
    int licznik = 0;
    for(int i = 0; i < strlen(number); i++)
    {
        if(number[i] >= 48 && number[i] <= 57)
            licznik++;
    }
    if(licznik == strlen(number) && strlen(number) == 9)
        return 1;
    return 0;
}
/** \brief Funkcja sprawdza czy podany adres mailowy jest poprawny..
 *
 *  \param surname zmienna,ktora umo¿liwia podanie maila klienta.
 *  \return zwraca 1, gdy email klienta jest poprawny.
 *
 */
int check_email(char email[30])
{
    int licznik = 0;
    for(int i = 0; i < strlen(email); i++)
    {
        if(email[i] == '@')
            licznik++;
    }
    if(licznik == 1)
        return 1;
    return 0;
}
/** \brief Funkcja umozliwia dodanie nowego klienta.
 *
 *  \param struct clients_pointers zawiera wskazniki na klientow.
 *
 */
void add_client(struct clients_pointers *clients_p)
{
     struct clients *newclient = (struct clients *)malloc(sizeof(struct clients));
     if(NULL != newclient)
     {
         newclient->next = NULL;
         newclient->id = ++client_id;
         while(1)
        {
            printf("Podaj nazwisko:");
            char surname[30];
            scanf("%s",surname);
            if(check_surname(surname))
            {
                strcpy(newclient->surname, surname);
                break;
            }
            else
                printf("Niepoprawnie podano nazwisko.\n");
         }
         while(1)
        {
            printf("Podaj imie:");
            char name[30];
            scanf("%s",name);
            if(check_surname(name))
            {
                strcpy(newclient->name, name);
                break;
            }
            else
                printf("Niepoprawnie podano imie.\n");
         }
         while(1)
         {
             printf("Podaj nr telefonu:");
             char number[10];
             scanf("%s",number);
             if(check_number(number))
             {
                 strcpy(newclient->phone_number, number);
                 break;
             }
             else
                printf("Niepoprawnie podano number.\n");
         }
         while(1)
         {
             printf("Podaj e-mail:");
             char email[30];
             scanf("%s",email);
             if(check_email(email))
             {
                 strcpy(newclient->email, email);
                 break;
             }
             else
                printf("Niepoprawnie podano email.\n");
         }
         if(NULL == clients_p->first)
            clients_p->first = clients_p->last = newclient;
         clients_p->last->next = newclient;
         clients_p->last = newclient;
         printf("Numer karty klienta to: %d.\n",client_id);
     }
}
/** \brief Funkcja realizuje pytanie o kontynuacje dzialania.
 *
 *  \return zwraca 1, gdy wybrano kontynuacje.
 *
 */
int client_question()
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
/** \brief Funkcja umozliwia edycje klienta.
 *
 *  \param struct clients_pointers zawiera wskazniki na klientow.
 *
 */
void edit_client(struct clients_pointers *clients_p)
{
    if(clients_p->first == NULL)
    {
        printf("Brak klientow do edycji.\n");
        return;
    }
    printf("Podaj numer karty klienta, ktorego dane chcesz edytowac: ");
    int id, choice;
    scanf("%d",&id);
    struct clients *current = clients_p->first;
    while(current->id != id)
    {
        current = current->next;
        if(current == NULL)
        {
            printf("Brak klienta o podanym numerze karty.\n");
            return;
        }
    }
    system("cls");
    printf("Dane tego kilenta:\n\n");
    printf("%-4s %-15s %-15s %-15s %-15s\n","ID","NAZWISKO","IMIE","NUMER TELEFONU","EMAIL");
    puts("~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~");
    printf("%-4d %-15s %-15s %-15s %-15s",current->id,current->surname,current->name,current->phone_number,current->email);
    puts("");
    puts("");
    if(client_question()){
    system("cls");
    printf("Podaj, co chcesz edytowac: 1 - nazwisko, 2 - imie, 3 - nr telefonu, 4 - e-mail:");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        while(1)
        {
            system("cls");
            printf("Podaj nowe nazwisko:");
            char surname[30];
            scanf("%s",surname);
            if(check_surname(surname))
            {
                strcpy(current->surname, surname);
                break;
            }
            else
                printf("Niepoprawnie podano nazwisko.\n");
         }
         break;
    case 2:
        while(1)
        {
            system("cls");
            printf("Podaj imie:");
            char name[30];
            scanf("%s",name);
            if(check_surname(name))
            {
                strcpy(current->name, name);
                break;
            }
            else
                printf("Niepoprawnie podano imie.\n");
         }
        break;
    case 3:
        while(1)
         {
             system("cls");
             printf("Podaj nr telefonu:");
             char number[10];
             scanf("%s",number);
             if(check_number(number))
             {
                 strcpy(current->phone_number, number);
                 break;
             }
             else
                printf("Niepoprawnie podano number.\n");
         }
        break;
    case 4:
        while(1)
         {
             system("cls");
             printf("Podaj e-mail:");
             char email[30];
             scanf("%s",email);
             if(check_email(email))
             {
                 strcpy(current->email, email);
                 break;
             }
             else
                printf("Niepoprawnie podano email.\n");
         }
        break;
    default:
        printf("Nie ma takiej opcji edycji.\n");
        break;
    }
    }
}
/** \brief Funkcja umozliwia usuniecie klienta.
 *
 *  \param struct clients_pointers zawiera wskazniki na klientow.
 *
 */
void delete_client(struct clients_pointers *clients_p)
{
    if(clients_p->first == NULL)
    {
        printf("Brak klientow do usuniecia.\n");
        return;
    }
    printf("Podaj numer karty klienta, ktorego chcesz usunac: ");
    int id;
    scanf("%d",&id);
    struct clients *current = clients_p->first;
    struct clients *prev;
    while(current->id != id)
    {
        prev = current;
        current = current->next;
        if(current == NULL)
        {
            printf("Brak klienta o podanym numerze karty.\n");
            return;
        }
    }
    system("cls");
    printf("Dane tego kilenta:\n\n");
    printf("%-4s %-15s %-15s %-15s %-15s\n","ID","NAZWISKO","IMIE","NUMER TELEFONU","EMAIL");
    puts("~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~");
    printf("%-4d %-15s %-15s %-15s %-15s",current->id,current->surname,current->name,current->phone_number,current->email);
    puts("");
    puts("");
    if(client_question()){
    if(current == clients_p->first)
    {
        clients_p->first = current->next;
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
/** \brief Funkcja zapisujaca dane do pliku "clients.txt".
 *
 *  \param struct clients_pointers zawiera wskazniki na klientow.
 *
 */
void print_clients_to_file(struct clients_pointers clients_p)
{
    FILE *file = fopen("clients.txt","w");
    if(file == NULL)
    {
        printf("Blad otwarcia pliku do zapisu.");
        exit(1);
    }
    else
    {
        if(clients_p.first == NULL)
        {
            printf("Brak klientow do zapisania.\n");
            return;
        }
        for(;clients_p.first!=NULL;clients_p.first=clients_p.first->next)
        {
            fprintf(file,"%d %s %s %s %s\n",clients_p.first->id,clients_p.first->surname,clients_p.first->name,clients_p.first->phone_number,clients_p.first->email);
        }
        fclose(file);
    }
}
/** \brief Funkcja przedstawia menu wyboru dostepnych operacji.
 *
 */
void choose_client_operation()
{
    int choice = 0;
    while(choice != 5)
    {
        printf("Wybierz operacje:\n1 - wyswietlenie klientow\n2 - dodanie klienta\n3 - edycja klienta\n4 - usuniecie klienta\n5 - zapis klientow i powrot do glownego menu\n");
        scanf("%d", &choice);
        {
            switch(choice)
            {
            case 1:
                system("cls");
                print_clients(pointers);
                break;
            case 2:
                system("cls");
                add_client(&pointers);
                break;
            case 3:
                system("cls");
                edit_client(&pointers);
                break;
            case 4:
                system("cls");
                delete_client(&pointers);
                break;
            case 5:
                system("cls");
                print_clients_to_file(pointers);
                return main();
                break;
            default:
                printf("Nie ma takiej opcji.\n");
                break;
            }
        }
    }
}
