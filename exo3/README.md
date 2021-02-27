# BUILD BINARIES
```console
$ ./build.sh
```

# RUN (COMMUNICATION WITH A PIPE)
```console
$ ./client | ./serveur
<...>
```

# RUN (COMMUNICATION THROUGH A NETWORK)
```console
<server machine>$ nc -l localhost 55555 | ./serveur
```
```console
<client machine>$ ./client | nc localhost 55555 -q1
```
```console
<...>
<server machine>$
```