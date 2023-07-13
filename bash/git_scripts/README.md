# HOW TO USE

## interactive mode

```terminal
$ gittransaction
BEGIN TRANSACTION
# type in git commands
# ...
transaction...> exit
END TRANSACTION
Cleaning...
```

## passing a script file (bash or sh)

```terminal
gittransaction < example.sh
BEGIN TRANSACTION
# <script output if any>
END TRANSACTION
Cleaning...
```

## passing a script file (bash or sh) with a timeout

```terminal
timeout 10s gittransaction < example.sh
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
