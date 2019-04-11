# Extended Todo List

## Must Have

- [ ] release version 0.2
- [ ] Make a proper readme with screenshots

- [x] Indent and format all code
- [x] Finalise code
- [x] implement HELP Command for client side - authentication + main loop
- [x] mark all the log statements by `@logging`
- [x] clean all the printing/logging
- [x] put correct response codes everywhere
- [x] document all code
  - [x] utils
  - [x] headers
  - [x] commands
  - [x] server
  - [x] client
- [x] tell to client why this dir cant be changed. server already knows
- [x] put response code in just major places for now
- [x] Improve authentication. change authentication handler, such that server class stores `ftpUsername`. This will be useful for error messages and such.
- [x] implement authentication via USER and PASS
- [x] The code right now will not work with NAT. Make a helper utility that help in creating a client to server connection to use as dummy then use that for data transfer.
- [x] make verbose mode default. Remove this option. Instead silent using `/dev/null`
- [x] reimplement sys command
- [x] Implement quit command
- [x] find a way to store server/client IP in the OBJECT after forking
- [x] Implement PORT. Do client's counterpart of PORT
- [x] TEST LS in current connection first.
- [x] Implement data connection manager
- [x] Establist a data connection from Server to Client
- [x] implement basic pwd
- [x] implement FORK on new command
- [x] check if prev command was a port command. if not, use default PORT values. if yes, use new PORT values
- [x] Semicolon truncated during sanitization
- [x] sanitize request convert `ls` to `LIST`

## Good To Have

- [x] Make a proper todolist
- [ ] Remove useless headers
- [x] Improve makefile to make everything inside a build folder
- [ ] Optimize makefile for minimum building
- [ ] stor / retr supports pathnames, not just filenames. TEST thoroughly.
- [ ] Update `LIST` command to not use `ls` system command and use `readdir` instead.
- [ ] Switch to PORT command's `h1,h2,h3,h4,p1,p2` format
- [x] Implement some more commands. as Listed in `server.cpp`
  - [x] CDUP
  - [x] STRU, TYPE, MODE
- [x] argument error checking for all commands
- [x] Implement client side supported commands
- [x] implement client side functions (child commands) - !ls, !pwd
- [x] implement client side - shell builtins - `cd` for now
- [ ] do graceful exception handling
- [ ] colorize all the logging ?
- [ ] Implement ABORT. for ABORT to work, the parent should not wait for the result of child LS and maybe somehow save its pid for it to kill it. Because it is cut in middle, it might need clean up its leftovers.

## Future scope

- [ ] Resolve all the `@todos`
- [ ] implement PASV command. Test with one client & server-to-server transfer
- [ ] Transferring multiple files in single data connection
- [ ] Using ncurses to handle input `history` and other useful stuff
- [ ] When ready, move to precise colored outputs, and no logging.
