#include "def/rcp_type.h"

#ifdef RCP_INTERNAL_STRUCTURE

#define RCP_DICT_TEMPLATEA \
	{\
		sizeof(struct rcp_tree_core),\
		0,\
		NULL,\
		rcp_dict_init,\
		rcp_dict_deinit,\
		rcp_dict_copied,\
		rcp_default_compare,\
		rcp_dict_write_json,\
		rcp_dict_at,\
		rcp_default_replace,\
		rcp_dict_merge,\
		rcp_dict_unset,\
	}

#define RCP_DICT_TEMPLATEB(key,data) \
	{RCP_DICT_TEMPLATEA,{(key),(data)}}

#define RCP_DICT_TEMPLATE(name,key,data) \
	struct rcp_dict_core name = RCP_DICT_TEMPLATEB(key,data);

//This shoul'd called as rcp_dict_type_core
struct rcp_dict_core{
	struct rcp_type_core core;
	struct rcp_type_dict_ext ext;
};

#endif //RCP_INTERNAL_STRUCTURE

extern const rcp_type_ref rcp_int64_ref_dict;
extern const rcp_type_ref rcp_uint32_ptr_dict;
extern const rcp_type_ref rcp_str_ref_dict; 
extern const rcp_type_ref rcp_str_uint64_dict;
extern const rcp_type_ref rcp_str_ptr_dict; 
extern const rcp_type_ref rcp_str_str_dict; 
extern const rcp_type_ref rcp_uint32_null_dict;
extern const rcp_type_ref rcp_ref_null_dict;
extern const rcp_type_ref rcp_ptr_null_dict;
