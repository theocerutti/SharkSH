/*
** EPITECH PROJECT, 2019
** lib
** File description:
** lib
*/

#ifndef LIB_H_
#define LIB_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <termios.h>
#include <termcap.h>
#include <curses.h>
#include <term.h>
#include <ctype.h>
#include <grp.h>
#include <stdarg.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/utsname.h>
#include <signal.h>
#include "../vector/my_vector.h"
#include "arraylist.h"
#include "linked_list.h"
#include "struct.h"
#include "line_edition.h"

#define LETTER(a) (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')
#define ALPHANUMERIC(a) (LETTER(a) || (a >= '0' && a <= '9'))
#define REDIRECTION(a) (a == '|' || a == '<' || a == '>' || a == ';' \
|| a == '&')
#define NORMAL_CHAR(c) (c > 31 && c < 127)
#define FALSE 0
#define TRUE 1
#define ERROR -1
#define SUCCESS 1
#define FAILURE 0
#define EXIT(all, code) all->exit_code = all->exit_code == 0 ? code : \
all->exit_code; return;
extern int fd_out;

#define UNUSED __attribute__((unused))

#endif /* !lib */
