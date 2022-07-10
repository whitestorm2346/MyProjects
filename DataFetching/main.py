import os
import urllib.request as req
import bs4
from openpyxl import Workbook, load_workbook
from openpyxl.utils import get_column_letter
from openpyxl.styles import Font

class TravelAgencyInfo:
    def __init__(self, title, class_, phone, address, member, insurance_info):
        self.title = title
        self.class_ = class_
        self.phone = phone
        self.address = address
        self.member = member
        self.insurance_info = insurance_info

try:
    wb = load_workbook('綜合旅行社.xlsx')
except Exception:
    wb = Workbook()
    file_path = os.path.dirname(os.path.abspath(__file__))
    base_path = os.path.join(file_path, '綜合旅行社.xlsx')

    wb.save(base_path)

    wb = load_workbook('綜合旅行社.xlsx')

travel_agency_list = list()
page_count = 1

while True:
    url = f'https://admin.taiwan.net.tw/TravelIndustryList.aspx?Pindex={page_count}&SIKEY=%E7%B6%9C%E5%90%88'
    request = req.Request(url, headers={
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.124 Safari/537.36 Edg/102.0.1245.41"
    })

    with req.urlopen(request) as response:
        code = response.read().decode('utf-8')
        root = bs4.BeautifulSoup(code, "html.parser")

        travel_agency = root.find_all("div", class_="travel_item")

        for ta in travel_agency:
            travel_data = ta.find("div", class_="travel_data")
            travel_data_list = travel_data.find_all("dd")

            travel_agency_list.append(TravelAgencyInfo(
                title=ta.h4.string,
                class_=travel_data_list[0].string,
                phone=travel_data_list[1].string,
                address=travel_data_list[2].string,
                member=travel_data_list[3].string,
                insurance_info=travel_data_list[4].string
            ))

            print('title: {0}'.format(ta.h4.string))
            print('class: {0}'.format(travel_data_list[0].string))
            print('phone: {0}'.format(travel_data_list[1].string))
            print('address: {0}'.format(travel_data_list[2].string))
            print('member: {0}'.format(travel_data_list[3].string))
            print('insurance info: {0}'.format(travel_data_list[4].string), end='\n\n')

    if travel_agency == []:
        break

    page_count += 1

for sheet in wb.sheetnames:
    wb.remove(wb[sheet])

wb.create_sheet(title='工作表1')
ws = wb.active

ws.append([
    '旅行社',
    '公司類別',
    '電話',
    '地址',
    '品保會員',
    '保險資料'
])

for col in range(1, 7):
    ws[get_column_letter(col) + '1'].font = Font(bold=True)

for ta in travel_agency_list:
    ws.append([
        ta.title,
        ta.class_,
        ta.phone,
        ta.address,
        ta.member,
        ta.insurance_info
    ])

wb.save('綜合旅行社.xlsx')



