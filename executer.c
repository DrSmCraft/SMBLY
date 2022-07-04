#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <stdint.h>

uint64_t num_directives = 0;

int registers[100];
int instruction_index = 0;
char **directives = NULL;
int *label_instruction_pos = NULL;
char *input_path = NULL;
int silent_mode = 0;
int verbose_mode = 0;

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

int execute_SR(int *registers, int out_reg, int first_operand, int first_immediate) {
    if (first_immediate > 0) {
        registers[out_reg] = first_operand;
    } else {
        registers[out_reg] = registers[first_operand];
    }
    return 0;
}

int execute_ADD(int *registers, int out_reg, int first_operand, int second_operand, int first_immediate,
                int second_immediate) {
    int result = 0;
    if (first_immediate > 0) {
        result = first_operand;
    } else {
        result = registers[first_operand];
    }

    if (second_immediate > 0) {
        result += second_operand;
    } else {
        result += registers[second_operand];
    }

    registers[out_reg] = result;
    return 0;
}


int execute_SUB(int *registers, int out_reg, int first_operand, int second_operand, int first_immediate,
                int second_immediate) {
    int result = 0;
    if (first_immediate > 0) {
        result = first_operand;
    } else {
        result = registers[first_operand];
    }

    if (second_immediate > 0) {
        result -= second_operand;
    } else {
        result -= registers[second_operand];
    }

    registers[out_reg] = result;
    return 0;
}


int execute_MUL(int *registers, int out_reg, int first_operand, int second_operand, int first_immediate,
                int second_immediate) {
    int result = 0;
    if (first_immediate > 0) {
        result = first_operand;
    } else {
        result = registers[first_operand];
    }

    if (second_immediate > 0) {
        result *= second_operand;
    } else {
        result *= registers[second_operand];
    }

    registers[out_reg] = result;
    return 0;
}

int execute_DIV(int *registers, int out_reg, int first_operand, int second_operand, int first_immediate,
                int second_immediate) {
    int result = 0;
    if (first_immediate > 0) {
        result = first_operand;
    } else {
        result = registers[first_operand];
    }

    if (second_immediate > 0) {
        result /= second_operand;
    } else {
        result /= registers[second_operand];
    }

    registers[out_reg] = result;
    return 0;
}

int execute_MOD(int *registers, int out_reg, int first_operand, int second_operand, int first_immediate,
                int second_immediate) {
    int result = 0;
    if (first_immediate > 0) {
        result = first_operand;
    } else {
        result = registers[first_operand];
    }

    if (second_immediate > 0) {
        result %= second_operand;
    } else {
        result %= registers[second_operand];
    }

    registers[out_reg] = result;
    return 0;
}


int execute_EQ(int *registers, int out_reg, int first_operand, int second_operand, int first_immediate,
               int second_immediate) {
    int val1 = 0;
    int val2 = 0;

    if (first_immediate > 0) {
        val1 = first_operand;
    } else {
        val1 = registers[first_operand];
    }

    if (second_immediate > 0) {
        val2 = second_operand;
    } else {
        val2 = registers[second_operand];
    }

    registers[out_reg] = val1 == val2;
    return 0;
}

int execute_NEQ(int *registers, int out_reg, int first_operand, int second_operand, int first_immediate,
                int second_immediate) {
    int val1 = 0;
    int val2 = 0;

    if (first_immediate > 0) {
        val1 = first_operand;
    } else {
        val1 = registers[first_operand];
    }

    if (second_immediate > 0) {
        val2 = second_operand;
    } else {
        val2 = registers[second_operand];
    }

    registers[out_reg] = val1 != val2;
    return 0;
}

int execute_GT(int *registers, int out_reg, int first_operand, int second_operand, int first_immediate,
               int second_immediate) {
    int val1 = 0;
    int val2 = 0;

    if (first_immediate > 0) {
        val1 = first_operand;
    } else {
        val1 = registers[first_operand];
    }

    if (second_immediate > 0) {
        val2 = second_operand;
    } else {
        val2 = registers[second_operand];
    }

    registers[out_reg] = val1 > val2;
    return 0;
}

int execute_GTE(int *registers, int out_reg, int first_operand, int second_operand, int first_immediate,
                int second_immediate) {
    int val1 = 0;
    int val2 = 0;

    if (first_immediate > 0) {
        val1 = first_operand;
    } else {
        val1 = registers[first_operand];
    }

    if (second_immediate > 0) {
        val2 = second_operand;
    } else {
        val2 = registers[second_operand];
    }

    registers[out_reg] = val1 >= val2;
    return 0;
}


