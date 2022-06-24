#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_SYNTAX_TREE_CHILDREN 3
enum Command {
    SR = 0,
    ADD = 1,
    SUB = 2,
    MUL = 3,
    DIV = 4,
    MOD = 5,
    EQ = 6,
    NEQ = 7,
    GT = 8,
    GTE = 9,
    LT = 10,
    LTE = 11,
    AND = 12,
    OR = 13,
    NOT = 14,
    XOR = 15,
    SLL = 16,
    SRL = 17,
    LBL = 18,
    GOTO = 19,
    GEQ = 20,
    GNQ = 21,
    PRINT = 22,
    PRINTLN = 23,
    HALT = 24,
    INPUT = 25

};

enum TokenType {
    COMMAND = 1, REGISTER = 2, DECIMAL = 3, HEXIDECIMAL = 4, DIRECTIVE = 5, END_STATEMENT = 9
};


struct Token {
    char *symbol;
    int line;
    int pos;
    enum TokenType type;

} Token;

struct TokenNode {
    struct TokenNode *next;
    struct TokenNode *prev;
    struct Token *token;


} TokenNode;

struct SyntaxTreeNode {
    int type;
    struct SyntaxTreeNode *children[MAX_SYNTAX_TREE_CHILDREN];

} SyntaxTreeNode;

struct SyntaxTreeNode proper_syntax_tree[26] = {
        { /* SR */
                .type = COMMAND, .children =  {&(struct SyntaxTreeNode) {.type=REGISTER, .children={
                &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
        }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* ADD */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* SUB */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* MUL */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* DIV */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* MOD */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* EQ */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* NEQ */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* GT */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* GTE */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* LT */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* LTE */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* AND */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* OR */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* NOT */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* XOR */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* SLL */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* SRL */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DECIMAL, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                                &(struct SyntaxTreeNode) {.type= REGISTER, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* LBL */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=DIRECTIVE, .children={
                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* GOTO */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=DIRECTIVE, .children={
                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* GEQ */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DIRECTIVE, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DIRECTIVE, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* GNQ */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                                &(struct SyntaxTreeNode) {.type= DIRECTIVE, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                        }
                        },
                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                                &(struct SyntaxTreeNode) {.type= DIRECTIVE, .children={
                                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                        }
                        },
                }}, &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}, NULL}},
        { /* PRINT */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                &(struct SyntaxTreeNode) {.type=DIRECTIVE, .children={
                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}}
        },
        { /* PRINTLN */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=DECIMAL, .children={
                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                &(struct SyntaxTreeNode) {.type=DIRECTIVE, .children={
                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}}
        },
        { /* HALT */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}

        }},
        { /* INPUT */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
        }
        },
};

char *get_token_type_from_int(int type) {
    if (type == COMMAND) {
        return "COMMAND";
    } else if (type == REGISTER) {
        return "REGISTER";
    } else if (type == DECIMAL) {
        return "DECIMAL";
    } else if (type == HEXIDECIMAL) {
        return "HEXIDECIMAL";
    } else if (type == DIRECTIVE) {
        return "DIRECTIVE";
    } else if (type == END_STATEMENT) {
        return "END_STATEMENT";
    }
    return "UNKOWN";
}

char *lstrip(char *string) {
    if (string == NULL) {
        return NULL;
    }
    int length = strlen(string);

    int index = 0;
    while (isspace(string[index])) {
        index++;
    }
    char *out = malloc(length - index + 1);
    strncpy(out, &string[index], length - index);
    out[length - index] = '\0';
    return out;
}

char *rstrip(char *string) {
    if (string == NULL) {
        return NULL;
    }

    int length = strlen(string);

    int index = length - 1;
    while (isspace(string[index])) {
        index--;
    }
    char *out = malloc(index + 1);
    strncpy(out, &string[0], index + 1);
    out[index + 1] = '\0';
    return out;
}

char *strip(char *string) {
    return rstrip(lstrip(string));
}


