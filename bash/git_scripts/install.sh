#!/usr/bin/env bash

set -o errexit

trap '>&2 echo "ABORTED !"' ERR

home_dir="$HOME"
install_dir="$home_dir/.local/bin"
prog_path="$install_dir/gittransaction"

>&2 echo "Creating installation dir \`$install_dir\` ..."
mkdir -p "$install_dir"

>&2 echo "Downloading gittransaction.sh to \`$prog_path\` ..."
wget -O "$prog_path" \
    https://github.com/Motyak/cestleclate/raw/master/bash/git_scripts/gittransaction.sh
chmod u+x "$prog_path"

>&2 echo "Adding gittransaction to user \`$(whoami)\`'s .bashrc ..."
echo $'\n'"alias gittransaction='$prog_path'" >> "$home_dir/.bashrc"

>&2 echo "Adding gittransaction to current shell ..."
alias gittransaction="\'$prog_path\'"

>&2 echo "DONE !"