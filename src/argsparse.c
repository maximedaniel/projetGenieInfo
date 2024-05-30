/*
* DO NOT EDIT THIS FILE
*/
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>

#include "argsparse.h"

static int file_count = 0 ;
static int argument_count = 0 ;
static int debug;

void parse_arguments( int argc, char **argv, Config* conf ) {
  int c ;
  int length ;
  static struct option long_options[] =
    {
      {"debug", no_argument,     &debug, 1},
      {"brief", no_argument,     &debug, 0},
      {"version",  no_argument, 0, 'v'},
      {"file",  required_argument, 0, 'f'},
      {"command",required_argument, 0, 'c'},
      {"type",  required_argument, 0, 't'},
      {0, 0, 0, 0}
    };


  while (1) {
      int option_index = 0;

      c = getopt_long (argc, argv, "f:c:v:", long_options, &option_index);
      conf->debug_mode=debug;
      /* Detect the end of the options. */
      if (c == -1) {
        break;
      }
      switch (c) {
        case 0 : break ;
        case 'f':
          length = strlen( optarg ) + 1 ;
          conf->filenames[ file_count ] = malloc( length ) ;
          strncpy( conf->filenames[ file_count ], optarg, length ) ;
          file_count = file_count + 1 ;
          break;
        case 'c':
          strncpy( conf->command, optarg, MAX_LENGTH_COMMAND ) ;
          break;
        case 't':

          break;
        case '?':
          /* getopt_long already printed an error message. */
          break;
        case 'v':
          puts("Version 1.0.0");
          exit(0);
          break;
        default:
          printf ("option %s unhandled", long_options[option_index].name);
          abort ();
        }
    }
    /* Print any remaining command line arguments (not options). */
    if (optind < argc) {
        while (optind < argc) {
          length = strlen( argv[optind] ) + 1 ;
          conf->arguments[ argument_count ] = malloc( length ) ;
          strncpy( conf->arguments[ argument_count ], argv[optind], length ) ;
          argument_count = argument_count + 1 ;
          optind = optind + 1 ;
        }
      }
}

void check_file() {
    if ( file_count < 1 ) {
        printf("Missing file\n" );
        abort();
    }
}

void check_debug_mode(Config conf) {
    if (conf.debug_mode) {
        printf("debug flag is set");
        int file_index ;
        for ( file_index = 0 ; file_index < file_count ; file_index++ ) {
            printf( "file %d/%d: %s\n", file_index + 1 , file_count, conf.filenames[ file_index ] );
        }
        int argument_index ;
        for ( argument_index = 0 ; argument_index < argument_count ; argument_index++ ) {
            printf( "arguments %d/%d: %s\n", argument_index + 1 , argument_count, conf.arguments[ argument_index ] );
        }
        printf( "option: %s\n", conf.command );
  }
}