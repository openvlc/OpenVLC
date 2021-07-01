import os
import subprocess
from sys import platform

def check_modules():
    """
    Checks if the required modules are installed and if not, installs them via pip
    :return: none
    """
    # Modules list
    modules = ("tkinter", "netmiko", "pxssh")
    for m in modules:
        try:
            __import__(m)
        except ModuleNotFoundError:
            os.system("pip3 install " + m)

def check_cmds():
    """
    Checks if the required commands to run are installed and if not, installs them via pip
    :return: none
    """
    # Command list
    cmds = ('ssh', 'xterm')
    for c in cmds:
        if subprocess.check_output(['command -v ', c], shell=True) == 'b''':
            if platform == 'linux':
                os.system('sudo apt install ' + c)


# Check and install required modules
check_modules()
check_cmds()
