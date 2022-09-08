from selenium import webdriver
from selenium.webdriver.common.by import By

edge_driver = webdriver.Chrome(executable_path='msedgedriver.exe')
edge_driver.get('https://popcat.click')

popcat = edge_driver.find_element(By.XPATH, '//*[@id="app"]/div')

while True:
    popcat.click()
