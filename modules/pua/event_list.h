/*
 * $Id$
 *
 * pua module - presence user agent module
 *
 * Copyright (C) 2007 Voice Sistem S.R.L.
 *
 * This file is part of opensips, a free SIP server.
 *
 * opensips is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * opensips is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	initial version  2007-05-03 (anca)
 */

#ifndef _PUA_EVLIST_H_
#define _PUA_EVLIST_H_

#include "../../str.h"
//#include "send_publish.h"

struct publ_info;

typedef int (evs_process_body_t)(struct publ_info* , str** final_body,
		int ver, str* tuple);

typedef struct pua_event
{
	int ev_flag;
	str name;
	str content_type;         /* default content type for that event*/	
	evs_process_body_t* process_body;
	struct pua_event* next;

}pua_event_t;

extern pua_event_t* pua_evlist;

pua_event_t* init_pua_evlist(void);

int add_pua_event(int ev_flag, char* name, char* content_type,
		evs_process_body_t* process_body);

typedef int (*add_pua_event_t)(int ev_flag, char* name, char* content_type,
		evs_process_body_t* process_body);

pua_event_t* contains_pua_event(str* name);

pua_event_t* get_event(int ev_flag);

void destroy_pua_evlist(void);

#endif
