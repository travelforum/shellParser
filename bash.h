/*
 * shell header file
 */

#define MAX_ARGS 100

/* This is the definition of a command */
struct command {
    char *command;
    int argc;
    char *argv[MAX_ARGS];
    char *infile;
    char *outfile;
    char *errfile;
    int lines;

    char output_append; /* boolean: append stdout? */
    char error_append;  /* boolean: append stderr? */

    struct command *next;
};

/* externals */
extern int yydebug;
extern int debug;

/* global routine decls */
void doline(struct command *pass);
int yyparse(void);
