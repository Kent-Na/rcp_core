#include <stdio.h>
#include "rcp_type_pch.h"
#include "rcp_utility.h"

#include "rcp_record.h"

#define RCP_INTERNAL_STRUCTURE
#include "rcp_type.h"
#include "rcp_type_list.h"
#undef RCP_INTERNAL_STRUCTUREe

#include "rcp_string.h"
#include "rcp_array.h"
#include "rcp_array_list.h"
#include "rcp_dict.h"
#include "rcp_dict_list.h"

#include "rcp_parser.h"
#include "rcp_json.h"

static inline int rcp_json_is_number(char ch)
{
	return '0' <= ch && ch <= '9';
}

static inline int rcp_json_is_space(char ch)
{
	return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
}


static inline void rcp_json_skip_space(rcp_parser_ref parser)
{
	char ch = rcp_parser_get_char(parser);
	while (rcp_json_is_space(ch)){
		rcp_parser_increment_ptr(parser);
		ch = rcp_parser_get_char(parser);
	}
}

rcp_extern rcp_record_ref rcp_json_parse_c_str(
		const char* begin, const char* end)
{
	rcp_parser_ref parser = rcp_parser_new(begin, end);
	rcp_record_ref r_val = rcp_json_parse(parser);
	rcp_parser_delete(parser);
	return r_val;
}

rcp_extern rcp_record_ref rcp_json_parse_c_str_and_print_error(
		const char* begin, const char* end)
{
	rcp_parser_ref parser = rcp_parser_new(begin, end);
	rcp_record_ref r_val = rcp_json_parse(parser);
	rcp_parser_print_error(parser);
	rcp_parser_delete(parser);
	return r_val;
}

rcp_record_ref rcp_json_parse(rcp_parser_ref parser)
{
	//const char* ptr = *begin;

	rcp_json_skip_space(parser);

	const char ch = rcp_parser_get_char(parser);
	
	if (ch == '{'){
		return rcp_json_parse_object(parser);
	}
	else if (ch == '['){
		return rcp_json_parse_array(parser);
	}
	else if (ch == '\"'){
		return rcp_json_parse_string(parser);
	}
	else if (ch == '-' || rcp_json_is_number(ch)){
		return rcp_json_parse_number(parser);
	}
	else if (ch == 't'){
		if (rcp_json_parse_literal(parser, "true") != 0){
			rcp_parser_put_error(parser, "Unexpected token.");
			return NULL;
		}
		rcp_record_ref rec = rcp_record_new(rcp_bool8_type);
		uint8_t *data = (uint8_t*)rcp_record_data(rec);
		*data = 1;
		return rec;
	}
	else if (ch == 'f'){
		if (rcp_json_parse_literal(parser, "false") != 0){
			rcp_parser_put_error(parser, "Unexpected token.");
			return NULL;
		}
		rcp_record_ref rec = rcp_record_new(rcp_bool8_type);
		uint8_t *data = (uint8_t*)rcp_record_data(rec);
		*data = 0;
		return rec;
	}
	else if (ch == 'n'){
		if (rcp_json_parse_literal(parser, "null") != 0){
			rcp_parser_put_error(parser, "Unexpected token.");
			return NULL;
		}
		return rcp_record_new(rcp_null_type);
	}
	rcp_parser_put_error(parser, "Unexpected token.");
	return NULL;
}

rcp_record_ref rcp_json_parse_array(rcp_parser_ref parser)
{
	char ch = rcp_parser_get_char(parser);

	if (ch != '['){
		rcp_parser_put_error(parser, "Unexpected non array element.");
		return NULL;
	}

	rcp_parser_increment_ptr(parser);

	rcp_record_ref array_rec = rcp_record_new(rcp_ref_array);
	rcp_array_ref array = (rcp_array_ref)rcp_record_data(array_rec);
	rcp_record_ref rec = NULL;

	rcp_json_skip_space(parser);
	ch = rcp_parser_get_char(parser);

	if (ch == ']'){
		//end of empty array
		rcp_parser_increment_ptr(parser);
		return array_rec;
	}

	while (1){

		rec = rcp_json_parse(parser);
		if (!rec){
			rcp_string_ref err_str = rcp_string_new_with_format(
					"At array elements with index %i.", 
					rcp_array_len(array)+1);
			rcp_parser_put_error_str(parser, err_str);
			rcp_string_delete(err_str);
			break;
		}

		rcp_array_append_data(rcp_ref_array, array, (rcp_data_ref)&rec);
		rcp_record_release(rec);
		rec = NULL;

		rcp_json_skip_space(parser);
		ch = rcp_parser_get_char(parser);
		rcp_parser_increment_ptr(parser);
		rcp_json_skip_space(parser);

		if (ch == ','){
			//next element
			continue;
		}

		if (ch == ']'){
			//end of array
			return array_rec;
		}

		break;
	}
	rcp_parser_put_error(parser, "Missing end of array.");
	rcp_record_release(rec);
	rcp_record_release(array_rec);
	return NULL;
}

