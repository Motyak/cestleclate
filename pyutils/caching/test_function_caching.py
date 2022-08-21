import unittest
import os
import shutil

import function_caching


class TestFunctionCaching(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        function_caching.CACHE_DIR_PATH = './.test_cache'

    def tearDown(self):
        if os.path.isdir(function_caching.CACHE_DIR_PATH):
            shutil.rmtree(function_caching.CACHE_DIR_PATH)

    # assure that we uses the cache path constant in the package,
    # and that we return True for non-existence
    # assure that cache is a directory and has the expected permissions
    #
    # assume the environement doesn't have a cache dir before
    # the test
    def test_cache_dir_not_accessible(self):
        self.assertTrue(function_caching.cache_dir_not_accessible())
        with open(function_caching.CACHE_DIR_PATH, 'w') as _:
            pass
        self.assertTrue(function_caching.cache_dir_not_accessible())
        os.remove(function_caching.CACHE_DIR_PATH)
        os.makedirs(function_caching.CACHE_DIR_PATH)
        os.chmod(function_caching.CACHE_DIR_PATH, 0o500)
        self.assertTrue(function_caching.cache_dir_not_accessible())
        os.chmod(function_caching.CACHE_DIR_PATH, 0o700)
        self.assertFalse(function_caching.cache_dir_not_accessible())

    # assure that we uses the cache path constant in the package
    # assure that the cache directory has the proper permissions
    # assure that we recreate the cache directory if it already exists
    #
    # assume the environment doesn't have a cache dir before
    # the test
    def test_create_cache_dir(self):
        with open(function_caching.CACHE_DIR_PATH, 'w') as _:
            pass
        function_caching.create_cache_dir()
        with open(f'{function_caching.CACHE_DIR_PATH}/foo', 'w') as _:
            pass
        function_caching.create_cache_dir()
        self.assertEqual(0, len(os.listdir(function_caching.CACHE_DIR_PATH)))
        self.assertTrue(os.access(function_caching.CACHE_DIR_PATH, os.R_OK))
        self.assertTrue(os.access(function_caching.CACHE_DIR_PATH, os.W_OK))
        self.assertTrue(os.access(function_caching.CACHE_DIR_PATH, os.X_OK))

    # assure that we uses the invalid characters constant as well as
    # the max length constant in the package
    # assure we uses % symbol + hex ascii code to replace invalid characters
    # and that we have collision resistance (only one input should be mapped
    # to a given output)
    def test_sanitize_filename(self):
        for c in function_caching.FILENAME_INVALID_CHARACTERS:
            filename = f'foo{c}bar'
            self.assertEqual(f'foo%{ord(c):X}bar',
                             function_caching.sanitize_filename(filename))

        filename = 'a' * (function_caching.FILENAME_MAX_LENGTH + 1)
        self.assertGreater(function_caching.FILENAME_MAX_LENGTH,
                           len(function_caching.sanitize_filename(filename)))

        self.assertNotEqual(function_caching.sanitize_filename(r'/'),
                            function_caching.sanitize_filename(r'%2F'))


if __name__ == '__main__':
    unittest.main()
