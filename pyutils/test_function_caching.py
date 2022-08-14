import unittest
import os

import function_caching


class TestFunctionCaching(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.OLD_CACHE_DIR_PATH = function_caching.CACHE_DIR_PATH
        function_caching.CACHE_DIR_PATH = './.test_cache'

    @classmethod
    def tearDownClass(cls):
        function_caching.CACHE_DIR_PATH = cls.OLD_CACHE_DIR_PATH

    def tearDown(self):
        if os.path.isdir(function_caching.CACHE_DIR_PATH):
            os.rmdir(function_caching.CACHE_DIR_PATH)

    # assure that we uses the cache path constant in the package,
    # and that we return True for non-existence
    #
    # assume the environement doesn't have a cache dir before
    # the test
    def test_cache_dir_not_yet_created(self):
        self.assertTrue(function_caching.cache_dir_not_yet_created())
        os.makedirs(function_caching.CACHE_DIR_PATH)
        self.assertFalse(function_caching.cache_dir_not_yet_created())

    # assure that we uses the cache path constant in the package
    #
    # assume the environment doesn't have a cache dir before
    # the test
    def test_create_cache_dir(self):
        self.assertFalse(os.path.isdir(function_caching.CACHE_DIR_PATH))
        function_caching.create_cache_dir()
        self.assertTrue(os.path.isdir(function_caching.CACHE_DIR_PATH))

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
