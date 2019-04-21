# Extended Todo List

## Must Have

- [X] release version 0.2
- [X] Make a proper readme with features
- [X] client username in all the logging
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

- [ ] Create a demo video
- [X] add v0.2 logs
- [x] Make a proper todolist
- [ ] Remove useless headers
- [x] Improve makefile to make everything inside a build folder
- [ ] Optimize makefile for minimum building
- [ ] stor / retr supports pathnames, not just filenames. TEST thoroughly.
- [ ] Update `LIST` command to not use `ls` system command and use `readdir` instead.
- [ ] Switch to PORT command's `h1,h2,h3,h4,p1,p2` format. Not really required.
- [x] Implement some more commands. as Listed in `server.cpp`
  - [x] CDUP
  - [x] STRU, TYPE, MODE
- [x] argument error checking for all commands
- [x] Implement client side supported commands
- [x] implement client side functions (child commands) - !ls, !pwd
- [x] implement client side - shell builtins - `cd` for now
- [X] implement basic signal handling
- [X] reap off zombie processes on server-client side
- [X] do graceful exception handling
- [X] `Multi-file transfer` Not possible in stream Mode. Block mode is needed. Moved to future scope.
- [ ] Follow exactly as mentioned in `RFC 959` [`3.2.  ESTABLISHING DATA CONNECTIONS`](https://www.w3.org/Protocols/rfc959/3_DataTransfer.html) section. Probably a candidate for `v0.3`
  - Ideally, we have exact rules for `to which port of receiver` to send data, and `using which port of self` to send data.
  - Right now, the only thing considered important is `3.2.  ESTABLISHING DATA CONNECTIONS``to which port of receiver` should we send data.
  - This mechanics still works, because in reality, only this is important to transfer data.
  - The `using which port of self` is more about following the spec, and has no visible advantage for which it should be pursued.
  - However, because this implemention is about following the spec as closely as possible, it is good to follow this section as well.
  - For this, the `createDataConnection` function has to be edited. Consequently leading to `createSocketAndConnectToHost`, which will then result in formation of a new function doing exactly same as this, but which also lets us specify self port `createSocketBindPortAndConnectToHost`.
  - This new function will then help `createDataConnection` in doing things as per spec.

## Future scope

- [ ] Resolve all the `@todo`'s
- [ ] Do optimised exception handling
- [ ] Move to precise colored outputs ?? and no extra logging ??
- [ ] make a command buffer to allow simultaneous commands without pressing `enter`
- [ ] Handle input `history` and other stuff using `ncurses` ? Maybe.
- [ ] Implement ABORT and related functionality - refer to branch `develop-ABOR`
- [ ] implement PASV command. Test with one client & server-to-server transfer
- [ ] Implement `BLOCK MODE` - not closing the data connection immediately and reusing it in subsequent requests until a TTL.
- [ ] Implement `BLOCK MODE` to allow transferring of multiple files in a single data connection. 
- [ ] add unit tests
