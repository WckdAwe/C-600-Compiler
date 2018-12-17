/*
  Dimitriadis Vasileios || 2116104
  Kouskouras Taxiarchis || 2116162
  Papageorgiou Grigoris || 2116025
 */
#ifndef SETTINGS_H_INCLUDE_GUARD
#define SETTINGS_H_INCLUDE_GUARD

#define MAX_ERRORS                  0
#define MAX_STR_CONST               256

#ifndef FLEX_DEBUG
#define FLEX_DEBUG                  0
#define FLEX_SHOW_TOKENS            1
#define FLEX_SHOW_COMMENTS          1
#define FLEX_SHOW_NUMERIC           1
#define FLEX_SHOW_STRINGS           1
#endif

#ifndef HASHTBL_DEBUG
#define HASHTBL_DEBUG               0
#define HASHTBL_SHOW_INSERT         1
#define HASHTBL_SHOW_GET            1
#define HASHTBL_SHOW_GET_AS_TABLE   0
#endif

#endif
