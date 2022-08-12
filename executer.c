/**
 * @name executer.c
 * @author DrSmCraft
 * @copyright (c) 2022 All Rights Reserved
 *
 * This file runs given compiled *.s files.
 */
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdint.h>

#define VERSION 1.0
#define NUM_REGISTERS 100

uint64_t num_labels = 0;
uint64_t num_directives = 0;

int registers[NUM_REGISTERS];
int instruction_index = 0;
char **labels = NULL;
char **directives_values = NULL;
char **directives_names = NULL;
int *label_instruction_pos = NULL;
char *input_path = NULL;
int silent_mode = 0;
int verbose_mode = 0;

/**
 * Get the string representation of the command.
 * @param opcode Integer that corresponds to the opcode of the command.
 * @return String that represents the command. If the opcode is invalid, NULL is returned.
 */
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

/**
 * Execute a SR (Set Register) command.
 * @param out_reg The index of the output register.
 * @param first_operand The value of the first operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception.
 */
int execute_SR(int out_reg, int first_operand, int first_immediate) {
    if (first_immediate > 0) {
        registers[out_reg] = first_operand;
    } else {
        registers[out_reg] = registers[first_operand];
    }
    return 0;
}

/**
 * Execute a ADD (ADDition) command.
 * @param out_reg  The index of the output register.
 * @param first_operand The value of the first operand.
 * @param second_operand The value of the second operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception.
 */