rcp_record_ref rcp_json_parse_object(rcp_parser_ref parser)
{
	char ch = rcp_parser_get_char(parser);


	if (ch != '{'){
		rcp_parser_put_error(parser, "Unexpected non array element.");
		return NULL;
	}

	rcp_parser_increment_ptr(parser);

	const rcp_type_ref dict_type = rcp_str_ref_dict;
	rcp_record_ref dict_rec = rcp_record_new(dict_type);
	rcp_dict_ref dict = (rcp_dict_ref)rcp_record_data(dict_rec);
	rcp_record_ref key = NULL;
	rcp_record_ref value = NULL;

	rcp_json_skip_space(parser);
	ch = rcp_parser_get_char(parser);

	if (ch == '}'){
		//end of empty object
		rcp_parser_increment_ptr(parser);
		return dict_rec;
	}

	while (1){

		key = rcp_json_parse_string(parser);
		if (!key){
			rcp_parser_put_error(parser, "Expected key.");
			break;
		}

		rcp_json_skip_space(parser);
		ch = rcp_parser_get_char(parser);
		rcp_parser_increment_ptr(parser);
		if (ch != ':'){
			rcp_parser_put_error(parser, "Missing ':'.");
			break;
		}

		//get object
		value = rcp_json_parse(parser);
		if (!value){
			rcp_string_ref err_str = rcp_string_new_with_format(
					"For object value for key \"%s\".", 
					rcp_string_c_str((rcp_string_ref)rcp_record_data(key)));
			rcp_parser_put_error_str(parser, err_str);
			rcp_string_delete(err_str);
			break;
		}

		rcp_dict_node_ref node = rcp_dict_node_new(dict_type);
		rcp_move(rcp_string_type,
				rcp_record_data(key),rcp_dict_node_key(dict_type, node));
		rcp_move(rcp_ref_type,
				(rcp_data_ref)&value,rcp_dict_node_data(dict_type, node));
		rcp_dict_set_node(dict, node);

		rcp_record_init(key);
		rcp_record_release(key);
		key = NULL;
		value = NULL;

		rcp_json_skip_space(parser);
		ch = rcp_parser_get_char(parser);
		rcp_parser_increment_ptr(parser);
		rcp_json_skip_space(parser);

		if (ch == ','){
			//next element
			continue;
		}
		if (ch == '}'){
			//end of empty object
			return dict_rec;
		}

		break;
	}

	rcp_parser_put_error(parser, "Missing end of object.");
	//fail
	rcp_record_release(key);
	rcp_record_release(value);
	rcp_record_release(dict_rec);
	return NULL;
}

rcp_record_ref rcp_json_parse_string(rcp_parser_ref parser)
{
	char ch = rcp_parser_get_char(parser);

	if (ch != '\"'){
		rcp_parser_put_error(parser, "Unexpected non string element.");
		return NULL;
	}

	rcp_record_ref out_rec = rcp_string_new_rec(NULL);
	rcp_string_ref out = (rcp_string_ref)rcp_record_data(out_rec);
	
	while (1){

		rcp_parser_increment_ptr(parser);
		ch = rcp_parser_get_char(parser);

		if (ch == '\"'){
			//end of string
			rcp_string_put(out, '\0');
			rcp_parser_increment_ptr(parser);
			return out_rec;
		}
		if (ch == '\\'){
			rcp_parser_increment_ptr(parser);
			ch = rcp_parser_get_char(parser);

			if (ch == '\"')
				rcp_string_put(out, '\"');
			else if (ch == '\\')
				rcp_string_put(out, '\\');
			else if (ch == '/')
				rcp_string_put(out, '/');
			else if (ch == 'b')
				rcp_string_put(out, '\b');
			else if (ch == 'f')
				rcp_string_put(out, '\f');
			else if (ch == 'n')
				rcp_string_put(out, '\n');
			else if (ch == 'r')
				rcp_string_put(out, '\r');
			else if (ch == 't')
				rcp_string_put(out, '\t');
			else if (ch == 'u'){
				rcp_parser_put_error(parser, 
						"Unicode escape are not supported.");
				break;
			}
			else{
				rcp_parser_put_error(parser, "Unknown charactor escape.");
				break;
			}

			continue;
		}
		{
			rcp_string_put(out, ch);
		}
	}
	rcp_parser_put_error(parser, "Missing end of string.");
	rcp_record_release(out_rec);
	return NULL;
}

