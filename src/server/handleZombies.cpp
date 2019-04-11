#include "./server.hpp"

/**Reaper for zombie processes
 * When the parent doesn't collect the child's status, it becomes a zombie.
 *   
 * In our case,
 * the server main process (the one which always listens),
 * does not collect the status of the 
 * forked processes created to handle the incoming clients.
 * 
 * When the server runs indefinitely, a lot of clients come and go.
 * A lot of processes are created for these clients.
 * Therefore, a lot of zombies are lying around.
 * 
 * We need a mechanism to clean up these zombie processes.
 * 
*/
void handleZombieProcesses() {
    // method not implemented yet
    // @todo
}