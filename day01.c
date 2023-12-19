#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

long sum_of_calibration_values(const char *filename);
long sum_of_calibration_values_letters(const char *filename);

int main()
{
    // Perform tests for part 1 and 2 by using the example data.
    long result_example_1 = sum_of_calibration_values("inputs/day01-example.txt");
    if (result_example_1 != 142) {
        printf("Part 1 - Sum of all calibration values is not equal to 142 but: %ld", result_example_1);
        exit(EXIT_FAILURE);
    }

    long result_example_2 = sum_of_calibration_values_letters("inputs/day01-example2.txt");
    if (result_example_2 != 281) {
        printf("Part 2 - Sum of all calibration values is not equal to 281 but: %ld", result_example_2);
        exit(EXIT_FAILURE);
    }

    // Compute puzzle answers of part 1 and 2. 
    long result_part1 = sum_of_calibration_values("inputs/day01.txt");
    long result_part2 = sum_of_calibration_values_letters("inputs/day01.txt");

    printf("Part 1 - Sum of calibration values = %ld\n", result_part1); // 54304
    printf("Part 2 - Sum of calibration values = %ld\n", result_part2); // 54418
    exit(EXIT_SUCCESS);
}

long sum_of_calibration_values(const char *filename)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    long sum = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        char result[3] = {0};
        for (size_t i = 0; i < strlen(line); i++) {
            if (isdigit(line[i])) {
                if (!result[0]) result[0] = line[i];
                result[1] = line[i];
            }
        }

        sum += atol(result);
    }
    
    free(line);
    fclose(fp);

    return sum;
}

char parse_digit(const char *str)
{
    size_t len = strlen(str);
    if (len >= 1 && isdigit(str[0])) return str[0];
    if (len >= 3 && !strncmp(str, "one", 3)) return '1';
    if (len >= 3 && !strncmp(str, "two", 3)) return '2';
    if (len >= 5 && !strncmp(str, "three", 5)) return '3';
    if (len >= 4 && !strncmp(str, "four", 4)) return '4';
    if (len >= 4 && !strncmp(str, "five", 4)) return '5';
    if (len >= 3 && !strncmp(str, "six", 3)) return '6';
    if (len >= 5 && !strncmp(str, "seven", 5)) return '7';
    if (len >= 5 && !strncmp(str, "eight", 5)) return '8';
    if (len >= 4 && !strncmp(str, "nine", 4)) return '9';
    return 0;
}

long sum_of_calibration_values_letters(const char *filename)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    long sum = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        char result[3] = {0};
        for (size_t i = 0; i < strlen(line); i++) {
            char d = parse_digit(line + i);
            if (d) {
                if (!result[0]) result[0] = d;
                result[1] = d;
            }
        }

        sum += atol(result);
    }
    
    free(line);
    fclose(fp);

    return sum;
}