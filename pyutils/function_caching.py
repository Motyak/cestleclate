import io_wrapper

CACHE_DIR_PATH = './.cache'
# consider these illegal characters  < > : " / \ | ? *
# consider any character which ascii code is in {0,...,32,127}
# to be illegal
FILENAME_INVALID_CHARACTERS = [chr(i) for i in [*range(0, 33), 127]] +\
    [*r'<>:"/\|?*']
FILENAME_MAX_LENGTH = 255


def cache_dir_not_accessible():
    """
    returns True if CACHE_DIR_PATH doesn't exist, isn't a directory
    or doesn't have the expected permissions
    """
    return not io_wrapper.dir_exists(CACHE_DIR_PATH) or \
           not io_wrapper.file_has_permissions(CACHE_DIR_PATH, 'rwx')


def create_cache_dir():
    """
    (re)creates CACHE_DIR_PATH directory with proper permissions
    """
    io_wrapper.create_dir(CACHE_DIR_PATH, 0o700)


# consider we need to replace illegal characters with their
# ascii code in hexadecimal, preceded by a % sign, in order to minimize
# the input alteration while conserving collision resistance
def sanitize_filename(filename):
    for c in ['%', *FILENAME_INVALID_CHARACTERS]:
        filename = filename.replace(c, f'%{ord(c):X}')
    if len(filename) > FILENAME_MAX_LENGTH:
        filename = str(hash(filename))
    return filename


def generate_filename(function, *args):
    filename = f'{function.__name__}{args}.txt'
    return sanitize_filename(filename)


def not_available_in_cache(filename):
    file_path = f'{CACHE_DIR_PATH}/{filename}'
    return not io_wrapper.regular_file_exists(file_path)


def write_to_cache(filename, content):
    new_file_path = f'{CACHE_DIR_PATH}/{filename}'
    with open(new_file_path, 'w', encoding='utf-8') as text_file:
        text_file.write(content)


def read_from_cache(filename):
    file_path = f'{CACHE_DIR_PATH}/{filename}'
    with open(file_path, 'r', encoding='utf-8') as text_file:
        return text_file.read()


# @USE_CACHING for using this decorator
def USE_CACHING(function):
    def inner(*args):
        filename = generate_filename(function, *args)
        if not_available_in_cache(filename):
            result = function(*args)
            if cache_dir_not_accessible():
                create_cache_dir()
            write_to_cache(filename, result)
            return result
        return read_from_cache(filename)
    return inner
