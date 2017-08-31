#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <regex.h>

#define OUTPUT stdout
#define ASCII_CHAR_SIZE 1

char* slice_str(const char* start, const char* end)
{
    int i;
    int str_len = ( (int)end - (int)start ) / ASCII_CHAR_SIZE + ASCII_CHAR_SIZE;
    char* buffer[str_len+ASCII_CHAR_SIZE];
    
    for(i=0;i<str_len+1; i++)
    {
        buffer[i] = *start;
        start += ASCII_CHAR_SIZE;
    }
    buffer[i] = '\0';
    return strdup(buffer); 
}

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        printf("Usage : %s source_str regex\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int ret, i;
    char *p_regex;
    char *p_src_str;
    char buf_err[256];

    regex_t regex_pattern;
    regmatch_t result_match[MAX_EXPR_SUB_MATCH];
    char* result_str[MAX_EXPR_SUB_MATCH];
    
    p_src_str = strdup(argv[1]);    // malloc string and return pointer
    p_regex = strdup(argv[2]);      // free() available

    if( (ret = regcomp(&regex_pattern, p_regex, p_src_str, REGE_EXTENDED | REG_NEWLINE)) != 0)  // posix extended regex | line unit
    {
        regerr(ret, &regex_pattern, buf_err, sizeof(buf_err));
        fprintf(OUTPUT, "Fail : regcomp() %s\n", buf_err);
        exit(EXIT_FAILURE);
    }

    printf("regcomp : %s\n", p_regex_str);
    bzero(&result_match, sizeof(regmatch_t));
    
    if(regexec(&regex_pattern, p_src_str, MAX_EXPR_SUB_MATCH, result_match, ret) == REG_NOMATCH )
    {
        fprintf(OUTPUT, "No Match : regexec()\n");
        exit(0);
    }
    fprintf(OUTPUT, "Matches");
    for(i=0; i<MAX_EXPR_SUB_MATCH; i++)
    {
        if(-1 == result_match[i].rm_so) 
        {
             break; 
        }else{
            fprintf("%*s\n", result_match[i].rm_eo - result_match[i].rm_so, p_src_str[result_match.rm_so]);
        }
    }
    
    free(p_src_str);
    free(p_regex);
    regfree(&regex_pattern);

    return 0;
}


