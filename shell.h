#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <d_string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* toem_atoi.c */
int is_delimeter(char, char *);
int is_alpha(int);
int d_string_to_integer(char *);

/* read/write buffers */
#define d_read_buf_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* d_convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 for using system getline() */
#define USE_getline_diva 0
#define USE_d_strTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * d_struct listd_str - this is a singly linked list
 * @num: this is the number field
 * @d_str: this is a d_string
 * @next: thia points to the next node
 */
typedef d_struct listd_str
{
	int num;
	char *d_str;
	d_struct listd_str *next;
} list_t;

/**
 *d_struct passdivas_info - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer d_struct
 *@arg: a d_string generated from getline containing arguements
 *@argv: an array of d_strings generated from arg
 *@path: a d_string path for the current command
 *@argc: the argument count
 *@d_line_count: the error count
 *@err_num: the error code for exit()s
 *@d_line_count_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readd_fd: the d_fd from which to read line input
 *@histcount: the history line number count
 */
typedef d_struct passdivas_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int d_line_count;
	int err_num;
	int d_line_count_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readd_fd;
	int histcount;
} info_t;

#define divas_info_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *d_struct builtin - contains a builtin d_string and related function
 *@type: the builtin command flag
 *@func: the function
 */

typedef d_struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* for the toem_shloop.c */
int hsh(info_t *, char **);
int d_find_builtin(info_t *);
void diva_find_cmd(info_t *);
void diva_fork_cmd(info_t *);

/* for the toem_parser.c */
int d_is_d_cmd(info_t *, char *);
char *now_dupl_chars(char *, int, int);
char *d_find_path(info_t *, char *, char *);

/* for the loophsh.c */
int loophsh(char **);

/* for the toem_errors.c */
void _diva_s_d_puts(char *);
int _diva_eputchar(char);
int _d_putd_fd(char c, int d_fd);
int _d_d_putsd_fd(char *d_str, int d_fd);

/* for the toem_d_string.c */
int _d_strlen(char *);
int _d_strcmp(char *, char *);
char *is_haystack_starts(const char *, const char *);
char *_d_strcat(char *, char *);

/* for the toem_d_string1.c */
char *_d_strcpy(char *, char *);
char *_d_strdup(const char *);
void _d_puts(char *);
int _d_putchar(char);

/* for the toem_exits.c */
char *diva_d_str_cpy(char *, char *, int);
char *_d_d_str_cat(char *, char *, int);
char *_d_strchr(char *, char);

/*  for the toem_tokenizer.c */
char **d_strtow(char *, char *);
char **d_strtow2(char *, char);

/* for the toem_divs_realloc.c */
char *memset_b_d(char *, char, unsigned int);
void divs_ffree(char **);
void *_divs_realloc(void *, unsigned int, unsigned int);

/* for the toem_memory.c */
int d_be_free(void **);

/* for the toem_atoi.c */
int is_shell_interactive(info_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int d_string_to_integer(char *);

/* for the toem_errors1.c */
int _d_erratoi(char *);
void d_print_error(info_t *, char *);
int d_print_d(int, int);
char *d_convert_number(long int, int, int);
void d_remove_comments(char *);

/* for the toem_builtin.c */
int _mycd(info_t *);
int _myhelp(info_t *);

// for the builtin_exit.c
int _myexit(info_t *);

/* for the toem_builtin1.c */
// int _diva_history(info_t *);
// int _divas_alias(info_t *);

/* for the toem_getline_diva.c */
ssize_t d_get_input(info_t *);
int _getline_diva(info_t *, char **, size_t *);
void d_sigintHdlr(int);

/* for the toem_getdivas_info.c */
void clear_divas_info(info_t *);
void set_divas_info(info_t *, char **);
void free_divas_info(info_t *, int);

/* for the toem_environ.c */
char *divas_getenv(info_t *, const char *);
int divas_env(info_t *);
int _setdivaenv(info_t *);
int _unsetdivaenv(info_t *);
int diva_env_linkedlist_populate(info_t *);

/* for the toemdivas_getenv.c */
char **d_get_environ(info_t *);
int _d_und_setenv(info_t *, char *);
int _d_setenv(info_t *, char *, char *);

/* for the toem_history.c */
char *d_get_history_file(info_t *divas_info);
int write_history_diva(info_t *divas_info);
int read_history_diva(info_t *divas_info);
int diva_build_history_list(info_t *divas_info, char *buf, int d_line_count);
int diva_renumber_history(info_t *divas_info);

/* for the toem_lists.c */
list_t *diva_addnode(list_t **, const char *, int);
list_t *diva_addnode_end(list_t **, const char *, int);
size_t d_print_list_d_str(const list_t *);
int diva_del_node_at_index(list_t **, unsigned int);
void d_free_d_list(list_t **);

/* for the toem_lists1.c */
size_t d_print_list(const list_t *);
size_t d_list_len(const list_t *);
char **list_to_d_strings(list_t *);
list_t *divas_node_is_haystack_starts(list_t *, char *, char);
ssize_t get_node_index_diva(list_t *, list_t *);

/* for the toem_vars.c */
int is_diva_chain(info_t *, char *, size_t *);
int diva_replace_d_vars(info_t *);
void is_diva_chain_check(info_t *, char *, size_t *, size_t, size_t);
int diva_replace_d_alias(info_t *);
int diva_replace_d_string(char **, char *);

#endif
