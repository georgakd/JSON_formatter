/**********************************************************************************************************************
* Make a fake json with as many counters as possible and check the file size < 10K                                     
* Examine two namespaces (you can add more): 1. group_16000, 2. group_1000                                             
* *********************************************************************************************************************/

#include <iostream>
#include "formatJSON.h"

using namespace group_16000;

int main(){
	
	unsigned val = 0; 
	char *cnt_id = NULL; 
	cnt_id = new char[10]; //create an array of 10 chars
	
	extern	Counter Wtot; //general
	extern  Counter Welem; //element
	extern  Counter Wval; //counter values
	
	Wtot.start_rapid_json();
	Wtot.element_json(); //fill the elements the first time
	for (unsigned int i=0;i<Wtot.elements;++i) Wtot.add_cnt_element(Wtot.element_names[i],Wtot.element_value);		
	Wtot.element_json_counter();
	
	for (unsigned int j=0;j<Wtot.MEAS_LEN;++j) 
	{ 		
		
		sprintf(cnt_id,"%d",j+Wtot.PREFIX);
		
		Wtot.add_counter_id(cnt_id,val);		
		
		if ( ((j % 100) == 99) || (j == (Wtot.MEAS_LEN - 1)) ) 
			{
			 Wtot.element_json_end();
			 Wtot.element_json_counter_end();
			 					
			 tm_json_write_object_start(Wtot.handler);  	  	
			 tm_json_write_string(Wtot.handler,"entity");
			 tm_json_write_object_string(Wtot.handler, tm_json_write_result(Welem.handler));			
			 tm_json_write_string(Wtot.handler,"values");
			 tm_json_write_object_string(Wtot.handler, tm_json_write_result(Wval.handler));		
			
			 Wtot.element_json();
			 for (unsigned int i=0;i<Wtot.elements;++i) Wtot.add_cnt_element(Wtot.element_names[i],Wtot.element_value);
			 Wtot.element_json_counter();
			 tm_json_write_object_end(Wtot.handler);				
			}
	}		

	tm_json_write_destroy(Welem.handler);
    tm_json_write_destroy(Wval.handler);
    //tm_json_write_file_result(Wtot.handler); // fix-it, empty file
	Wtot.end_rapid_json();	
	tm_json_write_destroy(Wtot.handler);
	
	delete [] cnt_id;
	return 0;
	}
