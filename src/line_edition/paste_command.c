/*
** EPITECH PROJECT, 2019
** paste
** File description:
** paste
*/

#include "exec.h"

static int exec_clipboard(char **envp, char **av, int fd[2])
{
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    if (execve(av[0], av, envp) == -1)
        return (FAILURE);
    exit(0);
    return (SUCCESS);
}

static char *get_clipboard_data(int fd)
{
    int nalloc = BUF_CLIPBOARD;
    char *clipboard = malloc(sizeof(char) * nalloc);
    FILE *file = fdopen(fd, "r");
    int size = 0;
    size_t n = 0;
    int ret = 0;
    char *line = NULL;

    strcpy(clipboard, "");
    while ((ret = getline(&line, &n, file)) != -1) {
        size += ret;
        if (size > nalloc) {
            nalloc *= 2;
            clipboard = realloc(clipboard, nalloc);
        }
        strcat(clipboard, line);
    }
    return (clipboard);
}

char *get_clipboard(char **envp)
{
    char *av[] = {"/usr/bin/xclip", "-o", "-selection", "clipboard", NULL};
    int fd[2] = {0, 0};
    pid_t pid = 0;
    int save_out = dup(STDOUT_FILENO);
    char *clipboard = NULL;

    if (pipe(fd) == -1) exit(84);
    if ((pid = fork()) == -1) exit(84);
    if (pid == 0) {
        exec_clipboard(envp, av, fd);
    } else {
        close(fd[1]);
        clipboard = get_clipboard_data(fd[0]);
    }
    dup2(save_out, STDOUT_FILENO);
    close(save_out);
    return (clipboard);
}

int paste(all_t *all, cmdline_t *cline)
{
    int len = 0;
    char *clipboard = get_clipboard(all->ev_exec);

    if (clipboard[0] != '\0') {
        move_cur_left(cline->caps.ar_left, strlen(cline->line));
        cline->line = my_strcat(cline->line, clipboard);
        cline->line = realloc(cline->line, strlen(cline->line) + 2);
        redisplay_cmdline(all, cline);
        len = strlen(cline->line);
        cline->index = len;
        cline->nb_chars = len;
        move_cur_right(cline->caps.ar_right, len);
    }
    return (0);
}