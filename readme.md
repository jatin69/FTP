# todo

- [ ] for ABORT to work, the parent should not wait for the result of child LS
and maybe somehow save its pid for it to kill it
Because it is cut in middle, it might need clean up (might)
 

- find a way to store server/client IP in the OBJECT after forking
- 
- [X] DO port command
- [X] Do client's counterpart of PORT
- [ ] ensure that PORT has one argument atleast : error checking for all commands
- [X] then come back to list
- [ ] reimplement sys command
- [ ] current Ls command is very very unsafe, disallow semicolor or use readdir and create everything yourself 
 
- [X] TEST LS in current connection first, then implement below things
- [X] Implement client side supported commands

- [ ] sanitize request convert `ls` to `LIST`
- [X] implement basic pwd
- [X] implement FORK on new command
- [X] Implement data connection manager
- [X] Implement PORT

- [X] check if prev command was a port command
- [X] if not, use default PORT values 
- [X] if yes, use new PORT values

- Then establist a data connection from Server to Client
- But that'll not work with NAT
- make a helper utility that help in creating a client to server connection to use as dummy
then use that for data transfer

- DO THIS MUCH FIRST

- Now because this will need previous track, we can also implement user and pass in the same section with a `isAuthenticated` class function