int rcp_json_parse_literal(rcp_parser_ref parser, const char *literal)
{
	const char *ptr_src = rcp_parser_get_ptr(parser) + 1;
	const char *ptr_dst = literal + 1;
	while (*ptr_dst){
		if (ptr_src > rcp_parser_get_end(parser)){
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
	rcp_parser_set_ptr(parser, ptr_src);
	return 0;
}

rcp_extern rcp_record_ref rcp_json_parse_number(rcp_parser_ref parser)
{
	int sign = 1;
	int exp_sign = 1;
	int64_t significand= 0;
	//uint64_t fraction_part = 0;
	int64_t exponential_part_offset = 0;
	int64_t exponential_part = 0;

	char ch;

	ch = rcp_parser_get_char(parser);

	if (ch == '-'){
		sign = -1;
		rcp_parser_increment_ptr(parser);
	}

	// interger part
	ch = rcp_parser_get_char(parser);

	if (ch == '0'){
		rcp_parser_increment_ptr(parser);
	}
	else if (rcp_json_is_number(ch)){
		while (rcp_json_is_number(ch)){
			significand = significand * 10 + (ch - '0');
			rcp_parser_increment_ptr(parser);
			ch = rcp_parser_get_char(parser);
		}
	}
	else{
		rcp_parser_put_error(parser, "Unexpected charactor in the number.");
		return NULL;
	}
	
	// fraction part
	ch = rcp_parser_get_char(parser);

	if (ch == '.'){
		rcp_parser_increment_ptr(parser);

		ch = rcp_parser_get_char(parser);

		if (rcp_json_is_number(ch)){
			while (rcp_json_is_number(ch)){
				significand = significand * 10 + (ch - '0');
				exponential_part_offset --;
				rcp_parser_increment_ptr(parser);
				ch = rcp_parser_get_char(parser);
			}
		}
		else{
			rcp_parser_put_error(parser, 
					"Unexpected charactor in the number.");
			return NULL;
		}
	}
	significand*=sign;

	ch = rcp_parser_get_char(parser);

	// exponential part
	if (ch == 'e' || ch == 'E'){
		rcp_parser_increment_ptr(parser);

		ch = rcp_parser_get_char(parser);

		if (ch == '-'){
			rcp_parser_increment_ptr(parser);
			exp_sign = -1;
		}
		else if (ch == '+'){
			rcp_parser_increment_ptr(parser);
		}

		ch = rcp_parser_get_char(parser);

		if (rcp_json_is_number(ch)){
			while (rcp_json_is_number(ch)){
				exponential_part = exponential_part * 10 + (ch - '0');
				rcp_parser_increment_ptr(parser);
				ch = rcp_parser_get_char(parser);
			}
		}
		else{
			rcp_parser_put_error(parser, 
					"Unexpected charactor in the number.");
			return NULL;
		}
	}

	exponential_part = exponential_part*exp_sign + 
		exponential_part_offset;

	if (exponential_part == 0){
		rcp_record_ref rec = rcp_record_new(rcp_int64_type);
		int64_t *dat = (int64_t*)rcp_record_data(rec);
		*dat = significand;
		return rec;
	}
	else{
		//double
		rcp_record_ref rec = rcp_record_new(rcp_double_type);
		double *dat = (double*)rcp_record_data(rec);
		*dat = significand * pow(10.0 , exponential_part);
		return rec;
	}
}
