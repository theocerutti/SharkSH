/*
** EPITECH PROJECT, 2019
** print_info_sharksh
** File description:
** print_info_sharksh
*/

#include "exec.h"

static void print_line_sharksh(const sys_info_t info[],
char *line, int i, int *j)
{
    (i % 2) ? printf("\e[34m") : printf("\e[36m");
    printf("%s\t\e[39m", line);
    if (info[*j].info != NULL && (i % 2)) {
        printf("%s%s", info[*j].flag, info[*j].info);
        *j += 1;
    }
    printf("\n");
}

static char *get_env_term(void)
{
    char *path = getenv("TERM");

    if (path == NULL)
        return ("Not Found.");
    return (path);
}

static void print_header(const sys_info_t info[], FILE *fd)
{
    size_t n = 0;
    char *line = NULL;
    int len_line = 0;
    int j = 0;

    printf("\e[34m");
    for (int i = 0; getline(&line, &n, fd) != -1; i++) {
        len_line = strlen(line);
        if (line[len_line - 1] == '\n')
            line[len_line - 1] = '\0';
        print_line_sharksh(info, line, i, &j);
    }
    printf("\e[39m");
}

void print_info_sharksh(all_t *data)
{
    const sys_info_t info[] = {
        {"Login: ", get_user_name()},
        {"CPU: ", get_cpu_info()},
        {"MEM: ", get_mem_info()},
        {"Kernel: ", get_kernel_info()},
        {"Terminal: ", get_env_term()},
        {NULL, NULL}
    };
    FILE *fd = fopen("src/builtins/sharksh/sharksh_logo", "r");

    if (fd == NULL) {
        printf("SharkSH Logo not found.\n");
        return;
    }
    print_header(info, fd);
    (void)data;
    fclose(fd);
}