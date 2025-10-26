#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* path, size_t* out_len) {
    FILE *fp = fopen(path, "rb");

    if (!fp) return NULL;

    if (fseek(fp, 0, SEEK_END) != 0) { 
            fclose(fp); return NULL; 
    }

    long sz = ftell(fp);
    
    if (sz < 0) { 
            fclose(fp); 
            return NULL; 
    }

    rewind(fp);
    char *buf = malloc((size_t)sz + 1);
    
    if (!buf) { 
            fclose(fp); 
            return NULL; 
    }
    
    size_t n = fread(buf, 1, (size_t)sz, fp);
    fclose(fp);
    buf[n] = '\0';
    
    if(out_len) *out_len = n;
    return buf;
}
