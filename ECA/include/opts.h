#ifndef OPTS_H
#define OPTS_H

#include <nsstring>
#include <nsvector>

/// Prints help message
/// @param path path of executable
void help_prompt(string path);

/// Decodes command-line arguments
/// @param argc     argv count
/// @param argv     args to parse
/// @param o        return optimize flag
/// @param output   return output type flag
/// @param phase    return output phase flag
/// @param source   return source file storage
/// @param outfile  return output file storage
/// @param path     return parsed path
/// @return error
int decode_arguments(int argc, char ** argv, int * o, char * output, char * phase, vector<string> * source, string * outfile, string * path);

#endif