int execute_LT(int *registers, int out_reg, int first_operand, int second_operand, int first_immediate,
               int second_immediate) {
    int val1 = 0;
    int val2 = 0;

    if (first_immediate > 0) {
        val1 = first_operand;
    } else {
        val1 = registers[first_operand];
    }

    if (second_immediate > 0) {
        val2 = second_operand;
    } else {
        val2 = registers[second_operand];
    }

    registers[out_reg] = val1 < val2;
    return 0;
}

int execute_LTE(int *registers, int out_reg, int first_operand, int second_operand, int first_immediate,
                int second_immediate) {
    int val1 = 0;
    int val2 = 0;

    if (first_immediate > 0) {
        val1 = first_operand;
    } else {
        val1 = registers[first_operand];
    }

    if (second_immediate > 0) {
        val2 = second_operand;
    } else {
        val2 = registers[second_operand];
    }

    registers[out_reg] = val1 <= val2;
    return 0;
}


int execute_AND(int *registers, int out_reg, int first_operand, int second_operand, int first_immediate,
                int second_immediate) {
    int val1 = 0;
    int val2 = 0;

    if (first_immediate > 0) {
        val1 = first_operand;
    } else {
        val1 = registers[first_operand];
    }

    if (second_immediate > 0) {
        val2 = second_operand;
    } else {
        val2 = registers[second_operand];
    }

    registers[out_reg] = val1 & val2;
    return 0;
}

int execute_OR(int *registers, int out_reg, int first_operand, int second_operand, int first_immediate,
               int second_immediate) {
    int val1 = 0;
    int val2 = 0;

    if (first_immediate > 0) {
        val1 = first_operand;
    } else {
        val1 = registers[first_operand];
    }

    if (second_immediate > 0) {
        val2 = second_operand;
    } else {
        val2 = registers[second_operand];
    }

    registers[out_reg] = val1 | val2;
    return 0;
}

int execute_NOT(int *registers, int out_reg, int first_operand, int first_immediate) {
    int val1 = 0;

    if (first_immediate > 0) {
        val1 = first_operand;
    } else {
        val1 = registers[first_operand];
    }


    registers[out_reg] = ~val1;
    return 0;
}

int execute_XOR(int *registers, int out_reg, int first_operand, int second_operand, int first_immediate,
                int second_immediate) {
    int val1 = 0;
    int val2 = 0;

    if (first_immediate > 0) {
        val1 = first_operand;
    } else {
        val1 = registers[first_operand];
    }

    if (second_immediate > 0) {
        val2 = second_operand;
    } else {
        val2 = registers[second_operand];
    }

    registers[out_reg] = val1 ^ val2;
    return 0;
}

int execute_SLL(int *registers, int out_reg, int first_operand, int second_operand, int first_immediate,
                int second_immediate) {
    int val1 = 0;
    int val2 = 0;

    if (first_immediate > 0) {
        val1 = first_operand;
    } else {
        val1 = registers[first_operand];
    }

    if (second_immediate > 0) {
        val2 = second_operand;
    } else {
        val2 = registers[second_operand];
    }

    registers[out_reg] = val1 << val2;
    return 0;
}

int execute_SRL(int *registers, int out_reg, int first_operand, int second_operand, int first_immediate,
                int second_immediate) {
    int val1 = 0;
    int val2 = 0;

    if (first_immediate > 0) {
        val1 = first_operand;
    } else {
        val1 = registers[first_operand];
    }

    if (second_immediate > 0) {
        val2 = second_operand;
    } else {
        val2 = registers[second_operand];
    }

    registers[out_reg] = val1 >> val2;
    return 0;
}

int execute_LBL(int *registers, int directive_index) {
    char *directive = directives[directive_index];
    int success = 0;
    for (int i = 0; i < num_directives; ++i) {
        if (strcmp(directives[i], directive) == 0) {
            label_instruction_pos[i] = instruction_index;
            success = 1;
        }
    }
    if (success < 1) {
        return -1;
    }

    return 0;
}


int execute_GOTO(int *registers, int directive_index) {
    char *directive = directives[directive_index];
    int success = 0;
    for (int i = 0; i < num_directives; ++i) {
        if (strcmp(directives[i], directive) == 0) {
            int new_instruction_index = label_instruction_pos[i];
            instruction_index = new_instruction_index;
            success = 1;
        }
    }
    if (success < 1) {
        return -1;
    }

    return 1;
}


int execute_GEQ(int *registers, int out_reg, int second_operand, int second_immediate, int directive_index) {
    int value1 = registers[out_reg];
    int value2 = 0;
    if (second_immediate) {
        value2 = second_operand;
    } else {
        value2 = registers[second_operand];
    }
    if (value1 == value2) {
        char *directive = directives[directive_index];
        int success = 0;
        for (int i = 0; i < num_directives; ++i) {
            if (strcmp(directives[i], directive) == 0) {
                int new_instruction_index = label_instruction_pos[i];
                instruction_index = new_instruction_index;
                success = 1;
            }
        }
        if (success < 1) {
            return -1;
        }
        return 1;
    }

    return 0;
}


