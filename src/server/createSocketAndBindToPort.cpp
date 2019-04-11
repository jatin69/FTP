#include "./server.hpp"

/**Special Note :
 *
 * Note that this function `createSocketAndBindToPort` is very general.
 * and is exactly same in both server and client.
 *
 * It could have been extracted from both and kept in utils
 * but still, it is kept separate. There's a reason for that.
 *
 * For normal functions, above method works fine.
 * But when blocking system calls are in the picture, it causes problem.
 * Because the same object file from `utils` will be used.
 * Thus, when client and server try to execute the code simultaneously,
 * race condition occurs, and it is very unpredictable.
 *
 * One more method is to keep it in a `common` folder and #include it
 * in server and client code. That will copy its code to required places.
 * But even that is troublesome because it needs a lot of header files
 * so we include a single `./client.hpp` or `./server.hpp`
 * This recursive inclusion of files is messy.
 *
 * It could be made class functions, but that'll give a wrong idea.
 *
 * Therefore a copy is kept in both places to save all the trouble
 * In the makefile, creation of `client` object uses only files in the client and util
 * folder
 * therefore, this function is unique in that folder, and everything works fine.
 *
*/

/**create socket and bind to port
 *
 * @usage
 * creates a socket and binds self-address and given port number
*/
int createSocketAndBindToPort(int portNumber) {
	/**Converting port number to const char*
	 *
	 * Because all system calls expect it in const char* format.
	*/
	const char* port = to_string(portNumber).c_str();

	/**hints is of type : struct addrinfo
	 *
	 * These are hints you provide to the `getaddrinfo()` function.
	 * Fill it up as much as possible and just pass it to `getaddrinfo()`
	 * It will load up remaining values and give us a perfect structure
	 * Which can then be used in other system calls.
	*/
	struct addrinfo hints;

	/**Wiping the structure initially
	 *
	 * Setting all the memory bits to 0 using memset
	*/
	memset(&hints, 0, sizeof hints);

	/**AF_UNSPEC :over: AF_INET
	 *
	 * AF_UNSPEC makes us protocol unspecific
	 * It will then handle IPv4 and well as IPv6
	 *
	 * Traditional AF_INET will only handle IPv4 addresses
	*/
	hints.ai_family = AF_UNSPEC;

	/**SOCK_STREAM
	 *
	 * Other popular type of sockets are : SOCK_DGRAM
	*/
	hints.ai_socktype = SOCK_STREAM;

	/**AI_PASSIVE
	 *
	 * To let OS fill in our IP address for us.
	 * Saves us from hard-coding our address
	*/
	hints.ai_flags = AI_PASSIVE;

	/**getaddrinfo() :over: gethostbyname() and getservbyname()
	 *
	 * getaddrinfo() is an excellent function that will return information
	 * on a particular host name (such as its IP address) and
	 * load up a struct sockaddr for you, taking care of the gritty details
	 * (like if it's IPv4 or IPv6.)
	 *
	 * Note that, this `res` is extremely useful and helps in other system calls.
	 * Consequently, making them IP version independent
	 *
	*/
	struct addrinfo* res;
	int addr_status = getaddrinfo(NULL, port, &hints, &res);
	if (addr_status != 0) {
		printError("[ERROR] : Cannot get info from getaddrinfo()");
		throw std::runtime_error("Exiting : Cannot resolve self");
	}

	/**Sockfd is the socket descriptor
	 *
	*/
	int sock_fd = -1;

	/**Loop through results, bind to first one we can
	 *
	 * getaddrinfo returns a linkedlist of results
	 * majorly all the publicly visible IP addresses of the host and related info
	 * (eg. for google.com, it emits its IPv4 [Node 1] and IPv6 address[Node 2])
	*/
	struct addrinfo* p;
	for (p = res; p != NULL; p = p->ai_next) {
		/** Create the socket
		 *
		*/
		sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (sock_fd < 0) {
			printError("[SERVER] : Cannot Open Socket");
			continue;  // try next
		}

		/**Set socket options
		 *
		 * Avoids unncessary messages of : Port busy when re-running the server
		 *
		 * Sometimes, you might notice, you try to rerun a server and bind() fails,
		 * claiming “Address already in use.” What does that mean?
		 * Well, a little bit of a socket that was connected is still hanging around in
		 * the kernel,
		 * and it's hogging the port. You can either wait for it to clear (a minute or
		 * so),
		 * or add code to your program allowing it to reuse the port, like this:
		*/
		int yes = 1;
		int opt_status = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		if (opt_status == -1) {
			perror("server: setsockopt");
			throw std::runtime_error("Exiting : Server Failed to REUSE SOCKET");
		}

		/* Bind the socket to the port
		 *
		 */
		int bind_status = bind(sock_fd, p->ai_addr, p->ai_addrlen);
		if (bind_status != 0) {
			printError("[SERVER] : Cannot Bind to Socket");
			close(sock_fd);  // close this socket
			continue;		 // try another socket
		}

		// Bind the first one we can
		break;
	}

	// No binds happened in the above loop
	if (p == NULL) {
		printError("[SERVER] : Failed to Bind to all addresses");
		throw std::runtime_error("Exiting : Server Failed Binding");
	}

	/* Don't need the structure with address info any more
	 *
	 * This is not called before the above `if condition` to prevent
	 * overriding the value of `errno` by this system call.
	 */
	freeaddrinfo(res);

	/** return the sockfd
	 *
	 * This is a socket descriptor [SOCKET]
	 * currently binded [BIND]
	 * to this machine's IP address [HOST]
	 * and the supplied port in the arguments [PORT]
	*/
	return sock_fd;
}
