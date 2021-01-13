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
# RUN LOCALLY WITH EXPLANATIONS (BASH ONLY)
```console
$ t=transpiler; showmain && diff -a c.cpp <($t); cplusplus <($t)
int main()
{
    prix = $99.99 - 25%;
    afficher(prix);
}
32c32
<     prix = $99.99 - 25%;
---
>     prix = Prix{'$', 99.99} - Pourcentage{25};
$74.99
```

# RUN WITH CURL
```console
$ f=$(curl -sS https://raw.githubusercontent.com/Motyak/cestleclate/master/exo2/c.cpp); echo "$f" | showmain - && echo "$f" | transpiler | cplusplus -
int main()
{
    prix = $99.99 - 25%;
    afficher(prix);
}
$74.99
```
