# -------关联C++库---------------
import ControlPanel
import ctypes
import platform
system = platform.system()
if system == "Windows":
    pre = "./"
    suff = ".dll"
else:
    pre = "../lib/lib"
    suff = ".so"

libfile = ctypes.cdll.LoadLibrary
filename = pre+"MainWidgets"+suff

lib = libfile(filename)

# ---------------------------------

# -------定义函数------------------


def viewCounter(caseId, variable):
    variable = bytes(variable, encoding='utf-8')
    lib.viewCounter(caseId, variable)
    ControlPanel.updatePostTree(caseId)
    pass


def viewVector(caseId, variable):
    variable = bytes(variable, encoding='utf-8')
    lib.viewVector(caseId, variable)
    ControlPanel.updatePostTree(caseId)
    pass
