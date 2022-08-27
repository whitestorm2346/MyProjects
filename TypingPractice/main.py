from tkinter import *

DICTIONARY = 'dictionary.txt'
words = []

if __name__ == "__main__":
    root_window = Tk()

    root_window.title('Typing Practice')
    root_window.geometry('600x400')

    with open(DICTIONARY, 'r') as f:
        for line in f:
            words.append(line.split('\n'))

    label = Label(
        text='text',
        width=20,
        height=3,
        font=('Times New Roman', 48, 'bold')
    )
    entry = Entry(
        width=20,
        font=('Times New Roman', 42)
    )

    label.pack(side='top')
    entry.pack(side='top')

    root_window.mainloop()
