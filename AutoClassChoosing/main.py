'''
Step 1. Input student number
Step 2. Input password
Step 3. Input confirm code
Step 4. Input class id
'''

from pip import main
from selenium import webdriver  # for operating the website
from selenium.webdriver.common.by import By

LOGIN_URL = 'https://www.ais.tku.edu.tw/EleCos/login.aspx'
TARGET_URL = 'https://www.ais.tku.edu.tw/EleCos/action.aspx'

RESULT_FILE = 'result.txt'
CLASS_ID_FILE = 'classID.txt'


class AutoClassChoosing:
    def __init__(self) -> None:
        self.student_num = ''
        self.password = ''
        self.driver = webdriver.Edge(executable_path='msedgedriver.exe')

    def run(self) -> int:
        # get user's student number and password
        self.student_num = input('請輸入學號：')
        self.password = input('請輸入密碼：')

        while True:
            login_status = self.login()

            if login_status == 0:  # login success
                print('登入成功!!')
                break
            elif login_status == 1:  # wrong password
                self.password = input('密碼錯誤，請重新輸入密碼： ')
            elif login_status == 2:  # student id problems
                self.student_num = input('學號格式有誤或不存在，請重新輸入學號： ')
            else:  # other situations
                print('登入錯誤，程式將中斷執行')
                exit(1)

        class_choosing_status = self.choose_classes()

        if class_choosing_status == 0:  # class choosing successfully
            pass
        else:
            pass

        return 0

    def login(self) -> int:
        self.driver.get(LOGIN_URL)

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

        confirm_code_input.clear()
        confirm_code_input.send_keys(self.auto_detect_confirm_code())

        if self.driver.current_url == TARGET_URL:
            return 0
        else:
            return 3

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

                    line += msg

                    if msg:  # if the program failed to choose class
                        pass

                    result_file.write(line + '\n')

        return 0

    def auto_detect_confirm_code(self) -> str:
        confirm_code = ''

        new_confirm_code_btn = self.driver.find_element(
            By.XPATH, '//*[@id="bn_new_confirm"]')
        new_confirm_code_btn.click()

        # detecting the code

        return confirm_code


if __name__ == '__main__':
    auto_class_choosing = AutoClassChoosing()
    exe_code = auto_class_choosing.run()
