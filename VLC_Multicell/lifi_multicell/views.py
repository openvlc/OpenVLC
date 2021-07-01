import tkinter as tk
from tkinter import ttk
from tkinter import messagebox

from lifi_multicell.constants import *
import lifi_multicell.widgets as w
from lifi_multicell.controller import Controller


class MainView(tk.Frame):

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.c = Controller()

        # Interactions
        self.id_text = tk.StringVar()
        self.id_text.set("1")
        self.id_label = w.DeviceIdFrame(self, textvariable=self.id_text, font=("TkDefaultFont", 10), width=3, anchor=tk.CENTER)
        self.id_label.grid(row=2, column=0, sticky=tk.E)

        self.on_button = ttk.Button(self, text="ON", command=lambda state="ON": self.on_device(state), width=8)
        self.on_button.grid(row=2, column=1, sticky=tk.E)

        self.off_button = ttk.Button(self, text="OFF", command=lambda state="OFF": self.off_device(state), width=8)
        self.off_button.grid(row=2, column=2, sticky=tk.E)

        self.ssh_button = ttk.Button(self, text="SSH", command=lambda state="SSH": self.ssh_device(state), width=8)
        self.ssh_button.grid(row=2, column=3, sticky=tk.E)

        # Devices board representation
        self.board = w.DeviceBoard()
        self.board.grid(row=0, columnspan=4, sticky=tk.E)
        self.board.bind("<Configure>", self.redraw)

    def redraw(self, event=None):
        """
        Draws the GUI showing the network state
        """

        self.board.delete("rect")
        cellwidth = int(self.board.winfo_width() / columns_dev)
        cellheight = int(self.board.winfo_height() / rows_dev)
        for column in range(columns_dev):
            for row in range(rows_dev):
                x1 = column * cellwidth
                y1 = row * cellheight
                x2 = x1 + cellwidth
                y2 = y1 + cellheight
                tile = self.board.create_rectangle(x1, y1, x2, y2, fill="red", tags="rect")
                self.board.tiles[row, column] = tile
                self.board.tag_bind(tile, "<1>", lambda event, row=row, column=column:
                self.clicked(row=row, column=column, ))
                tile_id = (str(row * columns_dev + column + 1))
                self.board.tiles_id[row, column] = tile_id
                self.board.create_text(x1 + 15, y1 + 15, fill="darkblue", font="Times 15 italic bold", text=tile_id)
        self.board.grid(row=1, sticky=tk.E)

    def clicked(self, row, column):
        tile_id = self.board.tiles_id[row, column]
        self.set_text_(dev_Id=tile_id)

    def set_text_(self, dev_Id=None):
        if self.id_label.existingDevice(dev_Id):
            self.id_text.set(dev_Id)

    def on_device(self, state):
        dev_id = int(self.id_text.get())
        self.c.turn_on_device(dev_id)
        self.switch_color(dev_id, state)

    def off_device(self, state):
        dev_id = int(self.id_text.get())
        turn_off = self.c.turn_off_device(dev_id)
        if turn_off == 1:
            messagebox.showwarning(ssh_warning_title, ssh_warning_msg)
        else:
            self.switch_color(dev_id, state)

    def ssh_device(self, state):
        dev_id = int(self.id_text.get())
        self.c.ssh_device(dev_id)
        self.switch_color(dev_id, state)

    def id_to_tile(self, dev_id):
        """
        Calculates the row and column for a selected device ID

        :return:  int tuple [row, column]
        """
        row = dev_id // columns_dev
        column = dev_id - row * columns_dev - 1
        return [row, column]

    def switch_color(self, dev_id, state):
        [row, column] = self.id_to_tile(dev_id)
        tile = self.board.tiles[row, column]
        self.board.itemconfigure(tile, fill=tile_color[state])


class SshWarning(tk.messagebox.Message):

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.showwarning(title=ssh_warning_title, message=ssh_warning_msg)
