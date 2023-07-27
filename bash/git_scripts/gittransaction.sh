#!/usr/bin/env -S bash -i

[ "${BASH_SOURCE[0]}" != "$0" ] && >&2 echo "script should not be sourced" && return 1

g_git_dir_abs_path="$(git rev-parse --show-toplevel)"
[ $? -ne 0 ] && >&2 echo "script should not be executed outside of a git repository"
g_gitscripts_repo=""

set -o errexit

trap clean_and_exit EXIT
function clean_and_exit {
    local exit_code=$?

    # allow to locate at which step the failure took place (preparation, transaction itself or commit)
    [ $exit_code -ne 0 ] && >&2 echo "ABORT TRANSACTION"

    set +o errexit; trap - ERR # cleaning shall not fail
    >&2 echo "Cleaning..."
    git::unlock
    gitscripts::unlock

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

function uri_to_filename {
    sed -e 's/%/%25/g' \
        -e 's/\//%2f/g' \
        -e 's/:/%3a/g' \
        -e 's/?/%3f/g' \
        -e 's/\*/%2a/g' <<< "$@"
}

function get_cur_repo_id {
    local remote_origin_url; remote_origin_url="$(git config --get remote.origin.url)"
    local repository_name; repository_name="${remote_origin_url##*//}"
                           repository_name="$(uri_to_filename "${repository_name%.git}")"
    local hashed_git_dir_abs_path; hashed_git_dir_abs_path="$(md5sum <<< "$g_git_dir_abs_path")"

    local repository_id="$repository_name--${hashed_git_dir_abs_path::4}"
    echo -n "$repository_id"
}

function gitscripts::lock {
    local repository_id; repository_id="$(get_cur_repo_id)"
    # try and acquire the lock
    until (set -o noclobber; echo $$ > "/tmp/git-scripts/lock/$repository_id") &>/dev/null; do
        sleep 1 # retry in a second
    done
    g_gitscripts_repo="$repository_id"
}

function gitscripts::unlock {
    rm -f "/tmp/git-scripts/lock/$g_gitscripts_repo"
}

function begin_git_transaction {
    >&2 echo "PREPARE TRANSACTION"
    gitscripts::lock
    git::lock

    mkdir -p "/tmp/git-scripts/cache/$g_gitscripts_repo"; cd "$_"
    rsync -a --delete "$g_git_dir_abs_path/" .

    export GITTRANSACTION="occuring"
    >&2 echo "BEGIN TRANSACTION"
}

function end_git_transaction {
    >&2 echo "COMMIT TRANSACTION"
    cd -
    rsync -a --delete "$OLDPWD/" "$g_git_dir_abs_path"

    >&2 echo "END TRANSACTION"
}

# make sure these directories exist
mkdir -p /tmp/git-scripts/lock \
         /tmp/git-scripts/cache

begin_git_transaction
    bash -o errexit --rcfile <(echo 'PS1="transaction...> "')
end_git_transaction
