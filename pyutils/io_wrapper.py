import os
import shutil


def regular_file_exists(path):
    return os.path.isfile(path)


def dir_exists(path):
    return os.path.isdir(path)


def file_has_permissions(path, permissions: str):
    """
    permissions is formatted as 'r-x'
    """
    map = {'r': os.R_OK, 'w': os.W_OK, 'x': os.X_OK}
    for permission in permissions.replace('-', ''):
        if not os.access(path, map[permission]):
            return False
    return True


def create_dir(path):
    """
    force (re)creation of the directory with rwx permissions
    """
    if os.path.isdir(path):
        shutil.rmtree(path)
    elif os.path.exists(path):
        os.remove(path)
    os.makedirs(path)
