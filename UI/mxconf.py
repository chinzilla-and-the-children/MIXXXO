import os, tkinter, sys
from tkinter import font, filedialog, messagebox
import ctypes as c
from aesDec import aesDec

blue = "#30a9de"
black = "#090707"
white = "#fff"

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
        self.window.resizable(True, True)
        self.window.configure(background = black)
        self.window.iconbitmap(default = "img/icon.ico")

        self.font = tkinter.font.Font(family = "맑은 고딕", size = 10)
        self.titleimg = tkinter.PhotoImage(file = "img/title.png")
        self.mg1img = tkinter.PhotoImage(file = "img/mg1.png")
        self.infoimg = tkinter.PhotoImage(file = "img/info.png")

        # --- Main Window Objects --- #
        self.titleLabel = tkinter.Label(
            self.window,
            image = self.titleimg,
            bg = black,
        )

        self.mg1 = tkinter.Label(
            self.window,
            image = self.mg1img,
            bg = black
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
            bg = blue,
            font = self.font
        )

        self.info = tkinter.Label (
            self.window,
            image = self.infoimg,
            bg = black
        )

        # --- Pack Window Objects --- #
        self.titleLabel.pack()
        self.mg1.pack(pady = 10)
        self.button.pack(pady = 10)
        self.info.pack()

        self.window.mainloop()      # Window Execute
    # ========== End of __init__(self) ========== #

    # --- Required Functions --- #
    def openFile(self):
        self.window.dirname = filedialog.askdirectory()
        if(self.window.dirname):
            msg = "폴더 경로 : " + self.window.dirname + "\n\n선택하신 경로에 대한 암호화 파일 목록 수집을 완료했습니다."
            tkinter.messagebox.showinfo("filepath", msg)
            self.window.dirname = self.window.dirname.replace("/","\\")
            path = c.c_char_p(self.window.dirname.encode(), encoding='utf-8')
            File_load_all(path)
            self.window.destroy()
            aesDec()