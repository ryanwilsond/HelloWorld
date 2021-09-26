#ifndef OPTS_H
#define OPTS_H

#include <nsstring>
#include <nsvector>

/// Prints help message
void help_prompt();

/// Decodes command-line arguments
/// @param argc     argv count
/// @param argv     args to parse
/// @param o        optimize flag
/// @param output   output type flag
/// @param phase    output phase flag
/// @param source   source file storage
/// @param outfile  output file storage
int decode_arguments(int argc, char ** argv, int * o, char * output, char * phase, vector<string> * source, string * outfile);

#endif
