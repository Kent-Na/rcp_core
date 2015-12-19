#include "rcp_type_pch.h"
#include "rcp_utility.h"

#define RCP_INTERNAL_STRUCTURE

#include "rcp_type.h"
#include "rcp_record.h"
#include "rcp_dict.h"
#include "rcp_type_list.h"


void rcp_bool8_copy(
		rcp_type_ref type, rcp_data_ref src, rcp_data_ref dst){
	*(uint8_t*)dst = *(uint8_t*)src;
}
void rcp_bool32_copy(
		rcp_type_ref type, rcp_data_ref src, rcp_data_ref dst){
	*(uint32_t*)dst = *(uint32_t*)src;
}


void rcp_ref_init(rcp_type_ref type, rcp_data_ref data)
{
	rcp_record_ref *rec = (rcp_record_ref*)data;
	*rec = NULL;
}

void rcp_ref_deinit(rcp_type_ref type, rcp_data_ref data)
{
	rcp_record_ref *rec = (rcp_record_ref*)data;
	rcp_record_release(*rec);
}

void rcp_ref_copied(rcp_type_ref type, rcp_data_ref data)
{
	rcp_record_ref *rec = (rcp_record_ref*)data;
	rcp_record_retain(*rec);
}

void rcp_ref_copy(
		rcp_type_ref type, rcp_data_ref src, rcp_data_ref dst)
{
	rcp_record_ref *src_rec = (rcp_record_ref*)src;
	rcp_record_ref *dst_rec = (rcp_record_ref*)dst;
	rcp_record_retain(*src_rec);
	*dst_rec = *src_rec;
}

int  rcp_ref_compare(rcp_type_ref type, rcp_data_ref l, rcp_data_ref r)
{
	if (*(rcp_record_ref*)l<*(rcp_record_ref*)r)
		return -1;
	if (*(rcp_record_ref*)l>*(rcp_record_ref*)r)
		return +1;
	return 0;
}
void rcp_ref_at(rcp_type_ref *io_type, rcp_data_ref *io_data,
		rcp_type_ref key_type, rcp_data_ref key_data)
{
	rcp_record_ref rec = *(rcp_record_ref*)*io_data;
	*io_type = rcp_record_type(rec);
	*io_data = rcp_record_data(rec);
	rcp_at(io_type, io_data, key_type, key_data);
}

rcp_record_ref rcp_record_as_ref(rcp_record_ref rec){
	if (rcp_record_type(rec) != rcp_ref_type)
		return NULL;
	return *(rcp_record_ref*)rcp_record_data(rec);
}

rcp_record_ref rcp_dict_node_as_ref(
		rcp_type_ref dict_type, rcp_dict_node_ref node){
	if (rcp_dict_type_data_type(dict_type) != rcp_ref_type)
		return NULL;
	return *(rcp_record_ref*)rcp_dict_node_data(dict_type, node);
}
