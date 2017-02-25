# 需要导入Python3之中的urllib下的request module
import urllib.request


def read_text():
    quotes = open("../resources/movie_quotes.txt")
    contents_of_file = quotes.read()
    print(contents_of_file)
    quotes.close()
    check_profanity(contents_of_file)


def check_profanity(text_to_check):
    # urllib.urlopen()在Python3之中没有了
    connection = urllib.request.urlopen("http://www.wdylike.appspot.com/?q=" + text_to_check)
    # connection = urllib.request.urlopen("http://python.org/")
    output = connection.read()
    print(output)
    connection.close()


read_text()
