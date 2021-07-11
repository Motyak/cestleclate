# RUN LOCALLY
```console
$ f=c.cpp; showmain $f && transpiler $f | cplusplus -
int main()
{
	prix = $99.99 - 25%;
	afficher(prix);
}
$74.99
```

# RUN LOCALLY WITH STYLE
```console
$ f=c.cpp; showmain $f && cplusplus <(./$f)
int main()
{
	prix = $99.99 - 25%;
	afficher(prix);
}
$74.99
```

# RUN WITH CURL
```console
$ f=$(curl -sS https://raw.githubusercontent.com/Motyak/cestleclate/simple/exo2/c.cpp); echo "$f" | showmain - && echo "$f" | transpiler | cplusplus -
int main()
{
	prix = $99.99 - 25%;
	afficher(prix);
}
$74.99
```
