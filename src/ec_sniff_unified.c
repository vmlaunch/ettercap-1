/*
    ettercap -- unified sniffing method module

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

    $Header: /home/drizzt/dev/sources/ettercap.cvs/ettercap_ng/src/ec_sniff_unified.c,v 1.1 2003/03/17 19:42:26 alor Exp $
*/

#include <ec.h>
#include <ec_capture.h>
#include <ec_send.h>
#include <ec_threads.h>

/* proto */
void start_unified_sniff(void);
void forward_unified_sniff(struct packet_object *po);

/*******************************************/

void start_unified_sniff(void)
{
   DEBUG_MSG("start_unified_sniff");

   /* create the thread for packet capture */
   ec_thread_new("capture", "pcap handler and packet decoder", &capture, GBL_OPTIONS->iface);
}


void forward_unified_sniff(struct packet_object *po)
{

   /* 
    * forward the packet to Layer 3, the kernel
    * will route them to the correct destination (host or gw)
    *
    * don't forward if we are reading from pcap file
    */
   if (!GBL_OPTIONS->read)
      send_to_L3(po);
}

/* EOF */

// vim:ts=3:expandtab
