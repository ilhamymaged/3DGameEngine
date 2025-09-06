#include <Utility/Utility.h>

char* read_file(const char* path)
{
    FILE* filePtr = fopen(path, "r");
    if(!filePtr)
    {
        printf("FAILED TO OPEN FILE: %s\n", path);
        return NULL;
    }

    fseek(filePtr, 0, SEEK_END);
    long fileSize = ftell(filePtr);

    char* buffer = (char*)malloc(sizeof(char) * (fileSize + 1));
    if(!buffer)
    {
        printf("FAILED TO ALLOCATE MEMORY FOR THIS FILE: %s\n", path);
        fclose(filePtr);
        return NULL;
    }

    fseek(filePtr, 0, SEEK_SET);
    size_t bytesRead = fread(buffer, sizeof(char), (size_t)fileSize, filePtr);
    if(bytesRead != (size_t)fileSize)
    {
        printf("FAILED TO LOAD ALL THE FILE: %s\n", path);
        free(buffer);
        fclose(filePtr);
        return NULL;
    }
    buffer[fileSize] = '\0';

    fclose(filePtr);
    return buffer;
}
