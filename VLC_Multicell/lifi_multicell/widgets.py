import tkinter as tk
from tkinter import ttk
from lifi_multicell.constants import *


class DeviceBoard(tk.Canvas):

    def __init__(self, **kwargs):
        super().__init__(width=width_board, height=height_board, borderwidth=0, highlightthickness=0, **kwargs)
        self.tiles = {}
        self.tiles_id = {}

class DeviceIdFrame(ttk.Label):

    def __init__(self,  *args, **kwargs):
        super().__init__(*args, **kwargs)

    def existingDevice(self, dev_Id=None):
        if dev_Id in devices_ip: return True
        else: return False