int get_token_type(char *symbol) {

    if (symbol[0] == '"') {
        if (symbol[strlen(symbol) - 1] != '"') {
            return -1;
        }
        return DIRECTIVE;
    }

    char *upper_symbol = strupr(symbol);

    if (strcmp(upper_symbol, "SR") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "ADD") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "SUB") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "MUL") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "DIV") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "MOD") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "EQ") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "NEQ") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "GT") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "GTE") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "LT") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "LTE") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "AND") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "OR") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "NOT") == 0) {
        return COMMAND;

    }
    if (strcmp(upper_symbol, "XOR") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "SLL") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "SRL") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "LBL") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "GOTO") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "GEQ") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "GNQ") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "PRINT") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "PRINTLN") == 0) {
        return COMMAND;
    }
    if (strcmp(upper_symbol, "HALT") == 0) {
        return COMMAND;
    }
    if (upper_symbol[0] == '$') {
        int index = 1;
        while (index < strlen(upper_symbol)) {
            if (isdigit(upper_symbol[index]) != 1) {
                return -1;
            }
            index++;
        }
        return REGISTER;
    }
    if (upper_symbol[0] == '0' && upper_symbol[1] == 'X') {
        return HEXIDECIMAL;
    }

    if (isdigit(upper_symbol[0])) {
        int index = 1;
        while (index < strlen(upper_symbol)) {
            if (isdigit(upper_symbol[index]) != 1) {
                return -1;
            }
            index++;

        }
        return DECIMAL;
    }


    return -1;
}

/**
 * Parse line starting at the specified index and save it to a Token struct
 * @param line The line string.
 * @param line_number The line number of the line.
 * @param token Pointer to a Token struct. Saves all information in this variable.
 * @param index Index from where to start parsing from.
 * @return Returns the index to the beginning of the next token. If the whole line is precessed, returns -1.
 */
int parse_line(char *line, int line_number, struct Token *token, int index) {

    if (index >= strlen(line) || index < 0) {
        return -1;
    }
    int start_index = index;

    // While the whole line is not processed
    while (line[index] != '\0' && line[index] != '\n') {
        // If the first character is quotes, then find the ending quote
        if (line[index] == '"') {
            index++;
            while (line[index] != '"') {
                index++;
            }
            index++;
        }
            // Find the beginning of the next token
        else {
            while (line[index] != ' ' && line[index] != ',' && line[index] != '\0' && line[index] != '\n') {
                index++;
            }
        }

        // Copy the string section from start index to the index
        char *value = malloc(index - start_index);
        strncpy(value, &line[start_index], index - start_index);
        value[index - start_index] = '\0';

        // Find the beginning of the next token
        while (isalnum(line[index]) == 0 && line[index] != '$' && line[index] != '"') {
            if (line[index] == '\0' || line[index] == '\n') {
                break;
            }
            index++;
        }
        // Store data in token structure
        token->type = get_token_type(value);
        token->symbol = value;
        token->line = line_number;
        token->pos = start_index;

        return index;

    }
    return -1;

}

uint64_t get_opcode_for_symbol(char *symbol) {

    char *upper_symbol = strupr(symbol);

    if (strcmp(upper_symbol, "SR") == 0) {
        return SR;
    }
    if (strcmp(upper_symbol, "ADD") == 0) {
        return ADD;
    }
    if (strcmp(upper_symbol, "SUB") == 0) {
        return SUB;
    }
    if (strcmp(upper_symbol, "MUL") == 0) {
        return MUL;
    }
    if (strcmp(upper_symbol, "DIV") == 0) {
        return DIV;
    }
    if (strcmp(upper_symbol, "MOD") == 0) {
        return MOD;
    }
    if (strcmp(upper_symbol, "EQ") == 0) {
        return EQ;
    }
    if (strcmp(upper_symbol, "NEQ") == 0) {
        return NEQ;
    }
    if (strcmp(upper_symbol, "GT") == 0) {
        return GT;
    }
    if (strcmp(upper_symbol, "GTE") == 0) {
        return GTE;
    }
    if (strcmp(upper_symbol, "LT") == 0) {
        return LT;
    }
    if (strcmp(upper_symbol, "LTE") == 0) {
        return LTE;
    }
    if (strcmp(upper_symbol, "AND") == 0) {
        return AND;
    }
    if (strcmp(upper_symbol, "OR") == 0) {
        return OR;
    }
    if (strcmp(upper_symbol, "NOT") == 0) {
        return NOT;

    }
    if (strcmp(upper_symbol, "XOR") == 0) {
        return XOR;
    }
    if (strcmp(upper_symbol, "SLL") == 0) {
        return SLL;
    }
    if (strcmp(upper_symbol, "SRL") == 0) {
        return SRL;
    }
    if (strcmp(upper_symbol, "LBL") == 0) {
        return LBL;
    }
    if (strcmp(upper_symbol, "GOTO") == 0) {
        return GOTO;
    }
    if (strcmp(upper_symbol, "GEQ") == 0) {
        return GEQ;
    }
    if (strcmp(upper_symbol, "GNQ") == 0) {
        return GNQ;
    }
    if (strcmp(upper_symbol, "PRINT") == 0) {
        return PRINT;
    }
    if (strcmp(upper_symbol, "PRINTLN") == 0) {
        return PRINTLN;
    }
    if (strcmp(upper_symbol, "HALT") == 0) {
        return HALT;
    }
    if (strcmp(upper_symbol, "INPUT") == 0) {
        return INPUT;
    }

    return -1L;


}

