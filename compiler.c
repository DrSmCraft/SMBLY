#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <stdint.h>

char *get_token_type_from_int(int type) {
    if (type == 1) {
        return "COMMAND";
    }
    if (type == 2) {
        return "REGISTER";
    }
    if (type == 3) {
        return "DECIMAL";
    }
    if (type == 4) {
        return "HEXIDECIMAL";
    }
    if (type == 5) {
        return "DIRECTIVE";
    }
    if (type == 9) {
        return "END STATEMENT";
    }
    return "UNKNOWN";
}

char *lstrip(char *string) {
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

int get_token_type(char *symbol) {
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
    if (strcmp(upper_symbol, "MULT") == 0) {
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

    if (upper_symbol[0] == '"') {
        int index = 1;
        if (upper_symbol[strlen(upper_symbol) - 1] != '"') {
            return -1;
        }
        return DIRECTIVE;
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
    while (line[index] != '\0' && line[index] != '\n') {
        while (line[index] != ' ' && line[index] != ',' && line[index] != '\0' && line[index] != '\n') {
            index++;
        }

        char *value = malloc(index - start_index);
        strncpy(value, &line[start_index], index - start_index);
        value[index - start_index] = '\0';


        while (isalnum(line[index]) == 0 && line[index] != '$' && line[index] != '"') {
            if (line[index] == '\0' || line[index] == '\n') {
                break;
            }
            index++;
        }

        token->symbol = value;
        token->line = line_number;
        token->pos = start_index;
        token->type = get_token_type(value);

//        if (token->type == -1) {
//            printf("[ERROR] Unknown command '%s' at line %d.\n", value, line_number + 1);
//            exit(1);
//        }
        return index;

    }
    return -1;

}

uint64_t get_opcode_for_symbol(char *symbol) {

    char *upper_symbol = strupr(symbol);

    if (strcmp(upper_symbol, "SR") == 0) {
        return 0L;
    }
    if (strcmp(upper_symbol, "ADD") == 0) {
        return 1L;
    }
    if (strcmp(upper_symbol, "SUB") == 0) {
        return 2L;
    }
    if (strcmp(upper_symbol, "MULT") == 0) {
        return 3L;
    }
    if (strcmp(upper_symbol, "DIV") == 0) {
        return 4L;
    }
    if (strcmp(upper_symbol, "MOD") == 0) {
        return 5L;
    }
    if (strcmp(upper_symbol, "EQ") == 0) {
        return 6L;
    }
    if (strcmp(upper_symbol, "NEQ") == 0) {
        return 7L;
    }
    if (strcmp(upper_symbol, "GT") == 0) {
        return 8L;
    }
    if (strcmp(upper_symbol, "GTE") == 0) {
        return 9L;
    }
    if (strcmp(upper_symbol, "LT") == 0) {
        return 10L;
    }
    if (strcmp(upper_symbol, "LTE") == 0) {
        return 11L;
    }
    if (strcmp(upper_symbol, "AND") == 0) {
        return 12L;
    }
    if (strcmp(upper_symbol, "OR") == 0) {
        return 13L;
    }
    if (strcmp(upper_symbol, "NOT") == 0) {
        return 14L;

    }
    if (strcmp(upper_symbol, "XOR") == 0) {
        return 15L;
    }
    if (strcmp(upper_symbol, "SLL") == 0) {
        return 16L;
    }
    if (strcmp(upper_symbol, "SRL") == 0) {
        return 17L;
    }
    if (strcmp(upper_symbol, "LBL") == 0) {
        return 18L;
    }
    if (strcmp(upper_symbol, "GOTO") == 0) {
        return 19L;
    }
    if (strcmp(upper_symbol, "GEQ") == 0) {
        return 20L;
    }
    if (strcmp(upper_symbol, "GNQ") == 0) {
        return 21L;
    }
    if (strcmp(upper_symbol, "PRINT") == 0) {
        return 22L;
    }
    if (strcmp(upper_symbol, "PRINTLN") == 0) {
        return 23L;
    }
    if (strcmp(upper_symbol, "HALT") == 0) {
        return 24L;
    }

    return -1L;


}

struct TokenNode *lexer(char **lines, int num_lines, int *num_nodes) {
    struct TokenNode *tokens;
    struct TokenNode *head;


    int token_index = 0;

    *num_nodes = 0;
    for (int i = 0; i < num_lines; i++) {
        char *line = lines[i];
        char *stripped_line = strip(line);

        int length = strlen(stripped_line);
        if (length <= 0) {
            continue;
        } else if (length == 1 && stripped_line[0] == '\0' || stripped_line[0] == '\n') {
            printf("---Skipping line %d because of emptyness\n", i);
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


    return head;
}

int syntax_check(struct TokenNode *tokens, int num_nodes) {
    struct TokenNode *finger = tokens;

    int token_count = 0;
    while (token_count < num_nodes - 1) {
        if (finger->token->type == -1) {
            printf("[ERROR] Unknown command '%s' at line %d.\n", finger->token->symbol, finger->token->line + 1);
            exit(1);
        }

        finger = finger->next;
        token_count++;
    }
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
        } else if (token->type == DIRECTIVE) {
            char *directive_str = malloc((strlen(token->symbol) - 2) * sizeof(char));
            strncpy(directive_str, &(token->symbol[1]), strlen(token->symbol) - 2);
            int directive_index = -1;

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
        printf("[ERROR] Could not allocate memory for line with size %d\n", max_line_size);
        exit(1);
    }

    char **lines = (char **) malloc(num_lines * sizeof(char *));
    if (!lines) {
        printf("[ERROR] Could not allocate memory for lines with size %d\n", num_lines * sizeof(char *));
        exit(1);
    }
    for (int i = 0; i < 10; ++i) {
        lines[i] = (char *) malloc(max_line_size * sizeof(char));
    }
    // Read line by line
    int line_index = 0;
    while (fgets(line, max_line_size + 1, fp) != NULL) {
//        int char_index;
//        for (char_index = 0; char_index <= max_line_size; ++char_index) {
////            if(line[char_index] == '\0' || line[char_index] == '\n'){
////                break;
////            }
//            // Copy each character into lines array
//            char c = line[char_index];
//            lines[line_index][char_index] = c;
////            printf("Copied %c into line %d index %d\n", line[char_index], line_index, char_index);
//
//        }

        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
//        printf("line: %d %s\n", strlen(line), line);

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
        exit(syntax_check_result);
    }

    FILE *output_file;
    output_file = fopen(output_path, "wb");

    compile_tokens(tokens, output_file, num_nodes);
    fclose(output_file);

    return 0;
}

