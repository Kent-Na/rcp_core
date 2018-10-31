cmake_minimum_required(VERSION 3.12)
project(rcp)
set(files
	"rcp_tree.c"
	"rcp_type.c"
	"rcp_record.c"
	"rcp_array.c"
	"rcp_array_list.c"
	"rcp_string.c"
	"rcp_type_list.c"
	"rcp_type_utility.c"
	"rcp_dict.c"
	"rcp_dict_list.c"
	"rcp_number.c"
	"rcp_struct.c"
	"rcp_type_etc.c"
	"rcp_alias.c"
	"rcp_parser.c"
	"rcp_json.c"
	"rcp_json_write.c"
)

add_library(rcp_core ${files})
target_link_libraries(rcp_core m)
#compile_source_message = '\033[34mCompiling > \033[0m$SOURCE'
#link_program_message = '\033[35mLinking > \033[0m$TARGET'

#env = Environment(
	#CXXCOMSTR = compile_source_message,
	#CCCOMSTR = compile_source_message,
	#LINKCOMSTR = link_program_message,
	#ARCOMSTR = link_program_message,
	#RUNLIBCOMSTR = link_program_message,
#)
#
##env.Append(CCFLAGS = ['-O3'])
#env.Replace(CC = 'clang')
#env.Replace(CXX = 'clang++')
#env.Replace(OBJCC = 'clang')
#env.Replace(OBJCXX = 'clang++')
##env.Replace(CC = 'gcc-4.6')
##env.Replace(CXX = 'g++-4.6')
#env.Append(CCFLAGS = ['-Wall','-g'])
##env.Append(CCFLAGS = ['-Wall','-g','-O3'])
#
#cflags = [
	#'-fcolor-diagnostics',
	#'-Wno-pointer-sign',
	#'-Wno-deprecated-declarations',
	#'-Wno-narrowing',
	#'-Wno-unused']
#
##env.Append(CFLAGS = 
#env.Append(CCFLAGS = cflags)
#env.Append(CXXFLAGS = cflags)
#env.Append(CXXFLAGS = ['-std=gnu++0x'])
#env.Append(LIBS = ['m','freetype'])
##env.Append(LIBS = ['GL','glut'])
##env.Append(LIBPATH = ['/usr/local/pgsql/lib'])
#env.Append(CPPPATH = ['/usr/include/freetype2'])
#env.Append(FRAMEWORKS = ['openGL','GLUT','Cocoa'])
#
#Export('env')
#
#SConscript('SConscript', variant_dir='build', duplicate=0)
#
#env = Environment()
#Import('env')
#
#main =[
	#]
#
#env.Library(target = 'rcp_core', source = main);
