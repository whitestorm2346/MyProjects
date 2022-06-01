city_rainfall = {}


def record_rainfall() -> str:
    global city_rainfall

    city = input('請輸入城市: ')

    if city != '':
        rainfall = input('輸入雨量(mm): ')

        if rainfall == '':
            rainfall = 0.0
        else:
            rainfall = float(rainfall)

        if city in city_rainfall:
            city_rainfall[city] += rainfall
        else:
            city_rainfall[city] = rainfall

    return city


while True:
    city = record_rainfall()

    if city == '':
        break

print('====output===================')

for city in city_rainfall:
    print(city + ' : ', end='')
    print('%5.2f' % city_rainfall[city])
