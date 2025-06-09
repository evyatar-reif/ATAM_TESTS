#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EXPECTED_LINES 20
#define MAX_LINE_LEN 256
#define NUM_OF_TESTS 12

int compute_char_repeats(char* buffer, int line_length, char special_char);
int parse_lines(char* path, int* line_max_len, int* line_max_repeat);

int test_func1() {
    char *path = "./ATAM_TESTS/tests/func1.txt";
    FILE *fp = fopen(path, "r");
    if (!fp) {
        perror("Failed to open file.\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        // Remove newline if present
        line[strcspn(line, "\r\n")] = 0;

        // Get test number (before the dot)
        char *test_number_str = strtok(line, ".");
        char *rest = strtok(NULL, "");  // everything after the dot

        if (!test_number_str || !rest) {
            fprintf(stderr, "Malformed line (missing dot separator)\n");
            continue;
        }

        // Now split the rest by commas
        char *text = strtok(rest, ",");
        char *letter_str = strtok(NULL, ",");
        char *count_str = strtok(NULL, ",");

        if (!text || !letter_str || !count_str) {
            fprintf(stderr, "Malformed line (missing comma-separated fields)\n");
            continue;
        }

        int test_number = atoi(test_number_str);
        char letter = letter_str[0];
        int expected_count = atoi(count_str);

        int actual_count = compute_char_repeats(text, strlen(text), letter);
        if (actual_count == expected_count) {
            printf("\033[32mTest %d passed. \033[0m\n", test_number);
        } else {
            printf("\033[31m Test %d failed. \033[0m\n Text: %s\nLetter: '%c', Expected: %d, Actual: %d\n",
                   test_number, text, letter, expected_count, actual_count);
        }
    }

    fclose(fp);
	return 0;
}

int load_expected_results(const char* filename, char expected[][MAX_LINE_LEN], int max_results) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open expected results file");
        return -1;
    }

    int count = 0;
    char line[MAX_LINE_LEN];
    char separator_line[MAX_LINE_LEN];

    while (count < max_results && fgets(line, sizeof(line), fp)) {
        // Remove newline from line
        size_t len = strlen(line);
        while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r')) {
            line[--len] = '\0';
        }

        strcpy(expected[count], line);

        // Read separator line (---)
        if (!fgets(separator_line, sizeof(separator_line), fp)) {
            break; // no separator line, end early
        }

        count++;
    }

    fclose(fp);
    return count;
}

int test_func2() {
    int line_max_len = 0;
    int line_max_repeat = 0;
    char path[256];

    const int max_tests = NUM_OF_TESTS;  // func20.txt to func210.txt
    char expected_results[max_tests][MAX_LINE_LEN];
    int expected_count = load_expected_results("./ATAM_TESTS/tests/func2_expected.txt", expected_results, max_tests);
    if (expected_count < 0) {
        printf("Cannot load expected results\n");
        return 1;
    }

    for (int i = 0; i < max_tests; i++) {
        snprintf(path, sizeof(path), "./ATAM_TESTS/tests/func2%d.txt", i);

        line_max_len = 0;
        line_max_repeat = 0;

        int lines = parse_lines(path, &line_max_len, &line_max_repeat);
        if (lines < 0) {
            printf("Failed to process %s\n\n", path);
            continue;
        }

        // Build the actual result string to compare
        char actual_output[MAX_LINE_LEN];
        snprintf(actual_output, sizeof(actual_output),
                 "There are %d lines. The longest line is of length %d and the most repeats of the special character in a single line is %d.",
                 lines, line_max_len, line_max_repeat);

        // Compare with expected result
        if (i < expected_count && strcmp(actual_output, expected_results[i]) == 0) {
            printf("\033[32mTest %d PASSED.\033[0m\n", i);
        } else {
            printf("\033[31mTest %d FAILED.\033[0m\nExpected:\n%s\nGot:\n%s\n\n", i,
                   (i < expected_count ? expected_results[i] : "(no expected data)"), actual_output);
        }
    }

    return 0;
}

int main() {
printf("TESTING FUNCTION 1\n");
	test_func1();
printf("TESTING FUNCTION 2\n");
	test_func2();
	return 0;
}