struct TokenNode *lexer(char **lines, int num_lines, int *num_nodes) {
    printf("[Lexer] Lexing started...\n");
    struct TokenNode *tokens;
    struct TokenNode *head;

    int token_index = 0;

    *num_nodes = 0;
    for (int i = 0; i < num_lines; i++) {
        char *line = lines[i];
        printf("---%d\n", strlen(line));
        char *stripped_line = strip(line);

        int length = strlen(stripped_line);
        if (length <= 0) {
            continue;
        } else if (length == 1 && stripped_line[0] == '\0' || stripped_line[0] == '\n') {
//            printf("---Skipping line %d because of emptyness\n", i);
            continue;
        } else if (length > 1 && stripped_line[0] == '#') {
            continue;
        }

        int index = 0;
        while (index > -1 && index < length) {
            struct Token *token = malloc(sizeof(struct Token));
            index = parse_line(line, i, token, index);
            if (tokens == NULL) {
                tokens = malloc(sizeof(struct TokenNode));
                tokens->prev = NULL;
                tokens->next = NULL;
                tokens->token = token;
                head = tokens;

            } else {
                struct TokenNode *node = malloc(sizeof(struct TokenNode));
                node->token = token;
                node->prev = tokens;
                tokens->next = node;
                tokens = node;
            }
            token_index++;
            (*num_nodes)++;

        }
        struct Token *token = malloc(sizeof(struct Token));
        token->type = END_STATEMENT;
        token->line = i;
        token->pos = length - 1;
        token->symbol = "ENDS";

        struct TokenNode *node = malloc(sizeof(struct TokenNode));
        node->token = token;
        node->prev = tokens;
        tokens->next = node;
        tokens = node;
        token_index++;
        (*num_nodes)++;
    }

    printf("[Lexer] Lexing Finished\n");
    return head;
}

struct SyntaxTreeNode *
get_child_syntax_node_corresponding_to_token(struct TokenNode *token_node, struct SyntaxTreeNode *tree) {

    for (int i = 0; i < MAX_SYNTAX_TREE_CHILDREN; ++i) {
        if (tree->children[i] == NULL) {
            continue;
        } else if ((token_node->token->type == DECIMAL || token_node->token->type == HEXIDECIMAL) &&
                   (tree->children[i]->type == DECIMAL || tree->children[i]->type == HEXIDECIMAL)) {
            return tree->children[i];

        } else if (tree->children[i]->type == token_node->token->type) {
            return tree->children[i];
        }

    }
    return NULL;
}

int recursive_syntax_token_tree_check(struct TokenNode *finger, struct SyntaxTreeNode *tree) {

    struct SyntaxTreeNode *found_node = tree;
    struct SyntaxTreeNode *prev = NULL;
    while (finger->token->type != END_STATEMENT) {
        prev = found_node;
        found_node = get_child_syntax_node_corresponding_to_token(finger->next, found_node);
        if (found_node == NULL && finger->next->token->type != END_STATEMENT) {
            fprintf(stderr, "[ERROR] Unexpected token '%s' at line %d and pos %d\n", finger->next->token->symbol,
                    finger->next->token->line + 1, finger->next->token->pos + 1);
            return 1;
        } else if (found_node == NULL && finger->next->token->type == END_STATEMENT) {

            fprintf(stderr, "[ERROR] Expected a ");
            for (int i = 0; i < MAX_SYNTAX_TREE_CHILDREN; ++i) {
                if (prev->children[i] == NULL) {
                    continue;
                }
                fprintf(stderr, "%s ", get_token_type_from_int(prev->children[i]->type));
                if (i < MAX_SYNTAX_TREE_CHILDREN - 1 && prev->children[i + 1] != NULL) {
                    fprintf(stderr, "or ");
                }
            }
            fprintf(stderr, "at line %d and pos %d\n",
                    finger->token->line + 1,
                    finger->token->pos + strlen(finger->token->symbol));
            return 1;
        }


        finger = finger->next;

    }

    return 0;
}

