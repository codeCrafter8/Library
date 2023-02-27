#ifndef BIBLIOTEKA_H_INCLUDED
#define BIBLIOTEKA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>


/** \brief Struktura dynamiczna clients umozliwiajaca operacje na klientach.
 *
 *  \param id zmienna calkowita przechowujaca identyfikator klienta.
 *  \param surname zmienna przechowujaca nazwisko klienta.
 *  \param phone_number zmienna przechowujaca numer telefonu klienta.
 *  \param email zmienna przechowujaca email klienta.
 *  \param clients *next wskaznik na nastepne pole listy
 *
 */
struct clients
{
    int id;
    char surname[30];
    char name[30];
    char phone_number[10];
    char email[30];
    struct clients *next;
};
/** \brief Struktura dynamiczna zawieracjaca wskazniki w celu umozliwienia poruszania sie po liscie.
 *
 *  \param clients *first wskaznik wskazujacy na pierwszy element listy
 *  \param clients *last wskaznik wskazujacy na ostatni element listy
 *  \param clients *current wskaznik wskazujacy na obecny element listy
 *
 */
struct clients_pointers
{
    struct clients *first,*last, *current;
};
/** \brief Struktura dynamiczna books umozliwiajaca operacje na ksiazkach.
 *
 *  \param id zmienna calkowita przechowujaca identyfikator ksiazki.
 *  \param title zmienna przechowujaca tytul ksiazki.
 *  \param year zmienna przechowujaca rok wydania ksiazki.
 *  \param author zmienna przechowujaca imie i nazwisko autora.
 *  \param genre zmienna przechowujaca gatunek ksiazki.
 *  \param copies zmienna przechowujaca ilosc egzemplarzy.
 *  \param numberofrentals zmienna przechowujaca liczbe wypozyczonych ksiazek.
 *  \param books *next wskaznik na nastepne pole listy.
 *
 */
struct books
{
    int id;
    char title[30];
    char year[5];
    char author[30];
    char genre[30];
    int copies;
    int numberofrentals;
    struct books *next;
};
/** \brief Struktura dynamiczna zawieracjaca wskazniki w celu umozliwienia poruszania sie po liscie.
 *
 *  \param books *first wskaznik wskazujacy na pierwszy element listy.
 *  \param books *last wskaznik wskazujacy na ostatni element listy.
 *  \param books *current wskaznik wskazujacy na obecny element listy.
 *  \param books *current2 wskaznik wskazujacy na obecny element listy (pomocniczy).
 *  \param books *to_swap wskaznik wskazujacy na elemet do zamienienia.
 *
 */
struct books_pointers
{
    struct books *first,*last, *current, *current2, *to_swap;
};
/** \brief Struktura dynamiczna clients umozliwiajaca operacje na dacie.
 *
 *  \param day zmienna calkowita przechowujaca dzien.
 *  \param month zmienna calkowita przechowujaca miesiac
 *  \param year zmienna calkowita przechowujaca rok.
 *
 */
struct date
{
    int day;
    int month;
    int year;
};
/** \brief Struktura dynamiczna clients umozliwiajaca operacje na wypozyczeniach ksiazki.
 *
 *  \param id zmienna calkowita przechowujaca identyfikator wypozyczenia.
 *  \param client_id zmienna calkowita przechowujaca numer identyfikatora klienta, ktory wypozyczyl ksiazke.
 *  \param book_id zmienna calkowita przechowujaca numer identyfikatora ksiazki, ktora zostala wypozyczyczona.
 *  \param date rental_date struktura przechowujaca date wypozyczenia ksiazk.
 *  \param date return_date struktura przechowujaca date oddania ksiazk.
 *  \param rentals *next wskaznik na nastepne pole listy.
 *
 */
struct rentals
{
    int id;
    int client_id;
    int book_id;
    struct date rental_date;
    struct date return_date;
    struct rentals *next;
};
/** \brief Struktura dynamiczna zawierajaca wskazniki w celu umozliwienia poruszania sie po liscie.
 *
 *  \param rentals *first wskaznik wskazujacy na pierwszy element listy.
 *  \param rentals *last wskaznik wskazujacy na ostatni element listy.
 *  \param rentals *current wskaznik wskazujacy na obecny element listy.
 *
 */
struct rentals_pointers
{
    struct rentals *first, *last, *current;
};

struct clients_pointers pointers;

struct books_pointers pointers_b;

struct rentals_pointers pointers_r;

extern void create_clients(struct clients_pointers *);
extern void print_clients(struct clients_pointers);
extern void add_client(struct clients_pointers *);
extern void edit_client(struct clients_pointers *);
extern void delete_client(struct clients_pointers *);
extern void print_clients_to_file(struct clients_pointers);
extern void create_books(struct books_pointers *);
extern void print_books(struct books_pointers);
extern void add_book(struct books_pointers *);
extern void edit_book(struct books_pointers *);
extern void delete_book(struct books_pointers *);
extern void print_books_to_file(struct books_pointers);
extern void sort_books();
extern int sort_question();
extern void swap_books(struct books *, struct books *);
extern void sort_by_title(int, struct books_pointers *);
extern void sort_by_year(int, struct books_pointers *);
extern void sort_by_author(int, struct books_pointers*);
extern void sort_by_genre(int, struct books_pointers *);
extern void sort_by_copies(int, struct books_pointers *);
extern void find_book(struct books_pointers);
extern void find_book_by_author(struct books_pointers, char *);
extern void find_book_by_title(struct books_pointers, char *);
extern void find_book_by_id(struct books_pointers, int);
extern void find_book_by_genre(struct books_pointers, char *);
extern void find_book_by_copies(struct books_pointers, int);
extern void find_book_by_year(struct books_pointers, char*);
extern void create_rentals(struct rentals_pointers *);
extern void print_rentals(struct rentals_pointers, struct clients_pointers, struct books_pointers);
extern void print_rentals_to_file(struct rentals_pointers);
extern void add_rental(struct rentals_pointers *);
extern void delete_rental(struct rentals_pointers *);
extern int get_date_difference(struct date, struct date);
extern int check_if_book_id(int, struct books_pointers);
extern int check_if_client_id(int, struct clients_pointers);
extern int get_book_copies(int, struct books_pointers);
extern int get_book_numberofrentals(int, struct books_pointers);
extern void choose_client_operation();
extern void choose_books_operation();
extern void choose_rental_operation();
extern int client_question();
extern int book_question();
extern void add_to_number_of_rental(int, struct books_pointers *);
extern int check_surname(char *);
extern int check_number(char *);
extern int check_email(char *);
extern int check_author(char *);
extern int check_genre(char *);

#endif


