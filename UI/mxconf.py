import os, tkinter, sys
from tkinter import font, filedialog, messagebox
import ctypes as c

mainblue = "#155c7b"
white = "#fff"
black = "#001"

dll2 = c.WinDLL('./dec_pro.dll')
File_load_all = dll2['File_load_all']
File_load_all.argtypes = [c.c_char_p]
File_load_all.restype = c.c_int

class mixxxo:
    # ========== Start of __init__(self) ========== #
    def __init__(self):
        # --- Windows Settings --- #
        self.window = tkinter.Tk()
        self.window.title("MIXXXO - Jigsaw Ransomware Decryptor")
        self.window.geometry("640x400+300+150")
        self.window.resizable(False, False)
        self.window.configure(background = black)
        self.font = tkinter.font.Font(family = "맑은 고딕", size = 10)
        self.titleimg = tkinter.PhotoImage(file = "img/title.png")
        self.mg1img = tkinter.PhotoImage(file = "img/mg1.png")

        # --- Main Window Objects --- #
        self.titleLabel = tkinter.Label(
            self.window,
            image = self.titleimg,
            bg = black,
        )

        self.mg1 = tkinter.Label(
            self.window,
            image = self.mg1img,
            bg = black,
        )

        self.button = tkinter.Button(
            self.window,
            text = "폴더 열기",
            command = self.openFile,
            width = 10,
            repeatdelay = 1000,
            repeatinterval = 100,
            bd = 0,
            fg = white,
            bg = mainblue,
            font = self.font
        )

        self.titleLabel.pack()
        self.mg1.pack(pady = 10)
        self.button.pack()

        self.window.mainloop()      # Window Execute
    # ========== End of __init__(self) ========== #

    # --- Required Functions --- #
    def openFile(self):
        self.window.dirname = filedialog.askdirectory()
        if(self.window.dirname):
            tkinter.messagebox.showinfo("filepath", self.window.dirname)
            self.window.dirname = self.window.dirname.replace("/","\\")
            path = c.c_char_p(self.window.dirname.encode(), encoding='utf-8')
            File_load_all(path)
            self.window.destroy()
            os.execl(sys.executable, "python", "./aesDec.py", *sys.argv)