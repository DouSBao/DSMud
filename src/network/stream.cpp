#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "stream.h"

namespace DSMud{

SockStream::SockStream(int sock) : sock(sock)
{
	rdbuf.ptr = rdbuf.buf;
	rdbuf.left = 0;

	return;
}

SockStream::SockStream(SockStream &&rref) : SockStream(rref.sock)
{
	if(rref.rdbuf.left > 0){
		memcpy(rdbuf.buf, rref.rdbuf.buf, rref.rdbuf.left);
		rdbuf.ptr = rdbuf.buf + (rref.rdbuf.ptr - rref.rdbuf.buf);
		rdbuf.left = rref.rdbuf.left;
	}

	rref.sock = -1;

	return;
}

long SockStream::read(char *dest, std::size_t max) const
{
	std::size_t cnt, rc;
	char *ptr = dest, ch;

	for(cnt = 1; cnt < max; ++cnt){
		if((rc = _read(&ch, 1)) == 1){
			if(ch != '\0'){
				*ptr++ = ch;
			}else{
				break;
			}
		}else{
			return rc;
		}
	}

	*ptr = '\0';

	return cnt;
}

long SockStream::_read(char *dest, std::size_t max) const
{
	std::size_t cnt = max;

	// when cache is empty, refill it
	while(rdbuf.left <= 0){
		if((rdbuf.left = ::read(sock, rdbuf.buf, SOCKSTREAM_BUFSIZE)) > 0){
			rdbuf.ptr = rdbuf.buf;

			break;
		}else if(rdbuf.left < 0){
			if(errno != EINTR){
				return -1;
			}
		}else{
			// EOF is never read when there is data in the buffer
			return 0;
		}
	}

	if(cnt > rdbuf.left){
		cnt = rdbuf.left;
	}

	memcpy(dest, rdbuf.ptr, cnt);
	rdbuf.ptr += cnt;
	rdbuf.left -= cnt;

	return cnt;
}

long SockStream::write(const char *src) const
{
	int rc;
	const char *ptr = src;
	std::size_t length = strlen(src + 1);
	std::size_t left = length;

	while(left > 0){
		if((rc = ::write(sock, src, length)) > 0){
			left -= rc;
			ptr += rc;
		}else{
			if(errno != EINTR){
				return -1;
			}
		}
	}

	return length;
}

int operator*(const SockStream &rhs) noexcept
{
	return rhs.sock;
}

} // namespace DSMud
