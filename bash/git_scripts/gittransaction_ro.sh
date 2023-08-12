#!/usr/bin/env -S bash -i

[ "${BASH_SOURCE[0]}" != "$0" ] && {
    >&2 echo "script should not be sourced"
    return 1
}

git rev-parse || {
    >&2 echo "script should not be executed outside of a git repository"
    exit 1
}

set -o errexit

trap clean_and_exit EXIT
function clean_and_exit {
    local exit_code=$?

    # allow to locate at which step the failure took place (preparation, transaction itself or commit)
    [ $exit_code -ne 0 ] && >&2 echo "ABORT TRANSACTION"

    set +o errexit; trap - ERR # cleaning shall not fail
    >&2 echo "Cleaning..."
    git::unlock

    exit $exit_code
}

function git::lock {
    # try and acquire the lock
    until (set -o noclobber; echo $$ > .git/index.lock) &>/dev/null; do
        sleep 1 # retry in a second
    done
}

function git::unlock {
    rm -f .git/index.lock
}

function begin_git_transaction {
    >&2 echo "PREPARE TRANSACTION"
    git::lock

    export GITTRANSACTION="occuring"
    >&2 echo "BEGIN TRANSACTION"
}

function end_git_transaction {
    >&2 echo "END TRANSACTION"
}

begin_git_transaction
    bash -o errexit --rcfile <(echo 'PS1="transaction...> "')
end_git_transaction
