//Oprea-Groza Gabriel - 313CB

#include "functions.h"

void Console()
{
    /*Functie ce primeste input continuu, pana la comanda DELETE_DB si
    apeleaza functiile corespunzatoare */
    t_db* database;
    char cmd[MAX_CMD_LEN];

    while(FOREVER)
    {
        //Citesc comenzi pana intalnesc DELETE_DB
        fgets(cmd, MAX_CMD_LEN, stdin);

        //Elimin newline-ul de la sfarsit daca este cazul
        int len = strlen(cmd) - SPACE_LEN;
        if(cmd[len] == '\n')
            cmd[len] = '\0';

        char* cmd_copy = strdup(cmd); /*copiez comanda pentru a o afisa
        in cazul in care e introdusa gresit */

        //Obtin numarul de argumente din comanda
        int args = Nr_arg(cmd);

        //Impart comanda in token-uri
        char* part_cmd = strtok(cmd," ");
        
        //Daca am o comanda vida, trec mai departe
        if(part_cmd == NULL) continue;


        //Altfel execut functii pentru fiecare prim argument al comenzii
        if(!strcmp(part_cmd, "INIT_DB"))
        {
            //Initializez baza de date si verific
            database = INIT_DB(part_cmd);
            if(!database) exit(ERROR);
        }
        else if(!strcmp(part_cmd, "CREATE"))
        {
            CREATE(database, part_cmd, args);
        }
        else if(!strcmp(part_cmd, "CLEAR"))
        {
            CLEAR(database, part_cmd);
        }
        else if(!strcmp(part_cmd, "DELETE"))
        {
            DELETE(database, part_cmd);
        }
        else if(!strcmp(part_cmd, "PRINT"))
        {
            PRINT(database, part_cmd);
        }
        else if(!strcmp(part_cmd, "ADD"))
        {
            ADD(database, part_cmd, args);
        }
        else if(!strcmp(part_cmd, "SEARCH"))
        {
            SEARCH(database, part_cmd);
        }
        else if(!strcmp(part_cmd, "PRINT_DB"))
        {
            PRINT_DB(database);
        }
        else if(!strcmp(part_cmd, "DELETE_DB"))
        {
            DELETE_DB(&database);
            free(cmd_copy);
            break;
        }
        else
            printf("Unknown command:\"%s\".\n", cmd_copy);
        
        free(cmd_copy);
    }
}

t_db* INIT_DB(char* part_cmd)
{
    
    //Copiez numele bazei de date din argumentul urmator al comenzii
    t_db* database;
    char db_name[MAX_DB_NAME_LEN];
    strcpy(db_name, Next_Arg(part_cmd));

    //Creez baza de date respectiva
    database = Create_DB(db_name);
        if(!database)
            return NULL;
    return database;
}

void CLEAR(t_db* database, char* part_cmd)
{
    //Preiau numele tabelei din argumentul urmator al comenzii
    char table_name[MAX_TABLE_NAME_LEN];
    strcpy(table_name, Next_Arg(part_cmd));

    //Gasesc pointer la tabela respectiva
    t_table* p = Find_Table(database->tables, table_name);

    //Daca am gasit-o, o fac vida
    if(p != NULL)
        Clear_Table(&p);
    else
        printf("Table \"%s\" not found in database.\n", table_name);
}


