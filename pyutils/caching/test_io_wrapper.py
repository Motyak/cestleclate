import io_wrapper

import unittest
import os
import shutil


class TestFunctionCaching(unittest.TestCase):
    TEST_DIR_NAME = 'dir'
    TEST_FILE_NAME = 'file'

    def tearDown(self):
        if os.path.isdir(self.TEST_DIR_NAME):
            shutil.rmtree(self.TEST_DIR_NAME)
        if os.path.exists(self.TEST_FILE_NAME):
            os.remove(self.TEST_FILE_NAME)

    # assure we understand how to use foreign code
    def test_regular_file_exists(self):
        self.assertTrue(io_wrapper.regular_file_exists(__file__))

    # assure we understand how to use foreign code
    def test_dir_exists(self):
        self.assertTrue(io_wrapper.dir_exists('.'))

    # assure we properly translate string-formatted permissions
    # to octal and understand how to use foreign code
    #
    # assume the environment doesn't have a file named as TEST_FILE_NAME
    def test_file_has_permissions(self):
        with open(self.TEST_FILE_NAME, 'w') as _:
            pass
        os.chmod(self.TEST_FILE_NAME, 0o300)
        with self.assertRaises(io_wrapper.PermissionsFormatError):
            io_wrapper.file_has_permissions(self.TEST_FILE_NAME, 'xwr')
        self.assertTrue(io_wrapper.file_has_permissions(
            self.TEST_FILE_NAME, '-wx'))
        self.assertTrue(io_wrapper.file_has_permissions(
            self.TEST_FILE_NAME, '_w_'))

    # assure we delete any existing file/directory with target name
    # assure we create new directory with proper permissions
    #
    # assume the environment doesn't have a file named as TEST_DIR_NAME
    def test_create_dir(self):
        with open(self.TEST_DIR_NAME, 'w') as _:
            pass
        io_wrapper.create_dir(self.TEST_DIR_NAME, 0o700)
        with open(f'{self.TEST_DIR_NAME}/{self.TEST_FILE_NAME}', 'w') as _:
            pass
        self.assertTrue(os.access(self.TEST_DIR_NAME, os.R_OK))
        self.assertTrue(os.access(self.TEST_DIR_NAME, os.W_OK))
        self.assertTrue(os.access(self.TEST_DIR_NAME, os.X_OK))
        io_wrapper.create_dir(self.TEST_DIR_NAME)
        self.assertEqual(0, len(os.listdir(self.TEST_DIR_NAME)))
