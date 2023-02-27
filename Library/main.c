#include "bilbioteka.h"

/** \brief Funkcja realizujaca menu programu oraz wybrane polecenie przez uzytkownika.
 *
 */
int main()
{
    system("color 0b");
    create_clients(&pointers);
    create_books(&pointers_b);
    create_rentals(&pointers_r);
    int choice;
    printf("\t\t\t\t\t\tWitaj w bibliotece!\n");
    while(choice!=4)
    {
        printf("Wybierz dzial:\n1 - Klienci\n2 - Ksiazki\n3 - Wypozyczenia\n");
        scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        system("cls");
        choose_client_operation();
        break;
    case 2:
        system("cls");
        choose_books_operation();
        break;
    case 3:
        system("cls");
        choose_rental_operation();
        break;
    default:
        system("cls");
        printf("Brak opcji.\n");
        break;
    }
    }
    return 0;
}

