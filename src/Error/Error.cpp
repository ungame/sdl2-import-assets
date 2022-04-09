#include "Error.hpp"

#include <string.h>
#include <stdlib.h>

Error::Error(const char* err)
{
    int len = strlen(err);
    
    if (len == 0)
        return;

    _error = (char*) malloc(len);

    strncpy(_error, err, len);
}

Error::~Error()
{
    if(_error != nullptr)
        free(_error);
}