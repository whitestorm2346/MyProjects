'''
淡江大學自動選課程式

使用方式：
    。 將預加選之課程的"開課序號"逐一列在 classID.txt 裡
    。 執行 AutoClassChoosing.exe
    。 根據程式的指示輸入正確的學號、密碼以及選課的起始時間
    。 等待程式於指定時間自動登入進行選課
    。 程式執行完畢後，將會把選課資訊整理(成功或失敗)在 result.txt 裡

設計者： 資工二A 游昃勛
專案版本： 1.0
專案完成日期： 2022/08/07


'''

from datetime import datetime
from functools import reduce
from logging import root
from time import sleep
from tkinter import *
from turtle import title
from selenium import webdriver  # for operating the website
from selenium.webdriver.common.by import By
import ddddocr  # for detecting the confirm code
import base64   # for reading the image present in base 64

LOGIN_URL = 'https://www.ais.tku.edu.tw/EleCos/login.aspx'
TARGET_URL = 'https://www.ais.tku.edu.tw/EleCos/action.aspx'

RESULT_FILE = 'result.txt'
CLASS_ID_FILE = 'classID.txt'

LOGIN_FAIL = "E999 淡江大學個人化入口網帳密驗證失敗或驗證伺服器忙碌中, 請重新輸入或請參考密碼說明..."
CONFIRM_FAIL = "請輸入學號、密碼及驗證碼...(「淡江大學單一登入(SSO)」單一帳密驗證密碼)\n" \
               "※105學年度入學新生(含轉學生)起，預設為西元生日(西元年/月/日)後6碼，" \
               "例如西元生日為1997/01/05，則後6碼為970105※\nE903 驗證碼輸入錯誤,請重新輸入 !!!"
WRONG_TIME = "E999 登入失敗(非帳號密碼錯誤) ???\nE051 目前不是您的選課開放時間"

ADD_SUCCESS = " I000 加選成功!!!"
ADD_FAIL = " E999 加選失敗???"


