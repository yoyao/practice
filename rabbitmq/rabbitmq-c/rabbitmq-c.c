#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <amqp.h>
#include <amqp_ssl_socket.h>

#include <assert.h>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Winsock2.h>
#else
#include <sys/time.h>
#endif

#include "utils.h"

int main(int argc, char const *const *argv)
{
	char const *hostname;
	int port;
	int timeout;
	amqp_socket_t *socket;
	amqp_connection_state_t conn;
	struct timeval tval;
	struct timeval *tv;

	if (argc < 3) 
	{
		fprintf(stderr,
				"Usage: amqps_connect_timeout host port timeout_sec "
				"[cacert.pem [verifypeer] [verifyhostname] [key.pem cert.pem]]\n");
		return 1;

	}

	hostname = argv[1];
	port = atoi(argv[2]);

	timeout = atoi(argv[3]);
	if (timeout > 0) {
		tv = &tval;

		tv->tv_sec = timeout;
		tv->tv_usec = 0;

	} else {
		tv = NULL;

	}

	conn = amqp_new_connection();

	socket = amqp_ssl_socket_new(conn);
	if (!socket) {
		die("creating SSL/TLS socket");

	}

	amqp_ssl_socket_set_verify_peer(socket, 0);
	amqp_ssl_socket_set_verify_hostname(socket, 0);

	if (argc > 5)
	{
		int nextarg = 6;
		die_on_error(amqp_ssl_socket_set_cacert(socket, argv[5]),"setting CA certificate");
		if (argc > nextarg && !strcmp("verifypeer", argv[nextarg])) {
			amqp_ssl_socket_set_verify_peer(socket, 1);
			nextarg++;
		}
		if (argc > nextarg && !strcmp("verifyhostname", argv[nextarg])) {
			amqp_ssl_socket_set_verify_hostname(socket, 1);
			nextarg++;

		}
		if (argc > nextarg + 1) 
		{
			printf("client key path %s\n",argv[nextarg]);
			die_on_error(amqp_ssl_socket_set_key(socket, argv[nextarg + 1], argv[nextarg]),"setting client key");
		}

	}
    printf("hostname is %s\n",hostname);
	//hostname="47.93.50.121";
	die_on_error(amqp_socket_open_noblock(socket, hostname, port, tv),"opening SSL/TLS connection");

	die_on_amqp_error(amqp_login(conn, "vh_sweet", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN,"admin", "123456"),"Logging in");

	die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS),"Closing connection");
	die_on_error(amqp_destroy_connection(conn), "Ending connection");
	die_on_error(amqp_uninitialize_ssl_library(), "Uninitializing SSL library");

	printf("Done\n");
	return 0;

}
