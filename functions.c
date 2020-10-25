//Oprea-Groza Gabriel - 313CB

#include "functions.h"

void Ins_Col(t_column** head, char* nume)
{
    /* Functie care adauga o coloana cu numele primit ca parametru
    intr-o lista de coloane, la sfarsitul listei*/

    //Aloc coloana de adaugat
    t_column* aux = calloc(1,sizeof(t_column));
    if(!aux)
        exit(ERROR);

    //Copiez numele
    strcpy(aux->name, nume);

    t_column* p = *head;
    t_column* ant = NULL;

    //Daca lista e vida modific capul listei
    if(p == NULL)
        *head = aux;
    else
    {
        //Altfel adaug dupa ultimul element din lista
        while(p != NULL)
        {
            ant = p;
            p = p->next;
        }
    ant->next = aux;
    }

}

void Ins_Tabel(t_table** head, t_table* table)
{

    /* Functie care adauga un tabel gata construit intr-o lista de tabele,
    la sfarsitul listei*/

    t_table* p = *head;
    t_table* ant = NULL;

    /*Daca lista este vida modific capul listei,
    altfel parcurg lista si inserez dupa ultimul element*/

    if(p == NULL)
        *head = table;
    else
    {
        while(p != NULL)
        {
            ant = p;
            p = p->next;
        }
    ant->next = table;
    }

}

void Ins_INT(t_intCell** head, int val)
{

    /* Functie care adauga o noua celula cu valorea primita ca parametru
    intr-o lista de celule de tip INT, la sfarsitul listei*/

    //Aloc celula noua
    t_intCell* aux = calloc(1,sizeof(t_intCell));
    if(!aux)
        exit(ERROR);

    //Copiez valorea in celula noua
    aux->value = val;

    t_intCell* p = *head;
    t_intCell* ant = NULL;

    //O adaug in lista, modificand capul listei daca este necesar
    if(p == NULL)
        *head = aux;
    else
    {
        while(p != NULL)
        {
            ant = p;
            p = p->next;
        }
        ant->next = aux;
    }
}

void Ins_FLOAT(t_floatCell** head, float val)
{

    /* Functie care adauga o noua celula cu valorea primita ca parametru
    intr-o lista de celule de tip FLOAT, la sfarsitul listei*/

    t_floatCell* aux = calloc(1,sizeof(t_column));
    if(!aux)
       exit(ERROR);

    aux->value = val;

    t_floatCell* p = *head;
    t_floatCell* ant = NULL;

    if(p == NULL)
        *head = aux;
    else
    {
        while(p != NULL)
        {
            ant = p;
            p = p->next;
        }
        ant->next = aux;
    }
}

void Ins_STRING(t_stringCell** head, char* val)
{

    /* Functie care adauga o noua celula cu valorea primita ca parametru
    intr-o lista de celule cu elemente de tip STRING, la sfarsitul listei*/

    //Aloc celula de adaugat in lista
    t_stringCell* aux = calloc(1,sizeof(t_column));
    if(!aux)
        exit(ERROR);

    //Aloc dinamic si sirul de caractere din interiorul celulei noi
    aux->value = strdup(val);

    t_stringCell* p = *head;
    t_stringCell* ant = NULL;

    if(p == NULL)
        *head = aux;
    else
    {
        while(p != NULL)
        {
            ant = p;
            p = p->next;
        }
        ant->next = aux;
    }
}

void free_INT_line(t_intLine** lin)
{
    /* Functie ce elibereaza toata memoria ocupata de o linie
    de celule cu elemente de tip INT */

    t_intLine* del = *lin;
    t_intCell* p = del->cells;

    //Parcurg toata lista
    while(p != NULL)
    {
        /* Pastrez elementul curent intr-un auxiliar, accesez urmatoarea
        celula iar apoi eliberez elementul curent */
        t_intCell* aux = p;
        p = p->next;
        free(aux);
    }

    free(del);

    *lin = NULL;
}

