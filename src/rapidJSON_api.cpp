/******************************************************************************
 * Wrapper functions needed in the API for stringified JSON
 *****************************************************************************/
#include <iostream>
#include "rapidJSON_api.h"
#include "lib/rapidjson/include/rapidjson/document.h"
#include "lib/rapidjson/include/rapidjson/writer.h"
#include "lib/rapidjson/include/rapidjson/rapidjson.h"
#include "lib/rapidjson/include/rapidjson/filereadstream.h"
#include "lib/rapidjson/include/rapidjson/filewritestream.h"
#include "lib/rapidjson/include/rapidjson/stringbuffer.h"
#define MAX_LENGTH 65536

using namespace rapidjson;

// Creates a new Writer, StringBuffer struct object
tm_json_w_handler_t tm_json_write_create() {

	tm_json_w_handler_t wh;
	
	// allocate the string buffer and assign it in the struct
	StringBuffer* sb = new StringBuffer();
	wh.stringBuffer = static_cast<tm_json_stringbuffer_t>(sb);

	// allocate the writer and assign it in the struct
	Writer<StringBuffer>* w = new Writer<StringBuffer>(*sb);
	wh.writer = static_cast<tm_json_writer_t>(w);
	
	return wh;
}

// Writes out a String
int tm_json_write_string(tm_json_w_handler_t wh, const char* value) {
	Writer<StringBuffer>* w = static_cast<Writer<StringBuffer>*>(wh.writer);
	w->String(value);
	return 0;
}

// Writes out a Bool
int tm_json_write_boolean (tm_json_w_handler_t wh, int value) {
	Writer<StringBuffer>* w = static_cast<Writer<StringBuffer>*>(wh.writer);
	w->Bool(value);
	return 0;
}

// Writes out a Double
int tm_json_write_number (tm_json_w_handler_t wh, double value) {
	Writer<StringBuffer>* w = static_cast<Writer<StringBuffer>*>(wh.writer);
	w->Double(value);
	return 0;
}

// Writes out a uint
int tm_json_write_uint (tm_json_w_handler_t wh, unsigned value) {
	Writer<StringBuffer>* w = static_cast<Writer<StringBuffer>*>(wh.writer);
	w->Uint(value);
	return 0;
}

// Writes out a uint64
int tm_json_write_uint64 (tm_json_w_handler_t wh, uint64_t value) {
	Writer<StringBuffer>* w = static_cast<Writer<StringBuffer>*>(wh.writer);
	w->Uint64(value);
	return 0;
}

// Writes out an object start
int tm_json_write_object_start (tm_json_w_handler_t wh) {
	Writer<StringBuffer>* w = static_cast<Writer<StringBuffer>*>(wh.writer);
	w->StartObject();
	return 0;
}

// Writes out an object end
int tm_json_write_object_end (tm_json_w_handler_t wh) {
	Writer<StringBuffer>* w = static_cast<Writer<StringBuffer>*>(wh.writer);
	w->EndObject();
	return 0;
}

// Writes out an array start
int tm_json_write_array_start (tm_json_w_handler_t wh) {
	Writer<StringBuffer>* w = static_cast<Writer<StringBuffer>*>(wh.writer);
	w->StartArray();
	return 0;
}

// Writes out an array end
int tm_json_write_array_end (tm_json_w_handler_t wh) {
	Writer<StringBuffer>* w = static_cast<Writer<StringBuffer>*>(wh.writer);
	w->EndArray();
	return 0;
}

// Writes out an object as string
int tm_json_write_object_string (tm_json_w_handler_t wh, const char* value) {
	Writer<StringBuffer>* w = static_cast<Writer<StringBuffer>*>(wh.writer);
	w->Object(value);
	return 0;
}

// Writes final result
const char* tm_json_write_result (tm_json_w_handler_t wh) {
	StringBuffer* sb = static_cast<StringBuffer*>(wh.stringBuffer);
	return sb->GetString();
}

// Writes to file output.json for testing purposes
void tm_json_write_file_result (tm_json_w_handler_t wh) {
	StringBuffer* sb = static_cast<StringBuffer*>(wh.stringBuffer);
	Document d;
	d.Parse(sb->GetString());
	
	FILE *fp = fopen("output.json", "w");
	char writeBuffer[MAX_LENGTH];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	Writer<FileWriteStream> writer(os);
	d.Accept(writer);
	fclose(fp);
}



// Frees the writer, string buffer and the struct holding them
int tm_json_write_destroy(tm_json_w_handler_t wh) {
	delete static_cast<Writer<StringBuffer>*>(wh.writer);
	delete static_cast<StringBuffer*>(wh.stringBuffer);
	return 0;
}
