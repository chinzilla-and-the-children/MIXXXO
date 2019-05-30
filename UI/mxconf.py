import os, tkinter
from tkinter import font, filedialog

mainblue = "#155c7b"
white = "#fff"

class mixxxo:
    def __init__(self):
        self.window = tkinter.Tk()
        self.window.title("mixxxo")
        self.window.geometry("640x400+300+150")
        self.window.resizable(False, False)
        self.window.configure(background = white)
        self.titleFont = tkinter.font.Font(family = "ChopinScript", size = 20)
        self.font = tkinter.font.Font(family = "나눔스퀘어", size = 12)

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
            width = 15,
            repeatdelay = 1000,
            repeatinterval = 100,
            bd = 0,
            fg = white,
            bg = mainblue,
            font = self.font
        )

        self.titleLabel.pack(pady = 50)
        self.button.pack()

        self.window.mainloop()

    def openFile(self):
        self.window.dirname = filedialog.askdirectory()
        if(self.window.dirname):
            self.pathLabel = tkinter.Label(
                self.window,
                text = self.window.dirname,
                bg = white,
                font = self.font
            )
            self.pathLabel.pack()
            self.button.destroy()

    def fileList(self, path):
        file_list = os.listdir(path)
        file_list.sort()
        print(file_list)