'''
CPE考試自動報名程式

使用方式：
    。 執行 signUp.exe
    。 根據程式的指示輸入正確的身分證字號、密碼以及報名的起始時間
    。 等待程式於指定時間自動登入進行報名
    。 程式執行完畢後，會將報名結果儲存在 result.txt 裡
    
設計者： 資工二A 游昃勛
專案版本： 1.0
專案完成日期： 2022/12/
'''

from datetime import datetime
from time import sleep
from selenium import webdriver  # for operating the website
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import Select  # for selecting dropdown menu
import ddddocr  # for detecting the confirm code
import base64   # for reading the image present in base 64

LOGIN_URL = 'https://cpe.cse.nsysu.edu.tw/cpe/'
TARGET_URL = 'https://cpe.cse.nsysu.edu.tw/cpe/newest'

RESULT_FILE = 'result.txt'

LOGIN_FAIL = [
    "密碼輸入錯誤",
    "身分證字號輸入錯誤",
    "身分證字號輸入錯誤密碼輸入錯誤"
]
CONFIRM_FAIL = "驗證碼輸入錯誤"
WRONG_TIME = "E999 登入失敗(非帳號密碼錯誤) ???\nE051 目前不是您的選課開放時間"

SIGN_UP_SUCCESS = "已報名"
SIGN_UP_FAIL = "報名失敗"


class CPEsignUp:
    def __init__(self, id='', password='', starting_time='', expiry_time='', driver=None) -> None:
        self.id = id
        self.password = password
        self.starting_time = starting_time
        self.expiry_time = expiry_time
        self.driver = driver

    def run(self, entries=-1) -> int:
        if entries == -1:
            # get user's student number and password
            self.id = input('請輸入身分證字號：')
            self.password = input('請輸入密碼：')
            self.starting_time = input('請輸入報名起始時間(例如： 2022/08/07 12:30): ')

        self.starting_time = datetime.strptime(
            self.starting_time, '%Y/%m/%d %H:%M')

        print('基本設定完成，將於指定時間自動登入報名')

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
                print('身分證字號或密碼錯誤!')
                self.id = input('請輸入身分證字號： ')
                self.password = input('請輸入密碼： ')
            elif login_status == 2:  # wrong confirm code
                print('驗證碼錯誤，程式將重新判讀一次')
            elif login_status == 3:  # wrong login time
                self.starting_time = input(
                    '非登入時間，請輸入正確的報名起始時間(例如： 2022/08/07 12:30): ')
            else:  # other situations
                print('登入錯誤，程式將中斷執行')
                exit(1)

        sign_up_status = self.sign_up()

        if sign_up_status == 0:  # class choosing successfully
            print('完成自動報名，詳細結果紀錄於 result.txt')
        else:
            print('報名錯誤，程式將中斷執行')
            exit(1)

        self.driver.close()

        return 0

    def clock_on_time(self) -> bool:
        curr_time = datetime.now()
        is_expired = curr_time >= self.starting_time

        return is_expired

    def login(self) -> int:
        self.driver.get(LOGIN_URL)

        try:
            # identity input
            check_box = self.driver.find_element(
                By.XPATH, '//*[@id="student"]')
            check_box.click()

            # student number input
            id_input = self.driver.find_element(
                By.XPATH, '//*[@id="inputID"]')
            id_input.clear()
            id_input.send_keys(self.id)

            # password input
            password_input = self.driver.find_element(
                By.XPATH, '/html/body/div/form/div[3]/div/input')
            password_input.clear()
            password_input.send_keys(self.password)

            # confirm code input
            confirm_code_input = self.driver.find_element(
                By.XPATH, '/html/body/div/form/div[4]/div/input')
        except Exception as e:
            print('網頁HTML錯誤')

            return 4

        confirm_code_input.clear()
        confirm_code_input.send_keys(self.auto_detect_confirm_code())

        login_btn = self.driver.find_element(
            By.XPATH, '/html/body/div/form/div[5]/div/input')
        login_btn.click()

        if self.driver.current_url == TARGET_URL:
            return 0
        else:
            account_msg = self.driver.find_element(
                By.XPATH, '/html/body/div/form/div[2]/div/span')
            confirm_code_msg = self.driver.find_element(
                By.XPATH, '/html/body/div/form/div[4]/div/span')

            if account_msg.text in LOGIN_FAIL:
                return 1
            elif confirm_code_msg.text == CONFIRM_FAIL:
                return 2
            elif WRONG_TIME in account_msg.text:
                return 3
            else:
                return 4

    def auto_detect_confirm_code(self) -> str:
        # get the image(base64) using javascript
        captchaBase64 = self.driver.execute_async_script(
            """
            let canvas = document.createElement('canvas');
            let context = canvas.getContext('2d');
            let img = document.querySelector('#new_captcha > img')
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

    def sign_up(self) -> int:
        with open('result.txt', 'w') as result_file:
            line = ''

            # classroom choosing
            select = Select(self.driver.find_element(
                By.XPATH, '/html/body/div/form/table[3]/tbody/tr[2]/td[2]/center/select'))

            for option in select.options:
                if '淡江大學' in option.text:
                    select.select_by_value(option.get_attribute("value"))

            # sign-up button click
            sign_up_btn = self.driver.find_element(
                By.XPATH, '/html/body/div/form/table[3]/tbody/tr[2]/td[3]/center/input')
            sign_up_btn.click()

            msg = self.driver.find_element(
                By.XPATH, '/html/body/div/div[2]')

            if (SIGN_UP_SUCCESS in msg.text) or (SIGN_UP_FAIL in msg.text):
                line += msg.text
            else:
                line += "ERROR"

            result_file.write(line + '\n')

        return 0


if __name__ == "__main__":
    sign_up = CPEsignUp()

    sign_up.run()
