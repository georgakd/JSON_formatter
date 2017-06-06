#ifndef FORMATJSON_H_
#define FORMATJSON_H_

 
/***********************************************************************************************************************
* Make a fake json with as many counters as possible and check the file size < 10K                                     
* Examine two namespaces (you can add more): 1. group_16000, 2. group_1000                                             
* *********************************************************************************************************************/
#include "rapidJSON_api.h"

typedef unsigned long int dword;

class JsonFile {
	
	public:
	    tm_json_w_handler_t handler;	    
		static constexpr const char* element_value = "UNKNOWN"; // shared among all objects
		
	public:
	    JsonFile();
	    JsonFile(tm_json_w_handler_t handler): handler(handler) {}; //access to handler from base 
		void element_json();
		void element_json_end();
		void element_json_counter();
		void element_json_counter_end();		
		void start_rapid_json();
		void end_rapid_json();		
        void add_cnt_element(const char* elem_name, const char* elem_value);
        void add_counter_id(char* cnt_id, unsigned val);
        virtual ~JsonFile();
};

namespace group_1000 {
class Counter: public JsonFile {
	
	public:
		static const unsigned int PREFIX = 1000;
		static const unsigned int MEAS_LEN = 412;
		static const unsigned int elements = 5;
		const char* element_names[elements] = {"mcc", "mnc", "lac", "rac", "cid"}; // Case 1: LENGTH = 412 /*1000*/	
	public:	
		Counter();
		Counter(tm_json_w_handler_t handler):JsonFile(handler) {}; //access to handler from derived		
		virtual ~Counter();
			
	};
}

namespace group_16000 {	
class Counter: public JsonFile {
	
	public:
	    static const unsigned int PREFIX = 16000;
		static const unsigned int MEAS_LEN = 535;
		static const  unsigned int elements = 7;
		const char* element_names[elements] = {"iumcc", "iumnc", "iulac", "iurac", "iurnc", "iusac", "iucid"}; // Case 2: LENGTH = 535 /*16000*/
	public:
		Counter();
		Counter(tm_json_w_handler_t handler):JsonFile(handler) {}; //access to handler from derived		
		virtual ~Counter();	
	};	
}


#endif
