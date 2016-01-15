#ifdef __GNUG__
	#define SM_ATTR_COLD __attribute__ ((cold))
	#define SM_ATTR_HOT __attribute__ ((hot))
#else
	#define SM_ATTR_COLD
	#define SM_ATTR_HOT
#endif