class AutoClassChoosing:
    def __init__(self, student_num='', password='', starting_time='', expiry_time='', driver=None) -> None:
        self.student_num = student_num
        self.password = password
        self.starting_time = starting_time
        self.expiry_time = expiry_time
        self.driver = driver

    def run(self) -> int:
        # get user's student number and password
        self.student_num = input('請輸入學號：')
        self.password = input('請輸入密碼：')
        self.starting_time = input('請輸入選課起始時間(例如： 2022/08/07 12:30): ')

        self.starting_time = datetime.strptime(
            self.starting_time, '%Y/%m/%d %H:%M')

        print('基本設定完成，將於指定時間自動登入選課')

        while not self.clock_on_time():
            sleep(1)

        edge_options = webdriver.EdgeOptions()
        edge_options.add_argument('--log-level=3')

        self.driver = webdriver.Edge(
            options=edge_options,
            executable_path='msedgedriver.exe',
            service_log_path='NUL'
        )

        while True:
            login_status = self.login()

            if login_status == 0:  # login success
                print('登入成功!!')
                break
            elif login_status == 1:  # wrong password or wrong student number
                print('學號或密碼錯誤!')
                self.student_num = input('請輸入學號： ')
                self.password = input('請輸入密碼： ')
            elif login_status == 2:  # wrong confirm code
                print('驗證碼錯誤，程式將重新判讀一次')
            elif login_status == 3:  # wrong login time
                self.starting_time = input(
                    '非登入時間，請輸入正確的選課起始時間(例如： 2022/08/07 12:30): ')
            else:  # other situations
                print('登入錯誤，程式將中斷執行')
                exit(1)

        class_choosing_status = self.choose_classes()

        if class_choosing_status == 0:  # class choosing successfully
            print('完成自動選課，詳細結果紀錄於 result.txt')
        else:
            print('選課錯誤，程式將中斷執行')
            exit(1)

        return 0

    def clock_on_time(self) -> bool:
        curr_time = datetime.now()
        is_expired = curr_time >= self.starting_time

        return is_expired

    def login(self) -> int:
        self.driver.get(LOGIN_URL)

        try:
            # student number input
            student_num_input = self.driver.find_element(
                By.XPATH, '//*[@id="txtStuNo"]')
            student_num_input.clear()
            student_num_input.send_keys(self.student_num)

            # password input
            password_input = self.driver.find_element(
                By.XPATH, '//*[@id="txtPSWD"]')
            password_input.clear()
            password_input.send_keys(self.password)

            # confirm code input
            confirm_code_input = self.driver.find_element(
                By.XPATH, '//*[@id="txtCONFM"]')
        except Exception as e:
            print('網頁HTML錯誤')

            return 4

        confirm_code_input.clear()
        confirm_code_input.send_keys(self.auto_detect_confirm_code())

        login_btn = self.driver.find_element(By.XPATH, '//*[@id="btnLogin"]')
        login_btn.click()

        if self.driver.current_url == TARGET_URL:
            return 0
        else:
            msg = self.driver.find_element(
                By.XPATH, '//*[@id="form1"]/div[3]/table/tbody/tr[6]/td[2]')

            if msg.text == LOGIN_FAIL:
                return 1
            elif msg.text == CONFIRM_FAIL:
                return 2
            elif WRONG_TIME in msg.text:
                return 3
            else:
                return 4

    def auto_detect_confirm_code(self) -> str:
        # get the image(base64) using javascript
        captchaBase64 = self.driver.execute_async_script(
            """
            let canvas = document.createElement('canvas');
            let context = canvas.getContext('2d');
            let img = document.querySelector('#imgCONFM');

            canvas.height = img.naturalHeight;
            canvas.width = img.naturalWidth;

            context.drawImage(img, 0, 0);

            callback = arguments[arguments.length - 1];
            callback(canvas.toDataURL());
            """
        )

        # decode image(base64) to confirm code
        img = base64.b64decode(captchaBase64.split(',')[1])
        ocr = ddddocr.DdddOcr()
        confirm_code = ocr.classification(img)

        return confirm_code

    def choose_classes(self) -> int:
        with open('result.txt', 'w') as result_file:
            with open('classID.txt', 'r') as class_id_file:
                for id in class_id_file:
                    line = '開課序號：' + id + ' '

                    # class id input
                    class_id_input = self.driver.find_element(
                        By.XPATH, '//*[@id="txtCosEleSeq"]')
                    class_id_input.clear()
                    class_id_input.send_keys(id)

                    # add button click
                    add_btn = self.driver.find_element(
                        By.XPATH, '//*[@id="btnAdd"]')
                    add_btn.click()

                    msg = self.driver.find_element(
                        By.XPATH, '//*[@id="form1"]/div[3]/table/tbody/tr[2]/td[3]/font')

                    msg_in_line = msg.text.split('\n')

                    print(msg.text)

                    if msg_in_line[0] == ADD_SUCCESS:
                        line += msg_in_line[0].split(' ')[1]
                    elif msg_in_line[0] == ADD_FAIL:
                        line += msg_in_line[0].split(' ')[1]
                        line += msg_in_line[1]
                    else:
                        return 1

                    result_file.write(line + '\n')

        return 0


class ClassID:
    def __init__(self, frame) -> None:
        self.label = Label(frame)
        self.entry = Entry(frame)
        self.text = StringVar()

    def set_label(self, index) -> None:
        num = str(index)

        if index < 10:
            num = '0' + num

        self.label.config(
            text='開課序號 ' + num,
            font=('微軟正黑體', 12)
        )

    def set_entry(self) -> None:
        self.entry.config(
            textvariable=self.text,
            bg='lightyellow',
            font=('TimeNewRomans', 15, 'bold'),
            width=20
        )


def refresh_window() -> None:
    entries_frame.configure(height=frame_height)

    for i in range(0, len(class_id_entries)):
        class_id_entries[i].label.grid(row=i, column=0)
        class_id_entries[i].entry.grid(row=i, column=1)


def add_entry() -> None:
    global class_id_entries, entries_frame, frame_height

    class_id_entries.append(ClassID(frame=entries_frame))
    class_id_entries[-1].set_label(len(class_id_entries))
    class_id_entries[-1].set_entry()

    frame_height += 30

    refresh_window()


def reduce_entry() -> None:
    global class_id_entries, frame_height

    if len(class_id_entries) > 1:
        class_id_entries[-1].label.destroy()
        class_id_entries[-1].entry.destroy()
        class_id_entries.pop()

        frame_height -= 30

        refresh_window()


