#ifndef MUD_SOCKSTREAM_H
#define MUD_SOCKSTREAM_H

#include <cctype>
#include <string>

#define SOCKSTREAM_BUFSIZE 1024

/*
 * Intro: Buffered IO between sockets
 * Date: 2023-2-23
 * Developer: DouSBao
 */

namespace DSMud{

/*
 * --------------------------------------------------------------
 * Createable, noncopyable, move constructable
 * Therefore, buffered data should not be share (noncopyable), nor discard (non move assignable)
 * --------------------------------------------------------------
 */

class SockStream{
	struct SockStreamBuf{
		char *ptr;							// next position to read
		std::size_t left;					// unread data
		char buf[SOCKSTREAM_BUFSIZE + 1];
	};
public:
	SockStream(int sock);
	SockStream(const SockStream &) = delete;
	SockStream(SockStream &&rref);

	~SockStream(void) noexcept = default;

	const SockStream &operator=(const SockStream &) = delete;
	SockStream &operator=(SockStream &&rref) = delete;

	// Buffered. Read bytes until '\0'.
	// Return bytes been read, or 0 means EOF, or -1 when error.
	long read(char *dest, std::size_t max) const;

	// Unbuffered. Write '\0' terminated c-string src to socket.
	// Return bytes been written, or -1 when error.
	long write(const char *src) const;

	// Extract raw socket.
	friend int operator*(const SockStream &rhs) noexcept;

private:
	long _read(char *dest, std::size_t max) const;

	int sock;						// raw socket
	mutable SockStreamBuf rdbuf;	// reading buffer
};

} // namespace DSMud

#endif // MUD_SOCKSTREAM_H
