#include "def/rcp_parser.h"

rcp_extern rcp_parser_ref rcp_parser_new(
		const char* begin, const char* end);

rcp_extern void rcp_parser_delete(rcp_parser_ref parser);

const char* rcp_parser_get_ptr(rcp_parser_ref parser);
const char* rcp_parser_get_begin(rcp_parser_ref parser);
const char* rcp_parser_get_end(rcp_parser_ref parser);
void rcp_parser_set_ptr(rcp_parser_ref parser, const char* ptr);
void rcp_parser_reset_range(
		rcp_parser_ref parser, const char* begin, const char* end);

void rcp_parser_increment_ptr(rcp_parser_ref parser);
char rcp_parser_get_char(rcp_parser_ref parser);

void rcp_parser_print_error(
		rcp_parser_ref parser);

void rcp_parser_put_error_str(
		rcp_parser_ref parser, rcp_string_ref message);
void rcp_parser_put_error(
		rcp_parser_ref parser, const char* message);

int rcp_parser_parse_c_string(rcp_parser_ref parser, const char *target);
