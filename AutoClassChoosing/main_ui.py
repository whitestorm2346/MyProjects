from datetime import date
from tkinter import *
from tkinter import ttk
from auto_class_choosing import AutoClassChoosing

ENGLISH = 'Times New Roman'
CHINESE = '微軟正黑體'

root = Tk()
root.resizable(False, False)
root.geometry("500x700")
root.title('AutoClassChoosing Set-up')


### login part ###
login_frame = LabelFrame(root)
login_frame.config(text=' Login ', font=(ENGLISH, 12))
login_frame.pack(side=TOP, fill='x', padx=10, pady=10)

student_id_label = Label(login_frame)
student_id_label.config(text='Student ID', font=(ENGLISH, 14, 'bold'))
student_id_label.pack(side=TOP, pady=5)

student_id = StringVar(login_frame)
student_id_entry = Entry(login_frame)
student_id_entry.config(font=(ENGLISH, 12), textvariable=student_id)
student_id_entry.pack(side=TOP, fill='x', padx=5, pady=10)

password_label = Label(login_frame)
password_label.config(text='Password', font=(ENGLISH, 14, 'bold'))
password_label.pack(side=TOP, pady=5)

password = StringVar(login_frame)
password_entry = Entry(login_frame)
password_entry.config(font=(ENGLISH, 12), textvariable=password)
password_entry.pack(side=TOP, fill='x', padx=5, pady=10)


# datetime setting part
datetime_frame = LabelFrame(root)
datetime_frame.config(text=' Date-time Setting ', font=(ENGLISH, 12))
datetime_frame.pack(side=TOP, fill=X, padx=10, pady=10)

datetime_label = Label(datetime_frame)
datetime_label.config(text='YYYY/MM/DD hh:mm ',
                      font=(ENGLISH, 14, 'bold'))
datetime_label.pack(side=LEFT, padx=15, pady=10)

datetime_str = StringVar(datetime_frame)
datetime_entry = Entry(datetime_frame)
datetime_entry.config(font=(ENGLISH, 12), textvariable=datetime_str)
datetime_entry.pack(side=LEFT, padx=10, pady=10)


### class ID part ###
class_id_frame = LabelFrame(root)
class_id_frame.config(text=' Class ID Input ', font=(ENGLISH, 12))
class_id_frame.pack(side=TOP, fill='x', padx=10, pady=10)

inner_frame = Frame(class_id_frame)
inner_frame.pack(fill=BOTH, expand=True)

inner_canvas = Canvas(inner_frame)
inner_canvas.pack(side=LEFT, fill=BOTH, expand=True)

scrollbar = ttk.Scrollbar(inner_frame, orient=VERTICAL,
                          command=inner_canvas.yview)
scrollbar.pack(side=RIGHT, fill=Y)

inner_canvas.configure(yscrollcommand=scrollbar.set)
inner_canvas.bind('<Configure>', lambda e: inner_canvas.configure(
    scrollregion=inner_canvas.bbox('all')))

window_frame = Frame(inner_canvas)

inner_canvas.create_window((0, 0), window=window_frame, anchor='nw')


def scrollbar_resize(event):
    size = (window_frame.winfo_reqwidth(), window_frame.winfo_reqheight())
    inner_canvas.config(scrollregion="0 0 %s %s" % size)

    if window_frame.winfo_reqwidth() != inner_canvas.winfo_width():
        inner_canvas.config(width=window_frame.winfo_reqwidth())


window_frame.bind('<Configure>', scrollbar_resize)


class InputObject:
    def __init__(self, container) -> None:
        self.value = StringVar(container)
        self.label = Label(container)
        self.entry = Entry(container, textvariable=self.value)

    def set_label(self, text) -> None:
        self.label.config(text=text, font=(ENGLISH, 14))

    def set_entry(self) -> None:
        self.entry.config(font=(ENGLISH, 14))

    def place(self, index) -> None:
        self.label.grid(row=index, column=0, padx=15, pady=10)
        self.entry.grid(row=index, column=1, padx=10, pady=10)

    def destroy(self) -> None:
        self.entry.destroy()
        self.label.destroy()


entries = [InputObject(window_frame)]


def place_entries():
    global entries

    for i in range(0, len(entries)):
        entries[i].set_label('Class ID ' + str(i + 1))
        entries[i].place(i)


def add_btn_onclick():
    global entries, inner_canvas

    idx = len(entries)

    entries.append(InputObject(window_frame))
    entries[idx].set_label('Class ID ' + str(idx + 1))
    entries[idx].place(idx)


def del_btn_onclick():
    global entries, inner_canvas

    if len(entries) <= 1:
        return

    entries[-1].destroy()
    entries.pop()


def start_btn_onclick():
    global student_id, password, datetime_str, entries

    bot = AutoClassChoosing(
        student_num=student_id.get(),
        password=password.get(),
        starting_time=datetime_str.get()
    )

    bot.run()


add_btn = Button(root)
add_btn.config(text='add', font=(ENGLISH, 14, 'bold'),
               height=2, width=6, command=add_btn_onclick)
add_btn.pack(side=LEFT, padx=20)

del_btn = Button(root)
del_btn.config(text='del', font=(ENGLISH, 14, 'bold'),
               height=2, width=6, command=del_btn_onclick)
del_btn.pack(side=LEFT, padx=20)

start_btn = Button(root)
start_btn.config(text='start', font=(ENGLISH, 14, 'bold'),
                 height=2, width=8, command=start_btn_onclick)
start_btn.pack(side=LEFT, padx=20)

quit_btn = Button(root)
quit_btn.config(text='quit', font=(ENGLISH, 14, 'bold'),
                height=2, width=8, command=root.quit)
quit_btn.pack(side=LEFT, padx=20)

place_entries()
root.mainloop()
