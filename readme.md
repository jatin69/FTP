# FTP

A client-server Implementation of the File Transfer Protocol closely following [RFC-959](https://tools.ietf.org/html/rfc959) and [Beej's Guide](https://beej.us/guide/bgnet/html/multi/index.html). 

Checkout the extented todoList [here](./todoList.md)

## How to make

- make sure you have `make` installed
- then simply clone the project and run `make -s` in the folder
- it'll give you two executables `./bin/server` and `./bin/client`

## How to Run

- go to bin folder `cd ./bin`
- `server` can be started as `./server <servePort[9000]>`
- `client` can be started as `./client <serverIP> <serverPort[9000]>`
- For localhost you can use `./server 9000` and `./client 127.0.0.1 9000`
- Also ensure that you run server first.

## How to Debug

- To verify everything is going as intented, use `strace`
- `strace -fe trace=process,network,signal ./server 9000`
- `strace -fe trace=process,network,signal ./client 127.0.0.1 9000`

## How to production

- To hide all output from server/client use the null device `./server &>/dev/null`

## Testing

The code in this project has been tested in `all three cases` below and it works. Phew.
The maximum file size tested is `40MB` pdf file. That's a pretty big file for FTP. In theory, it should work for even bigger file sizes. File integrity has been checked and no corruption occurs. File is as usable as the original one.

### Localhost

- Both client and server are on same machine.
- Use `127.0.0.1` or `localhost` as Server IP

### LAN

- Both system are on Local Network
- use localIPs like `192.168.0.9`. You must know server's local IP for this.

### Internet

- Both systems are on internet. 
- Verify that your system is accessible from the Internet, and there exists a route from Internet to your system. 
- The easiest way to know this is 
- Run the server program on your machine 
- From the VM run command `telnet <yourSystemsPublicInternetIP> <portOnWhichServerIsRUnning=9000>` 
- It should ideally establish connection, because FTP is based on the telnet protocol. If however, it says `No route to Host`, then it means your system is behind a router and NAT is your enemy.
- VM Instances
  - A VM on digital ocean was also used for testing. It is no longer active now.
  - VM-1 on Google cloud `ssh jatin@ftp-tester-1` : acts as server
  - VM-2 on Google cloud `ssh jatin@ftp-tester-2` : acts as client
  - Above roles on client and server machine can also be switched.
  - Note that these are my VMs. You might need to create yours to test.
  - To get your own VMs working
    - Simply create some `VM instances` on google cloud
    - Setup ssh login. Then login using `ssh <username>@<external-IP>`
    - If you don't want to remember external IP's you can also add custom hostnames and resolve them in your `/etc/hosts` file
    - Note that, on google cloud, all ports are blocked by default. But our ftp-server should be allowed to use ports freely. So we have to add two `Firewall rules` to allow `ingress and egress traffic` on `all ports` on `all protocols` accessible by `all IPs` i.e. `0.0.0.0/0` 
    - Then `clone` the project, `make` it, and run
    - Note that - to connect to server, client needs his `public internet ip`. 
    - To obtain a machine's internet IP, use `curl ifconfig.me` 
