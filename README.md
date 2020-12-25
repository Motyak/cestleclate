# INSTALL.. (needs sudo)
```console
$ sh <(curl -sS https://raw.githubusercontent.com/Motyak/cestleclate/master/cplusplus/install.sh)
```

# .. AND RUN
```console
$ curl -sS https://raw.githubusercontent.com/Motyak/cestleclate/master/c.cpp | cplusplus -
lundi
```

# OR JUST RUN (no sudo needed)
```console
$ sh <(curl -sS https://raw.githubusercontent.com/Motyak/cestleclate/master/run.sh)
lundi
```

# [INSTALL SHOWMAIN (needs sudo)]
```console
$ sh <(curl -sS https://raw.githubusercontent.com/Motyak/cestleclate/master/showmain/install.sh)
```

# SHOW MAIN AND EXEC (no sudo needed)
```console
$ f=$(curl -sS https://raw.githubusercontent.com/Motyak/cestleclate/master/c.cpp); echo "$f" | showmain - && echo "$f" | cplusplus -
int main()
{
    jour = mardi + 6;
    afficher(jour);
}
lundi
```

# [INSTALL TRANSPILER (needs sudo)]
```console
$ sh <(curl -sS https://raw.githubusercontent.com/Motyak/cestleclate/master/transpiler/install.sh)
```
