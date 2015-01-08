
#ifdef __cplusplus
#define rcp_extern extern "C"
#else
#define rcp_extern extern
#endif

#define field_sizeof(t, f) (sizeof(((t*)0)->f))
