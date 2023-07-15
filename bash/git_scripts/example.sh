# make sure we only execute this using gittransaction
[ -v GITTRANSACTION ] || exit 1

current_branch_name=$(git branch --show-current)
git fetch origin "$current_branch_name"
git merge --ff-only "origin/$current_branch_name" || {
    # make a local backup of current branch #
    backup_branch_name="backupp/$current_branch_name/$(date +%Y-%m-%d_%H-%M-%S)"
    git branch "$backup_branch_name"

    # overwrite local branch with remote state
    git reset --hard "origin/$current_branch_name"
}