int syntax_check(struct TokenNode *tokens, int num_nodes) {
    printf("[Lexer] Syntax Checking...\n");

    struct TokenNode *finger = tokens;
    int token_count = 0;


    while (token_count < num_nodes - 1) {
        if (finger->token->type == -1) {
            fprintf(stderr, "[ERROR] Unknown command '%s' at line %d.\n", finger->token->symbol,
                    finger->token->line + 1);
            return 1;
        } else if (finger->token->type == COMMAND) {
            struct SyntaxTreeNode tree = proper_syntax_tree[(int) get_opcode_for_symbol(finger->token->symbol)];
            int result = recursive_syntax_token_tree_check(finger, &tree);
            if (result != 0) {
                return result;
            }
        }

        finger = finger->next;
        token_count++;
    }
    printf("[Lexer] Syntax Check Finished...\n");

    return 0;
}

void compile_tokens(struct TokenNode *tokens, FILE *output, int num_nodes) {
    printf("[COMPILER] Compiling...\n");
    uint64_t code = 0;
    long argument_offset = 32L;
    struct TokenNode *finger = tokens;
    int token_count = 0;


    uint64_t codes[num_nodes];
    int code_count = 0;
    int directive_count = 0;
    char *directives[num_nodes];

    for (int i = 0; i < num_nodes; ++i) {
        directives[i] = "";
    }

    while (token_count < num_nodes - 1) {
        struct Token *token = finger->token;


        if (token->type == COMMAND) {
            uint64_t opcode = get_opcode_for_symbol(token->symbol);
            code |= ((opcode << (12 * 4)) & 0xFFFF000000000000L);

        } else if (token->type == END_STATEMENT) {
            codes[code_count] = code;
            argument_offset = 32L;
            code = 0;
            code_count++;

        } else if (token->type == REGISTER) {
            int len = strlen(token->symbol);
            char *reg = malloc(len - 1);
            strncpy(reg, &(token->symbol[1]), len - 1);
            int reg_index = atoi(reg);

            if (argument_offset == 32L) {
                code |= (((uint64_t) reg_index << (8 * 4)) & 0x0000FFFF00000000L);
            } else if (argument_offset == 16L) {
                code |= (((uint64_t) reg_index << (4 * 4)) & 0x000000007FFF0000L);
            } else {
                code |= (((uint64_t) reg_index << (0 * 4)) & 0x0000000000007FFFL);

            }
            argument_offset -= 16L;
        } else if (token->type == DECIMAL) {

            int immediate = atoi(token->symbol);

            if (argument_offset == 32L) {
                code |= (((uint64_t) immediate << (8 * 4)) & 0x0000FFFF00000000L);
            } else if (argument_offset == 16L) {
                code |= 0x0000000080000000L;
                code |= (((uint64_t) immediate << (4 * 4)) & 0x000000007FFF0000L);
            } else {
                code |= 0x0000000000008000L;
                code |= (((uint64_t) immediate << (0 * 4)) & 0x0000000000007FFFL);
            }
            argument_offset -= 16L;
        } else if (token->type == HEXIDECIMAL) {
            int immediate = strtol(token->symbol + 2, NULL, 16);

            if (argument_offset == 32L) {
                code |= (((uint64_t) immediate << (8 * 4)) & 0x0000FFFF00000000L);
            } else if (argument_offset == 16L) {
                code |= 0x0000000080000000L;
                code |= (((uint64_t) immediate << (4 * 4)) & 0x000000007FFF0000L);
            } else {
                code |= 0x0000000000008000L;
                code |= (((uint64_t) immediate << (0 * 4)) & 0x0000000000007FFFL);
            }
            argument_offset -= 16L;
        } else if (token->type == DIRECTIVE) {
            char *directive_str = malloc((strlen(token->symbol) - 2));
            strncpy(directive_str, &(token->symbol[1]), strlen(token->symbol) - 2);
            int directive_index = -1;
            directive_str[strlen(token->symbol) - 2] = '\0';

            for (int i = 0; i < directive_count; ++i) {
                if (strcmp(directives[i], directive_str) == 0) {
                    directive_index = i;
                }
            }

            if (directive_index < 0) {
                directives[directive_count] = directive_str;
                directive_index = directive_count;
                directive_count++;
            } else {
                directives[directive_index] = directive_str;
            }

            if (argument_offset == 32L) {
                code |= (((uint64_t) directive_index << (8 * 4)) & 0x0000FFFF00000000L);
            } else if (argument_offset == 16L) {
                code |= (((uint64_t) directive_index << (4 * 4)) & 0x000000007FFF0000L);
            } else {
                code |= (((uint64_t) directive_index << (0 * 4)) & 0x0000000000007FFFL);
            }

//            free(directive_str);

        }
        finger = finger->next;
        token_count++;
    }


    uint64_t section_separator = 0xFFFF0000FFFF0000L;
    fwrite(&section_separator, 1, sizeof(section_separator), output);
    uint64_t num_directives = (uint64_t) directive_count;
    fwrite(&num_directives, 1, sizeof(num_directives), output);
    char directive_separator = '\0';
    for (int i = 0; i < directive_count; ++i) {
        char *directive = directives[i];
        fwrite(directive, 1, strlen(directive), output);
        fwrite(&directive_separator, 1, sizeof(directive_separator), output);

    }
    section_separator = 0x0000FFFF0000FFFFL;
    fwrite(&section_separator, 1, sizeof(section_separator), output);

    for (int i = 0; i < code_count; ++i) {
        code = codes[i];
        fwrite(&code, 1, sizeof(code), output);
    }
    printf("[COMPILER] Compiled\n");

}


