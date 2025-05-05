#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // TODO: Read the hashes file into an array.
    //   Use either a 2D array or an array of arrays.
    //   Use the loadFile function from fileutil.c
    //   Uncomment the appropriate statement.
    int size;
    //char (*hashes)[HASH_LEN] = loadFile(argv[1], &size);
    char **hashes = loadFile(argv[1], &size);
    
    // CHALLENGE1: Sort the hashes using qsort.
    
    // TODO
    // Open the password file for reading.
    FILE *dictFile = fopen(argv[2], "r");
    if (!dictFile) {
        fprintf(stderr, "Error opening dictionary file.\n");
        exit(1);
    }

    // TODO
    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.
    int cracked = 0;
    char word[PASS_LEN];

    while (fgets(word, PASS_LEN, dictFile)) {
        // Trim newline
        int i = 0;
        while (word[i] != '\0') {
            if (word[i] == '\n') {
                word[i] = '\0';
                break;
            }
            i++;
        }

        char *hashed = md5(word, strlen(word));

        // If you find it, display the password and the hash.
        // Keep track of how many hashes were found.
        if (linearSearch(hashes, size, hashed) != -1) {
            printf("%s %s\n", hashed, word);
            cracked++;
        }

        free(hashed);
    }

    // TODO
    // When done with the file:
    //   Close the 
    fclose(dictFile);

    //   Display the number of hashes found.
    printf("%d hashes cracked!\n", cracked);

    //   Free up memory.
    freeAA(hashes, size);
}
