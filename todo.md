# Extended Todo List

## Must Have

- [ ] implement HELP Command for client side - authentication + main loop
- [ ] Indent and format all code
- [ ] Finalise code
- [ ] Make a proper readme with screenshots
- [ ] Finalise project

- [X] mark all the log statements by `@logging`
- [X] clean all the printing/logging
- [X] put correct response codes everywhere
- [X] document all code
  - [X] utils
  - [X] headers
  - [X] commands
  - [X] server
  - [X] client
- [X] tell to client why this dir cant be changed. server already knows
- [X] put response code in just major places for now
- [X] Improve authentication. change authentication handler, such that server class stores `ftpUsername`. This will be useful for error messages and such.
- [X] implement authentication via USER and PASS
- [X] The code right now will not work with NAT. Make a helper utility that help in creating a client to server connection to use as dummy then use that for data transfer.
- [X] make verbose mode default. Remove this option. Instead silent using `/dev/null`
- [X] reimplement sys command
- [X] Implement quit command
- [X] find a way to store server/client IP in the OBJECT after forking
- [X] Implement PORT. Do client's counterpart of PORT
- [X] TEST LS in current connection first.
- [X] Implement data connection manager
- [X] Establist a data connection from Server to Client
- [X] implement basic pwd
- [X] implement FORK on new command
- [X] check if prev command was a port command. if not, use default PORT values. if yes, use new PORT values
- [X] Semicolon truncated during sanitization
- [X] sanitize request convert `ls` to `LIST`

## Good To Have

- [X] Make a proper todolist
- [ ] Remove useless headers
- [X] Improve makefile to make everything inside a build folder
- [ ] Optimize makefile for minimum building
- [ ] stor / retr supports pathnames, not just filenames. TEST thoroughly.
- [ ] Update `LIST` command to not use `ls` and use `readdir`
- [ ] Switch to PORT command's `h1,h2,h3,h4,p1,p2` format
- [X] Implement some more commands. as Listed in `server.cpp`
  - [X] CDUP
  - [X] STRU, TYPE, MODE
- [X] argument error checking for all commands
- [X] Implement client side supported commands
- [X] implement client side functions (child commands) - !ls, !pwd
- [X] implement client side - shell builtins - `cd` for now
- [ ] do graceful exception handling
- [ ] colorize all the logging ?
- [ ] Implement ABORT. for ABORT to work, the parent should not wait for the result of child LS and maybe somehow save its pid for it to kill it. Because it is cut in middle, it might need clean up its leftovers.
- [ ] resolve all the @todos
  - [ ] closing unncessary connections

## Future scope

- [ ] implement PASV command. Test with one client & server-to-server transfer
- [ ] Transferring multiple files in single data connection
- [ ] Using ncurses to handle input `history` and other useful stuff