int execute_GNQ(int *registers, int out_reg, int second_operand, int second_immediate, int directive_index) {
    int value1 = registers[out_reg];
    int value2 = 0;
    if (second_immediate) {
        value2 = second_operand;
    } else {
        value2 = registers[second_operand];
    }
    if (value1 != value2) {
        char *directive = directives[directive_index];
        int success = 0;
        for (int i = 0; i < num_directives; ++i) {
            if (strcmp(directives[i], directive) == 0) {
                int new_instruction_index = label_instruction_pos[i];
                instruction_index = new_instruction_index;
                success = 1;
            }
        }
        if (success < 1) {
            return -1;
        }


        return 1;
    }
    return 0;
}

int execute_PRINT(int *registers, int out_reg, int first_immediate) {
    if (first_immediate) {
        printf("%s", directives[out_reg]);

    } else {
        printf("%d", registers[out_reg]);
    }
    return 0;
}


int execute_PRINTLN(int *registers, int out_reg, int first_immediate) {
    if (first_immediate) {
        printf("%s\n", directives[out_reg]);

    } else {
        printf("%d\n", registers[out_reg]);
    }
    return 0;
}

int execute_INPUT(int *registers, int out_reg) {
    scanf("%d", &(registers[out_reg]));
    return 0;
}

int execute_HALT() {
    exit(0);
    return 0;
}

/**
 * Execute a line of code given the following parameters.
 * @param opcode The operation code of the command
 * @param out_reg The register the result will write to.
 *                  It could also be the first operand if the syntax requires it.
 *                  This  value must be a register index in ALL cases.
 * @param first_operand The first operand. Could be a register or an immediate.
 * @param second_operand The second operand. Could be a register or an immediate.
 * @param first_immediate Delineates if the first operand is a register or immediate.
 *                          If =0, then first operand is assumed to be a register.
 *                          If > 1, then first operand is assumed to be an immediate.
 * @param second_immediate Delineates if the second operand is a register or immediate.
 *                          If =0, then second operand is assumed to be a register.
 *                          If > 1, then second operand is assumed to be an immediate.
 * @return Executed line status.
 *          -1 means there is a runtime error
 *          0 means the line was run successfully
 *          1 means a jump is needed
 */
