#ifndef ASSETS_H
#define ASSETS_H

#include <stdlib.h>

#include "etc.h"

/// @brief Reads csv file into a float* into printing
/// Expected format for the csv is X, Y, Z, R, G, B\n
/// @param file_path String to open the file
/// @param out_size The size of the float array
/// @returns an array of floats - Make sure this gets freed when done 
EXTERN_C float* asset_csv(const char* file_path, size_t* out_size);

#endif
