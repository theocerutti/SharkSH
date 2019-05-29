/*
** EPITECH PROJECT, 2019
** read_cmdline
** File description:
** read_cmdline
*/

#include "exec.h"

kkey_t key_tab_ptr[] = {
    {K_LEFT, move_left},
    {K_RIGHT, move_right},
    {K_UP, cmdline_history_up},
    {K_DOWN, cmdline_history_down},
    {0, backspace},
    {K_DEL, delete},
    {K_TAB, tab_print_dir},
    {CTRL_A, ctrl_a_begin_line},
    {CTRL_B, ctrl_b_move_left},
    {0, ctrl_c_sigint},
    {CTRL_D, ctrl_c_sigint},
    {CTRL_E, ctrl_e_end_line},
    {CTRL_F, ctrl_f_move_right},
    {CTRL_J, ctrl_j_new_line},
    {CTRL_K, ctrl_k_cut_line_right},
    {CTRL_L, ctrl_l_clear_scr},
    {CTRL_T, ctrl_t_transpose_char},
    {CTRL_U, ctrl_u_clear_line},
    {CTRL_W, ctrl_w_cut_line_left},
    {CTRL_V, paste},
    {0, NULL}
};

static int read_loop(all_t *all, cmdline_t *cmdline)
{
    int i = 0;
    int ret = 0;

    for (i = 0; key_tab_ptr[i].pressed != NULL; i++) {
        if (cmdline->c == key_tab_ptr[i].key_id) {
            ret = key_tab_ptr[i].pressed(all, cmdline);
            if (ret == QUIT_CMD)
                return (QUIT_CMD);
            break;
        }
    }
    if (key_tab_ptr[i].pressed == NULL && NORMAL_CHAR(cmdline->c))
        insert_char(all, cmdline);
    cmdline->c = '\0';
    read(STDIN_FILENO, &cmdline->c, sizeof(int));
    return (0);
}

static int read_line_edition(all_t *all, cmdline_t *cmdline)
{
    const int K_BACK = cmdline->newterm.c_cc[VERASE];
    const int CTRL_C = cmdline->newterm.c_cc[VINTR];

    key_tab_ptr[4].key_id = K_BACK;
    key_tab_ptr[9].key_id = CTRL_C;
    read(STDIN_FILENO, &cmdline->c, sizeof(int));
    while (cmdline->c != '\n') {
        if (read_loop(all, cmdline) == QUIT_CMD)
            return (QUIT_CMD);
    }
    return (0);
}

char *read_cmdline(all_t *all)
{
    cmdline_t cmdline = {0, 0, 0, 0, {}, {}, {},
    all->history.get_size(&all->history) - 1 + 3, BUF_CMD};
    int len_line = 0;

    if (setup_new_term(&cmdline) == 84)
        exit(84);
    cmdline.line = malloc(sizeof(char) * BUF_CMD);
    for (int i = 0; i < BUF_CMD; i++)
        cmdline.line[i] = '\0';
    read_line_edition(all, &cmdline);
    my_putchar('\n');
    len_line = my_strlen(cmdline.line);
    cmdline.line[len_line] = '\n';
    cmdline.line[len_line + 1] = '\0';
    tcsetattr(0, TCSANOW, &cmdline.oldterm);
    return (cmdline.line);
}