int execute_line(int opcode, int out_reg, int first_operand, int second_operand, int first_immediate,
                 int second_immediate) {


    if (opcode == 0) {
        return execute_SR(registers, out_reg, first_operand, first_immediate);
    } else if (opcode == 1) {
        return execute_ADD(registers, out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 2) {
        return execute_SUB(registers, out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 3) {
        return execute_MUL(registers, out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 4) {
        return execute_DIV(registers, out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 5) {
        return execute_MOD(registers, out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 6) {
        return execute_EQ(registers, out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 7) {
        return execute_NEQ(registers, out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 8) {
        return execute_GT(registers, out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 9) {
        return execute_GTE(registers, out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 10) {
        return execute_LT(registers, out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 11) {
        return execute_LTE(registers, out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 12) {
        return execute_AND(registers, out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 13) {
        return execute_OR(registers, out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 14) {
        return execute_NOT(registers, out_reg, first_operand, first_immediate);
    } else if (opcode == 15) {
        return execute_XOR(registers, out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 16) {
        return execute_SLL(registers, out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 17) {
        return execute_SRL(registers, out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 18) {
        return execute_LBL(registers, out_reg);
    } else if (opcode == 19) {
        return execute_GOTO(registers, out_reg);
    } else if (opcode == 20) {
//        return "GEQ";
        return execute_GEQ(registers, out_reg, first_operand, first_immediate, second_operand);
    } else if (opcode == 21) {
//        return "GNQ";
        return execute_GNQ(registers, out_reg, first_operand, first_immediate, second_operand);
    } else if (opcode == 22) {
        return execute_PRINT(registers, out_reg, first_immediate);
    } else if (opcode == 23) {
        return execute_PRINTLN(registers, out_reg, first_immediate);
    } else if (opcode == 24) {
        return execute_HALT();
    } else if (opcode == 25) {
        return execute_INPUT(registers, out_reg);
    }
    return -1;

}

void print_registers(int *registers) {

    for (int i = 0; i < 10; ++i) {
        printf("%d\t", registers[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        char *arg = argv[i];

        input_path = arg;

    }


    for (int i = 1; i < argc; ++i) {
        char *arg = argv[i];
        if (strcmp(arg, "-h") == 0 || strcmp(arg, "-?") == 0 || strcmp(arg, "--help") == 0) {
            printf("  _____  __  __  ____   _      __     __   _____                           _  _             \n"
                   " / ____||  \\/  ||  _ \\ | |     \\ \\   / /  / ____|                         (_)| |            \n"
                   "| (___  | \\  / || |_) || |      \\ \\_/ /  | |       ___   _ __ ___   _ __   _ | |  ___  _ __ \n"
                   " \\___ \\ | |\\/| ||  _ < | |       \\   /   | |      / _ \\ | '_ ` _ \\ | '_ \\ | || | / _ \\| '__|\n"
                   " ____) || |  | || |_) || |____    | |    | |____ | (_) || | | | | || |_) || || ||  __/| |   \n"
                   "|_____/ |_|  |_||____/ |______|   |_|     \\_____| \\___/ |_| |_| |_|| .__/ |_||_| \\___||_|   \n"
                   "                                                                   | |                      \n"
                   "                                                                   |_|                      \n");
            printf("Usage: SMBLY inputFile [options]\n\n");
            printf("Options:\n");
            printf("-h, --help\t\t\t\tShow this help message\n");
            printf("-s, --silent\t\t\tDo not show any messages from the compiler\n");
            printf("-v, --verbose\t\t\tShow all messages from the compiler\n");

            return 0;
        } else if (strcmp(arg, "-s") == 0 || strcmp(arg, "--silent") == 0) {
            silent_mode = 1;
        } else if (strcmp(arg, "-v") == 0 || strcmp(arg, "--verbose") == 0) {
            verbose_mode = 1;
        } else {
            input_path = arg;
        }
    }

    if (input_path == NULL) {
        printf("Did not get SMBLY source file. Aborting!!!!");
        return 1;
    }


    FILE *fp = fopen(input_path, "rb");
    if (fp == NULL) {
        printf("File %s cannot be read. Does it exist?\n", input_path);
        return 1;
    }

    // Registers
    for (int i = 0; i < 100; ++i) {
        registers[i] = 0;
    }


    uint64_t section_identifier = 0;

    while (fread(&section_identifier, 1, sizeof(section_identifier), fp) == 8) {


        if (section_identifier == 0xFFFF0000FFFF0000L) {
            // Directives section
            int result = fread(&num_directives, 1, sizeof(num_directives), fp);
            if (result != 8) {
                return 1;
            }
            directives = malloc(sizeof(char *) * num_directives);
            label_instruction_pos = malloc(sizeof(int) * num_directives);
            int max_line_size = 30;
            for (int directive_index = 0; directive_index < num_directives; ++directive_index) {
                char c;
                char *directive = (char *) malloc(max_line_size * sizeof(char));
                int i = 0;
                while ((c = getc(fp)) != '\0') {
                    directive[i] = c;
                    i++;
                }
                directive[i] = '\0';
                directives[directive_index] = directive;
            }


        } else if (section_identifier == 0x0000FFFF0000FFFFL) {
            // codes section
            if (directives == NULL) {
                return 1;
            }

            uint64_t code = 0;
            uint64_t file_code_section_offset;
            file_code_section_offset = ftell(fp);

            // First scan file for directives then execute instructions
            while (fread(&code, 1, sizeof(code), fp) == 8) {
                int opcode = ((code) & 0xFFFF000000000000L) >> 12 * 4;
                int out_reg = ((code) & 0x0000FFFF00000000L) >> 8 * 4;

                if (opcode == 18) {
                    // Processing a LBL, save the directive to directives array
                    execute_LBL(registers, out_reg);
                }
                instruction_index++;

            }

            fseek(fp, file_code_section_offset, SEEK_SET);
            instruction_index = 0;
            // Now, Read through the file and execute the commands
            while (fread(&code, 1, sizeof(code), fp) == 8) {
                int opcode = ((code) & 0xFFFF000000000000L) >> 12 * 4;
                int out_reg = ((code) & 0x0000FFFF00000000L) >> 8 * 4;
                int first_operand = ((code) & 0x000000007FFF0000L) >> 4 * 4;
                int second_operand = ((code) & 0x0000000000007FFFL) >> 0 * 4;

                int first_immediate = ((code) & 0x0000000080000000L) >> 31;
                int second_immediate = ((code) & 0x0000000000008000L) >> 15;


                instruction_index++;

                if (opcode == 18) {
                    // Ignore LBLs because they were already read in the first loop
                    continue;
                }
                int result = execute_line(opcode, out_reg, first_operand, second_operand, first_immediate,
                                          second_immediate);
                if (result == -1) {
                    //error
                    printf("[ERROR] Encountered Runtime Error");
                    exit(1);
                }
                if (result == 1) {
                    // Need to jump to a new instruction index (GOTO was processed)
                    fseek(fp, instruction_index * sizeof(code) + file_code_section_offset, SEEK_SET);
                }

            }


        } else {
            return 1;
        }
    }

    free(directives);
    free(label_instruction_pos);
    return 0;
}

