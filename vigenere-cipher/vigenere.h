#ifndef VIGENERE_H
#define VIGENERE_H

char *OpenFromFile(char *);
void Encrypt(char *,int);
void Decrypt(char*,int);
void GetShifts(int *,char *);
void Vigenere(char *,char *,char *);
void WriteToFile(char *, char *);

#endif
