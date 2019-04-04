# Todo List

- [ ] implement HELP Command for client side - authentication + main loop
- [ ] put correct response codes everywhere
- [ ] clean all the printing/logging
- [ ] resolve all the @todos
- [ ] document all code
- [ ] Indent and format all code
- [ ] Finalise code
- [ ] Make a proper readme with screenshots
- [ ] Finalise project

- [ ] [goodToHave] Improve makefile to make everything inside a build folder
- [ ] [goodToHave] stor / retr supports pathnames, not just filenames
- [ ] [goodToHave] implement PASV command - pretty easy and will make it more wholesome
- [ ] [goodToHave] Implement ABORT. for ABORT to work, the parent should not wait for the result of child LS and maybe somehow save its pid for it to kill it. Because it is cut in middle, it might need clean up (might)

- [ ] [addition] colorize all the logging ?
- [ ] [addition] implement client side functions - !ls, !pwd

- [ ] change authentication handler, such that server class stores `ftpUsername`. This will be useful for error messages and such.
- [X] Make a proper todolist
- [X] implement authentication via USER and PASS
- [X] Implement some more commands. as Listed in `server.cpp`
  - [X] CDUP
  - [X] STRU, TYPE, MODE
- [X] The code right now will not work with NAT. Make a helper utility that help in creating a client to server connection to use as dummy then use that for data transfer.
- [X] make verbose mode default. Remove this option. Instead silent using `/dev/null`
- [X] ensure that PORT has one argument atleast : error checking for all commands or maybe assumeall commands are correct. FOR now
- [X] reimplement sys command
- [X] Implement quit command
- [X] current Ls command is very very unsafe, disallow semicolor or use readdir and create everything yourself. Semicolon truncated during sanitization.
- [X] find a way to store server/client IP in the OBJECT after forking
- [X] DO port command. Do client's counterpart of PORT
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