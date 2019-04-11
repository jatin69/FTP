#include "./client.hpp"

/**get IP address string
 *
 * @returns
 * IP address in human readable form from the given sockaddr structure
 *
 * @used-inside
 * function : `inet_ntop`
 * Converts internet-address from network format to presentation format.
 * Reverse is possible with `inet_pton`.
 *
 * Notice the if, else if conditions inside,
 * they are done to support both IPv4 and IPv6 addresses
 *
*/
void get_ip_str(const struct sockaddr* sa, char* s, size_t maxlen) {
	if (sa->sa_family == AF_INET) {
		inet_ntop(AF_INET, &(((struct sockaddr_in*)sa)->sin_addr), s, maxlen);
	} else if (sa->sa_family == AF_INET6) {
		inet_ntop(AF_INET6, &(((struct sockaddr_in6*)sa)->sin6_addr), s, maxlen);
	} else {
		strncpy(s, "Unknown AF", maxlen);
	}
}