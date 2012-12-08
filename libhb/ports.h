/* ports.h

   Copyright (c) 2003-2012 HandBrake Team
   This file is part of the HandBrake source code
   Homepage: <http://handbrake.fr/>.
   It may be used under the terms of the GNU General Public License v2.
   For full terms see the file COPYING file or visit http://www.gnu.org/licenses/gpl-2.0.html
 */

#ifndef HB_PORTS_H
#define HB_PORTS_H

#if defined(_WIN32)
#define DIR_SEP_STR "\\"
#else
#define DIR_SEP_STR "/"
#endif

/************************************************************************
 * Utils
 ***********************************************************************/
uint64_t hb_get_date();
void     hb_snooze( int delay );
int      hb_get_cpu_count();
#ifdef SYS_MINGW
char *strtok_r(char *s, const char *delim, char **save_ptr);
#endif

#ifdef __LIBHB__

/* Everything from now is only used internally and hidden to the UI */

/************************************************************************
 * DVD utils
 ***********************************************************************/
int hb_dvd_region(char *device, int *region_mask);

/************************************************************************
 * File utils
 ***********************************************************************/
void hb_get_temporary_directory( char path[512] );
void hb_get_tempory_filename( hb_handle_t *, char name[1024],
                              char * fmt, ... );
void hb_mkdir( char * name );

/************************************************************************
 * Threads
 ***********************************************************************/
typedef struct hb_thread_s hb_thread_t;

#if defined( SYS_BEOS ) || defined( SYS_HAIKU )
#  define HB_LOW_PRIORITY    5
#  define HB_NORMAL_PRIORITY 10
#elif defined( SYS_DARWIN )
#  define HB_LOW_PRIORITY    0
#  define HB_NORMAL_PRIORITY 31
#elif defined( SYS_LINUX ) || defined( SYS_FREEBSD ) || defined ( SYS_SunOS ) || defined ( __FreeBSD_kernel__ )
#  define HB_LOW_PRIORITY    0
#  define HB_NORMAL_PRIORITY 0
#elif defined( SYS_CYGWIN )
#  define HB_LOW_PRIORITY    0
#  define HB_NORMAL_PRIORITY 1
#elif defined( SYS_MINGW )
#  define HB_LOW_PRIORITY    0
#  define HB_NORMAL_PRIORITY 0
#endif

typedef void (thread_func_t)(void *);
hb_thread_t * hb_thread_init( const char * name, thread_func_t *function,
                              void * arg, int priority );
void          hb_thread_close( hb_thread_t ** );
int           hb_thread_has_exited( hb_thread_t * );

/************************************************************************
 * Mutexes
 ***********************************************************************/

hb_lock_t * hb_lock_init();
void        hb_lock_close( hb_lock_t ** );
void        hb_lock( hb_lock_t * );
void        hb_unlock( hb_lock_t * );

/************************************************************************
 * Condition variables
 ***********************************************************************/
typedef struct hb_cond_s hb_cond_t;

hb_cond_t * hb_cond_init();
void        hb_cond_wait( hb_cond_t *, hb_lock_t * );
void        hb_cond_timedwait( hb_cond_t * c, hb_lock_t * lock, int msec );
void        hb_cond_signal( hb_cond_t * );
void        hb_cond_broadcast( hb_cond_t * c );
void        hb_cond_close( hb_cond_t ** );

/************************************************************************
 * Network
 ***********************************************************************/
typedef struct hb_net_s hb_net_t;

hb_net_t * hb_net_open( char * address, int port );
int        hb_net_send( hb_net_t *, char * );
int        hb_net_recv( hb_net_t *, char *, int );
void       hb_net_close( hb_net_t ** );

#endif /* __LIBHB__ */

#endif

