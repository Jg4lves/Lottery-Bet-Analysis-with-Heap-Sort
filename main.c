//To compile: gcc -o main main.c -lm
// To run: ./main input_example

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Bet {
    char code[50];
    uint32_t numbers[15];
    uint32_t position;
    uint32_t count;
} Bet;

void Add(Bet *list, const char code[50], const uint32_t numbers[15], uint32_t counter) {
    strcpy(list->code, code);
    memcpy(list->numbers, numbers, 15 * sizeof(uint32_t));
    list->count = counter;
}

Bet *left(Bet *parent, Bet *list[], uint32_t num_bets) {
    uint32_t new_position = parent->position * 2;

    for (uint32_t i = 0; i < num_bets; i++) {
        if (new_position == list[i]->position) {
            return list[i];
        }
    }
    return NULL;
}

Bet *right(Bet *parent, Bet *list[], uint32_t num_bets) {
    uint32_t new_position = (2 * parent->position) + 1;

    for (uint32_t i = 0; i < num_bets; i++) {
        if (new_position == list[i]->position) {
            return list[i];
        }
    }
    return NULL;
}

void heapify(Bet *list, double size, uint32_t i) {
    uint32_t P = i;
    Bet *L = left(&list[i], &list, size);
    Bet *R = right(&list[i], &list, size);

    if (L != NULL && L->position > list[P].position) {
        P = L->position;
    }
    if (R != NULL && R->position > list[P].position) {
        P = R->position;
    }

    if (P != i) {
        Bet temp = list[i];
        list[i] = list[P];
        list[P] = temp;

        heapify(list, size, P);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    if (input == NULL || output == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    uint32_t prize;
    uint32_t num_bets;
    uint32_t drawn_numbers[10];
    char code[50];
    uint32_t numbers[15];
    uint32_t counter = 0;
    uint32_t max_count = 0;
    uint32_t min_count = 0;

    fscanf(input, "%u", &prize);
    fscanf(input, "%u", &num_bets);

    Bet *list = (Bet *)malloc(num_bets * sizeof(Bet));
    if (list == NULL) {
        printf("Error allocating memory for 'list'.\n");
        return 1;
    }

    for (uint32_t i = 0; i < 10; i++) {
        fscanf(input, "%u", &drawn_numbers[i]);
    }

    for (uint32_t j = 0; j < num_bets; j++) {
        fscanf(input, "%s", code);
        for (uint32_t k = 0; k < 15; k++) {
            fscanf(input, "%u", &numbers[k]);
        }
        Add(&list[j], code, numbers, counter);
    }

    double size = ceil(log2(num_bets + 1)) - 1;
    for (uint32_t r = 0; r < num_bets; r++) {
        heapify(list, size, r);
    }

    Bet *max = NULL;
    Bet *min = NULL;
    for (uint32_t l = 0; l < num_bets; l++) {
        for (uint32_t m = 0; m < 15; m++) {
            for (uint32_t n = 0; n < 10; n++) {
                if (list[l].numbers[m] == drawn_numbers[n]) {
                    list[l].count += 1;
                }
            }
        }
        if (max == NULL || list[l].count == max->count) {
            max_count++;
        }
        if (min == NULL || list[l].count == min->count) {
            min_count++;
        }
        if (min == NULL || list[l].count < min->count) {
            min = &list[l];
        }
        if (max == NULL || list[l].count > max->count) {
            max = &list[l];
        }
    }

    uint32_t value = prize / 2;
    fprintf(output, "[%u:%u:%u]\n", max_count, max->count, (max_count != 0) ? value / max_count : 0);
    for (uint32_t o = 0; o < num_bets; o++) {
        if (list[o].count == max->count) {
            fprintf(output, "%s", list[o].code);
            while (max_count - 1) {
                fprintf(output, "\n");
                max_count--;
            }
        }
    }

    fprintf(output, "\n[%u:%u:%u]\n", min_count, min->count, (min_count != 0) ? value / min_count : 0);
    for (uint32_t p = 0; p < num_bets; p++) {
        if (list[p].count == min->count) {
            fprintf(output, "%s", list[p].code);
            while (min_count - 1) {
                fprintf(output, "\n");
                min_count--;
            }
        }
    }

    fclose(input);
    fclose(output);
    free(list);
    return 0;
}
