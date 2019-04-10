#include <string>

/**one Way Hash Function
 * 
 * @Usage
 * usernames and passwords on the server should be stored 
 * in hashed format, and not in plaintext format.
 * 
 * Then, when the user enters server access credentials, they are hashed,
 * and matched with the hash present on the server.
 * 
 * This function serves as that one way hash function (md5, etc)
 * For now, we simply store and match in plaintext.
 * 
*/
std::string oneWayHash(std::string s) {
    return s;
}