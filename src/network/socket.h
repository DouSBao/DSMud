#ifndef MUD_SOCKET_H
#define MUD_SOCKET_H

#include <netdb.h>
#include <type_traits>
#include <boost/mpl/int_fwd.hpp>

#define SOCKFACTORY_LISTENMAX 1024

/*
 * Intro: Helper to create different sockets
 * Date: 2023-2-23
 * Developer: DouSBao
 */

namespace DSMud{

// Valid socket types
using SocketListen = boost::mpl::int_<0>;
using SocketConnect = boost::mpl::int_<1>;

/*
 * --------------------------------------------------------------
 * Static utils class. Not createable.
 * Fake factory.
 * --------------------------------------------------------------
 */

class SockFactory{
public:
	SockFactory(void) = delete;

	// Create given type socket.
	// Return raw socket, or -1 when error.
	template<typename>
	static inline int create(const char *host, const char *port) noexcept;

private:
	static int _create(const char *host, const char *port, std::true_type) noexcept;
	static int _create(const char *host, const char *port, std::false_type) noexcept;
};

template<typename SocketType>
inline int SockFactory::create(const char *host, const char *port) noexcept
{
	// TODO: add log feature
	return _create(host, port, std::is_same<SocketType, SocketListen>());
}

} // namespace DSMud

#endif // MUD_SOCKET_H
