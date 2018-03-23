import os


def rename_files():
    file_list = os.listdir("../resources/prank/")
    print(file_list)
    saved_path = os.getcwd()
    # print("The current working directory is "+saved_path)

    os.chdir("../resources/prank")
    for file_name in file_list:
        print("Old name--" + file_name)
        # str.maketrans()函数是个静态函数，注意参数问题，第三个参数是需要被替换成空的字符，前两个参数必须是空字符
        # Python3这个函数的定义与Python2不一样
        print("New name--" + file_name.translate(str.maketrans("", "", "0123456789")))
        os.rename(file_name, file_name.translate(str.maketrans("", "", "0123456789")))
    os.chdir(saved_path)


rename_files()
