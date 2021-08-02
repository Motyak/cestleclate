# RUN LOCALLY
```console
$ f=c.cpp; showmain $f && cplusplus $f
int main()
{
    jour = mardi + 6;
    afficher(jour);
}
lundi
```

# RUN WITH CURL
```console
$ f=$(curl -sS https://raw.githubusercontent.com/Motyak/cestleclate/master/exo1/c.cpp); echo "$f" | showmain - && echo "$f" | cplusplus -
int main()
{
    jour = mardi + 6;
    afficher(jour);
}
lundi
```
