#ifndef __NET_HELP
#define __NET_HELP

#define TCP_LISTENQ  1024  /* second argument to listen() */

/* 
 * open_listenfd - open and return a listening socket on port
 * Returns -1 in case of failure 
 */
int tcp_listen(int port);

/*
 * open_clientfd - open connection to server at <hostname, port>
 *   and return a socket descriptor ready for reading and writing.
 *   Return <0 in case of failure.
 */
int tcp_connect(char *hostname, int port);

#endif




