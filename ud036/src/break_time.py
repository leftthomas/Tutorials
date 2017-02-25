import time
import webbrowser

total_breaks = 3
break_count = 0

print("this program started on " + time.ctime())
while break_count < total_breaks:
    time.sleep(10)
    # 打开周杰伦的《告白气球》MV
    webbrowser.open("https://v.qq.com/x/cover/wkfi7sdq44mto0i/u00222le4ox.html")
    break_count += 1
