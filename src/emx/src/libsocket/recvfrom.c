/* $Id: $ */
/** @file
 *
 * recvfrom().
 *
 * Copyright (c) 2003 knut st. osmundsen <bird-srcspam@anduin.net>
 *
 *
 * This file is part of Innotek LIBC.
 *
 * Innotek LIBC is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Innotek LIBC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Innotek LIBC; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/*******************************************************************************
*   Header Files                                                               *
*******************************************************************************/
#include "libc-alias.h"
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <emx/io.h>
#define __LIBC_LOG_GROUP __LIBC_LOG_GRP_SOCKET
#include <InnoTekLIBC/logstrict.h>
#include "socket.h"

ssize_t recvfrom(int socket, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen)
{
    LIBCLOG_ENTER("socket=%d buf=%p len=%d flags=%#x from=%p from=%p\n",
                  socket, buf, len, flags, (void *)from, (void *)fromlen);
    PLIBCSOCKETFH   pFHSocket = __libc_TcpipFH(socket);
    if (pFHSocket)
    {
        int rc;
        rc = __libsocket_recvfrom(pFHSocket->iSocket, buf, len, flags, from, (int *)fromlen);
        if (rc >= 0)
        {
            if (from && fromlen)
            {
#ifdef TCPV40HDRS
                if (*fromlen > sizeof(struct sockaddr_in) && from->sa_family == AF_INET)
                    *fromlen = sizeof(struct sockaddr_in);
#else
                if (*fromlen > from->sa_len)
                    *fromlen = from->sa_len;
#endif
            }
            LIBCLOG_RETURN_INT(rc);
        }
        __libc_TcpipUpdateErrno();
    }

    LIBCLOG_RETURN_INT(-1);
}


