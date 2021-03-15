# RUN (COMMUNICATION WITH A PIPE)
```console
$ prog='eval cplusplus <(./c.cpp) -D'; $prog client | $prog serveur
Double cheese: 1x
Total: 3.50EUR 440Cal.
Cheeseburger: 1x
Frites moyenne: 1x
Total: 4.40EUR 540Cal.
```

# RUN (COMMUNICATION THROUGH A NETWORK)
```console
user1@server$ nc -l localhost 55555 | cplusplus <(./c.cpp) -D serveur
```
```console
user2@client$ cplusplus <(./c.cpp) -D client | nc localhost 55555 -q1
```
```console
Double cheese: 1x
Total: 3.50EUR 440Cal.
Cheeseburger: 1x
Frites moyenne: 1x
Total: 4.40EUR 540Cal.
user1@server$
```

# BUILD AND RUN BINARIES
```console
$ for prog in client serveur; do g++ -x c++ <(./c.cpp) -D $prog -o $prog -I . -std=c++17; done
$ ./client | ./serveur
Double cheese: 1x
Total: 3.50EUR 440Cal.
Cheeseburger: 1x
Frites moyenne: 1x
Total: 4.40EUR 540Cal.
```