# HOW TO USE

## interactive mode

```terminal
$ gittransaction
PREPARE TRANSACTION
BEGIN TRANSACTION
# type in git commands
# ...
transaction...> exit
END TRANSACTION
Cleaning...
```

## passing a script file (bash or sh)

```terminal
$ gittransaction < example.sh
PREPARE TRANSACTION
BEGIN TRANSACTION
# <script output if any>
END TRANSACTION
Cleaning...
```

## passing a script file (bash or sh) with a timeout

```terminal
$ timeout 10s gittransaction < example.sh
PREPARE TRANSACTION
# suppose getting the lock takes too much time...
Cleaning...
```

## passing a block of bash commands

```bash
gittransaction <<EOF
    # git commands
    # ...
EOF
```

# HOW TO INSTALL

```terminal
$ wget -nv -O >(bash) https://raw.githubusercontent.com/Motyak/cestleclate/master/bash/git_scripts/install.sh
```
