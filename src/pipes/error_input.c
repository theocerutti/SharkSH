/*
** EPITECH PROJECT, 2019
** my_pipe
** File description:
** my_pipe
*/

#include "exec.h"

int verify_match_order(char match[5][3], int i, char *str)
{
    int a = 0;

    for (int j = 0; str[j] != '\0'; j++) {
        if (is_inhib(j, match[i][0], str))
            a++;
        if (is_inhib(j, match[i][1], str))
            a--;
        if (a < 0) {
            fprintf(stderr, "Too many %c\'s.\n", match[i][1]);
            return (84);
        }
    }
    return (0);
}

int error_match_process(char match[5][3], int i, char *str)
{
    if (match[i][0] == match[i][1]) {
        if (match[i][2] % 2 == 1) {
            fprintf(stderr, "Unmatched \'%c\'.\n", match[i][0]);
            return (84);
        }
    } else {
        if (match[i][2] < 0) {
            fprintf(stderr, "Too many %c\'s.\n", match[i][1]);
            return (84);
        } else if (match[i][2] > 0) {
            fprintf(stderr, "Too many %c\'s.\n", match[i][0]);
            return (84);
        }
        if (match[i][0] != match[i][1])
            return (verify_match_order(match, i, str));
    }
    return (0);
}

int print_error_match(char match[5][3], char *str)
{
    if (match[0][2] % 2 == 1 && match[2][2] % 2 == 1)
        if (error_match_special(str) == 84)
            return (84);
    for (int i = 0; i < 3; i++)
        if (error_match_process(match, i, str) == 84)
            return (84);
    return (0);
}

int error_esp_or(char *str)
{
    int idx = 0;

    for (idx = my_strlen(str); idx != 0; idx--)
        if (str[idx] != ' ' && str[idx] != '\t' && str[idx] != '\n'
        && str[idx] != '\0') break;
    if (str[idx] == '&' || str[idx] == '|')
        return (84);
    return (0);
}

int error_input_match(char *str)
{
    char match[5][3] = {{'"', '"', 0}, {'(', ')', 0}, {'\'', '\'', 0}};
    int ret = 0;

    if (error_esp_or(str) == 84) {
        my_puterror("Invalid null command.\n");
        return (84);
    }
    for (int j = 0; str[j] != '\0'; j++) {
        for (int i = 0; i < 3; i++) {
            if (is_inhib(j, match[i][0], str))
                match[i][2] += 1;
            if (is_inhib(j, match[i][1], str) && \
            match[i][1] != match[i][0])
                match[i][2] -= 1;
        }
    }
    ret = print_error_match(match, str);
    return (ret);
}