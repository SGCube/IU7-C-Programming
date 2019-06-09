#ifndef __STR_H__
#define __STR_H__

int text_read(FILE *f, char **txt);
int find_words(char *txt, char **words);
void word_times(char *words, int nw, FILE *f);

#endif