void free_FLOAT_line(t_floatLine** lin)
{
    /* Functie ce elibereaza toata memoria ocupata de o linie
    de celule cu elemente de tip FLOAT */

    t_floatLine* del = *lin;
    t_floatCell* p = del->cells;

    while(p != NULL)
    {
        t_floatCell* aux = p;
        p = p->next;
        free(aux);
    }

    free(del);

    *lin = NULL;
}

void free_STRING_line(t_stringLine** lin)
{
    /* Functie ce elibereaza toata memoria ocupata de o linie
    de celule cu elemente de tip STRING */

    t_stringLine* del = *lin;
    t_stringCell* p = del->cells;
    while(p != NULL)
    {
        /*Pentru celule de string-uri voi elibera mai intai sirul
        de caractere din celula curenta */
        t_stringCell* aux = p;
        p = p->next;
        free(aux->value);
        free(aux);
    }

    free(del);

    *lin = NULL;
}

t_intLine* Create_int_line(int nr_col, int* val)
{
    /* Functie ce creaza o linie cu celule ce contin valori de tip int.
    Valorile sunt retinute intr-un vector. Linia nou creata va contine
    nr_col elemente */

    //Aloc linia noua
    t_intLine* new = calloc(1, sizeof(t_intLine));

    if(!new)
        return NULL;

    new->next = NULL;

    //Parcurg linia nou creata si inserez fiecare valoare din vector
    for(int i = 0;i < nr_col; i++)
        Ins_INT(&new->cells, val[i]);

    return new;
}

t_floatLine* Create_float_line(int nr_col, float* val)
{

    /* Functie ce creaza o linie cu celule ce contin valori de tip int.
    Valorile sunt retinute intr-un vector de elemente de tip float */

    t_floatLine* new = calloc(1, sizeof(t_floatLine));

    if(!new)
        return NULL;

    new->next = NULL;

    for(int i = 0;i < nr_col; i++)
        Ins_FLOAT(&new->cells, val[i]);

    return new;
}

t_stringLine* Create_string_line(int nr_col, char** val)
{

    /* Functie ce creaza o linie cu celule ce contin valori de tip
    string / char*. Valorile sunt retinute intr-un vector de elemente
    de tip char pointer */

    t_stringLine* new = calloc(1, sizeof(t_stringLine));

    if(!new)
        return NULL;

    new->next = NULL;

    for(int i = 0;i < nr_col; i++)
        Ins_STRING(&new->cells, val[i]);

    return new;
}

void Add_int_line(t_table* table, int nr_col, int* val)
{

    /* Functie ce adauga intr-un tabel o noua linie cu elemente de tip INT,
    construita pe baza unui vector de valori si al numarului de
    valori nr_col. Inserarea se face la sfarsit */

    //Creez o linie noua de celule ce contin INT-uri cu functia precedenta

    t_intLine* new = Create_int_line(nr_col, val);
    if(!new)
        exit(ERROR);

    t_intLine* p = (t_intLine*) table->lines;
    t_intLine* ant = NULL;

    while(p != NULL)
    {
        ant = p;
        p = p->next;
    }
    if(ant == NULL)
        table->lines = (void*) new;
    else
        ant->next = new;
}

void Add_float_line(t_table* table, int nr_col, float* val)
{

    /* Functie ce adauga intr-un tabel o noua linie cu elemente de tip FLOAT,
    construita pe baza unui vector de valori si al numarului de
    valori nr_col */

    t_floatLine* new = Create_float_line(nr_col, val);
    if(!new)
        exit(ERROR);

    t_floatLine* p = (t_floatLine*) table->lines;
    t_floatLine* ant = NULL;

    //Parcurg lista de linii; in cazul in care e vida, inserez in capul listei
    while(p != NULL)
    {
        ant = p;
        p = p->next;
    }
    if(ant == NULL)
        table->lines = (void*) new;
    else
        ant->next = new;
}

