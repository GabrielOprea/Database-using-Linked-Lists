//Oprea-Groza Gabriel - 313CB

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structures.h"


void Ins_Col(t_column** head, char* nume); //Insereaza o coloana
void Ins_Tabel(t_table** head, t_table* table); //Insereaza un tabel

//Insereaza un element intr-o lista de celule de un anumit tip
void Ins_INT(t_intCell** head, int val);
void Ins_FLOAT(t_floatCell** head, float val);
void Ins_STRING(t_stringCell** head, char* val);

void Align(char* val); //Adauga padding pentru tabel

//Afiseaza valoarea primita ca parametru, aliniata intr-un tabel
void Afi_String(char* value);
void Afi_Float(float value);
void Afi_Int(int value);

//Elibereaza toata memoria ocupata de o linie
void free_INT_line(t_intLine** lin);
void free_FLOAT_line(t_floatLine** lin);
void free_STRING_line(t_stringLine** lin);

//Creaza o linie noua cu valorile din vectorul primit
t_intLine* Create_int_line(int nr_col, int* val);
t_floatLine* Create_float_line(int nr_col, float* val);
t_stringLine* Create_string_line(int nr_col, char** val);

/*Construieste o linie cu valorile din vectorul primit ca parametru
si adauga linia in tabel */
void Add_int_line(t_table* table, int nr_col, int* val);
void Add_float_line(t_table* table, int nr_col, float* val);
void Add_string_line(t_table* table, int nr_col, char** val);

//Obtine elementul de la pozitia no_col dintr-o linie
int Get_IntCell_Val(t_intLine* lin, int no_col);
float Get_FloatCell_Val(t_floatLine* lin, int no_col);
char* Get_StringCell_Val(t_stringLine* lin, int no_col);

/*Afiseaza toate liniile din tabel al caror element de pe pozitia no_col
respecta relatia cu cel de la adresa val*/
void Search_int_lines(t_table* table, int no_col, void* val,
t_operator rel);
void Search_float_lines(t_table* table, int no_col, void* val,
t_operator rel);
void Search_string_lines(t_table* table, int no_col, void* val,
t_operator rel);

/*Sterge toate liniile din tabel al caror element de pe pozitia no_col
respecta relatia cu cel de la adresa val*/
void Delete_int_lines(t_table* table, int no_col, t_operator rel,
void* val);
void Delete_float_lines(t_table* table, int no_col, t_operator rel,
void* val);
void Delete_string_lines(t_table* table, int no_col, t_operator rel,
void* val);

t_db* Create_DB(char* db_name); //Aloca memorie pentru o baza de date

int Exista(t_db* database, char* table_name); //Verifica daca exista un tabel

void Create_Table(t_db* database, char* name, t_cellType data_type,
char** table_col, int nr_col); //Creeaza un tabel in baza de date

void Clear_Table(t_table** db_table); //Transforma tabela in tabela vid

void Delete_Table(t_table** db_table); //Elibereaza memorie pentru tabela

//Returneaza 1 sau 0, in functie de validitatea conditiei
int Cond(t_operator rel, t_cellType type, void* el1, void* el2);

void Print_Table(t_table* table); //Afiseaza o tabela cu padding si header

int Get_Column_ID(t_table* table, char* name); //Obtine index-ul unei coloane

//Afiseaza selectiv liniile dintr-o baza de date ce respecta conditia rel
void Search_Selective(t_table* table, char* name, void* val, t_operator rel);

//Sterge selectiv liniile dintr-o baza de date ce respecta conditia rel
void Delete_Selective(t_table* table, char* name, void* val, t_operator rel);

//Transforma un string de tipul "<=",">=","<", ">", "==", "!=" intr-un enum
t_operator Relation(char op[MAX_OP_LEN]);

//Returneaza o tabela dintr-o lista cu an anumit nume
t_table* Find_Table(t_table* table_list, char* table_name);

//Preia urmatorul argument al unei comenzii
char* Next_Arg(char* part_cmd);

//Obtine numarul de argumente al unei comenzi
int Nr_arg(char* cmd);

//Deschide o consola interactiva
void Console();

//Functiile ce vor fi apelate din consola interactiva:
t_db* INIT_DB(char* part_cmd); //initialieaza o baza de date
void DELETE_DB(t_db** database); //sterge o baza de date
void ADD(t_db* database, char* part_cmd, int args); //adauga o liie
void PRINT(t_db* database, char* part_cmd); //afiseaza un tabel
void CREATE(t_db* database, char* part_cmd, int args); //creeza o tabela
void SEARCH(t_db* database, char* part_cmd); //cauta selectiv
void DELETE(t_db* database, char* part_cmd); //sterge selectiv
void CLEAR(t_db* database, char* part_cmd); //Goleste o tabela
void PRINT_DB(t_db* database); //Afiseaza o baza de date

