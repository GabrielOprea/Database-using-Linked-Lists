//Oprea-Groza Gabriel - 313CB
#include "functions.h"

void Align(char* val)
{
    //Functie ce afiseaaza padding-ul de spatii albe dupa o valoare
    int length = MAX_COLUMN_NAME_LEN - strlen(val) + SPACE_LEN;
    for(int j = 0; j < length; j++)
        printf(" ");
}

void Print_headers(t_table* table)
{
    /*Functie ce afiseaz header-ul unui tabel
    (numele tabelului si numele coloanelor) */
    printf("TABLE: %s\n",table->name);

    //Parcurg lista de coloane din tabel
    t_column* col = table->columns;
    while(col != NULL)
    {
        //Pentru fiecare coloana afisez valoarea si o aliniez
        printf("%s", col->name);
        Align(col->name);
        col = col->next;
    }
    printf("\n");

    /*Pentru fiecare coloana, afisez si linia formata din minusuri
    dedesubtul tabelului */
    col = table->columns;
    while(col != NULL)
    {
        for(int j = 0; j < MAX_COLUMN_NAME_LEN; j++)
            printf("-");
        printf(" ");
        col = col->next;
    }
}

t_db* Create_DB(char* db_name)
{
    //Functie ce aloca memorie pentru o baza de date cu numele din parametru
    t_db* new = calloc(1,sizeof(t_db));
    if(!new)
        return NULL;

    //Copiez numle primit ca parametru in structura
    strcpy(new->name, db_name);
    return new;
}

int Exista(t_db* database, char* table_name)
{

    //Verifica daca tabela cu table_name exista deja in baza de date
    t_table* p = database->tables;

    while(p != NULL)
    {
        if(!strcmp(table_name, p->name))
            return TRUE;
        p = p->next;
    }
    return FALSE;
}

void Create_Table(t_db* database, char* name, t_cellType data_type,
char** table_col, int nr_col)
{
    /*Functie ce creeaza un tabel cu caracteristicile primite ca parametru si
    il adauga in baza de date */
    if(Exista(database, name))
    {
        /*In cazul in care exista deja un tabel cu acest nume, nu mai
        creez unul nou*/
        printf("Table \"%s\" already exists.\n\n", name);
        return;
    }

    //Aloc o noua tabela
    t_table* new_table = calloc(1, sizeof(t_table));
    if(!new_table)
        exit(ERROR);

    //Setez numele, data type-ul si pointer-ul next
    strcpy(new_table->name, name);
    new_table->next = NULL;
    new_table->type = data_type;

    int count = 0;
    /*Parcurg vectorul de nume de coloane primit ca parametru si inserez
    fiecare coloana in lista de coloane a tabelei */
    while(count < nr_col)
    {
        Ins_Col(&new_table->columns, table_col[count]);
        count++;
    }

    //La final inserez tabelul in lista de tabele a bazei de date
    Ins_Tabel(&database->tables, new_table);
}

void Clear_Table(t_table** db_table)
{
    /*Functie ce sterge si elibereaza memoria pentru toate
    liniile dintr-un tabel */
    t_table* table = *db_table;

    /* Pentru fiecare tip de date fac cast-ul corespunzator, iar apoi
    parcurg lista de linii */
    if(table->type == INT)
    {
        t_intLine* intL = (t_intLine*)table->lines;
        while(intL != NULL)
        {
            /*Pentru fiecare linie, retin intr-un auxiliar linia inainte sa
            accesez campul next, apoi eliberez memoria*/
            t_intLine* aux = intL;
            intL = intL->next;
            free_INT_line(&aux);
        }
    }
    else
        if(table->type == FLOAT)
        {
            t_floatLine* floatL = (t_floatLine*)table->lines;
            while(floatL != NULL)
            {
                t_floatLine* aux = floatL;
                floatL = floatL->next;
                free_FLOAT_line(&aux);
            }
        }
        else
            if(table->type == STRING)
            {
                t_stringLine* stringL = (t_stringLine*)table->lines;

                while(stringL != NULL)
                {
                    t_stringLine* aux = stringL;
                    stringL = stringL->next;
                    free_STRING_line(&aux);
                }
            }
    //Setez capul listei de linii cu NULL;
    table->lines = NULL;
}

void Delete_Table(t_table** db_table)
{
    //Functie ce elibereaza toata memoria alocata pentru un tabel
    t_table* table = *db_table;
    Clear_Table(db_table);
    t_column* col = table->columns;

    //Parcurg lista de coloane si eliberez fiecare celula
    while(col != NULL)
    {
        t_column* aux = col;
        col = col->next;
        free(aux);
    }

    free(table);
    *db_table = NULL;
}

int Cond(t_operator rel, t_cellType type, void* el1, void* el2)
{
    /*Funcie ce primeste un enum rel, care contine una din relatiile
    de comparare(<+, >=, !=. ==, <, >) */

    /*Setez un element care va avea rol de comparator, continand
    diferenta dintre cele 2 elemente */
    float cmp;

    //Daca tipul este int sau float, comparatorul va fi diferenta
    if(type == INT)
        cmp = *(int*)el1 - *(int*)el2;

    else
        if(type == FLOAT)
            cmp = *(float*)el1 - *(float*)el2;

        else
            if(type == STRING)
                cmp = strcmp((char*)el1, (char*)el2);

    switch(rel)
    {

        /*Consider fiecare caz al relatiei rel. In functie de comparator,
        returnez 1 daca relatia este indeplinita, 0 in caz contrar */
        case NE:
            return cmp == 0 ? 0 : 1;
        case EQ:
            return cmp == 0 ? 1 : 0;
        case BT:
            return cmp > 0 ? 1 : 0;
        case LT:
            return cmp < 0 ? 1 : 0;
        case LE:
            return cmp <= 0 ? 1 : 0;
        case BE:
            return cmp >= 0 ? 1 : 0;
        default:
            return NOT_FOUND;
    }
}


