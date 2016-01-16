#ifndef HINTS_HPP_
#define HINTS_HPP_

#ifdef __GNUG__
	#define SM_ATTR_COLD __attribute__ ((cold))
	#define SM_ATTR_HOT __attribute__ ((hot))
  #define SM_RESTRICT __restrict__
#else
	#define SM_ATTR_COLD
	#define SM_ATTR_HOT
  #define SM_RESTRICT
#endif

#endif