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
        os.rmdir(function_caching.CACHE_DIR_PATH)

    def test_cache_dir_not_yet_created(self):
        self.assertTrue(function_caching.cache_dir_not_yet_created())
        os.makedirs(function_caching.CACHE_DIR_PATH)
        self.assertFalse(function_caching.cache_dir_not_yet_created())


if __name__ == '__main__':
    unittest.main()