int execute_ADD(int out_reg, int first_operand, int second_operand, int first_immediate,
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

/**
 * Execute a SUB (SUBtract) command.
 * @param out_reg  The index of the output register.
 * @param first_operand The value of the first operand.
 * @param second_operand The value of the second operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception.
 */
int execute_SUB(int out_reg, int first_operand, int second_operand, int first_immediate,
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

/**
 * Execute a MUL (MULtiply) command.
 * @param out_reg  The index of the output register.
 * @param first_operand The value of the first operand.
 * @param second_operand The value of the second operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception.
 */
int execute_MUL(int out_reg, int first_operand, int second_operand, int first_immediate,
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

/**
 * Execute a DIV (DIVide) command.
 * @param out_reg  The index of the output register.
 * @param first_operand The value of the first operand.
 * @param second_operand The value of the second operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception. If a divide by zero is encountered, error message is printed and -1 is returned.
 */
int execute_DIV(int out_reg, int first_operand, int second_operand, int first_immediate,
                int second_immediate) {
    int result = 0;
    if (first_immediate > 0) {
        result = first_operand;
    } else {
        result = registers[first_operand];
    }
    int second_value = 0;
    if (second_immediate > 0) {
        second_value = second_operand;
    } else {
        second_value = registers[second_operand];
    }

    if (second_value == 0) {
        printf("[ERROR] Division by Zero Error\n");
        return -1;
    }
    result /= second_value;
    registers[out_reg] = result;
    return 0;
}

/**
 * Execute a MOD (MODulus) command.
 * @param out_reg  The index of the output register.
 * @param first_operand The value of the first operand.
 * @param second_operand The value of the second operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception. If a divide by zero is encountered, error message is printed and -1 is returned.
 */
int execute_MOD(int out_reg, int first_operand, int second_operand, int first_immediate,
                int second_immediate) {
    int result = 0;
    if (first_immediate > 0) {
        result = first_operand;
    } else {
        result = registers[first_operand];
    }

    int second_value = 0;
    if (second_immediate > 0) {
        second_value = second_operand;
    } else {
        second_value = registers[second_operand];
    }

    if (second_value == 0) {
        printf("[ERROR] Modulo by Zero Error\n");
        return -1;
    }
    result /= second_value;
    registers[out_reg] = result;
    return 0;
}

/**
 * Execute a EQ (EQuals) command.
 * @param out_reg  The index of the output register. If both operands are equal, then 1 is placed in the out_reg. Otherwise, 0 is placed in out_reg.
 * @param first_operand The value of the first operand.
 * @param second_operand The value of the second operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception.
 */
int execute_EQ(int out_reg, int first_operand, int second_operand, int first_immediate,
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

/**
 * Execute a NEQ (Not EQuals) command.
 * @param out_reg  The index of the output register. If operands are not equal, then 1 is placed in the out_reg. Otherwise, 0 is placed in out_reg.
 * @param first_operand The value of the first operand.
 * @param second_operand The value of the second operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception.
 */
int execute_NEQ(int out_reg, int first_operand, int second_operand, int first_immediate,
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

/**
 * Execute a GT (Greater Than) command.
 * @param out_reg  The index of the output register. If operand_one is greater than operand_2, then 1 is placed in the out_reg. Otherwise, 0 is placed in out_reg.
 * @param first_operand The value of the first operand.
 * @param second_operand The value of the second operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception.
 */
int execute_GT(int out_reg, int first_operand, int second_operand, int first_immediate,
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

/**
 * Execute a GTE (Greater Than or Equal) command.
 * @param out_reg  The index of the output register. If operand_one is greater than or equal to operand_2, then 1 is placed in the out_reg. Otherwise, 0 is placed in out_reg.
 * @param first_operand The value of the first operand.
 * @param second_operand The value of the second operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception.
 */
int execute_GTE(int out_reg, int first_operand, int second_operand, int first_immediate,
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

/**
 * Execute a LT (Less Than) command.
 * @param out_reg  The index of the output register. If operand_one is less than operand_2, then 1 is placed in the out_reg. Otherwise, 0 is placed in out_reg.
 * @param first_operand The value of the first operand.
 * @param second_operand The value of the second operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception.
 */
int execute_LT(int out_reg, int first_operand, int second_operand, int first_immediate,
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

/**
 * Execute a LTE (Less Than or Equal) command.
 * @param out_reg  The index of the output register. If operand_one is less than or equal to operand_2, then 1 is placed in the out_reg. Otherwise, 0 is placed in out_reg.
 * @param first_operand The value of the first operand.
 * @param second_operand The value of the second operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception.
 */
int execute_LTE(int out_reg, int first_operand, int second_operand, int first_immediate,
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

/**
 * Execute a AND (bitwise AND) command.
 * @param out_reg  The index of the output register.
 * @param first_operand The value of the first operand.
 * @param second_operand The value of the second operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception.
 */
int execute_AND(int out_reg, int first_operand, int second_operand, int first_immediate,
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

/**
 * Execute a OR (bitwise OR) command.
 * @param out_reg  The index of the output register.
 * @param first_operand The value of the first operand.
 * @param second_operand The value of the second operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception.
 */
int execute_OR(int out_reg, int first_operand, int second_operand, int first_immediate,
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

/**
 * Execute a NOT (bitwise NOT) command.
 * @param out_reg  The index of the output register.
 * @param first_operand The value of the first operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception.
 */
int execute_NOT(int out_reg, int first_operand, int first_immediate) {
    int val1 = 0;

    if (first_immediate > 0) {
        val1 = first_operand;
    } else {
        val1 = registers[first_operand];
    }


    registers[out_reg] = ~val1;
    return 0;
}

/**
 * Execute a XOR (bitwise XOR) command.
 * @param out_reg  The index of the output register.
 * @param first_operand The value of the first operand.
 * @param second_operand The value of the second operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception.
 */
int execute_XOR(int out_reg, int first_operand, int second_operand, int first_immediate,
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

/**
 * Execute a SLL (bitwise Shift Left Logical) command. It shifts the first_operand by second_operand number of bits to the left.
 * @param out_reg The index of the output register.
 * @param first_operand The value of the first operand.
 * @param second_operand The value of the second operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception.
 */
int execute_SLL(int out_reg, int first_operand, int second_operand, int first_immediate,
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

/**
 * Execute a SRL (bitwise Shift Right Logical) command. It shifts the first_operand by second_operand number of bits to the right.
 * @param out_reg The index of the output register.
 * @param first_operand The value of the first operand.
 * @param second_operand The value of the second operand.
 * @param first_immediate Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @return 0 if successfully executed. Non-zero if there is an exception.
 */
int execute_SRL(int out_reg, int first_operand, int second_operand, int first_immediate,
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

/**
 * Execute a LBL (LaBeL) command.
 * @param label_index Index of the stored label.
 * @return 0 if successfully executed. -1 if the label was not found.
 */
int execute_LBL(int label_index) {
    char *label = labels[label_index];
    int success = 0;
    for (int i = 0; i < num_labels; ++i) {
        if (strcmp(labels[i], label) == 0) {
            label_instruction_pos[i] = instruction_index;
            success = 1;
        }
    }
    if (success < 1) {
        return -1;
    }

    return 0;
}


/**
 * Execute a GOTO (GO TO) command.
 * @param label_index Index of the stored label.
 * @return 1 if successfully executed. (Returning 1 prepares the executer for a jump in instruction index). -1 if the label was not found.
 */
int execute_GOTO(int label_index) {
    char *label = labels[label_index];
    int success = 0;
    for (int i = 0; i < num_labels; ++i) {
        if (strcmp(labels[i], label) == 0) {
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

/**
 * Execute a GEQ (Go to on EQuality) command. If the values of the first_operand_register and second_operand are equal, then go to the label_index.
 * @param first_operand_register The register index of the first operand.
 * @param second_operand The value of the second operand.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param label_index The label index that needs to go to.
 * @return 1 if successfully executed. (Returning 1 prepares the executer for a jump in instruction index). -1 if the label was not found.
 */
int execute_GEQ(int first_operand_register, int second_operand, int second_immediate, int label_index) {
    int value1 = registers[first_operand_register];
    int value2 = 0;
    if (second_immediate) {
        value2 = second_operand;
    } else {
        value2 = registers[second_operand];
    }
    if (value1 == value2) {
        char *label = labels[label_index];
        int success = 0;
        for (int i = 0; i < num_labels; ++i) {
            if (strcmp(labels[i], label) == 0) {
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

/**
 * Execute a GNQ (Go to on No eQuality) command. If the values of the first_operand_register and second_operand are not equal, then go to the label_index.
 * @param first_operand_register The register index of the first operand.
 * @param second_operand The value of the second operand.
 * @param second_immediate  Integer flag to distinguish whether second_operand is an immediate or register index.
 *      If first_immediate > 0, then first_operand is treated as an immediate. Otherwise, first_operand is treated as a register index.
 * @param label_index The label index that needs to go to.
 * @return 1 if successfully executed. (Returning 1 prepares the executer for a jump in instruction index). -1 if the label was not found.
 */
int execute_GNQ(int first_operand_register, int second_operand, int second_immediate, int label_index) {
    int value1 = registers[first_operand_register];
    int value2 = 0;
    if (second_immediate) {
        value2 = second_operand;
    } else {
        value2 = registers[second_operand];
    }
    if (value1 != value2) {
        char *label = labels[label_index];
        int success = 0;
        for (int i = 0; i < num_labels; ++i) {
            if (strcmp(labels[i], label) == 0) {
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

/**
 * Execute a PRINT (PRINT) command. This will print the given values without a new line at the end.
 * @param first_operand The value of the first operand.
 * @param first_directive Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_directive > 0, then first_operand is treated as an directive index. Otherwise, first_operand is treated as a register index.
 *       Immediate values are not allowed for PRINT.
 * @return 0 if successfully executed. Otherwise, non-zero is returned.
 */
int execute_PRINT(int first_operand, int first_directive) {
    if (first_directive) {
        printf("%s", directives_values[first_operand]);

    } else {
        printf("%d", registers[first_operand]);
    }
    return 0;
}

/**
 * Execute a PRINTLN (PRINT LiNe) command. This will print the given values with a new line at the end.
 * @param first_operand The value of the first operand.
 * @param first_directive Integer flag to distinguish whether first_operand is an immediate or register index.
 *       If first_directive > 0, then first_operand is treated as an directive index. Otherwise, first_operand is treated as a register index.
 *       Immediate values are not allowed for PRINT.
 * @return 0 if successfully executed. Otherwise, non-zero is returned.
 */
int execute_PRINTLN(int out_reg, int first_immediate) {
    if (first_immediate) {
        printf("%s\n", directives_values[out_reg]);

    } else {
        printf("%d\n", registers[out_reg]);
    }
    return 0;
}

/**
 * Execute a INPUT (INPUT) command. This will wait for user to input an integer.
 * @param reg_index The index of the register that the inputted value will be stored.
 * @return 0 if successfully executed. Otherwise, non-zero is returned.
 */
int execute_INPUT(int reg_index) {
    scanf("%d", &(registers[reg_index]));
    return 0;
}

/**
 * Execute a HALT (HALT) command. This will terminate the execution of the program
 * @return 0 if successfully executed. Otherwise, non-zero is returned.
 *      However, the return value will never be used because the program exits before any value is returned.
 */
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
        return execute_SR(out_reg, first_operand, first_immediate);
    } else if (opcode == 1) {
        return execute_ADD(out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 2) {
        return execute_SUB(out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 3) {
        return execute_MUL(out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 4) {
        return execute_DIV(out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 5) {
        return execute_MOD(out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 6) {
        return execute_EQ(out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 7) {
        return execute_NEQ(out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 8) {
        return execute_GT(out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 9) {
        return execute_GTE(out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 10) {
        return execute_LT(out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 11) {
        return execute_LTE(out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 12) {
        return execute_AND(out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 13) {
        return execute_OR(out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 14) {
        return execute_NOT(out_reg, first_operand, first_immediate);
    } else if (opcode == 15) {
        return execute_XOR(out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 16) {
        return execute_SLL(out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 17) {
        return execute_SRL(out_reg, first_operand, second_operand, first_immediate, second_immediate);
    } else if (opcode == 18) {
        return execute_LBL(out_reg);
    } else if (opcode == 19) {
        return execute_GOTO(out_reg);
    } else if (opcode == 20) {
//        return "GEQ";
        return execute_GEQ(out_reg, first_operand, first_immediate, second_operand);
    } else if (opcode == 21) {
//        return "GNQ";
        return execute_GNQ(out_reg, first_operand, first_immediate, second_operand);
    } else if (opcode == 22) {
        return execute_PRINT(out_reg, first_immediate);
    } else if (opcode == 23) {
        return execute_PRINTLN(out_reg, first_immediate);
    } else if (opcode == 24) {
        return execute_HALT();
    } else if (opcode == 25) {
        return execute_INPUT(out_reg);
    }
    return -1;

}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        char *arg = argv[i];

        input_path = arg;

    }


    for (int i = 1; i < argc; ++i) {
        char *arg = argv[i];
        if (strcmp(arg, "-h") == 0 || strcmp(arg, "-?") == 0 || strcmp(arg, "--help") == 0) {
            printf("  ____  __  __ ____  _  __   __  _____                     _            \n"
                   " / ___||  \\/  | __ )| | \\ \\ / / | ____|_  _____  ___ _   _| |_ ___ _ __ \n"
                   " \\___ \\| |\\/| |  _ \\| |  \\ V /  |  _| \\ \\/ / _ \\/ __| | | | __/ _ \\ '__|\n"
                   "  ___) | |  | | |_) | |___| |   | |___ >  <  __/ (__| |_| | ||  __/ |   \n"
                   " |____/|_|  |_|____/|_____|_|   |_____/_/\\_\\___|\\___|\\__,_|\\__\\___|_|   \n"
                   "                                                                        \n");
            printf("                              Version %.1f                          \n\n", VERSION);

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


        if (section_identifier == 0xAAAAAAAAAAAAAAAAL) {
            // Labels section
            int result = fread(&num_labels, 1, sizeof(num_labels), fp);
            if (result != 8) {
                return 1;
            }
            labels = malloc(sizeof(char *) * num_labels);
            label_instruction_pos = malloc(sizeof(int) * num_labels);
            int max_line_size = 30;
            for (int label_index = 0; label_index < num_labels; ++label_index) {
                char c;
                char *label = (char *) malloc(max_line_size * sizeof(char));
                int i = 0;
                while ((c = getc(fp)) != '\0') {
                    label[i] = c;
                    i++;
                }
                label[i] = '\0';
                labels[label_index] = label;
            }


        } else if (section_identifier == 0xBBBBBBBBBBBBBBBBL) {
            // Directive section
            int result = fread(&num_directives, 1, sizeof(num_directives), fp);
            if (result != 8) {
                return 1;
            }
            int n = num_directives;
            directives_names = malloc(sizeof(char *) * num_directives);
            directives_values = malloc(sizeof(char *) * num_directives);

            int max_line_size = 30;
            for (int directive_index = 0; directive_index < num_directives; ++directive_index) {
                char c;
                char *directive_name = (char *) malloc(max_line_size * sizeof(char));
                char *directive_value = (char *) malloc(max_line_size * sizeof(char));

                int i = 0;
                while ((c = getc(fp)) != '\0') {
                    directive_name[i] = c;
                    i++;
                }
                directive_name[i] = '\0';

                i = 0;
                while ((c = getc(fp)) != '\0') {
                    directive_value[i] = c;
                    i++;
                }
                directive_value[i] = '\0';

                directives_names[directive_index] = directive_name;
                directives_values[directive_index] = directive_value;

            }
        } else if (section_identifier == 0xCCCCCCCCCCCCCCCCL) {
            // codes section
            if (labels == NULL) {
                return 1;
            }

            uint64_t code = 0;
            uint64_t file_code_section_offset;
            file_code_section_offset = ftell(fp);

            // First scan file for labels then execute instructions
            while (fread(&code, 1, sizeof(code), fp) == 8) {
                int opcode = ((code) & 0xFFFF000000000000L) >> 12 * 4;
                int out_reg = ((code) & 0x0000FFFF00000000L) >> 8 * 4;

                if (opcode == 18) {
                    // Processing a LBL, save the label to labels array
                    execute_LBL(out_reg);
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
//                    printf("[ERROR] Encountered Runtime Error");
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

    free(labels);
    free(directives_names);
    free(directives_values);
    free(label_instruction_pos);
    return 0;
}

