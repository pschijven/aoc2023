#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    int sum;
    int sum_powers;
} results_t;

results_t compute_solution(const char *filename);

int main()
{
    // Test our code against the example data
    results_t example = compute_solution("inputs/day02-example.txt");
    if (example.sum != 8L || example.sum_powers != 2286) {
        printf("Result is wrong! Received sum=%d, sum_powers=%d", example.sum, example.sum_powers);
        exit(EXIT_FAILURE);
    }

    // Compute the final solutions for the input data. 
    results_t solution = compute_solution("inputs/day02.txt");
    printf("Final result part 1: %d\n", solution.sum); // 1931
    printf("Final result part 2: %d\n", solution.sum_powers); // 83105

    return 0;
}

results_t compute_solution(const char *filename)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("File %s does not exist", filename);
        exit(EXIT_FAILURE);
    }

    results_t results = { .sum = 0, .sum_powers = 0 };

    while((read = getline(&line, &len, fp)) != -1) {
        // Parse the game ID.
        int game_id;
        sscanf(line, "Game %d:", &game_id);

        // Extract all the data for the current game
        const char *game_data = strstr(line, ":") + 2;

        int red = 0, green = 0, blue = 0; // Store the amount of stones in each round of a game
        int max_red = 0, max_green = 0, max_blue = 0; // Maximum values of the colored stones in a game
        char amount[10] = { '\0' }; // Array to store the amount of stones of a particular color in a round
        int amount_idx = 0;
        int possible = 1; // Boolean flag to indicate if the game/round is possible.

        for (size_t i = 0; i < strlen(game_data) + 1; i++) {
            if (game_data[i] == ' ') continue;
            if (isdigit(game_data[i])) {
                amount[amount_idx++] = game_data[i];
                continue;
            }
            if (game_data[i] == ',' || game_data[i] == ';') {
                // Reset amount, since the current amount + color is parsed
                for (int j = 0; j < 10; j++) {
                    amount[j] = '\0';
                }
                amount_idx = 0;
                if (game_data[i] == ';') {
                    // Reset round
                    blue = 0;
                    green = 0;
                    red = 0;
                }
                continue;
            }
            
            // Check if the current substr starts with a specific color
            const char *current_substr = game_data + i;
            size_t len = strlen(current_substr);
            if (len >= 3 && !strncmp(current_substr, "red", 3)) {
                red = atoi(amount);
                i += 2;
            }
            if (len >= 5 && !strncmp(current_substr, "green", 5)) {
                green = atoi(amount);
                i += 4;
            }
            if (len >= 4 && !strncmp(current_substr, "blue", 4)) {
                blue = atoi(amount);
                i += 3;
            }

            // Check if current round is valid
            if (blue > 14 || green > 13 || red > 12 ) {
                possible = 0;
            }

            // Update max values
            if (blue > max_blue) max_blue = blue;
            if (red > max_red) max_red = red;
            if (green > max_green) max_green = green;
        }

        if (possible) {
            results.sum += game_id;
        }

        results.sum_powers += max_red * max_green * max_blue;
    }

    return results;
}