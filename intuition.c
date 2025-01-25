#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_HISTORY 10


void print_history(int *history, int *guessed, int size) {
    printf("Numbers: ");
    for (int i = 0; i < size; i++) {
        if (guessed[i]) {
            printf("\033[0;32m%d\033[0m ", history[i]); // Verde para acertados
        } else {
            printf("\033[0;31m%d\033[0m ", history[i]); // Rojo para fallados
        }
    }
    printf("\n");
}

int main() {
    int step = 1, hits = 0, misses = 0;
    int history[MAX_HISTORY] = {0};
    int guessed[MAX_HISTORY] = {0};
    int history_count = 0;

    char input[10];
    srand(time(NULL)); 

    while (1) {
        
        int random_number = rand() % 10;

        if (history_count < MAX_HISTORY) {
            history[history_count] = random_number;
            guessed[history_count] = 0;
            history_count++;
        } else {
            
            memmove(history, history + 1, (MAX_HISTORY - 1) * sizeof(int));
            memmove(guessed, guessed + 1, (MAX_HISTORY - 1) * sizeof(int));
            history[MAX_HISTORY - 1] = random_number;
            guessed[MAX_HISTORY - 1] = 0;
        }

        printf("Step: %d\n", step);
        printf("Please enter number from 0 to 9 (q - quit): ");
        scanf("%s", input);

        if (strcmp(input, "q") == 0) {
            printf("Goodbye!\n");
            break;
        }

        char *endptr;
        int user_input = strtol(input, &endptr, 10);
        if (*endptr != '\0' || user_input < 0 || user_input > 9) {
            printf("Input error!\n");
            continue;
        }

        if (user_input == random_number) {
            printf("Hit! My number: %d\n", random_number);
            hits++;
            guessed[history_count - 1] = 1; // Marcar como acertado
        } else {
            printf("Miss! My number: %d\n", random_number);
            misses++;
        }

        int total = hits + misses;
        int hit_percentage = (hits * 100) / total;
        int miss_percentage = (misses * 100) / total;

        printf("Hit: %d%% Miss: %d%%\n", hit_percentage, miss_percentage);

        print_history(history, guessed, history_count);

        step++;
    }

    return 0;
}
