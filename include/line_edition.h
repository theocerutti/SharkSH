/*
** EPITECH PROJECT, 2019
** line_edition_header
** File description:
** line_edition_header
*/

#ifndef __LINE_EDITION__
#define __LINE_EDITION__

#define BUF_CMD 256
#define BUF_CLIPBOARD 4096
#define QUIT_CMD 1

enum key_id {
    K_LEFT = 4479771,
    K_RIGHT = 4414235,
    K_UP = 4283163,
    K_DOWN = 4348699,
    K_DEL = 2117294875,
    K_SUPR = 127,
    CTRL_A = 1,
    CTRL_B = 2,
    CTRL_D = 4,
    CTRL_E = 5,
    CTRL_F = 6,
    CTRL_I = 9,
    CTRL_J = 10,
    CTRL_K = 11,
    CTRL_L = 12,
    CTRL_T = 20,
    CTRL_U = 21,
    CTRL_V = 22,
    CTRL_W = 23,
    K_TAB = 9,
    K_ENTER = '\n'
};

typedef struct caps_s {
    char *ar_left;
    char *ar_right;
    char *ar_down;
    char *ar_up;
    char *clear_scr;
    char *del_ch;
    char *save_curs;
    char *restore_save_curs;
    char *clear_line;
    char *clear_bottom_screen;
    char *hide_cursor;
    char *show_cursor;
} caps_t;

typedef struct cmdline_s {
    int index;
    int nb_chars;
    char *line;
    int c;
    struct termios oldterm;
    struct termios newterm;
    caps_t caps;
    int history_index;
    int size_alloc;
} cmdline_t;

typedef struct kkey_s {
    int key_id;
    int (*pressed)(all_t *, cmdline_t *);
} kkey_t;

char *read_cmdline(all_t *all);
struct termios setup_new_terminal(void);
void getc_handler(all_t *all, cmdline_t *cmdline);
char *insert_char_line(char *line, int index, char c);
void arrows_handling(all_t *all, cmdline_t *cline);
int backspace(all_t *all, cmdline_t *cline);
int insert_char(all_t *all, cmdline_t *cline);
int delete(all_t *all, cmdline_t *cline);
void delete_index_char(char *line, int index);
int cmdline_history_up(all_t *all, cmdline_t *cline);
int cmdline_history_down(all_t *all, cmdline_t *cline);
void move_cur_right(char *cap_right, int nb_time);
void move_cur_left(char *cap_left, int nb_time);
int setup_new_term(cmdline_t *cline);
int init_termcap_sys(caps_t *caps);
int move_left(all_t *all, cmdline_t *cline);
int move_right(all_t *all, cmdline_t *cline);
void exec_cap(char *cap);
void clear_cmdline(all_t *all, cmdline_t *cline);
void redisplay_cmdline(all_t *all, cmdline_t *cline);
int tab_print_dir(all_t *all, cmdline_t *cline);
int ctrl_l_clear_scr(all_t *all, cmdline_t *cline);
int ctrl_a_begin_line(all_t *all, cmdline_t *cline);
int ctrl_b_move_left(all_t *all, cmdline_t *cline);
int ctrl_c_sigint(all_t *all, cmdline_t *cline);
int ctrl_e_end_line(all_t *all, cmdline_t *cline);
int ctrl_j_new_line(all_t *all, cmdline_t *cline);
int ctrl_u_clear_line(all_t *all, cmdline_t *cline);
int ctrl_f_move_right(all_t *all, cmdline_t *cline);
int ctrl_i_complete_word(all_t *all, cmdline_t *cline);
int ctrl_k_cut_line_right(all_t *all, cmdline_t *cline);
int ctrl_w_cut_line_left(all_t *all, cmdline_t *cline);
int ctrl_t_transpose_char(all_t *all, cmdline_t *cline);
int paste(all_t *all, cmdline_t *cline);

#endif