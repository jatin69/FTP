# FTP

A client-server Implementation of the File Transfer Protocol closely following [RFC-959](https://tools.ietf.org/html/rfc959) and [Beej's Guide](https://beej.us/guide/bgnet/html/multi/index.html). 

## Demo

Screenshots / screencasts coming soon.

## How to make

- `git clone` and `cd` in the folder
- make sure you have `make` installed, then run `make -s`
- it'll give you two executables in the bin folder

## How to Run

- go to where executable live `cd ./bin`
- `server` can be started as `./server <servePort[9000]>`
- `client` can be started as `./client <serverIP> <serverPort[9000]>`
- For localhost you can use `./server 9000` and `./client 127.0.0.1 9000`
- Also ensure that you run server first.

## How to Debug

- To verify everything is going as intented, use `strace`
- `strace` will allow you to monitor relevant system calls as they happen.
- `strace -fe trace=process,network,signal ./server 9000`
- `strace -fe trace=process,network,signal ./client 127.0.0.1 9000`

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

- Both systems wants to transfer files over internet. 
- Internet Testing has been done with VM instances for below 2 scenarios.
  - `Scenario 1` : Server and client are both on different VMs. Both have static IP.
  - `scenario 2` : Server is on VM with static IP. Client is my machine (behind a router).
  - VM-1 on Google cloud `ssh jatin@ftp-tester-1` : acts as server
  - VM-2 on Google cloud `ssh jatin@ftp-tester-2` : acts as client
- Ensure that server has `static IP`. The easiest way to know if a machine has a `static internet IP` is :
  - Run the server program on the machine you wish to test for static IP
  - From any other machine `telnet <machineInternetIP> <portOnWhichServerIsRUnning=9000>` 
  - To obtain a machine's internet IP, use `curl ifconfig.me`
  - It should ideally establish connection, because FTP is based on the telnet protocol. If however, it says `No route to Host`, then it means the machine is behind a router and NAT is your enemy.
- Things to keep in mind while creating your VMs for testing -
  - First, create some `VM instances` on google cloud. Make sure you have free credits.
  - Server needs to have a static IP. In your project, go to `VPC network` > `External IP addresses` and reserve static IP address for your machines.
  - On google cloud, all ports are blocked by default. But our ftp-server should be allowed to use ports freely. So we have to add two `Firewall rules` to allow `ingress and egress traffic` on `all ports` on `all protocols` accessible by `all IPs` i.e. `0.0.0.0/0` 
  - Setup ssh login. Then login using `ssh <username>@<external-IP>`
  - If you don't want to remember external IP's you can also add custom hostnames and resolve them in your `/etc/hosts` file
  - Then `clone` the project, `make` it, and run
  - To connect to server, client needs to know server's `static internet ip`. That's a pre-requisite.

## Production

- To hide all output from server use the null device `./server &>/dev/null`
- To generate logs along with display use `tee` command
  - `make | tee logs/makelog.txt`
  - `./bin/server | tee logs/serverlog.txt`
  - `./bin/client | tee logs/clientlog.txt`

## Supported Commands

| command | nickname | Action                                        |
| ------- | -------- | --------------------------------------------- |
| `LIST`  | `ls`     | Displays Directory Listing of Server          |
| `PWD`   | `pwd`    | Displays present working directory for server |
|         |          |                                               |