void Print_Table(t_table* table)
{
    //Functie ce afiseaza o tabela, cu tot cu coloane si padding
    Print_headers(table);

    //Pentru fiecare tip, fac cast-ul corespunzator al listei de linii
    if(table->type == INT)
    {
        t_intLine* p = (t_intLine*) table->lines;
        while(p != NULL)
        {
            //Parcurg lista si afisez fiecare celula
            printf("\n");
            t_intCell* q = p->cells;
            while(q != NULL)
            {
                Afi_Int(q->value);
                q = q->next;
            }
            p = p->next;
        }
    }
    if(table->type == FLOAT)
    {
        t_floatLine* p = (t_floatLine*) table->lines;
        while(p != NULL)
        {
            printf("\n");
            t_floatCell* q = p->cells;
            while(q != NULL)
            {
                Afi_Float(q->value);
                q = q->next;
            }
            p = p->next;
        }
    }
    if(table->type == STRING)
    {
        t_stringLine* p = (t_stringLine*) table->lines;
        while(p != NULL)
        {
            printf("\n");
            t_stringCell* q = p->cells;
            while(q != NULL)
            {
                Afi_String(q->value);
                q = q->next;
            }
            p = p->next;
        }
    }
    printf("\n\n");
}

int Get_Column_ID(t_table* table, char* name)
{
    //Functie ce obtine indicele coloanei cu numele name dintr-un tabel
    t_column* col = table->columns;
    int no_col = 0;

    //Parcurg lista de coloane. setand un contor
    while(col != NULL)
    {
        //Cand intalnesc coloana potrivita, returnez contorul
        if(!strcmp(col->name, name))
            return no_col;
        no_col++;
        col = col->next;
    }

    //Daca nu am gasit coloana, intorc un cod de eroare
    return NOT_FOUND;
}

void Search_Selective(t_table* table, char* name, void* val, t_operator rel)
{
    /*Functie ce cauta si afiseaza selectiv doar liniile din tabel a caror
    valoare de pe coloana cu numele primit ca parametru respecta relatia rel
    cu valoarea de la adresa val */

    //Obtin indicele coloanei cu functia aferenta
    int no_col = Get_Column_ID(table, name);

    //Daca nu am gasit coloana, afisez un mesaj si ies din functie
    if(no_col == NOT_FOUND)
    {
        printf("Table \"%s\" does not contain column \"%s\".\n",
        table->name, name);
        return;
    }

    //In cazul in care am gasit coloana, afisez header-ul tabelului
    Print_headers(table);
    printf("\n");

    if(table->type == INT)
        Search_int_lines(table, no_col, val, rel);

    else if(table->type == FLOAT)
        Search_float_lines(table, no_col, val, rel);
    
    else if(table->type == STRING)
        Search_string_lines(table, no_col, val, rel);
    
    printf("\n");
}


void Delete_Selective(t_table* table, char* name, void* val, t_operator rel)
{

    /* Functie ce va sterge selectiv dintr-un tabel doar liniile ale caror
    valoare de la coloana cu numele primit ca parametru respecta o anumita
    relatie fata de elementul de la adresa val */
    int no_col = Get_Column_ID(table, name);

    //Daca nu am gasit coloana, afisez un mesaj si ies din functie
    if(no_col == NOT_FOUND)
    {
        printf("Table \"%s\" does not contain column \"%s\".\n",
        table->name, name);
        return;
    }

    //Altfel, apelez functiile corespunzatoare pentru fiecare tip
    if(table->type == INT)
        Delete_int_lines(table, no_col, rel,val);
    
    else if(table->type == FLOAT)
        Delete_float_lines(table, no_col, rel, val);
    
    else if(table->type == STRING)
        Delete_string_lines(table, no_col, rel, val);
}

t_operator Relation(char op[2])
{
    /*Functie ce primeste un sir de maxim 2 caractere in care este stocat un
    operator ca un string, si va atribui intr-un enum de tip t_operator
    valoarea corespunzatoare */
    if(!strcmp(op, "=="))
        return EQ;
    if(!strcmp(op, "<="))
        return LE;
    if(!strcmp(op, ">="))
        return BE;
    if(!strcmp(op, "!="))
        return NE;
    if(!strcmp(op, "<"))
        return LT;
    if(!strcmp(op, ">"))
        return BT;
    return NOT_FOUND;
}

char* Next_Arg(char* part_cmd)
{
    //Functie ce obtine urmatorul argument dintr-o comanda
    part_cmd = strtok(NULL, " ");
    return part_cmd;
}

t_table* Find_Table(t_table* table_list, char* table_name)
{
    /*Functie ce primeste o lista de tabele si un nume al unei tabele si
    returneaza pointer catre tabela cu acel nume din lista */
    t_table* p = table_list;
    while(p != NULL)
    {
        if(!strcmp(p->name, table_name))
            break;
        p = p->next;
    }
    return p;
}

int Nr_arg(char* cmd)
{
    //Functie ce determina numarul de argumente dintr-o comanda;
    int count = 0;
    int len = strlen(cmd);

    //Parcurg comanda, iar pentru fiecare spatiu incrementez un contor
    for(int i = 0 ; i < len; i++)
        if(cmd[i] == ' ')
            count++;
    return count;
}
