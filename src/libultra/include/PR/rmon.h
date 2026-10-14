/* libultra 2.0I PR/rmon.h: interface reconstructed from decompals/ultralib e24c836. */

/**************************************************************************
 *
 *  $Revision: 1.6 $
 *  $Date: 1997/02/11 08:30:08 $
 *  $Source: /exdisk2/cvs/N64OS/Master/cvsmdev2/PR/include/rmon.h,v $
 *
 **************************************************************************/

#ifndef _RMON_H_
#define	_RMON_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/ultratypes.h>
#define RMON_DBG_BUF_SIZE  2048
#define RMON_STACKSIZE 0x1000

extern void rmonMain( void * );
extern void rmonPrintf( const char *, ... );

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif /* !_OS_H */
