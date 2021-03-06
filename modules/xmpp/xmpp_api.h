/*
 * $Id$
 *
 * XMPP Module
 * This file is part of opensips, a free SIP server.
 *
 * Copyright (C) 2006 Voice Sistem S.R.L.
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
 * 
 */

#ifndef _XMPP_API_H_
#define _XMPP_API_H_

#define XMPP_RCV_MESSAGE      (1<<0)
#define XMPP_RCV_PRESENCE     (1<<1)
#define XMPP_RCV_IQ			  (1<<2)

typedef void (xmpp_cb_f) (char *msg, int type, void *param);
typedef int (*register_xmpp_cb_t)(int types, xmpp_cb_f f, void *param);


typedef struct xmpp_callback_
{
	int types;                   /* types of events that trigger the callback*/
	xmpp_cb_f *cbf;              /* callback function */
	void *cbp;                   /* param to be passed to callback function */
	struct xmpp_callback_ *next;
} xmpp_callback_t;

typedef struct xmpp_cb_list_
{
	xmpp_callback_t *first;
	int types;
} xmpp_cb_list_t;


extern xmpp_cb_list_t*  _xmpp_cb_list;


#define xmpp_isset_cb_type(_types_) \
	((_xmpp_cb_list->types)|(_types_) )


int init_xmpp_cb_list();

void destroy_xmpp_cb_list();


int register_xmpp_cb( int types, xmpp_cb_f f, void *param );

/* run all transaction callbacks for an event type */
static inline void run_xmpp_callbacks( int type, char *msg)
{
	xmpp_callback_t *it;

	for (it=_xmpp_cb_list->first; it; it=it->next)  {
		if(it->types&type) {
			LM_DBG("cb: msg=%p, callback type %d/%d fired\n",
				msg, type, it->types );
			it->cbf( msg, type, it->cbp );
		}
	}
}

typedef int (*xmpp_send_xpacket_f)(str *from, str *to, str *msg, str *id);
int xmpp_send_xpacket(str *from, str *to, str *msg, str *id);

typedef int (*xmpp_send_xmessage_f)(str *from, str *to, str *msg, str *id);
int xmpp_send_xmessage(str *from, str *to, str *msg, str *id);

typedef int (*xmpp_send_xsubscribe_f)(str *from, str *to, str *msg, str *id);
int xmpp_send_xsubscribe(str *from, str *to, str *msg, str *id);

typedef int (*xmpp_send_xnotify_f)(str *from, str *to, str *msg, str *id);
int xmpp_send_xnotify(str *from, str *to, str *msg, str *id);

typedef char* (*uri_sip2xmpp_f)(str* uri);
typedef char* (*uri_xmpp2sip_f)(char* uri, int* len);

typedef struct xmpp_api_
{
	register_xmpp_cb_t register_callback;
	uri_xmpp2sip_f uri_xmpp2sip;
	uri_sip2xmpp_f uri_sip2xmpp;
	xmpp_send_xpacket_f xpacket;
	xmpp_send_xmessage_f xmessage;
	xmpp_send_xsubscribe_f xsubscribe;
	xmpp_send_xnotify_f xnotify;
} xmpp_api_t;

typedef int (*bind_xmpp_t)(xmpp_api_t* api);
int bind_xmpp(xmpp_api_t* api);

#endif

