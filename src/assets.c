#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* read_file(const char* path, size_t* out_size);

float* asset_csv(const char* file_path, size_t* out_size) {
        char* csv_data = read_file(file_path, out_size);

        // Make a copy so we can safely modify it with strtok
        char* buffer = malloc(*out_size + 1);
        if (!buffer) return NULL;
        memcpy(buffer, csv_data, *out_size);
        buffer[*out_size] = '\0';
        
        // Count how many numbers there are
        size_t count = 0;
        for (size_t i = 0; i < *out_size; i++) {
            if (csv_data[i] == ',' || csv_data[i] == '\n') count++;
        }
        count++; // last value
        
        float* values = malloc(count * sizeof(float));
        if (!values) {
            free(buffer);
            return NULL;
        }
        
        // Parse the CSV
        size_t idx = 0;
        char* token = strtok(buffer, ",\n\r");
        while (token) {
            // skip whitespace
            while (isspace((unsigned char)*token)) token++;
            values[idx++] = strtof(token, NULL);
            token = strtok(NULL, ",\n\r");
        }
        
        *out_size = idx;
        free(buffer);
        free(csv_data);
        return values;
}