void Add_string_line(t_table* table, int nr_col, char** val)
{

    /* Functie ce adauga intr-un tabel o noua linie cu elemente de tip STRING,
    construita pe baza unui vector de valori si al numarului de
    valori nr_col */

    t_stringLine* new = Create_string_line(nr_col, val);
    if(!new)
        exit(ERROR);

    t_stringLine* p = (t_stringLine*) table->lines;
    t_stringLine* ant = NULL;
    while(p != NULL)
    {
        ant = p;
        p = p->next;
    }
    if(ant == NULL)
        table->lines = (void*) new;
    else
        ant->next = new;
}

void Afi_String(char* value)
{
    /* Functie ce afiseaza o valore de tip string , si o aliniaza
    intr-un tabel, adaugand padding-ul corespunzator */

    printf("%s", value);

    Align(value);
}

void Afi_Int(int value)
{
    /* Functie ce afiseaza o valoarea int, si apoi o aliniaza
    intr-un tabel */
    printf("%d", value);

    //Aloc buffer-ul corespunzator, pentru a retine in el valoarea de tip int
    char* buffer = calloc(MAX_COLUMN_NAME_LEN, sizeof(char));
    if(!buffer)
        exit(ERROR);
    sprintf(buffer, "%d", value);

    //Aliniez valoarea pentru a respecta formatul coloanei
    Align(buffer);

    free(buffer);
}

void Afi_Float(float value)
{

    // Functie ce afiseaza o valoare float, si apoi o aliniaza intr-un tabel

    printf("%f", value);

    /*Pentru a adauga padding-ul, va trebui sa convertesc valoarea de tip
    float la una de tip string */
    char* buffer = calloc(MAX_COLUMN_NAME_LEN, sizeof(char));
    if(!buffer)
        exit(ERROR);

    //Adaug valoarea float intr-un buffer, pe care il aliniez
    sprintf(buffer, "%f", value);
    Align(buffer);

    //Eliberez memoria alocata pentru buffer
    free(buffer);
}

int Get_IntCell_Val(t_intLine* lin, int no_col)
{
    /* Functie ce returneaza valorea INT retinuta la coloana cu indicele
    no_col din linia primita ca parametru */
    t_intCell* cell = lin->cells;

    //Parcurg lista de celule doar pana la celula de indice no_col
    for(int i = 0; i < no_col; i++)
        cell = cell->next;

    //Returnez valoarea din celula
    return cell->value;
}

float Get_FloatCell_Val(t_floatLine* lin, int no_col)
{
    //Procedez in aceeasi maniera pentru fiecare tip de date
    t_floatCell* cell = lin->cells;
    for(int i = 0; i < no_col; i++)
        cell = cell->next;
    return cell->value;
}

char* Get_StringCell_Val(t_stringLine* lin, int no_col)
{
    t_stringCell* cell = lin->cells;
    for(int i = 0; i < no_col; i++)
        cell = cell->next;
    return cell->value;

}

void Search_int_lines(t_table* table, int no_col, void* val, t_operator rel)
{

    /* Functie ce afiseaza toate liniile dintr-o tabela primita ca parametru,
    ale caror elemente de pe pozitia no_col respecta conditia data de
    parametrul rel(un enum care retine relatiile "<=" ">=" "<" ...).*/

    //Parcurg lista de linii a tabelului
    t_intLine* lin = (t_intLine*)table->lines;
    while(lin != NULL)
    {
        //Obtin valoarea din celula de la pozitia no_col
        int cell_val = Get_IntCell_Val(lin, no_col);

        //Verific ca respecta conditia
        if(Cond(rel, table->type, (void*)&cell_val, val))
        {
            /*In caz afirmativ, parcurg intreaga linie de la inceput,
            si afisez pe rand fiecare element */
            t_intCell* current = lin->cells;
            while(current != NULL)
            {
                Afi_Int(current->value);
                current = current->next;
            }
            printf("\n");
        }
        lin = lin->next;
    }
}