void DELETE(t_db* database, char* part_cmd)
{
    char table_name[MAX_TABLE_NAME_LEN];
    strcpy(table_name, Next_Arg(part_cmd));

    t_table* p = database->tables;
    t_table* ant = NULL;

    part_cmd = Next_Arg(part_cmd); //Verific daca mai sunt argumente

    //Daca nu mai sunt argumente, inseamna ca trebuie stearsa toata tabela
    if(part_cmd == NULL)
    {
        while(p != NULL)
        {
            //Caut tabela in lista si rup legaturile
            if(!strcmp(p->name, table_name))
            {
                if(ant != NULL)
                    ant->next = p->next;
                else
                    database->tables = p->next;
                break;
            }
            ant = p;
            p = p->next;
        }
        if(p != NULL)
            //Daca am gasit tabela, o sterg
            Delete_Table(&p);
        else
            printf("Table \"%s\" not found in database.\n", table_name);
    }
    else
    {
        //Daca mai sunt argumente, inseamna ca va urma o stergere selectiva
        p = Find_Table(database->tables, table_name);
        if(p == NULL)
        {
            printf("Table \"%s\" not found in database.\n", table_name);
            return;
        }

        //Citesc in continuare coloana si operatia de comparatie
        char col_name[MAX_COLUMN_NAME_LEN];
        strcpy(col_name, part_cmd);

        char op[MAX_OP_LEN];
        strcpy(op, Next_Arg(part_cmd));
        t_operator rel = Relation(op);

        //Citesc si valoarea cu care compar
        char* value = strdup(Next_Arg(part_cmd));

        if(p->type == INT)
        {
            //Daca am tabela int, convertesc valoarea de compar la un intreg
            int val_int = atoi(value);
            Delete_Selective(p, col_name, (void*)(&val_int), rel);
        }
        else if(p->type == FLOAT)
        {
            //In cazul float, folosesc functia atof
            float val_float = atof(value);
            Delete_Selective(p, col_name, (void*)(&val_float), rel);
        }
        else
            Delete_Selective(p, col_name, (void*)value, rel);

        free(value);
    }
}

void PRINT(t_db* database, char* part_cmd)
{
    //Obtin urmatorul argument, anume tabela de afisat
    char table_name[MAX_TABLE_NAME_LEN];
    strcpy(table_name, Next_Arg(part_cmd));
    t_table* p = database->tables;

    //Caut tabela si o afisez cu functia de afisare tabela
    p = Find_Table(database->tables, table_name);
    if(p != NULL)
        Print_Table(p);
    else
        printf("Table \"%s\" not found in database.\n", table_name);
}

void ADD(t_db* database, char* part_cmd, int args)
{

    //Obtin initial numele tabelei, si o caut in lista
    char table_name[MAX_TABLE_NAME_LEN];
    strcpy(table_name, Next_Arg(part_cmd));

    t_table* p = Find_Table(database->tables, table_name);
    if(p == NULL)
    {
        printf("Table \"%s\" not found in database.\n", table_name);
        return;
    }

    //Obtin numarul de coloane in functie de numarul de argumente initial
    int nr_col = args - NR_ARG_ADD;

    //Aloc un vector de string-uri cu valorile liniilor
    char** lin_val = calloc(nr_col, sizeof(char*));
    if(!lin_val) exit(ERROR);

    int i;
    for(i = 0; i < nr_col; i++)
    {
        //Obtin coloanele rand pe rand
        part_cmd = Next_Arg(part_cmd);

        //Retin fiecare string din linie
        lin_val[i] = strdup(part_cmd);
        if(!lin_val[i]) exit(ERROR);
    }
    if(p->type == STRING)
        Add_string_line(p, nr_col, lin_val);

    if(p->type == INT)
    {
        /*Daca tabela este int, va fi nevoie sa convertesc valorile citite ca
        string ale liniilor cu atoi */
        int* int_val = calloc(nr_col, sizeof(int));
        if(!int_val)
            exit(ERROR);

        for(int j = 0; j < nr_col; j++)
            int_val[j] = atoi(lin_val[j]);
        Add_int_line(p, nr_col, int_val);
        free(int_val);
    }

    if(p->type == FLOAT)
    {
        //In cazul float folosec atof
        float* float_val = calloc(nr_col, sizeof(int));
        if(!float_val)
            exit(ERROR);

        for(int j = 0; j < nr_col; j++)
            float_val[j] = atof(lin_val[j]);
        Add_float_line(p, i, float_val);
        free(float_val);
    }

    //Eliberez toate alocarile auxiliare
    for(int j = 0; j < nr_col; j++)
        free(lin_val[j]);
    free(lin_val);
}

