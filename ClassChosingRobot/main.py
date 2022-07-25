from pip import main
from selenium import webdriver
from time import sleep
import pickle  # for save and get cookie
import os

login_url = 'https://www.ais.tku.edu.tw/EleCos/login.aspx?ReturnUrl=%2Felecos%2F'
tku_class_url = ''
target_url = ''


class ClassChoosing:
    def __init__(self) -> None:
        self.status = 0
        self.login_method = 1
        self.driver = webdriver.Edge(executable_path='edgedriver.exe')

    def set_cookie(self) -> None:
        self.driver.get(tku_class_url)

        print('Please login......')

        while self.driver.find('淡江大學網路選課系統') != -1:
            sleep(1)

        print('Login seccessfully......')
        pickle.dump(self.driver.get_cookies(), open(
            'cookies.pkl', 'wb'))  # saving cookies
        print('Cookies have saved......')

        self.driver.get(target_url)

    def get_cookie(self) -> None:
        cookies = pickle.load(open('cookies.pkl', 'rb'))

        for cookie in cookies:
            cookie_dict = {
                'domain': '.damian.cn',
                'name': cookie.get('name'),
                'value': cookie.get('value')
            }

            self.driver.add_cookie(cookie_dict)

        print('Cookies have loaded......')

    def login(self) -> None:
        if self.login_method == 0:
            self.driver.get(login_url)
            print('Start login......')
        elif self.login_method == 1:
            if os.path.exists('cookies.pkl'):
                self.driver.get(target_url)
                self.get_cookie()
            else:
                self.set_cookie()

    def enter_class_choosing(self) -> None:
        print('Open the browser......')

        self.login()
        self.driver.refresh()
        self.status = 2

        print('Login seccessfully......')


if __name__ == '__main__':
    class_choosing = ClassChoosing()
    class_choosing.enter_class_choosing()
