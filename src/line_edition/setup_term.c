/*
** EPITECH PROJECT, 2019
** setup_term
** File description:
** setup_term
*/

#include "exec.h"

int init_termcap_sys(caps_t *caps)
{
    int status = 0;

    if (setupterm("xterm-256color", STDOUT_FILENO, &status) != OK)
        return (84);
    caps->ar_left = tigetstr("cub1");
    caps->ar_right = tigetstr("cuf1");
    caps->ar_down = tigetstr("cud1");
    caps->ar_up = tigetstr("cuu1");
    caps->clear_scr = tigetstr("clear");
    caps->del_ch = NULL;
    caps->clear_line = tigetstr("dl1");
    caps->save_curs = tigetstr("sc");
    caps->restore_save_curs = tigetstr("rc");
    caps->clear_bottom_screen = tigetstr("ed");
    caps->hide_cursor = tigetstr("civis");
    caps->show_cursor = tigetstr("cvvis");
    return (0);
}

int setup_new_term(cmdline_t *cline)
{
    struct termios newterm;
    struct termios oldterm;

    if (init_termcap_sys(&cline->caps) == 84)
        return (84);
    if (tcgetattr(0, &newterm) == -1)
        return (84);
    if (tcgetattr(0, &oldterm) == -1)
        return (84);
    cline->oldterm = oldterm;
    newterm.c_lflag &= ~(ICANON | ECHO);
    cline->newterm = newterm;
    if (tcsetattr(0, TCSANOW, &newterm) == -1)
        return (84);
    return (0);
}