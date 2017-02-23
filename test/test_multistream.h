#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "libp2p/net/multistream.h"

int test_multistream_connect() {
	int retVal = 0;
	char* response;
	size_t response_size;

	struct Stream* stream = libp2p_net_multistream_connect("www.jmjatlanta.com", 4001);
	if (stream == NULL)
		goto exit;

	retVal = 1;

	exit:

	return retVal > 0;
}

int test_multistream_get_list() {
	int retVal = 0, socket_fd = -1;
	unsigned char* response;
	size_t response_size;

	struct Stream* stream = libp2p_net_multistream_connect("www.jmjatlanta.com", 4001);
	if (socket_fd < 0)
		goto exit;

	// try to respond something, ls command
	const unsigned char* out = "ls\n";

	if (libp2p_net_multistream_write(stream, out, strlen((char*)out)) <= 0)
		goto exit;

	// retrieve response
	retVal = libp2p_net_multistream_read(stream, &response, &response_size);
	if (retVal <= 0)
		goto exit;

	fprintf(stdout, "Response from multistream ls: %s", (char*)response);

	retVal = 1;

	exit:

	return retVal > 0;
}
