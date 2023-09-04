#ifndef __MD5_H__
#define __MD5_H__


void md5_data(const void* data, unsigned int size, char* result);
void md5_file(const char* file_name, char* result);


#endif
