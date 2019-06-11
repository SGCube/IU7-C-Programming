#define MAX 20

void sep_words(char *line, char words[][MAX], int *len_arr);
void print_to_file(char words[][MAX], int len_arr, FILE *f);
void del(char words[][MAX], int *len_arr, char result[][MAX]);