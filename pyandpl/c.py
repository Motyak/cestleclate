#!/usr/bin/env python3

import sys # stdin
import math # floor()
from datetime import datetime

class utils:
    @staticmethod
    def parseArgs(userInput, sep=';'):
        return userInput.split(sep)

class today:
    @staticmethod
    def yday():
        return datetime.now().timetuple().tm_yday
    @staticmethod
    def year():
        return datetime.now().year

def yearProgress(yday=today.yday(), year=today.year()):
    isLeapYear = year % 4 == 0
    nbOfDaysInYear = 365 + 1 * int(isLeapYear)
    percentage = math.floor(yday / nbOfDaysInYear * 100)
    return f'{percentage}%'

def yearProgressFromStr(str=''):
    if not str:
        return yearProgress()
    args = utils.parseArgs(str)
    return yearProgress(*[int(a) for a in args])

userInput = sys.stdin.read()
res = yearProgressFromStr(userInput)
print(res, end='')
