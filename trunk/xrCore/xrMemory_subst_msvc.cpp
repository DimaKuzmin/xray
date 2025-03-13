#include "stdafx.h"
#pragma hdrstop

#include "xrMemory_align.h"
#include "xrMemory_pure.h"

#ifndef	__BORLANDC__

#ifndef DEBUG_MEMORY_MANAGER
#	define	debug_mode 0
#endif // DEBUG_MEMORY_MANAGER

#ifdef DEBUG_MEMORY_MANAGER
	XRCORE_API void*	g_globalCheckAddr = NULL;
#endif // DEBUG_MEMORY_MANAGER

#ifdef DEBUG_MEMORY_MANAGER
	extern void save_stack_trace	();
#endif // DEBUG_MEMORY_MANAGER

MEMPOOL		mem_pools			[mem_pools_count];

// MSVC
ICF	u8*		acc_header			(void* P)	{	u8*		_P		= (u8*)P;	return	_P-1;	}
ICF	u32		get_header			(void* P)	{	return	(u32)*acc_header(P);				}
ICF	u32		get_pool			(size_t size)
{
	u32		pid					= u32(size/mem_pools_ebase);
	if (pid>=mem_pools_count)	return mem_generic;
	else						return pid;
}

 bool	g_use_pure_alloc		= false;
 
void*	xrMemory::mem_alloc		(size_t size)
{
	Msg("Alloca: %u", size);
	stat_calls++; 
 	void							*result = malloc(size);
	return							(result); 
}

void	xrMemory::mem_free		(void* P)
{
	stat_calls++;
	free					(P);	 
}

extern BOOL	g_bDbgFillMemory	;

void*	xrMemory::mem_realloc	(void* P, size_t size )
{
	stat_calls++;
 	void* result = ::realloc(P, size);
	return (result);
}

#endif // __BORLANDC__