/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*    In addition, as a special exception, the author gives permission to
*    link the code of this program with the Half-Life Game Engine ("HL
*    Engine") and Modified Game Libraries ("MODs") developed by Valve,
*    L.L.C ("Valve").  You must obey the GNU General Public License in all
*    respects for all of the code used other than the HL Engine and MODs
*    from Valve.  If you modify this file, you may extend this exception
*    to your version of the file, but you are not obligated to do so.  If
*    you do not wish to do so, delete this exception statement from your
*    version.
*
*/

#pragma once

#include "netadr.h"
#include "enums.h"
#include "common_rehlds.h"

enum
{
	FLOW_OUTGOING = 0,
	FLOW_INCOMING,

	MAX_FLOWS
};

// 0 == regular, 1 == file stream
enum
{
	FRAG_NORMAL_STREAM = 0,
	FRAG_FILE_STREAM,

	MAX_STREAMS
};

// NETWORKING INFO

// Max size of udp packet payload
const int MAX_UDP_PACKET	= 4010; // 9 bytes SPLITHEADER + 4000 payload?

// Max length of a reliable message
const int MAX_MSGLEN		= 3990; // 10 reserved for fragheader?

// Max length of unreliable message
const int MAX_DATAGRAM		= 4000;

// This is the packet payload without any header bytes (which are attached for actual sending)
const int NET_MAX_PAYLOAD	= 65536;

// This is the payload plus any header info (excluding UDP header)

// Packet header is:
//  4 bytes of outgoing seq
//  4 bytes of incoming seq
//  and for each stream
// {
//  byte (on/off)
//  int (fragment id)
//  short (startpos)
//  short (length)
// }
#define HEADER_BYTES (8 + MAX_STREAMS * 9)

// Pad this to next higher 16 byte boundary
// This is the largest packet that can come in/out over the wire, before processing the header
//  bytes will be stripped by the networking channel layer
//#define NET_MAX_MESSAGE PAD_NUMBER( ( MAX_MSGLEN + HEADER_BYTES ), 16 )
// This is currently used value in the engine. TODO: define above gives 4016, check it why.
const int NET_MAX_MESSAGE = 4037;

// Message data
typedef struct
{
	int size;		// Size of message sent/received
	double time;	// Time that message was sent/received
} flowstats_t;

const int MAX_LATENT = 32;

typedef struct flow_s
{
	flowstats_t stats[MAX_LATENT];	// Data for last MAX_LATENT messages
	int current;					// Current message position
	double nextcompute;				// Time when we should recompute k/sec data

	// Average data
	float kbytespersec;
	float avgkbytespersec;
} flow_t;

const int FRAGMENT_C2S_MIN_SIZE = 16;
const int FRAGMENT_S2C_MIN_SIZE = 256;
const int FRAGMENT_S2C_MAX_SIZE = 1024;

const int CLIENT_FRAGMENT_SIZE_ONCONNECT = 128;
const int CUSTOMIZATION_MAX_SIZE = 20480;

const int FRAGMENT_MAX_SIZE = 1024;

// Client sends normal fragments only while connecting
#define MAX_NORMAL_FRAGMENTS (NET_MAX_PAYLOAD / CLIENT_FRAGMENT_SIZE_ONCONNECT)

// While client is connecting it sending fragments with minimal size, also it transfers sprays with minimal fragments...
// But with sv_delayed_spray_upload it sends with cl_dlmax fragment size
#define MAX_FILE_FRAGMENTS (CUSTOMIZATION_MAX_SIZE / FRAGMENT_C2S_MIN_SIZE)

const int UDP_HEADER_SIZE = 28;
const int MAX_RELIABLE_PAYLOAD = 1200;

#define MAKE_FRAGID(id,count)	((( id & 0xffff) << 16) | (count & 0xffff))
#define FRAG_GETID(fragid)		((fragid >> 16) & 0xffff)
#define FRAG_GETCOUNT(fragid)	(fragid & 0xffff)

// Generic fragment structure
typedef struct fragbuf_s
{
	fragbuf_s *next;							// Next buffer in chain
	int bufferid;								// Id of this buffer
	sizebuf_t frag_message;						// Message buffer where raw data is stored

	byte frag_message_buf[FRAGMENT_MAX_SIZE];	// The actual data sits here

	qboolean isfile;							// Is this a file buffer?
	qboolean isbuffer;							// Is this file buffer from memory ( custom decal, etc. ).
	qboolean iscompressed;

	char filename[MAX_PATH];					// Name of the file to save out on remote host
	int foffset;								// Offset in file from which to read data
	int size;									// Size of data to read at that offset
} fragbuf_t;

// Waiting list of fragbuf chains
typedef struct fragbufwaiting_s
{
	fragbufwaiting_s *next;	// Next chain in waiting list
	int fragbufcount;		// Number of buffers in this chain
	fragbuf_t *fragbufs;	// The actual buffers
} fragbufwaiting_t;

// Network Connection Channel
typedef struct netchan_s
{
	// NS_SERVER or NS_CLIENT, depending on channel.
	netsrc_t sock;

	// Address this channel is talking to.
	netadr_t remote_address;

	int player_slot;
	// For timeouts.  Time last message was received.
	float last_received;
	// Time when channel was connected.
	float connect_time;

	// Bandwidth choke
	// Bytes per second
	double rate;
	// If realtime > cleartime, free to send next packet
	double cleartime;

	// Sequencing variables
	//
	// Increasing count of sequence numbers
	int incoming_sequence;
	// # of last outgoing message that has been ack'd.
	int incoming_acknowledged;
	// Toggles T/F as reliable messages are received.
	int incoming_reliable_acknowledged;
	// single bit, maintained local
	int incoming_reliable_sequence;
	// Message we are sending to remote
	int outgoing_sequence;
	// Whether the message contains reliable payload, single bit
	int reliable_sequence;
	// Outgoing sequence number of last send that had reliable data
	int last_reliable_sequence;

	void *connection_status;
	int (*pfnNetchan_Blocksize)(void *pData);

	// Staging and holding areas
	sizebuf_t message;
	byte message_buf[MAX_MSGLEN];

	// Reliable message buffer. We keep adding to it until reliable is acknowledged. Then we clear it.
	int reliable_length;
	byte reliable_buf[MAX_MSGLEN];

	// Waiting list of buffered fragments to go onto queue. Multiple outgoing buffers can be queued in succession.
	fragbufwaiting_t *waitlist[MAX_STREAMS];

	// Is reliable waiting buf a fragment?
	int reliable_fragment[MAX_STREAMS];
	// Buffer id for each waiting fragment
	unsigned int reliable_fragid[MAX_STREAMS];

	// The current fragment being set
	fragbuf_t *fragbufs[MAX_STREAMS];
	// The total number of fragments in this stream
	int fragbufcount[MAX_STREAMS];

	// Position in outgoing buffer where frag data starts
	short int frag_startpos[MAX_STREAMS];
	// Length of frag data in the buffer
	short int frag_length[MAX_STREAMS];

	// Incoming fragments are stored here
	fragbuf_t *incomingbufs[MAX_STREAMS];
	// Set to true when incoming data is ready
	qboolean incomingready[MAX_STREAMS];

	// Only referenced by the FRAG_FILE_STREAM component
	// Name of file being downloaded
	char incomingfilename[MAX_PATH];

	void *tempbuffer;
	int tempbuffersize;

	// Incoming and outgoing flow metrics
	flow_t flow[MAX_FLOWS];
} netchan_t;
