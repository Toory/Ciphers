#ifndef CIPHER_H
#define CIPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

#define N 10000 
#define ALPHA 26 /*Alphabet length*/

void Decrypt(char *,int);
void Encrypt(char *,int);
char *OpenFromFile(char *);
void WriteToFile(char *, char *);
void BruteForce(char *);

#endif
