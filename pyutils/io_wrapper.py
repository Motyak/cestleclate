import os
import shutil


def regular_file_exists(path):
    return os.path.isfile(path)


def dir_exists(path):
    return os.path.isdir(path)


def file_has_permissions(path, permissions: str):
    """
    permissions are only checked for the user (the script runner)
    permissions are formatted as 'r-x', you can also use _ on
    permissions you do not wish to check (e.g.: '_w_')
    """
    if len(permissions) != 3 or \
            permissions[0] not in ['r', '-', '_'] or \
            permissions[1] not in ['w', '-', '_'] or \
            permissions[2] not in ['x', '-', '_']:
        raise PermissionsFormatError(f"Invalid format: '{permissions}'")

    ok = [os.R_OK, os.W_OK, os.X_OK]
    for i in range(3):
        if permissions[i] == '_':
            continue
        permission_ok = os.access(path, ok[i])
        if permissions[i] == '-':
            if permission_ok:
                return False
        elif not permission_ok:
            return False
    return True


def create_dir(path, permissions=0o777):
    """
    force (re)creation of the directory with the given permissions
    permissions are passed as an octal number (e.g.: 0o750)
    """
    if os.path.exists(path):
        if os.path.isdir(path):
            shutil.rmtree(path)
        else:
            os.remove(path)
    os.makedirs(path)
    os.chmod(path, permissions)


class PermissionsFormatError(Exception):
    pass
