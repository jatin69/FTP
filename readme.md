# FTP

A client-server Implementation of the File Transfer Protocol closely following [RFC-959](https://tools.ietf.org/html/rfc959) and [Beej's Guide](https://beej.us/guide/bgnet/html/multi/index.html).

## Demo

The developer was too lazy to make a screencast. You may want checkout the [`logs`](logs/).

## Features

- Closely follows the official spec for FTP : `RFC-959`
- Provides basic authentication with multiuser support.
- Supports multiple client connections.
- Handles control connection (`PI`) and data connection (`DTP`) separately.
- Supports switching of data connection port with `PORT` command.
- Works over `localhost`, `local network` and over the `internet`.

<details> 
<summary> Click here to know about all the supported commands. </summary>

## Supported commands

All command mentioned below are case insensitive unless otherwise specified.

| Command  | Usage                                                                                                             | Action                                                                                                                 |
| -------- | ----------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------- |
| HELP     | `help`                                                                                                            | Show all the available commands                                                                                        |
| `!<cmd>` | `!pwd`<br> `!cd ..`<br> `!mkdir clientDir`                                                                        | Execute a command on the client itself. Because they are directly executed on client system, these are case sensitive. |
| NOOP     | `noop`                                                                                                            | Execute No operation. Serves as a dummy command.                                                                       |
| USER     | `USER <username>`<br> `user root`                                                                                 | Provide username for login                                                                                             |
| PASS     | `PASS <password>`<br> `pass root`                                                                                 | Provide password for login                                                                                             |
| SYS      | `sys`                                                                                                             | Get System Details Of server                                                                                           |
| PWD      | `pwd`                                                                                                             | Print working directory                                                                                                |
| LIST     | `LIST`<br> `ls`<br> `ls serverDir`                                                                                | List directory contents                                                                                                |
| CWD      | `cwd ..`<br> `cd ..`<br> `cd serverDir`                                                                           | Change working directory                                                                                               |
| CDUP     | `cdup`                                                                                                            | Change to parent directory                                                                                             |
| MKD      | `mkd dirName`<br> `mkdir dirName`                                                                                 | Make directory                                                                                                         |
| RMD      | `rmd dirName`<br> `rmdir dirName`                                                                                 | Remove directory                                                                                                       |
| STOR     | `STOR putFileOnServer.txt`<br> `put putFileOnServer.txt`                                                          | Send File to Server                                                                                                    |
| RETR     | `RETR getFileFromServer.txt`<br> `get getFileFromServer.txt`                                                      | Retrive File from Server                                                                                               |
| PORT     | `PORT <IP> <Port>` <br> `PORT CURRENT_MACHINE_IP 5643` <br> `PORT localhost 9584` <br> `PORT 200.212.111.32 8868` | Switch data connection IP, Port                                                                                        |
| QUIT     | `quit`<br> `exit`                                                                                                 | Quit the application                                                                                                   |
| ABORT    | `abort`<br> `abor`                                                                                                | Abort the last command and related data transfer                                                                       |
| PASV     | `pasv`                                                                                                            | Switch to Passive Receive Mode                                                                                         |
| TYPE     | `TYPE A E`                                                                                                        | Switch the representation type. Default is `ASCII Non Print`.                                                          |
| MODE     | `MODE S`                                                                                                          | Switch the transfer mode. Default is `Stream`.                                                                         |
| STRU     | `STRU F`                                                                                                          | Switch the File structure Type. Default is `File`.                                                                     |

</details>

## How to make

- `git clone` and `cd` in the folder
- make sure you have `make` installed, then run `make -s`
- it will create a bin folder with two executables `client` and `server`

## How to Run

- go to where executables live `cd ./bin`
- `server` needs to be started first. Usage is as follows.
  - `./server` This uses `port=9000` as default.
  - `./server <portNumber>` in case you want to supply custom port number.
- `client` can be started as follows.
  - `./client` This uses `host=localhost` and `port=9000` as defaults.
  - `./client <serverIP> <serverPort>` in case server is on different machine.

## Testing

The code has been tested in `all three cases` mentioned above.
The maximum file size tested is `190 MB` over the internet and `2.5 GB` over `localhost`.
In theory, it should work for even bigger file sizes.
File integrity is intact, no corruption occurs during the transfer.

<details> <summary> Click here to know more about the testing details. </summary>

### Localhost

- Both client and server are on same machine.
- Use `127.0.0.1` or `localhost` as Server IP

### LAN

- Both system are on Local Network
- use localIPs like `192.168.0.9`. You must know server's local IP for this.

### Internet

- Both systems want to transfer files over the internet.
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

</details>

## General Questions

<details> <summary> How to analyse what's happening behind the scenes ? </summary>

## How to analyse

- Monitoring system calls with `strace`
  - `strace` will allow you to monitor relevant system calls as they happen.
  - go to where executable live `cd ./bin`
  - `strace -fe trace=process,network,signal ./bin/server 9000`
  - `strace -fe trace=process,network,signal ./bin/client 127.0.0.1 9000`
- Monitoring processes, their children, pid, ppid, pgid with `ps`
  - Use `ps fj` to see the tree format of all the forks, along with their pid's and ppid's.
- Generating logs with `tee`. This is very unpredictable for interactive programs.
  - `make | tee logs/makelog.txt`
  - `./bin/server | tee logs/serverlog.txt`
  - `./bin/client | tee logs/clientlog.txt`
- Hiding all the server logs with output redirection
  - To hide all output from server, send it to the null device
  - `./server &>/dev/null`

</details>

<details> <summary> How is the code in the project formatted ? </summary>

## How to Format code

- a `chromium` based, `opinionated` `.clang-format` file is present in project root.
- This has been used for all the formatting in this project.
- Set your IDE format settings to file.
- For VS Code, add these in your `setting.json`
  ```json
  "C_Cpp.clang_format_path": "/usr/bin/clang-format-3.8",
  "C_Cpp.clang_format_style": "file",
  "C_Cpp.clang_format_fallbackStyle": "Chromium",
  ```
- Build your own formatter file [here](https://zed0.co.uk/clang-format-configurator/)
- Know more about unified formatting across IDE's [here](https://xiaoyuliu.github.io/2018/03/30/20180330-clang-format/)

</details>

<details>
  <summary>
    How much work was involved in the project? What's the future scope?
  </summary>

- The project was divided into a lot of small tasks.
- The tasks belonged either of the three categories - 
    + Must have features,
    + Good to have features, and 
    + Future scope.
- You can find all these details in the [extended todo list](./todo.md)

</details>