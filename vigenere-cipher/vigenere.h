#ifndef VIGENERE_H
#define VIGENERE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

#define N 10000
#define ALPHA 26 /*Alphabet length*/

char *OpenFromFile(char *);
void Encrypt(char *,int);
void Decrypt(char*,int);
void GetShifts(int *,char *);
void Vigenere(char *,char *,char *);
void WriteToFile(char *, char *);

#endif
