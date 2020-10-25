//Oprea-Groza Gabriel - 313CB

#ifndef __STRUCTURES__
#define __STRUCTURES__

#define MAX_COLUMN_NAME_LEN 30
#define MAX_TYPE_NAME_LEN   6
#define MAX_TABLE_NAME_LEN  30
#define MAX_DB_NAME_LEN     30
#define MAX_CMD_LEN         300

//Codul de eroare returnat la o alocare sau functie esuata
#define ERROR               1
//Codul utilizat intr-o bucla infinita
#define FOREVER             1
//Dimensiunea maxima a unui operator de comparatie
#define MAX_OP_LEN          2
//Dimensiunea unui spatiu gol
#define SPACE_LEN           1
//Cod de eroare la un element negasit
#define NOT_FOUND           -1

/*Numarul de argumente citite pana la lista de coloane, in cazul
functiei CREATE */
#define NR_ARG_CREATE       2

/*Numarul de argumente citite pana la lista de coloane, in cazul
functiei ADD */
#define NR_ARG_ADD          1

#define TRUE                1
#define FALSE               0

typedef struct intCell {
    int    value;
    struct intCell* next;
} t_intCell;

typedef struct intLine {
    t_intCell*      cells;
    struct intLine* next;
} t_intLine;

// float
typedef struct floatCell {
    float  value;
    struct floatCell* next;
} t_floatCell;

typedef struct floatLine {
    t_floatCell*      cells;
    struct floatLine* next;
} t_floatLine;

// string
typedef struct stringCell {
    char*  value;
    struct stringCell* next;
} t_stringCell;

typedef struct stringLine {
    t_stringCell*       cells;
    struct stringLine* next;
} t_stringLine;

// cell type
typedef enum {
    INT,
    FLOAT,
    STRING
} t_cellType;

/* Tipul operator, care va retine mai multe relatii,
corespunzatoare comparatiilor intre 2 numere */
typedef enum {
    EQ, // ==
    LT, // <
    BT, // >
    BE, // >=
    LE, // <=
    NE, // !=
} t_operator;

// column
typedef struct column {
    char name[MAX_COLUMN_NAME_LEN];
    struct column* next;
} t_column;

// table
typedef struct table {
    char name[MAX_TABLE_NAME_LEN];
    t_cellType    type;
    t_column*     columns;
    void*         lines;// t_intLine* | t_floatLine* | t_stringLine*
    struct table* next;
} t_table;

// database
typedef struct db {
    char name[MAX_DB_NAME_LEN];
    t_table* tables;
} t_db;

#endif
