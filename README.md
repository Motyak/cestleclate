# INSTALL.. (needs sudo)
```console
foo@bar:<...>$ sudo -- sh -c 'wget https://raw.githubusercontent.com/Motyak/cestleclate/master/cplusplus/install.sh && sh install.sh && rm install.sh'
```

# .. AND RUN
```console
foo@bar:<...>/cestleclate$ cplusplus c.cpp
lundi
```

# OR JUST RUN (no sudo needed)
```console
foo@bar:<...>$ FILE=/tmp/$(date +%s) && wget -qO $FILE.sh https://raw.githubusercontent.com/Motyak/cestleclate/master/cplusplus/s.sh && wget -qO $FILE.cpp https://raw.githubusercontent.com/Motyak/cestleclate/master/c.cpp && sh $FILE.sh $FILE.cpp && rm $FILE.sh $FILE.cpp
lundi
```