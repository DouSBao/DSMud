#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "socket.h"

namespace DSMud{

int SockFactory::_create(const char *host, const char *port, std::true_type) noexcept
{
	int sock;
	struct addrinfo hints, *list, *p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG | AI_NUMERICSERV;

	if(getaddrinfo(host, port, &hints, &list) != 0){
		return -1;
	}

	for(p = list; p != nullptr; p = p->ai_next){
		if((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
			continue;
		}

		if(bind(sock, p->ai_addr, p->ai_addrlen) != -1){
			break;
		}

		close(sock);
	}

	freeaddrinfo(list);

	if(p == nullptr){
		return -1;
	}

	if(listen(sock, SOCKFACTORY_LISTENMAX) == -1){
		close(sock);
		return -1;
	}

	return sock;
}

int SockFactory::_create(const char *host, const char *port, std::false_type) noexcept
{
	int sock;
	struct addrinfo hints, *list, *p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;

	if(getaddrinfo(host, port, &hints, &list) != 0){
		return -1;
	}

	for(p = list; p != nullptr; p = p->ai_next){
		if((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
			continue;
		}

		if(connect(sock, p->ai_addr, p->ai_addrlen) != -1){
			break;
		}

		close(sock);
	}

	freeaddrinfo(list);

	if(p == nullptr){
		return -1;
	}

	return sock;
}

} // namespace DSMud
