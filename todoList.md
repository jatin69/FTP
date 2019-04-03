# Todo List

- [ ] Implement some more commands. as Listed in `server.cpp`
- [ ] Implement ABORT. for ABORT to work, the parent should not wait for the result of child LS
    and maybe somehow save its pid for it to kill it. Because it is cut in middle, it might need clean up (might)
- [ ] The code right now will not work with NAT. Make a helper utility that help in creating a client to server connection to use as dummy then use that for data transfer.

- [ ] clean all the printing/logging
- [ ] colorize all the logging
- [ ] resovle all the @todos
- [ ] Indent and format all code
- [ ] document all code
- [ ] Finalise code
- [ ] Finalise project
- [ ] Make a proper readme with screenshots
  
- [X] make verbose mode default. Remove this option. Instead silent using `/dev/null`
- [X] ensure that PORT has one argument atleast : error checking for all commands or maybe assumeall commands are correct. FOR now
- 

- [ ] Make a proper todolist
- [X] reimplement sys command
- [X] Implement quit command
- [X] current Ls command is very very unsafe, disallow semicolor or use readdir and create everything yourself. Semicolon truncated during sanitization.
- [X] find a way to store server/client IP in the OBJECT after forking
- [X] DO port command
- [X] Do client's counterpart of PORT
- [X] then come back to list
- [X] TEST LS in current connection first, then implement below things
- [X] Implement client side supported commands
- [X] sanitize request convert `ls` to `LIST`
- [X] implement basic pwd
- [X] implement FORK on new command
- [X] Implement data connection manager
- [X] Implement PORT
- [X] check if prev command was a port command
- [X] if not, use default PORT values 
- [X] if yes, use new PORT values
- [X] Then establist a data connection from Server to Client