import os, tkinter
from tkinter import font, filedialog, messagebox
import ctypes as c

'''dll1 = c.WinDLL('./File_load_all.dll')
File_load_all = dll1['File_load_all']
File_load_all.argtypes = [c.c_char_p]
File_load_all.restype = c.c_void_p'''

dll2 = c.WinDLL('./Dll1.dll')
aes_decrypt = dll2['aes_decrypt']
aes_decrypt.argtypes = [c.c_char_p]
aes_decrypt.restype = c.c_int

mainblue = "#155c7b"
white = "#fff"

class mixxxo:
    # ========== Start of __init__(self) ========== #
    def __init__(self):
        # --- Windows Settings --- #
        self.window = tkinter.Tk()
        self.window.title("mixxxo")
        self.window.geometry("640x400+300+150")
        self.window.resizable(False, False)
        self.window.configure(background = white)
        self.titleFont = tkinter.font.Font(family = "ChopinScript", size = 20)
        self.font = tkinter.font.Font(family = "나눔스퀘어", size = 10)

        # --- Main Window Objects --- #
        self.titleLabel = tkinter.Label(
            self.window,
            text = "mixxxo",
            fg = mainblue,
            bg = white,
            font = self.titleFont
        )

        self.button = tkinter.Button(
            self.window,
            text = "폴더 열기",
            command = self.openFile,
            relief = "groove",
            overrelief = "groove",
            width = 10,
            repeatdelay = 1000,
            repeatinterval = 100,
            bd = 0,
            fg = white,
            bg = mainblue,
            font = self.font
        )

        self.titleLabel.pack(pady = 50)
        self.button.pack()

        self.window.mainloop()      # Window Execute
    # ========== End of __init__(self) ========== #

    # --- Required Functions --- #
    def openFile(self):
        self.window.dirname = filedialog.askdirectory()
        if(self.window.dirname):
            '''self.files = tkinter.Listbox(
                self.window,
                selectmode = 'extended',
                height = 0,
                font = self.font
            )'''
            
            tkinter.messagebox.showinfo("filepath", self.window.dirname)