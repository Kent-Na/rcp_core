#include <stdio.h>
#include "rcp_type_pch.h"
#include "rcp_utility.h"

//#include "rcp_record.h"

//#define RCP_INTERNAL_STRUCTURE
//#include "rcp_type.h"
//#include "rcp_type_list.h"
//#undef RCP_INTERNAL_STRUCTUREe

#include "rcp_string.h"
#include "rcp_array.h"
#include "rcp_array_list.h"
//#include "rcp_dict.h"
//#include "rcp_dict_list.h"

#include "rcp_parser.h"

struct rcp_parser_core{
	const char* begin;
	const char* end;
	const char* ptr;
	rcp_array_ref errors;
};

void rcp_parser_init(
		rcp_parser_ref parser, const char* begin, const char* end);

void rcp_parser_deinit(
		rcp_parser_ref parser);


rcp_extern rcp_parser_ref rcp_parser_new(
		const char* begin, const char* end)
{
	rcp_parser_ref parser;
	parser = malloc(sizeof *parser);
	rcp_parser_init(parser, begin, end);
	return parser;
}

rcp_extern void rcp_parser_delete(rcp_parser_ref parser)
{
	rcp_parser_deinit(parser);
	free(parser);
}

void rcp_parser_init(
		rcp_parser_ref parser, const char* begin, const char* end)
{
	parser->begin = begin;
	parser->ptr = begin;
	parser->end = end;
	parser->errors = rcp_array_new(rcp_string_array);
}

void rcp_parser_deinit(
		rcp_parser_ref parser)
{
	rcp_array_delete(rcp_string_array, parser->errors);
}

const char* rcp_parser_get_ptr(rcp_parser_ref parser){
	return parser->ptr;
}
const char* rcp_parser_get_begin(rcp_parser_ref parser){
	return parser->begin;
}
const char* rcp_parser_get_end(rcp_parser_ref parser){
	return parser->end;
}
void rcp_parser_reset_range(
		rcp_parser_ref parser, const char* begin, const char* end)
{
	parser->ptr = begin;
	parser->begin = begin;
	parser->end = end;
}
void rcp_parser_set_ptr(rcp_parser_ref parser, const char* ptr){
	parser->ptr = ptr;
}

void rcp_parser_increment_ptr(rcp_parser_ref parser){
	parser->ptr ++;
}

char rcp_parser_get_char(rcp_parser_ref parser)
{
	if (parser->ptr >= parser->end)
		return '\0';
	else 
		return *parser->ptr;
}

void rcp_parser_print_error(
		rcp_parser_ref parser)
{
	rcp_array_iterater_ref itr = rcp_array_begin(parser->errors);
	while(itr){
		rcp_string_ref str = (rcp_string_ref)rcp_array_iterater_data(itr);
		printf("%s\n", rcp_string_c_str(str));
		itr = 
			rcp_array_iterater_next(rcp_string_array, parser->errors, itr);
	}
}

void rcp_parser_put_error_str(
		rcp_parser_ref parser, rcp_string_ref message)
{
	if (! message) return;
	rcp_array_append_data(
			rcp_string_array, parser->errors, (rcp_data_ref)message);
}

void rcp_parser_put_error(
		rcp_parser_ref parser, const char* message)
{
	if (! message) return;
	rcp_string_ref err_str = rcp_string_new(message);
	rcp_parser_put_error_str(parser, err_str);
	rcp_string_delete(err_str);
}

int rcp_parser_parse_c_string(rcp_parser_ref parser, const char *target)
{
	const char *ptr_src = parser->ptr;
	const char *ptr_dst = target;
	while (*ptr_dst){
		if (ptr_src > parser->end){
			//Not enough charactor.
			return -1;
		}
		if (*ptr_src != *ptr_dst){
			//Missmatch
			return -1;
		}
		ptr_src++;
		ptr_dst++;
	}
	parser->ptr = ptr_src;
	return 0;
}
