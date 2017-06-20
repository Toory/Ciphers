#ifndef CIPHER_H
#define CIPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

void decrypt(char *,int);
void encrypt(char *,int);
char *OpenFromFile(char *);
void WriteToFile(char *, char *);

#endif
