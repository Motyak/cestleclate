# RUN (COMMUNICATION WITH A PIPE)
```console
$ prog='eval cplusplus <(./c.cpp) -D'; $prog client | $prog serveur
Hamburger: x1
Nuggets: x1
Coca-cola: x1
Total: 6.60EUR 630Cal.

Wings: x1
Frites: x1
Coca-cola: x1
Sundae: x1
Total: 9.60EUR 1020Cal.

Hamburger: x1
Frites: x1
Coca-cola: x1
Total: 6.40EUR 640Cal.
```

# RUN (COMMUNICATION THROUGH A NETWORK)
```console
user1@server$ nc -l localhost 55555 | cplusplus <(./c.cpp) -D serveur
```
```console
user2@client$ cplusplus <(./c.cpp) -D client | nc localhost 55555 -q1
```
```console
Hamburger: x1
Nuggets: x1
Coca-cola: x1
Total: 6.60EUR 630Cal.

Wings: x1
Frites: x1
Coca-cola: x1
Sundae: x1
Total: 9.60EUR 1020Cal.

Hamburger: x1
Frites: x1
Coca-cola: x1
Total: 6.40EUR 640Cal.
user1@server$
```

# BUILD AND RUN BINARIES
```console
$ for prog in client serveur; do g++ -x c++ <(./c.cpp) -D $prog -o $prog -I . -std=c++17; done
$ ./client | ./serveur
Hamburger: x1
Nuggets: x1
Coca-cola: x1
Total: 6.60EUR 630Cal.

Wings: x1
Frites: x1
Coca-cola: x1
Sundae: x1
Total: 9.60EUR 1020Cal.

Hamburger: x1
Frites: x1
Coca-cola: x1
Total: 6.40EUR 640Cal.
```