void CREATE(t_db* database, char* part_cmd, int args)
{

    //In cazul functiei create, obtin tabela de creat
    part_cmd = Next_Arg(part_cmd);
    char* table_name = strdup(part_cmd);

    t_cellType type;

    //Obtin tipul tabelei    
    part_cmd = Next_Arg(part_cmd);

    char* type_name = strdup(part_cmd);

    //Setez enum-ul
    if(!strcmp(type_name, "INT"))
        type = INT;
    else if(!strcmp(type_name, "FLOAT"))
        type = FLOAT;
    else if(!strcmp(type_name, "STRING"))
        type = STRING;
    else
    {
        printf("Unknown data type:\"%s\".\n\n", part_cmd);
        free(table_name);
        free(type_name);

        //Daca nu am gasit datatype-ul, ies din functie
        return;
    }


    //Determin numarul de coloane ramase de citit
    int nr_col = args - NR_ARG_CREATE;

    //Aloc un vector de string-uri pentru coloane
    char** col_names = calloc(nr_col, sizeof(char*));
    if(!col_names) exit(ERROR);

    int i;
    for(i = 0; i < nr_col; i++)
    {
        part_cmd = Next_Arg(part_cmd);
        if(part_cmd == NULL)
            break;

        col_names[i] = strdup(part_cmd);
        if(!col_names[i]) exit(ERROR);
    }

    //Creez tabela cu functia aferenta dupa ce am preluat toti parametri
    Create_Table(database, table_name, type, col_names, nr_col);
    
    for(int j = 0; j < nr_col; j++)
        free(col_names[j]);
    free(col_names);

    free(table_name);
    free(type_name);

}

void SEARCH(t_db* database, char* part_cmd)
{
    char table_name[MAX_TABLE_NAME_LEN];
    strcpy(table_name, Next_Arg(part_cmd));

    //Caut tabela in lista
    t_table* p = Find_Table(database->tables, table_name);
    if(p == NULL)
    {
        printf("Table \"%s\" not found in database.\n", table_name);
        return;
    }

    //Dupa ce am gasit-o, preiau din argumente numele coloanei si operatia
    char col_name[MAX_COLUMN_NAME_LEN];
    strcpy(col_name, Next_Arg(part_cmd));

    char op[MAX_OP_LEN];
    strcpy(op, Next_Arg(part_cmd));
    t_operator rel = Relation(op);
    

    //Preiau valoarea cu care compar
    char* value = strdup(Next_Arg(part_cmd));


    //In functie de tip, va fi nevoie sa fac cast
    if(p->type == INT)
    {
        int val_int = atoi(value);

        /*Deoarece functia Search_Selective are nevoie de un void*, in cazul
        int si float fac cast la adresa */
        Search_Selective(p, col_name, (void*)(&val_int), rel);
    }
    else if(p->type == FLOAT)
    {
        float val_float = atof(value);
        Search_Selective(p, col_name, (void*)(&val_float), rel);
    }
    else
        //In cazul string convertesc direct la void*
        Search_Selective(p, col_name, (void*)value, rel);

    free(value);
}

void PRINT_DB(t_db* database)
{
    /*Functie ce afiseaza o baza de date, cu toate
    tabelele continute de aceasta */
    t_table* current = database->tables;

    //Afisez header-ul bazei de date
    printf("DATABASE: %s\n", database->name);
    printf("\n");

    while(current != NULL)
    {
        //Parcurg lista de tabile si afisez fiecare tabel
        Print_Table(current);
        current = current->next;
    }
}

void DELETE_DB(t_db** database)
{
    //Functie ce elibereaza toata memoria pentru o baza de date
    t_db* db = *database;

    while(db->tables != NULL)
    {
        //Parcurg tabelele din baza de date si eliberez memoria pentru fiecare
        t_table* aux = db->tables;
        db->tables = db->tables->next;
        Delete_Table(&aux);
    }

    //Eliberez memoria pentru descriptor si setez pointer-ul la NULL
    free(*database);
    *database = NULL;
}


int main()
{
    Console();
    return 0;
}
