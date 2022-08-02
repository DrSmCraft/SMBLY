#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>

#define MAX_SYNTAX_TREE_CHILDREN 3
#define NUM_COMMANDS 26

char *strupr(char *input) {
    int length = strlen(input);
    for (int i = 0; i < length; ++i) {
        toupper(input[i]);
    }
    return input;
}

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

struct SyntaxTreeNode proper_syntax_tree[NUM_COMMANDS] = {
        { /* SR */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={

                        &(struct SyntaxTreeNode) {.type=DECIMAL, .children={

                                &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},

                        &(struct SyntaxTreeNode) {.type=REGISTER, .children={

                                &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}}

                }},
                &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL},
                NULL}
        },
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
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                &(struct SyntaxTreeNode) {.type=DIRECTIVE, .children={
                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                NULL}
        },
        { /* PRINTLN */
                .type = COMMAND, .children =  {
                &(struct SyntaxTreeNode) {.type=REGISTER, .children={
                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                &(struct SyntaxTreeNode) {.type=DIRECTIVE, .children={
                        &(struct SyntaxTreeNode) {.type=END_STATEMENT, .children=NULL}}},
                NULL}
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

int silent_mode = 0;
int verbose_mode = 0;


char *output_path = "out.s";
char *input_path = NULL;


char *get_symbol_for_opcode(int opcode) {
    if (opcode == 0) {
        return "SR";
    } else if (opcode == 1) {
        return "ADD";
    } else if (opcode == 2) {
        return "SUB";
    } else if (opcode == 3) {
        return "MUL";
    } else if (opcode == 4) {
        return "DIV";
    } else if (opcode == 5) {
        return "MOD";
    } else if (opcode == 6) {
        return "EQ";
    } else if (opcode == 7) {
        return "NEQ";
    } else if (opcode == 8) {
        return "GT";
    } else if (opcode == 9) {
        return "GTE";
    } else if (opcode == 10) {
        return "LT";
    } else if (opcode == 11) {
        return "LTE";
    } else if (opcode == 12) {
        return "AND";
    } else if (opcode == 13) {
        return "OR";
    } else if (opcode == 14) {
        return "NOT";
    } else if (opcode == 15) {
        return "XOR";
    } else if (opcode == 16) {
        return "SLL";
    } else if (opcode == 17) {
        return "SRL";
    } else if (opcode == 18) {
        return "LBL";
    } else if (opcode == 19) {
        return "GOTO";
    } else if (opcode == 20) {
        return "GEQ";
    } else if (opcode == 21) {
        return "GNQ";
    } else if (opcode == 22) {
        return "PRINT";
    } else if (opcode == 23) {
        return "PRINTLN";
    } else if (opcode == 24) {
        return "HALT";
    } else if (opcode == 25) {
        return "INPUT";
    }

    return NULL;
}


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
    if (length <= 0) {
        return "";
    }
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
    if (length <= 0) {
        return "";
    }
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
    if (strlen(string) <= 0) {
        return "";
    }
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
    if (strcmp(upper_symbol, "INPUT") == 0) {
        return COMMAND;
    }
    if (upper_symbol[0] == '$') {
        int index = 1;
        while (index < strlen(upper_symbol)) {

            if (isdigit(upper_symbol[index]) <= 0) {
                return -1;
            }
            index++;
        }
        return REGISTER;
    }
    if (upper_symbol[0] == '0' && upper_symbol[1] == 'X') {
        return HEXIDECIMAL;
    }

    if (isdigit(upper_symbol[0]) > 0) {
        int index = 1;
        while (index < strlen(upper_symbol)) {
            if (isdigit(upper_symbol[index]) <= 0) {
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

    if (line[index] == ';') {
        token->type = END_STATEMENT;
        token->symbol = ";";
        token->line = line_number;
        token->pos = start_index;
        if (verbose_mode)
            printf("[LEXER] Read Token %s, classifying it as a %s\n", ";",
                   get_token_type_from_int(END_STATEMENT));
        while (isalnum(line[index]) == 0 && line[index] != '$' && line[index] != '"') {
            if (line[index] == '\0' || line[index] == '\n' || line[index] == '#' || line[index] == ';') {
                break;
            }
            index++;
        }
        return index + 1;
    }
    // While the whole line is not processed
    while (line[index] != '\0' && line[index] != '\n') {
        if (line[index] == '"') {
            // If the first character is quotes, then find the ending quote
            index++;
            while (line[index] != '"') {
                index++;
            }
            index++;
        } else if (line[index] == '#') {
            // If the line has hashtag (#), then ignore the rest of the line
            if (verbose_mode)
                printf("[LEXER] Ignoring line %d at position %d because of a inline comment\n", line_number + 1,
                       index + 1);
            return -1;
        } else {
            // Find the beginning of the next token
            while (line[index] != ' ' && line[index] != ',' && line[index] != '\0' && line[index] != '\n' &&
                   line[index] != ';') {
                index++;
            }
        }

        // Copy the string section from start index to the index
        char *value = malloc(index - start_index);
        strncpy(value, &line[start_index], index - start_index);
        value[index - start_index] = '\0';

        // Find the beginning of the next token
        while (isalnum(line[index]) == 0 && line[index] != '$' && line[index] != '"') {
            if (line[index] == '\0' || line[index] == '\n' || line[index] == '#' || line[index] == ';') {
                break;
            }
            index++;
        }

        // Store data in token structure
        token->type = get_token_type(value);
        token->symbol = value;
        token->line = line_number;
        token->pos = start_index;
        if (verbose_mode)
            printf("[LEXER] Read Token %s, classifying it as a %s\n", value,
                   get_token_type_from_int(get_token_type(value)));
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
    if (!silent_mode)
        printf("[LEXER] Lexing started...\n");
    struct TokenNode *tokens = NULL;
    struct TokenNode *head = NULL;

    int token_index = 0;

    *num_nodes = 0;
    for (int i = 0; i < num_lines; i++) {
        char *line = lines[i];
        char *stripped_line = strip(line);

        int length = strlen(stripped_line);
        if (length <= 0) {
            continue;
        } else if (length == 1 && stripped_line[0] == '\0' || stripped_line[0] == '\n') {
            if (verbose_mode)
                printf("[LEXER] Skipping line %d because of emptyness\n", i + 1);
            continue;
        } else if (length > 1 && stripped_line[0] == '#') {
            if (verbose_mode)
                printf("[LEXER] Skipping line %d because of comment\n", i + 1);
            continue;
        }

        int index = 0;
        if (verbose_mode)
            printf("[LEXER] Parsing line %d\n", i + 1);

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
                if (index > -1) {
                    struct TokenNode *node = malloc(sizeof(struct TokenNode));
                    node->token = token;
                    node->prev = tokens;
                    tokens->next = node;
                    tokens = node;
                }
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

    if (!silent_mode)
        printf("[LEXER] Lexing Finished\n");
    return head;
}

struct SyntaxTreeNode *
get_child_syntax_node_corresponding_to_token(struct TokenNode *token_node, struct SyntaxTreeNode *tree) {

    if (tree == NULL) {
        return NULL;
    }
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

int iterative_syntax_token_tree_check(struct TokenNode *finger, struct SyntaxTreeNode *tree) {
    int syntax_check_result = 0;
    struct SyntaxTreeNode *found_node = tree;
    struct SyntaxTreeNode *prev = NULL;
    while (finger->token->type != END_STATEMENT) {
        prev = found_node;
        found_node = get_child_syntax_node_corresponding_to_token(finger->next, found_node);
        if (found_node == NULL && finger->next->token->type != END_STATEMENT) {
            if (!silent_mode) {
                printf("[ERROR] File %s:%d:%d\n\t\t\tUnexpected token '%s' at line %d and pos %d\n",
                       input_path, finger->next->token->line + 1, finger->next->token->pos + 1,
                       finger->next->token->symbol,
                       finger->next->token->line + 1, finger->next->token->pos + 1);
            }
            syntax_check_result = 1;
        } else if (found_node == NULL && finger->next->token->type == END_STATEMENT) {
            if (!silent_mode && prev != NULL) {

                printf("[ERROR] File %s:%d:%d\n\t\t\tExpected a ", input_path, finger->next->token->line + 1,
                       finger->next->token->pos + 1);
                for (int i = 0; i < MAX_SYNTAX_TREE_CHILDREN; ++i) {
                    if (prev->children[i] == NULL) {
                        continue;
                    }
                    printf("%s ", get_token_type_from_int(prev->children[i]->type));
                    if (i < MAX_SYNTAX_TREE_CHILDREN - 1 && prev->children[i + 1] != NULL) {
                        printf("or ");
                    }
                }

                printf("at line %d and pos %d\n",
                       finger->token->line + 1,
                       finger->token->pos + strlen(finger->token->symbol));
            }
            syntax_check_result = 1;
        }


        finger = finger->next;

    }

    return syntax_check_result;
}

int syntax_check(struct TokenNode *tokens, int num_nodes) {
    int syntax_check_result = 0;
    if (!silent_mode)
        printf("[LEXER] Syntax Checking...\n");

    struct TokenNode *finger = tokens;
    int token_count = 0;


    while (token_count < num_nodes - 1) {
        if (finger->token->type == -1) {
            if (!silent_mode)
                printf("[ERROR] Unknown command '%s' at line %d.\n", finger->token->symbol,
                       finger->token->line + 1);
            syntax_check_result = 1;
        } else if (finger->token->type == COMMAND) {
            struct SyntaxTreeNode tree = proper_syntax_tree[(int) get_opcode_for_symbol(finger->token->symbol)];
            if (verbose_mode)
                printf("[LEXER] Running Syntax Check for command %s at line %d\n", finger->token->symbol,
                       finger->token->line + 1);
            int result = iterative_syntax_token_tree_check(finger, &tree);
            if (result != 0) {
                syntax_check_result = result;
            }
        }

        finger = finger->next;
        token_count++;
    }
    if (!silent_mode)

        printf("[LEXER] Syntax Check Finished...\n");

    return syntax_check_result;
}

void compile_tokens(struct TokenNode *tokens, FILE *output, int num_nodes) {
    if (!silent_mode)
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

    while (token_count < num_nodes) {
        struct Token *token = finger->token;


        if (token->type == COMMAND) {
            printf("Compiling %s\n", token->symbol);
            uint64_t opcode = get_opcode_for_symbol(token->symbol);
            code |= ((opcode << (12 * 4)) & 0xFFFF000000000000L);

        } else if (token->type == END_STATEMENT) {
            printf("ENDING\n");

            codes[code_count] = code;
            argument_offset = 32L;
            code = 0;
            code_count++;


        } else if (token->type == REGISTER) {
            printf("Compiling %s\n", token->symbol);
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
            printf("Compiling %s\n", token->symbol);

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
                code |= 0x0000000080000000L;
            } else if (argument_offset == 16L) {
                code |= 0x0000000080000000L;
                code |= (((uint64_t) directive_index << (4 * 4)) & 0x000000007FFF0000L);
            } else {
                code |= 0x0000000000008000L;
                code |= (((uint64_t) directive_index << (0 * 4)) & 0x0000000000007FFFL);
            }
            argument_offset -= 16L;

//            free(directive_str);

        }
        finger = finger->next;
        token_count++;
    }


    uint64_t section_separator = 0xFFFF0000FFFF0000L;
    fwrite(&section_separator, 1, sizeof(section_separator), output);
    uint64_t num_directives = (uint64_t) directive_count;
    if (verbose_mode)
        printf("[COMPILER] Starting directive section...\n");
    fwrite(&num_directives, 1, sizeof(num_directives), output);
    char directive_separator = '\0';
    for (int i = 0; i < directive_count; ++i) {
        char *directive = directives[i];
        if (verbose_mode)
            printf("[COMPILER] Writing directive %s to file\n", directive);
        fwrite(directive, 1, strlen(directive), output);
        fwrite(&directive_separator, 1, sizeof(directive_separator), output);

    }
    if (verbose_mode) {
        printf("[COMPILER] Finished directive section\n");
        printf("[COMPILER] Starting codes section with %d codes...\n", code_count);
    }
    section_separator = 0x0000FFFF0000FFFFL;
    fwrite(&section_separator, 1, sizeof(section_separator), output);

    for (int i = 0; i < code_count; ++i) {
        code = codes[i];
        if (verbose_mode)
            printf("[COMPILER] Writing code %lu to file\n", code);
        fwrite(&code, 1, sizeof(code), output);
    }
    if (verbose_mode)
        printf("[COMPILER] Finished codes section\n");
    if (!silent_mode)

        printf("[COMPILER] Compiled\n");

}

void print_single_rule(struct SyntaxTreeNode node, int num_indents) {

    for (int i = 0; i < num_indents; ++i) {
        printf("\t");
    }
    printf("{\n");
    for (int i = 0; i < num_indents + 1; ++i) {
        printf("\t");
    }
    printf("\"type\": \"%s\"", get_token_type_from_int(node.type));
    if (node.type != END_STATEMENT) {
        printf(",\n");
        for (int i = 0; i < num_indents + 1; ++i) {
            printf("\t");
        }
    } else {
        printf("\n");
    }


    if (node.type != END_STATEMENT) {
        printf("\"syntax\": [\n", get_token_type_from_int(node.type));
        for (int child_index = 0; child_index < MAX_SYNTAX_TREE_CHILDREN; ++child_index) {
            if (node.children[child_index] == NULL) {
                continue;
            }
            print_single_rule(*node.children[child_index], num_indents + 2);
            for (int i = 0; i < num_indents + 1; ++i) {
                printf("\t");
            }
            printf(",\n");
        }
        for (int i = 0; i < num_indents + 1; ++i) {
            printf("\t");
        }
        printf("]\n");
    }

    for (int i = 0; i < num_indents; ++i) {
        printf("\t");
    }
    printf("}\n");
}

void print_syntax_rules() {


    printf("{\n");
    for (int i = 0; i < NUM_COMMANDS; ++i) {
        struct SyntaxTreeNode node = proper_syntax_tree[i];
        char *name = get_symbol_for_opcode(i);
        printf("\t\"%s\": {\n", name);
        printf("\t\t\"opcode\" : %d,\n", i);
        printf("\t\t\"syntax\" : [\n");
        print_single_rule(node, 2);
        printf("\t\t\t\t]\n");

        if (i < NUM_COMMANDS - 1) {
            printf("\t\t},\n");
        } else {
            printf("\t\t}\n");

        }
    }
    printf("}\n");

}

int main(int argc, char *argv[]) {
    int output_path_next = 0;

    for (int i = 1; i < argc; ++i) {
        char *arg = argv[i];
        if (strcmp(arg, "-o") == 0 || strcmp(arg, "--output") == 0) {
            output_path_next = 1;
            continue;
        } else if (output_path_next) {
            output_path = arg;
            output_path_next = 0;
            continue;
        } else if (strcmp(arg, "-h") == 0 || strcmp(arg, "-?") == 0 || strcmp(arg, "--help") == 0) {
            printf("  ____  __  __ ____  _  __   __   ____                      _ _           \n"
                   " / ___||  \\/  | __ )| | \\ \\ / /  / ___|___  _ __ ___  _ __ (_) | ___ _ __ \n"
                   " \\___ \\| |\\/| |  _ \\| |  \\ V /  | |   / _ \\| '_ ` _ \\| '_ \\| | |/ _ \\ '__|\n"
                   "  ___) | |  | | |_) | |___| |   | |__| (_) | | | | | | |_) | | |  __/ |   \n"
                   " |____/|_|  |_|____/|_____|_|    \\____\\___/|_| |_| |_| .__/|_|_|\\___|_|   \n"
                   "                                                     |_|                  \n");
            printf("Usage: SMBLY-C inputFile [options]\n\n");
            printf("Options:\n");
            printf("-h, --help\t\t\t\tShow this help message\n");
            printf("-o outputFile,\t\t\tStore the compiled code in the given file\n");
            printf("\t--output outputFile\n");
            printf("-s, --silent\t\t\tDo not show any messages from the compiler\n");
            printf("-v, --verbose\t\t\tShow all messages from the compiler\n");

            return 0;
        } else if (strcmp(arg, "-s") == 0 || strcmp(arg, "--silent") == 0) {
            silent_mode = 1;
        } else if (strcmp(arg, "-v") == 0 || strcmp(arg, "--verbose") == 0) {
            verbose_mode = 1;
        } else if (strcmp(arg, "--syntax-rules") == 0) {
            print_syntax_rules();
            return 0;
        } else {
            input_path = arg;
        }
    }

    if (input_path == NULL) {
        if (!silent_mode)
            printf("Did not get SMBLY source file. Aborting!!!!");
        return 1;
    }

//    printf("Found Input path %s\n", input_path);
//    printf("Found Output path %s\n", output_path);

    FILE *fp = fopen(input_path, "r");
    if (fp == NULL) {
        if (!silent_mode)
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

    if (max_line_size < 0 || max_line_size < line_size) {
        max_line_size = line_size;
    }
    max_line_size++;
    if (!silent_mode && verbose_mode) {
        printf("[READER] Num lines: %d\n", num_lines);
        printf("[READER] Max line size: %d\n", max_line_size);
        printf("[READER] Line size: %d\n", line_size);
    }
// Go back to beginning of the file
    fseek(fp,
          0, SEEK_SET);

// Create buffers for lines
    char *line = (char *) malloc(max_line_size);
    if (!line) {
        if (!silent_mode)

            printf("[ERROR] Could not allocate memory for line with size %d\n", max_line_size);
        exit(1);
    }

    char *lines[num_lines];
    if (!lines) {
        if (!silent_mode)

            printf("[ERROR] Could not allocate memory for lines with size %d\n", num_lines * sizeof(char *));
        return 1;
    }
    for (int i = 0; i < num_lines; ++i) {
        lines[i] = (char *) malloc(max_line_size * sizeof(char));
        lines[i][0] = '\0';
    }
    // Read line by line
    int line_index = 0;
    while (fgets(line, max_line_size + 1, fp) != NULL) {

        int length = strlen(line);

        if (line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        char *copied_line = malloc(length * sizeof(char));
        strncpy(copied_line, line, length);
        copied_line[length] = '\0';

        lines[line_index] = copied_line;
        line_index++;
    }

//    free(line);


    int num_nodes = 0;
    struct TokenNode *tokens = lexer(lines, num_lines, &num_nodes);
    int syntax_check_result = syntax_check(tokens, num_nodes);
    if (syntax_check_result != 0) {
        if (!silent_mode)

            fprintf(stderr, "[STATUS] Building Failed\n");
        exit(syntax_check_result);
    }

    FILE *output_file;
    output_file = fopen(output_path, "wb");

    compile_tokens(tokens, output_file, num_nodes);
    fclose(output_file);

    return 0;
}

