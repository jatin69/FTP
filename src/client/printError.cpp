#include "./client.hpp"

/**print Error Message
 *
 * print the string version of `errno` along with user's custom message
*/
void printError(const char* msg) {
	int saved_errno = errno;
	fprintf(stderr, "\n[ERROR] : %s \n[ERROR code %d ] : %s\n", msg, saved_errno,
			strerror(saved_errno));

	if (saved_errno == 32) {
		printf("\nServer end closed. \nExiting ...\n");
		exit(0);
	}
}
