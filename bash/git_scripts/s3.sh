#!/usr/bin/env bash

set -o errexit
set -o nounset

trap clean_and_exit EXIT
function clean_and_exit {
    local exit_code=$?

	set +o errexit; trap - ERR # cleaning shall not fail
	>&2 echo "Cleaning..."
    git::unlock
	gitscripts::unlock

    exit $exit_code
}

g_git_locking=false
g_gitscripts_locking=""

function git::lock {
	$g_git_locking && return 0 # git is already being locked => early return
	# try and acquire the lock
	until (set -o noclobber; echo $$ > .git/index.lock) &>/dev/null; do
		sleep 1 # retry in a second
	done
    g_git_locking=true
}

function git::unlock {
    $g_git_locking || return 0 # git isnt being locked => early return
    rm -f .git/index.lock
    g_git_locking=false
}

function gitscripts::lock {
	local repository_id=$1

	$g_gitscripts_locking && return 0 # gitscripts is already being locked => early return
	# try and acquire the lock
	until (set -o noclobber; echo $$ > "/tmp/git-scripts/lock/$repository_id") &>/dev/null; do
		sleep 1 # retry in a second
	done
    g_gitscripts_locking=true
}

function gitscripts::unlock {
	local repository_id=$1

	$g_gitscripts_locking || return 0 # gitscripts isnt being locked => early return
    rm -f "/tmp/git-scripts/lock/$repository_id"
    g_gitscripts_locking=false
}

function uri_to_filename {
	sed -e 's/%/%25/g' \
		-e 's/\//%2f/g' \
		-e 's/:/%3a/g' \
		-e 's/?/%3f/g' \
		-e 's/\*/%2a/g' <<< "$@"
}

function begin_git_transaction {
	local remote_origin_url; remote_origin_url="$(git config --get remote.origin.url)"
	local repository_name; repository_name="$(uri_to_filename ${remote_origin_url##*//})"
	
	local git_dir_abs_path; git_dir_abs_path="$(git rev-parse --show-toplevel)"
	local hashed_git_dir_abs_path; hashed_git_dir_abs_path="$(md5sum <<< $git_dir_abs_path)"

	local repository_id="${repository_name%.git}-${hashed_git_dir_abs_path::4}"

	gitscripts::lock "$repository_id"
	git::lock
	
	# rsync current git repository in git-scripts/
}

function end_git_transaction {
	# ...
	git::unlock
}

# make sure these directories exist
mkdir -p /tmp/git-scripts/lock \
		 /tmp/git-scripts/cache

git::lock # BEGIN TRANSACTION BLOCK
	current_branch_name=$(git branch --show-current)
	git fetch origin "$current_branch_name"
	git merge --ff-only "origin/$current_branch_name" || {
		# make a local backup of current branch #
		backup_branch_name="backupp/$current_branch_name/$(date +%Y-%m-%d_%H-%M-%S)"
		git branch "$backup_branch_name"
	
		# overwrite local branch with remote state
		git reset --hard "origin/$current_branch_name"
	}
git::unlock # END TRANSACTION BLOCK
