#include "def/rcp_tree.h"

typedef struct rcp_tree_node_core *rcp_tree_node_ref;

#ifdef RCP_INTERNAL_STRUCTURE
struct rcp_tree_core{
	rcp_tree_node_ref root;
	int (*compare)(const void *extra_data, void *l, void *r);
	void* extra_data;
};

//forrowed by data
struct rcp_tree_node_core{
	// l < r
	struct rcp_tree_node_core *l;
	struct rcp_tree_node_core *r;
	struct rcp_tree_node_core *p;
	//0 black 1 red
	uint8_t color;
};
#endif

rcp_extern rcp_tree_node_ref rcp_tree_node_new(size_t size);
rcp_extern void rcp_tree_node_delete(rcp_tree_node_ref node);
rcp_extern void *rcp_tree_node_data(rcp_tree_node_ref node);
rcp_extern rcp_tree_node_ref rcp_tree_node_next(rcp_tree_node_ref node);

rcp_extern rcp_tree_ref rcp_tree_new(
		int(*compare)(const void*,void*,void*), void* extra_data);
rcp_extern void rcp_tree_init(
		rcp_tree_ref tree, 
		int(*const compare)(void const*,void*,void*), void* extra_data);
rcp_extern void rcp_tree_deinit(rcp_tree_ref tree);
rcp_extern void rcp_tree_delete(rcp_tree_ref tree);
rcp_extern void rcp_tree_verify(rcp_tree_ref tree);
rcp_extern void rcp_tree_free(rcp_tree_ref tree);
rcp_extern rcp_tree_node_ref rcp_tree_find(rcp_tree_ref tree, void *key);
rcp_extern rcp_tree_node_ref rcp_tree_begin(rcp_tree_ref tree);

//return: null if success, node elseware
#define rcp_tree_add(tree, node) rcp_tree_put((tree), (node), 0);

//return: previous value if exist, or NULL elseware
#define rcp_tree_set(tree, node) rcp_tree_put((tree), (node), 1);

rcp_extern rcp_tree_node_ref rcp_tree_put(
		rcp_tree_ref tree, rcp_tree_node_ref node, int replace);

rcp_extern void rcp_tree_remove(rcp_tree_ref tree, rcp_tree_node_ref node);