# root window create
root_window = Tk()
root_window.title('AutoClassChoosing')
root_window.geometry('900x600')
root_window.resizable(0, 0)


# header part
title_ = Label(
    root_window,
    text='Auto Class Choosing',
    font=('TimeNewRomans', 24, 'bold')
)
title_.place(x=69, y=51)

subtitle = Label(
    root_window,
    text='自動選課應用程式',
    font=('微軟正黑體', 12),
    fg='#868686'
)
subtitle.place(x=87, y=92)


# account entries part
student_num_label = Label(
    root_window,
    text='學號：',
    font=('微軟正黑體', 13)
)
student_num_label.place(x=87, y=150)

student_num_entry = Entry(
    root_window,
    bg='lightyellow',
    font=('TimeNewRomans', 15, 'bold')
)
student_num_entry.place(x=153, y=150)

password_label = Label(
    root_window,
    text='密碼：',
    font=13
)
password_label.place(x=87, y=190)

password_entry = Entry(
    root_window,
    bg='lightyellow',
    font=('TimeNewRomans', 15, 'bold')
)
password_entry.place(x=153, y=190)


# datetime setting part
datetime_label = Label(
    root_window,
    text='Starting Time Setting',
    font=('TimeNewRomans', 20, 'bold')
)
datetime_label.place(x=69, y=270)

datetime_sub_label = Label(
    root_window,
    text='起始時間設定',
    font=('微軟正黑體', 12),
    fg='#868686'
)
datetime_sub_label.place(x=87, y=310)

datetime_bg = Canvas(
    root_window,
    bg='#868686',
    width=300,
    height=200
)
datetime_bg.place(x=85, y=360)


# class ID list part
class_id_label = Label(
    root_window,
    text='Class ID List',
    font=('TimeNewRomans', 20, 'bold')
)
class_id_label.place(x=480, y=55)

class_id_sub_label = Label(
    root_window,
    text='開課序號列表',
    font=('微軟正黑體', 12),
    fg='#868686'
)
class_id_sub_label.place(x=498, y=95)

class_id_border = LabelFrame(
    root_window,
    width=350,
    height=275
)
class_id_border.place(x=493, y=195)

add_entry_btn = Button(
    root_window,
    text='+',
    font=('TimeNewRomans', 12, 'bold'),
    width=3,
    height=1,
    command=add_entry
)
add_entry_btn.place(x=498, y=155)

reduce_entry_btn = Button(
    root_window,
    text='-',
    font=('TimeNewRomans', 12, 'bold'),
    width=3,
    height=1,
    command=reduce_entry
)
reduce_entry_btn.place(x=543, y=155)

entries_bg = Canvas(
    class_id_border,
    width=345,
    height=265
)
entries_bg.place(x=0, y=0)

frame_scrollbar = Scrollbar(
    class_id_border,
    orient='vertical',
    command=entries_bg.yview
)
frame_scrollbar.place(x=330, y=0, height=270)

entries_bg.configure(yscrollcommand=frame_scrollbar.set)
entries_bg.bind('<Configure>', lambda e: entries_bg.configure(
    scrollregion=entries_bg.bbox('all')))


def _on_mouse_wheel(event):
    entries_bg.yview_scroll(-1 * int((event.delta / 120)), "units")


entries_bg.bind_all("<MouseWheel>", _on_mouse_wheel)

entries_frame = Frame(
    entries_bg,
    width=345,
    height=265
)
entries_frame.place(x=0, y=0)

entries_bg.create_window((0, 0), window=entries_frame, anchor='nw')

class_id_entries = [ClassID(frame=entries_frame)]
frame_height = 30

class_id_entries[0].set_label(1)
class_id_entries[0].set_entry()


# footer part
start_btn = Button(
    root_window,
    text='start',
    font=('TimeNewRomans', 18, 'bold'),
    bg='lightyellow'
)
start_btn.place(x=540, y=480)

exit_btn = Button(
    root_window,
    text='exit',
    font=('TimeNewRomans', 18, 'bold'),
    bg='lightyellow',
    command=root_window.destroy
)
exit_btn.place(x=680, y=480)


refresh_window()
root_window.mainloop()

auto_class_choosing = AutoClassChoosing()
# exe_code = auto_class_choosing.run()