int main(int argc, char *argv[]) {
    int output_path_next = 0;
    char *output_path = "out.s";
    char *input_path = NULL;
    for (int i = 1; i < argc; ++i) {
        char *arg = argv[i];


        if (strcmp(arg, "-o") == 0) {
            output_path_next = 1;
            continue;
        } else if (output_path_next) {
            output_path = arg;
            output_path_next = 0;
            continue;
        } else {
            input_path = arg;
        }
    }

    if (input_path == NULL) {
        printf("Did not get SMBLY source file. Aborting!!!!");
        return 1;
    }

//    printf("Found Input path %s\n", input_path);
//    printf("Found Output path %s\n", output_path);

    FILE *fp = fopen(input_path, "r");
    if (fp == NULL) {
        printf("File %s cannot be read. Does it exist?\n", input_path);
        return 1;
    }

    // Count the number of lines in file fp and the length of the longest line
    int max_line_size = -1;
    int num_lines = 0;
    char ch;
    int line_size = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            num_lines++;
            if (line_size > max_line_size) {
                max_line_size = line_size;
            }
            line_size = 0;
        } else {
            line_size++;
        }
    }
    num_lines++;

    if (max_line_size < 0) {
        max_line_size = line_size + 1;
    }
    max_line_size++;
    printf("[READER] Num lines: %d\n", num_lines);
    printf("[READER] Max line size: %d\n", max_line_size);
    printf("[READER] Line size: %d\n", line_size);

    // Go back to beginning of the file
    fseek(fp, 0, SEEK_SET);

    // Create buffers for lines
    char *line = (char *) malloc(max_line_size);
    if (!line) {
        fprintf(stderr, "[ERROR] Could not allocate memory for line with size %d\n", max_line_size);
        exit(1);
    }

    char **lines = (char **) malloc(num_lines * sizeof(char *));
    if (!lines) {
        fprintf(stderr, "[ERROR] Could not allocate memory for lines with size %d\n", num_lines * sizeof(char *));
        exit(1);
    }
    for (int i = 0; i < 10; ++i) {
        lines[i] = (char *) malloc(max_line_size * sizeof(char));
    }
    // Read line by line
    int line_index = 0;
    while (fgets(line, max_line_size + 1, fp) != NULL) {


        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        printf("line: %d %s\n", strlen(line), line);

        char *copied_line = malloc(strlen(line) * sizeof(char));
        strncpy(copied_line, line, strlen(line));
        copied_line[strlen(line)] = '\0';

        lines[line_index] = copied_line;
//        printf("Got %d %s\n-------\n", strlen(copied_line), copied_line);
        line_index++;
    }
//    free(line);

//    printf("[READER]Last line %s\n",  lines[num_lines-1]);

    int num_nodes = 0;
    struct TokenNode *tokens = lexer(lines, num_lines, &num_nodes);
    int syntax_check_result = syntax_check(tokens, num_nodes);
    if (syntax_check_result != 0) {
        fprintf(stderr, "[STATUS] Building Failed\n");
        exit(syntax_check_result);
    }

    FILE *output_file;
    output_file = fopen(output_path, "wb");

    compile_tokens(tokens, output_file, num_nodes);
    fclose(output_file);

    return 0;
}

