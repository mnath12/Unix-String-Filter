#include "translate.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Helper function for interpreting escapes. Given the character that
// follows a backslash, returns the character that the combination
// should be replaced with. Recognizes the seven standard C escapes, and
// maps every other character to itself.
char interpret_escape(char c)
{
    switch (c) {
    case 'a': return '\a';
    case 'b': return '\b';
    case 'f': return '\f';
    case 'n': return '\n';
    case 'r': return '\r';
    case 't': return '\t';
    case 'v': return '\v';
    default:  return c;
    }
}

size_t charseq_length(const char* src)
{
    size_t result = 0;

    //
    // TODO: Your code goes here
    //
    int count = 0;
    size_t pos = 0;
    while (pos  < strlen(src)) {
        if (src[pos] == '\0'){
            result = count;
        }
        else if ((src[pos+1] == '-') && (src[pos+2] != '\0')) {
            char start = src[pos];
            char end = src[pos+2];
            if (start > end) {        
                pos += 3;  
            } else {
                int length = end - start + 1;
                count += length;     
                pos += 3;
            }      
        }
        else if ((src[pos] == '\\') && (src[pos+1] != '\0')) {
            count++;
            pos += 2; 
        } else {
            count++;
            pos++;
        }
    }
    result = count;    
    return result;
}

char* expand_charseq(const char* src)
{
    char* const dst = malloc(charseq_length(src) + 1);
    if (!dst) {
        return NULL;
    }

    size_t i = 0; // for position in src
    size_t j = 0; // for position in dst

    (void)i;  // Marks variable `i` as "used" to avoid a compiler warning.
              // (Delete it once you've written code that uses `i`.)

    //
    // TODO: Your code goes here
    //
     while (i < strlen(src)) {
        if (src[i] == '\0'){
            dst[j] = '\0';   
        }
        else if ((src[i+1] == '-') && (src[i+2] != '\0')) {
            int start = src[i];
            int end = src[i+2];
            if (start > end) {
                i+=3; 
            } else {
                 while (start <= end) {
                // store start to destination position advance destination position and increment start
                    dst[j] = start;
                    j++;
                    start++;
                }
            i += 3;
            }
        }
        else if ((src[i] == '\\') && (src[i+1] != '\0')) {
                dst[j] = interpret_escape(src[i+1]);
                j++;
                i += 2;
        } else {
            dst[j] = src[i];
            j++;
            i++;
        }
    }
        // change actions at each step, how do i increment j?????
    dst[j] = '\0';

    return dst;
}

char translate_char(char c, const char* from, const char* to)
{
    //
    // TODO: Your code goes here
    //
    for (int i = 0; i < strlen(from); i++) {
        if (from[i] == c) {
            c = to[i];
            break;
        }        
    }
    return c;
}

void translate(char* s, const char* from, const char* to)
{
    //
    // TODO: Your code goes here
    //
    for (int i = 0; i < strlen(s); i++) {
       s[i] =  translate_char(s[i], from, to);
    }
}

