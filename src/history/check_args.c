/*
** EPITECH PROJECT, 2019
** check args history
** File description:
** sharksh
*/

#include "exec.h"

int is_digit_or_letter(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
    (c >= '0' && c <= '9'))
        return (1);
    return (0);
}

int is_only_digit(char *num)
{
    for (int i = 0; num[i] != '\0'; i++)
        if (num[i] < '0' || num[i] > '9')
            return (0);
    return (1);
}

void make_history_interact(char *cmd, int begin, int end, all_t *all)
{
    char *stock = malloc(end - begin + 2);
    int beg_end[2] = {begin, end};

    stock[end - begin + 1] = '\0';
    for (int i = begin, w = 0; i <= end; i++, w++)
        stock[w] = cmd[i];
    stock += 1;
    if (is_only_digit(stock))
        exec_command_x(stock, all, beg_end);
    else
        exec_same_cmd(stock, all, beg_end);
}

void check_beginning_his(all_t *all, int *begin, int *i)
{
    if (all->input[*i] == '!' && is_digit_or_letter(all->input[*i + 1])) {
        *begin = *i;
        *i += 1;
    }
}

int check_history(all_t *all)
{
    int begin = -1;
    int end = -1;

    for (int i = 0; all->input[i] != '\0'; i++) {
        check_beginning_his(all, &begin, &i);
        if (begin != -1 && is_digit_or_letter(all->input[i]))
            end = i;
        if (begin != -1 && (all->input[i] == '\n' || all->input[i] == '\t' ||
        all->input[i + 1] == '\0' || all->input[i] == ';' || all->input[i] ==
        ')' || all->input[i] == '&' || all->input[i] == '|' ||
        all->input[i] == '\'' || all->input[i] == '\"'
        || all->input[i] == ' ')) {
            make_history_interact(all->input, begin, end, all);
            begin = -1;
        }
    }
    if (all->exit_code == 0 && end != -1)
        print_command_clean(all->input);
    return (all->exit_code);
}