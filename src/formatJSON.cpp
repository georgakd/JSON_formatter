/**********************************************************************************************************************
* Make a fake json with as many counters as possible and check the file size < 10K                                     
* Examine two namespaces (you can add more): 1. group_16000, 2. group_1000                                             
* *********************************************************************************************************************/

// You can add the Counter from the namespace of your choice e.g. group_1000::Counter etc...
// Example group names are: min group_1000.... max group_16000.
// As group index increases the json file size increases.

#include <iostream>
#include "formatJSON.h"
#include "rapidJSON_api.h"

JsonFile::JsonFile(){} //default
group_16000::Counter::Counter(){} //default

group_16000::Counter Wtot; //general
group_16000::Counter Welem; //element
group_16000::Counter Wval; //counter values


void JsonFile::element_json() {
	Welem.handler = tm_json_write_create();
	tm_json_write_object_start(Welem.handler);
}

void JsonFile::element_json_end() {
	tm_json_write_object_end(Welem.handler);	
}

void JsonFile::element_json_counter() {
	Wval.handler = tm_json_write_create();
	tm_json_write_object_start(Wval.handler);
}

void JsonFile::element_json_counter_end() {
	tm_json_write_object_end(Wval.handler);	
}


void JsonFile::start_rapid_json() {
    long epocstart;
    
	time_t epoch = time(NULL); //seconds
	if (epoch == -1) { std::cout << "time() failure"; return; }
  
   	epocstart = (uint64_t)epoch; 	   	
	epocstart = epocstart*1000; //msec	
	epocstart = epocstart - (epocstart%60000); //min	
	
	Wtot.handler = tm_json_write_create(); //json constructor
	
    tm_json_write_object_start(Wtot.handler);
    tm_json_write_string(Wtot.handler,"time");
    tm_json_write_uint64(Wtot.handler,epocstart);
    tm_json_write_string(Wtot.handler,"source");    
    tm_json_write_object_start(Wtot.handler);
    tm_json_write_string(Wtot.handler,"app");
    tm_json_write_string(Wtot.handler,"my_counter_app");
    tm_json_write_string(Wtot.handler,"ver");
    tm_json_write_string(Wtot.handler,"0.1");
    tm_json_write_object_end(Wtot.handler);   
    tm_json_write_string(Wtot.handler,"eventType");
    tm_json_write_string(Wtot.handler,"counter");
    tm_json_write_string(Wtot.handler,"eventFields");
    tm_json_write_array_start(Wtot.handler);
}

void JsonFile::end_rapid_json() {
	
	tm_json_write_array_end(Wtot.handler);
    tm_json_write_object_end(Wtot.handler); 

    std::cout << tm_json_write_result(Wtot.handler) << std::endl;    
}

void JsonFile::add_cnt_element(const char* elem_name, const char* elem_value) {
	tm_json_write_string(Welem.handler,elem_name);
	tm_json_write_string(Welem.handler,elem_value);
}

void JsonFile::add_counter_id(char* cnt_id, unsigned val) {
	tm_json_write_string(Wval.handler,cnt_id);
	tm_json_write_uint(Wval.handler,val);
}

group_16000::Counter::~Counter(){}
JsonFile::~JsonFile(){}
