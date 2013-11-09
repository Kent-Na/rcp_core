env = Environment()
Import('env')

main =[
	'rcp_utility.c',
	'rcp_tree.c',
	'rcp_type.c',
	'rcp_record.c',
	'rcp_array.c',
	'rcp_array_list.c',
	'rcp_string.c',
	'rcp_type_list.c',
	'rcp_type_utility.c',
	'rcp_dict.c',
	'rcp_dict_list.c',
	'rcp_number.c',
	'rcp_struct.c',
	'rcp_type_etc.c',
	'rcp_alias.c',
	'rcp_json.c',
	'rcp_json_write.c',
	]

env.Library(target = 'rcp_core', source = main);
