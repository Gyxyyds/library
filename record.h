#ifndef __RECORD_H__
#define __RECORD_H__

typedef struct Record 
{
    char userId[20];
    char ISBN[20];
    char borrowDate[20];
    char returnDate[20];
    int quantity;
    char note[100];
} RECORD;

#endif