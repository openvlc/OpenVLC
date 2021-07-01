import tkinter as tk

from lifi_multicell.constants import *
from lifi_multicell.views import MainView

class Application(tk.Tk):

    def __init__(self, *args, **kwargs):

        super().__init__(*args, **kwargs)
        self.title(window_title)
        self.view = MainView()
        self.view.grid(row=0)

