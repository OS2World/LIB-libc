/* Modified for emx by hv 1996
 * Modified for gcc/os2 by bird 2003
 *
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
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
 *	from: @(#)udp_var.h	7.7 (Berkeley) 6/28/90
 *	$Id: udp_var.h,v 1.5 1994/01/10 23:27:48 mycroft Exp $
 */

#ifndef _NETINET_UDP_VAR_H_
#define _NETINET_UDP_VAR_H_

#ifdef TCPV40HDRS
struct  udpstat {
	u_long	udps_hdrops;
	u_long	udps_badsum;
	u_long	udps_badlen;
	u_long	udps_udpInDatagrams;
	u_long	udps_udpNoPorts;
	u_long	udps_udpOutDatagrams;
};

#else

/*
 * UDP kernel structures and variables.
 */
#pragma pack(1)
struct  udpiphdr {
        struct  ipovly ui_i;            /* overlaid ip structure */
        struct  udphdr ui_u;            /* udp header */
};
#pragma pack()
#define ui_next         ui_i.ih_next
#define ui_prev         ui_i.ih_prev
#define ui_x1           ui_i.ih_x1
#define ui_pr           ui_i.ih_pr
#define ui_len          ui_i.ih_len
#define ui_src          ui_i.ih_src
#define ui_dst          ui_i.ih_dst
#define ui_sport        ui_u.uh_sport
#define ui_dport        ui_u.uh_dport
#define ui_ulen         ui_u.uh_ulen
#define ui_sum          ui_u.uh_sum

struct  udpstat {
                                /* input statistics: */
        u_long  udps_ipackets;          /* total input packets */
        u_long  udps_hdrops;            /* packet shorter than header */
        u_long  udps_badsum;            /* checksum error */
        u_long  udps_badlen;            /* data length larger than packet */
        u_long  udps_noport;            /* no socket on port */
        u_long  udps_noportbcast;       /* of above, arrived as broadcast */
        u_long  udps_fullsock;          /* not delivered, input socket full */
        u_long  udpps_pcbcachemiss;     /* input packets missing pcb cache */
                                /* output statistics: */
        u_long  udps_opackets;          /* total output packets */
};

/*
 * Names for UDP sysctl objects
 */
#define UDPCTL_CHECKSUM         1       /* checksum UDP packets */
#define UDPCTL_STATS            2       /* statistics (read-only) */
#define UDPCTL_INETCFG          31      /* sysctl code-Generic UDP Inetcfg switching */
#define UDPCTL_TTL              32      /* sysctl code-TTL for UDP  packets */
#define UDPCTL_UDPSWIN          33      /* sysctl code-UDP really MAX datagram Size */
#define UDPCTL_UDPRWIN          34      /* sysctl code-UDP recieve window size */

#define UDPCTL_NAMES { \
        { 0, 0 }, \
        { "stats", CTLTYPE_STRUCT }, \
        { "inetcfg",CTLTYPE_INETCFG},\
}

#endif /* TCPV40HDRS */

#endif /* !_NETINET_UDP_VAR_H_ */
