#import nwchemex as nwx
import simde
import pluginplay
import ghostfragment
import unittest

def TestCapping(unittest.TestCase):
    def setUp(self):
        mm = pluginplay.ModuleManager()
        ghostfragment.load_modules(mm)
        # nwx.load_modules()
