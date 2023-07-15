/*
 * Main for Shell Project
 *
 * Nick Schuler - 9/23/2022
 */

#include <iostream>
#include <string.h>

using namespace std;

// types and definitions live in "C land" and must be flagged
extern "C" {
#include "bash.h"
#include "parser.tab.h"
extern "C" void yyset_debug(int d);
}

// global debugging flag
int debug = 0;

int main(int argc, char *argv[]) {
    if ((argc == 2) && (strcmp(argv[1], "-d") == 0))
        debug = 1; /* turn on ugly YACC debugging */

    if (debug)
        yydebug = 1; /* turn on ugly YACC debugging */

    /* parse the input file */
    yyparse();

    exit(0);
}

void doline(struct command *pcmd) {
    int counter = 0;

    while (true) { // output formatting
        cout << "========== line " << pcmd->lines << " ==========\n";

        int temp = pcmd->lines;

        while (pcmd->lines == temp) {
            cout << "Command name: '" << pcmd->argv[0] << "'\n";

            for (int i = 0; i < pcmd->argc; i++) { // ARGS
                cout << "    argv[" << i << "]: '" << pcmd->argv[i] << "'\n";
            }

            if (pcmd->infile != NULL) { // input direction
                if (strcmp(pcmd->infile, "PIPE") == 0) {
                    cout << "  stdin:  PIPE" << counter << '\n';
                } else {
                    cout << "  stdin:  '" << pcmd->infile << "'\n";
                }
            } else {
                cout << "  stdin:  '<undirected>'\n";
            }

            if (pcmd->outfile != NULL) { // output direction
                if (strcmp(pcmd->outfile, "PIPE") == 0) {
                    counter++;
                    cout << "  stdout: PIPE" << counter << '\n';
                } else {
                    cout << "  stdout: '" << pcmd->outfile << "'";
                    if (pcmd->output_append == 1) {
                        cout << " (append)\n";
                    } else {
                        cout << "\n";
                    }
                }
            } else {
                cout << "  stdout: '<undirected>'\n";
            }

            if (pcmd->errfile != NULL) { // err direction
                if (strcmp(pcmd->errfile, "PIPE") == 0) {
                    counter++;
                    cout << "  stderr: PIPE" << counter << '\n';
                } else {
                    cout << "  stderr: '" << pcmd->errfile << "'";
                    if (pcmd->error_append == 1) {
                        cout << " (append)\n";
                    } else {
                        cout << "\n";
                    }
                }
            } else {
                cout << "  stderr: '<undirected>'\n";
            }

            if (pcmd->next == NULL) { // exit condition
                break;
            } else {
                pcmd = pcmd->next;
            }
        }

        cout << endl;

        if (pcmd->next == NULL) { // exit condition
            break;
        }

        pcmd = pcmd->next;
    }
}
