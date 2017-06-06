#ifndef RAPIDJSON_API_H_
#define RAPIDJSON_API_H_

/*****************************************************************************
 * Wrapper functions needed in the API for stringified JSON
 *****************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>



// A collection of function pointers needed by Reader in rapidJSON
typedef struct tm_json_r_handler {
  void (*Default)(void);
  void (*Null)(void);
  void (*Bool)(bool);
  void (*Int)(int);
  void (*Uint)(unsigned);
  void (*Int64)(int64_t);
  void (*Uint64)(uint64_t);
  void (*Double)(double);
  void (*String)(const char*,size_t,bool);
  void (*StartObject)();
  void (*EndObject)(size_t);
  void (*StartArray)(void);
  void (*EndArray)(size_t);
} tm_json_r_handler_t;

// Writer and StringBuffer for the JSON writing
typedef void* tm_json_writer_t;
typedef void* tm_json_stringbuffer_t;
typedef struct tm_json_w_handler {
  tm_json_writer_t writer;
  tm_json_stringbuffer_t stringBuffer;
} tm_json_w_handler_t;

tm_json_w_handler_t tm_json_write_create();
int tm_json_write_string (tm_json_w_handler_t, const char*);
int tm_json_write_boolean (tm_json_w_handler_t, int);
int tm_json_write_number (tm_json_w_handler_t, double);
int tm_json_write_uint (tm_json_w_handler_t, unsigned);
int tm_json_write_uint64 (tm_json_w_handler_t, uint64_t);
int tm_json_write_null (tm_json_w_handler_t);
int tm_json_write_object_start (tm_json_w_handler_t);
int tm_json_write_object_end (tm_json_w_handler_t);
int tm_json_write_array_start (tm_json_w_handler_t);
int tm_json_write_array_end (tm_json_w_handler_t);
int tm_json_write_object_string (tm_json_w_handler_t,  const char*);
const char* tm_json_write_result (tm_json_w_handler_t);
void tm_json_write_file_result (tm_json_w_handler_t);
int tm_json_write_destroy(tm_json_w_handler_t);

#endif
