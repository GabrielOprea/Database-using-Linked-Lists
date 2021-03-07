# Database-using-Linked-Lists
A program in C which implements a database and offers the user an interactive console and an 
interface for interacting with it. Implementantion based on Simply/Doubly Linked Lists.

Oprea-Groza Gabriel

The program works as an interactive console and the user can use the following commands:

CREATE [Table_name Columns...]
CLEAR [Table_name]
DELETE [Table_name Condition]
PRINT [Table_name]
ADD [Table_name Entries...]
SEARCH [Table_name Condition]
PRINT_DB [Table_name]
DELETE_DB [Table_name]
INIT_DB [Database name]

Each table can contain either Integers, Floats or String values.

In the structures.h header file, I defined constants for the maximum number of characters
in the table/column/type name strings, number of arguments and many more. Also,
I defined the structures for a Cell or Line of the 3 specified types. I also
used an enum for number comparison, similar to the ones used in Shell Scripting
(EQ, LT, BT, BE, LE, NE).

Functions.h header file contains all the functions used in this application, separated
by their role.

In the console.c file, I implemented the interactive console, that reads line by
line from stdin until it receives the DELETE_DB command, that deletes all the
database and ends the program. All the possible commands are listed in a switch
statement. Based on the specified command, the input string is parsed accordingly.
I created a function per command type, each one calling Next_Arg function that
provides the next command line argument. Then, these function call the lower-level
functions from the file database.c.

In database.c I implemented all the auxiliary functions required for the database,
like selective searching, selective deleting, verifying that 2 entries satisfy
a specific relation(BE, EQ...).

Functions.c contains all the functions that depend on the cell type, implemented
3 versions for each one(int, float, string). These functions add, get, delete values
or create tables of specified value types.
