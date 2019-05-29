/*
** EPITECH PROJECT, 2019
** add cmd to history
** File description:
** Shark SH
*/

#include "exec.h"

void finalize_cmd(int *i, int *w, char *final_cmd, char *cmd)
{
    if (((cmd[*i + 1] == '(' || cmd[*i + 1] == ')' || cmd[*i + 1] == '|' ||
    cmd[*i + 1] == ';' || cmd[*i + 1] == '[' || cmd[*i + 1] == ']' ||
    cmd[*i + 1] == '&') && (cmd[*i] != ' ' && cmd[*i] != '|' &&
    cmd[*i] != '&')) && (cmd[*i] != cmd[*i + 1])) {
        final_cmd[*w] = cmd[*i];
        *w += 1;
        final_cmd[*w] = ' ';
    } else if ((*i != 0 && (cmd[*i - 1] == '(' || cmd[*i - 1] == ')' ||
    cmd[*i - 1] == '|' || cmd[*i - 1] == ';' || cmd[*i - 1] == '[' ||
    cmd[*i - 1] == ']' || cmd[*i - 1] == '&') && (cmd[*i] != ' ' &&
    cmd[*i] != '|' && cmd[*i] != '&')) && (cmd[*i] != cmd[*i - 1])) {
        final_cmd[*w] = ' ';
        *w += 1;
        final_cmd[*w] = cmd[*i];
    } else
        final_cmd[*w] = cmd[*i];
}

void add_special_space(char *cmd, all_t *all)
{
    int len_new = strlen(cmd);
    char *final_cmd = NULL;

    for (int i = 0; cmd[i] != '\0'; i++)
        if (cmd[i] == '(' || cmd[i] == ')' || cmd[i] == '|' || cmd[i] == ';' ||
        cmd[i] == '[' || cmd[i] == ']' || cmd[i] == '&')
            len_new += 2;
    final_cmd = malloc(len_new + 1);
    for (int i = 0; i <= len_new; i++)
        final_cmd[i] = '\0';
    for (int i = 0, w = 0; cmd[i] != '\0'; i++, w++)
        finalize_cmd(&i, &w, final_cmd, cmd);
    all->history.push(&all->history, (void *)final_cmd);
}

void reduce_space(char *cmd)
{
    while (cmd[0] == ' ') {
        for (int w = 0; cmd[w] != '\0'; w++)
            cmd[w] = cmd[w + 1];
    }
    for (int i = 0; cmd[i] != '\0'; i++)
        if (cmd[i] == ' ' && (cmd[i + 1] == ' ' || cmd[i + 1] == '\t' || \
        cmd[i + 1] == '\n' || cmd[i + 1] == '\0'))
            reduce(cmd, i);
}

void get_hour(struct tm *localtime, all_t *all)
{
    char *date = malloc(6);
    char *tim = malloc(4);

    date[0] = '\0';
    tim[0] = '\0';
    sprintf(tim, "%.2d", localtime->tm_hour);
    date = strcat(date, tim);
    date = strcat(date, ":");
    sprintf(tim, "%.2d", localtime->tm_min);
    date = strcat(date, tim);
    all->history.push(&all->history, (void *)date);
}

void get_history(all_t *all)
{
    static int index = 1;
    char *cmd = malloc(strlen(all->input) + 1);
    time_t seconds = time(NULL);
    struct tm *local_time = localtime(&seconds);

    all->history.push(&all->history, (void *)index);
    get_hour(local_time, all);
    cmd[strlen(all->input)] = '\0';
    cmd = strcpy(cmd, all->input);
    reduce_space(cmd);
    add_special_space(cmd, all);
    free(cmd);
    index += 1;
}