void Search_float_lines(t_table* table, int no_col, void* val, t_operator rel)
{
    /*Pentru elemente STRING si FLOAT procedez in acelasi mod ca la
    functia Search_int_lines */
    t_floatLine* lin = (t_floatLine*)table->lines;
    while(lin != NULL)
    {
        float cell_val = Get_FloatCell_Val(lin, no_col);
        
        if(Cond(rel, table->type, (void*)&cell_val, val))
        {
            t_floatCell* current = lin->cells;
            while(current != NULL)
            {
                Afi_Float(current->value);
                current = current->next;
            }
            printf("\n");
        }
        lin = lin->next;
    }
}

void Search_string_lines(t_table* table, int no_col, void* val, t_operator rel)
{
    t_stringLine* lin = (t_stringLine*)table->lines;
    while(lin != NULL)
    {
        char* cell_val = Get_StringCell_Val(lin, no_col);
        if(Cond(rel, table->type, (void*)(cell_val), val))
        {
            t_stringCell* current = lin->cells;
            
            while(current != NULL)
            {
                Afi_String(current->value);
                current = current->next;
            }
            printf("\n");
        }
        lin = lin->next;
    }
}

void Delete_int_lines(t_table* table, int no_col, t_operator rel, void* val)
{

    /* Functie ce sterge toate liniile dintr-o tabela primita ca parametru,
    ale caror elemente de pe pozitia no_col respecta conditia data de
    parametrul rel. Valorea cu care se compara este cea de la adresa val */

    //Parcurg lista de linii din tabel
    t_intLine* lin = (t_intLine*)table->lines;
    t_intLine* ant = NULL;
    
    while(lin != NULL)
    {
        //Pentru fiecare linie, obtin valoarea de la pozitia no_col
        int cell_val = Get_IntCell_Val(lin, no_col);

        /*Verific daca respecta conditia */
        if(Cond(rel, table->type, (void*)&cell_val, val))
        {
            // In caz afirmativ, elimin linia din tabel.
            t_intLine* aux = lin;
            if(ant == NULL)
                table->lines = (void*)(lin->next);
            else
                ant->next = lin->next;
            
            //Folosesc continue pentru a sari peste actualizarea de la final
            lin = lin->next;

            //Retin intr-un auxiliar linia de eliminat
            free_INT_line(&aux);
            continue;
        }
        ant = lin;
        lin = lin->next;
    }
}

void Delete_float_lines(t_table* table, int no_col, t_operator rel, void* val)
{

    /* Procedez in mod similar cu functia Delete_int_lines, doar ca voi folosi
    linii si celule cu elemente de tip float */
    t_floatLine* lin = (t_floatLine*)table->lines;
    t_floatLine* ant = NULL;

    while(lin != NULL)
    {
        float cell_val = Get_FloatCell_Val(lin, no_col);
        if(Cond(rel, table->type, (void*)&cell_val, val))
        {
            t_floatLine* aux = lin;
            if(ant == NULL)
                table->lines = (void*)(lin->next);
            else
                ant->next = lin->next;
        
            lin = lin->next;
            free_FLOAT_line(&aux);
            continue;
        }
        ant = lin;
        lin = lin->next;
    }
}

void Delete_string_lines(t_table* table, int no_col, t_operator rel, void* val)
{
    /* Procedez in mod similar cu functia Delete_int_lines, doar ca voi folosi
    linii si celule cu elemente de tip string */
    t_stringLine* lin = (t_stringLine*)table->lines;
    t_stringLine* ant = NULL;
    while(lin != NULL)
    {
        char* cell_val = Get_StringCell_Val(lin, no_col);
        if(Cond(rel, table->type, (void*)(cell_val), val))
        {
            t_stringLine* aux = lin;

            if(ant == NULL)
                table->lines = (void*)(lin->next);
            else
                ant->next = lin->next;

            lin = lin->next;
            free_STRING_line(&aux);
            continue;
        }
        ant = lin;
        lin = lin->next;
    }
}
