/*
** EPITECH PROJECT, 2019
** print_info_sharksh
** File description:
** print_info_sharksh
*/

#include "exec.h"

char *get_line_info_in_file(char *file, char *hashkey)
{
    char *line = NULL;
    char *info = NULL;
    FILE *fd = fopen(file, "r");
    size_t n = 0;
    int ret = 0;

    while ((ret = getline(&line, &n, fd)) != -1) {
        if ((info = strstr(line, hashkey)) != NULL)
            break;
    }
    fclose(fd);
    if (ret == -1)
        return ("Not Found.");
    if (info[strlen(info) - 1] == '\n')
        info[strlen(info) - 1] = '\0';
    return (info);
}

char *get_cpu_info(void)
{
    return (get_line_info_in_file("/proc/cpuinfo", "model name"));
}

char *get_mem_info(void)
{
    return (get_line_info_in_file("/proc/meminfo", "MemTotal"));
}

char *get_user_name(void)
{
    struct utsname *node_name = malloc(sizeof(struct utsname));

    if (uname(node_name) == -1)
        return ("Not Found.");
    return (node_name->nodename);
}

char *get_kernel_info(void)
{
    char *info = malloc(sizeof(char) * 256);
    struct utsname sys_info;

    if (uname(&sys_info) == -1)
        return ("Not Found.");
    strcpy(info, sys_info.machine);
    strcat(info, " ");
    strcat(info, sys_info.sysname);
    strcat(info, " ");
    strcat(info, sys_info.release);
    return (info);
}