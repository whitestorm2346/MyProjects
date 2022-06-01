class Book:
    def __init__(self, name, price, author) -> None:
        self.name = name
        self.price = price
        self.author = author


def getBookList(book_class) -> list:
    if book_class == '程式設計':
        return [Book('Python程式設計手冊', 520, '阿堂'),
                Book('Java聖經', 780, '美麗'),
                Book('C程式設計入門', 450, '小董')]
    elif book_class == '文學':
        return [Book('紅樓夢', 600, '曹雪芹'),
                Book('西遊記', 550, '吳承恩')]
    else:
        return []


programming = getBookList('程式設計')

for book in programming:
    print(book.name, end=' ')
    print(book.price, end=' ')
    print(book.author, end='\n\n')

literature = getBookList('文學')

for book in literature:
    print(book.name, end=' ')
    print(book.price, end=' ')
    print(book.author, end='\n\n')
