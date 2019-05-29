/*
** EPITECH PROJECT, 2019
** autocomplete get
** File description:
** SharkSH
*/

#include "exec.h"

void same_b_cmd(all_t *all, struct dirent *file, char **cmd)
{
    int len_cmd = strlen(cmd[all->str_on]);
    int advanced = 0;

    if (strncmp(cmd[all->str_on], "./", 2) == 0) {
        cmd[all->str_on] += 2;
        advanced = 1;
    }
    len_cmd = strlen(cmd[all->str_on]);
    if (my_strncmp(cmd[all->str_on], file->d_name, len_cmd) == 0) {
        all->complete.push(&all->complete, my_strcpy_auto(file->d_name));
        if ((len_cmd = strlen(all->complete.vector[all->complete.size - 1]))
        > all->len_bin)
            all->len_bin = len_cmd;
    }
    if (advanced == 1)
        cmd[all->str_on] -= 2;
}

void in_folder_cmd(all_t *all, struct dirent *file)
{
    int len_cmd = 0;

    if (file->d_name[0] != '.' || !(strlen(file->d_name) >= 2 &&
    file->d_name[0] == '.' && file->d_name[1] == '.'))
        all->complete.push(&all->complete, my_strcpy_auto(file->d_name));
    if ((len_cmd = strlen(all->complete.vector[all->complete.size - 1]))
    > all->len_bin)
        all->len_bin = len_cmd;
}

void get_file_in_path(all_t *all, char *exec_folder, \
char **cmd)
{
    DIR *folder = opendir(exec_folder);
    struct dirent *file = NULL;

    if (folder == NULL)
        perror("opendir");
    while ((file = readdir(folder)) != NULL) {
        if (file == NULL) {
            perror("readdir");
            break;
        } else if (all->str_on != -1) {
            same_b_cmd(all, file, cmd);
        } else
            in_folder_cmd(all, file);
    }
    closedir(folder);
}

int where_cursor(char *str, int index)
{
    int count = 0;

    for (int i = 0, z = 0; i <= (int)strlen(str); i++) {
        if (i != 0 && i == index && str[i - 1] != ' ')
            return (count - 1);
        else if (i == index && str[i - 1] == ' ')
            return (-1);
        if (str[i] <= 32 || str[i] >= 127)
            z = 0;
        if (str[i] > 32 && str[i] < 127 && z == 0) {
            count++;
            z = 1;
        }
    }
    return (-1);
}

void get_command_autocomp(all_t *all, cmdline_t *cline)
{
    char **path = get_exec_path(all);
    char **cmd = str_word_array(cline->line);

    all->complete.clear_v(&all->complete);
    all->len_bin = 0;
    all->str_on = where_cursor(cline->line, cline->index);
    if (all->str_on == 0 && strncmp(cmd[all->str_on], "./", 2) == 0) {
        get_file_in_path(all, ".", cmd);
    } else if (all->str_on == 0) {
        get_file_in_path(all, ".", cmd);
        for (int i = 0; path[i] != NULL; i++)
            get_file_in_path(all, path[i], cmd);
    }
    if (all->str_on != 0)
        get_file_in_path(all, ".", cmd);
    for (int i = 0; cmd[i] != NULL; i++)
        free(cmd[i]);
    free(cmd);
}