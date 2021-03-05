# RUN LOCALLY
```console
$ f=c.cpp; showmain $f && transpiler $f | cplusplus -pthread -
int main()
{
    afficher(heure);
    attendre(3s);
    afficher(heure);
}
Mon Feb 15 01:50:03 2021
Mon Feb 15 01:50:06 2021
```

# RUN LOCALLY WITH STYLE
```console
$ f=c.cpp; showmain $f && cplusplus <(./$f) -pthread
int main()
{
    afficher(heure);
    attendre(3s);
    afficher(heure);
}
Mon Feb 15 01:50:03 2021
Mon Feb 15 01:50:06 2021
```

# RUN WITH CURL
```console
$ f=$(curl -sS https://raw.githubusercontent.com/Motyak/cestleclate/master/exo2_bonus/c.cpp); echo "$f" | showmain - && echo "$f" | transpiler | cplusplus -pthread -
int main()
{
    prix = $99.99 - 25%;
    afficher(prix);
}
$74.99
```
