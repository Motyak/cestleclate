#!/usr/bin/env bash

set -o errexit

trap '>&2 echo "ABORTED !"' ERR

home_dir="$HOME"
install_dir="$home_dir/.local/bin"
prog_path="$install_dir/gittransaction"

>&2 echo "Creating installation dir \`$install_dir\` ..."
mkdir -p "$install_dir"

>&2 echo "Downloading gittransaction.sh to \`$prog_path\` ..."
wget -O "$prog_path" -q --show-progress \
    https://github.com/Motyak/cestleclate/raw/master/bash/git_scripts/gittransaction.sh
chmod u+x "$prog_path"

# escape PCRE metacharacters \/^$.[]|()?*+{}
function pcre::literal_str {
    sed -e 's/\\/\\\\/g' \
        -e 's/\//\\\//g' \
        -e 's/\^/\\\^/g' \
        -e 's/\$/\\\$/g' \
        -e 's/\./\\\./g' \
        -e 's/\[/\\\[/g' \
        -e 's/\]/\\\]/g' \
        -e 's/|/\\|/g' \
        -e 's/(/\\(/g' \
        -e 's/)/\\)/g' \
        -e 's/?/\\?/g' \
        -e 's/*/\\*/g' \
        -e 's/+/\\+/g' \
        -e 's/{/\\{/g' \
        -e 's/}/\\}/g' <<< "$@"
}

# if PATH doesn't contain install_dir..
grep -P '(^|:)'"$(pcre::literal_str "$install_dir")"'(:|$)' <<< "$PATH" || {
    >&2 echo "Adding \`$install_dir\` to user $(whoami)'s .bashrc ..."
    echo $'\n'"export PATH=\"$install_dir:\$PATH\"" >> "$home_dir/.bashrc"

    >&2 cat <<EOF

gittransaction will automatically be added whenever you open a new shell.
Type this command to add gittransaction to your current shell session:"
export PATH="$install_dir:\$PATH"
EOF
}

>&2 echo "DONE !"
