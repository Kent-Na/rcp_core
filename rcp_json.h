#include "def/rcp_record.h"
#include "def/rcp_string.h"
#include "def/rcp_parser.h"

//type table
//json		<->		rcp

//object	<->		dict(string, ref) 
//array		<->		array(ref)
//string	<->		string
//number	<->		double or int64
//bool		<->		bool8
//null		<->		null

//object	<--		struct


rcp_extern rcp_record_ref rcp_json_parse_c_str(
		const char* begin, const char* end);

rcp_extern rcp_record_ref rcp_json_parse_c_str_and_print_error(
		const char* begin, const char* end);

rcp_extern rcp_parser_ref rcp_json_parser_new(
		const char* begin, const char* end);

rcp_extern void rcp_json_parser_delete(rcp_parser_ref parser);

rcp_extern rcp_record_ref rcp_json_parse(
		rcp_parser_ref parser);

rcp_extern rcp_record_ref rcp_json_parse_object(
		rcp_parser_ref parser);
rcp_extern rcp_record_ref rcp_json_parse_array(
		rcp_parser_ref parser);

rcp_extern rcp_record_ref rcp_json_parse_string(
		rcp_parser_ref parser);

rcp_extern int rcp_json_parse_literal(
		rcp_parser_ref parser,
		const char *literal);

rcp_extern rcp_record_ref rcp_json_parse_number(
		rcp_parser_ref parser);
