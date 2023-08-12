[ "${BASH_SOURCE[0]}" == "$0" ] && {
    >&2 echo "script should not be executed"
    exit 1
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
