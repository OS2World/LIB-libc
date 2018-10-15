/* dirent.h,v 1.4 2004/09/14 22:27:32 bird Exp */
/** @file
 * FreeBSD 5.1
 * @changes bird: Merged in EMX stuff and internal LIBC stuff.
 */

/*-
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)dirent.h	8.2 (Berkeley) 7/28/94
 * $FreeBSD: src/include/dirent.h,v 1.13 2002/09/10 18:12:16 mike Exp $
 */

#ifndef _DIRENT_H_
#define _DIRENT_H_

/*
 * The kernel defines the format of directory entries returned by
 * the getdirentries(2) system call.
 */
#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/dirent.h>

#if __BSD_VISIBLE || __XSI_VISIBLE
/*
 * XXX this is probably illegal in the __XSI_VISIBLE case, but brings us closer
 * to the specification.
 */
#define	d_ino		d_fileno	/* backward and XSI compatibility */
#endif

#if __BSD_VISIBLE

/* definitions for library routines operating on directories. */
#define	DIRBLKSIZ	1024

struct _telldir;		/* see telldir.h */

/* bird: EMX internal structure. */
struct _dircontents
{
  struct _dircontents * _d_next;
  char *                _d_entry;
  __off_t               _d_size;
  unsigned short        _d_time;
  unsigned short        _d_date;
  unsigned short        _d_attr;
  ino_t                 _d_ino;
};

/* structure describing an open directory. */
typedef struct _dirdesc {
#if 0
	int	dd_fd;		/* file descriptor associated with directory */
	long	dd_loc;		/* offset in current buffer */
	long	dd_size;	/* amount of data returned by getdirentries */
	char	*dd_buf;	/* data buffer */
	int	dd_len;		/* size of data buffer */
	long	dd_seek;	/* magic cookie returned by getdirentries */
	long	dd_rewind;	/* magic cookie for rewinding */
	int	dd_flags;	/* flags for readdir */
	void	*dd_lock;	/* hack to avoid including <pthread.h> */
	struct _telldir *dd_td;	/* telldir position recording */
#else
        int                   dd_id;
        long                  dd_loc;
        struct _dircontents * dd_contents;
        struct _dircontents * dd_cp;
        struct dirent         dd_dirent;
#endif
} DIR;

#if 0 /* bird: we do it differently. */
#define	dirfd(dirp)	((dirp)->dd_fd)
#else                        /* bird */
#define	dirfd(dirp)	(-2) /* bird */
#endif                       /* bird */

/* flags for opendir2 */
#define DTF_HIDEW	0x0001	/* hide whiteout entries */
#define DTF_NODUP	0x0002	/* don't return duplicate names */
#define DTF_REWIND	0x0004	/* rewind after reading union stack */
#define __DTF_READALL	0x0008	/* everything has been read */

#ifndef NULL
#define	NULL	0
#endif

#else /* !__BSD_VISIBLE */

typedef	void *	DIR;

#endif /* __BSD_VISIBLE */

#ifndef _KERNEL

__BEGIN_DECLS
#if __BSD_VISIBLE
/** @todo DIR	*__opendir2(const char *, int); */
/** @todo int	 alphasort(const void *, const void *); */
int	 getdents(int, char *, int);
int	 getdirentries(int, char *, int, long *);
#endif
DIR	*opendir(const char *);
struct dirent *
	 readdir(DIR *);
#if __POSIX_VISIBLE >= 199506 || __XSI_VISIBLE >= 500
int	 readdir_r(DIR *, struct dirent *, struct dirent **);
#endif
void	 rewinddir(DIR *);
#if __BSD_VISIBLE
int	 scandir(const char *, struct dirent ***,
	    int (*)(struct dirent *), int (*)(const void *, const void *));
#endif
#if __XSI_VISIBLE
void	 seekdir(DIR *, long);
long	 telldir(DIR *);
#endif
int	 closedir(DIR *);


/* bird: EMX extra - start */
DIR *_opendir (const char *);
struct dirent *_readdir (DIR *);
void _seekdir (DIR *, long);
long _telldir (DIR *);
int _closedir (DIR *);
void _rewinddir (DIR *);
/* bird: EMX extra - end */

__END_DECLS

#endif /* !_KERNEL */

#endif /* !_DIRENT_H_ */
