#include "rcp_type_pch.h"
#include "rcp_utility.h"
#include "rcp_json_write.h"

#define RCP_INTERNAL_STRUCTURE
#include "rcp_type.h"
#include "rcp_type_list.h"
#include "rcp_tree.h"
#include "rcp_dict.h"
#include "rcp_dict_list.h"

RCP_DICT_TEMPLATE(rcp_int64_ref_dict_def, 
		&rcp_int64_type_def, &rcp_ref_type_def);
RCP_DICT_TEMPLATE(rcp_uint32_ptr_dict_def, 
		&rcp_uint32_type_def, &rcp_pointer_type_def);
RCP_DICT_TEMPLATE(rcp_str_ref_dict_def, 
		&rcp_string_type_def, &rcp_ref_type_def);
RCP_DICT_TEMPLATE(rcp_str_uint64_dict_def, 
		&rcp_string_type_def, &rcp_uint64_type_def);
RCP_DICT_TEMPLATE(rcp_str_ptr_dict_def, 
		&rcp_string_type_def, &rcp_pointer_type_def);
RCP_DICT_TEMPLATE(rcp_str_str_dict_def, 
		&rcp_string_type_def, &rcp_string_type_def);
RCP_DICT_TEMPLATE(rcp_uint32_null_dict_def, 
		&rcp_uint32_type_def, &rcp_null_type_def);
RCP_DICT_TEMPLATE(rcp_ref_null_dict_def, 
		&rcp_ref_type_def, &rcp_null_type_def);
RCP_DICT_TEMPLATE(rcp_ptr_null_dict_def, 
		&rcp_pointer_type_def, &rcp_null_type_def);

const rcp_type_ref rcp_int64_ref_dict = 
	&rcp_int64_ref_dict_def.core;
const rcp_type_ref rcp_uint32_ptr_dict = 
	&rcp_uint32_ptr_dict_def.core;
const rcp_type_ref rcp_str_uint64_dict = 
	&rcp_str_uint64_dict_def.core;
const rcp_type_ref rcp_str_ref_dict = 
	&rcp_str_ref_dict_def.core;
const rcp_type_ref rcp_str_ptr_dict = 
	&rcp_str_ptr_dict_def.core;
const rcp_type_ref rcp_str_str_dict = 
	&rcp_str_str_dict_def.core;
const rcp_type_ref rcp_uint32_null_dict = 
	&rcp_uint32_null_dict_def.core;
const rcp_type_ref rcp_ref_null_dict = 
	&rcp_ref_null_dict_def.core;
const rcp_type_ref rcp_ptr_null_dict = 
	&rcp_ptr_null_dict_def.core;
