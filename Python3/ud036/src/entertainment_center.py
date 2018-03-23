from Python3.ud036.src import fresh_tomatoes

from Python3.ud036.src import media

# 视频链接必须是YouTube的，因为fresh_tomatoes代码里面的设计是只针对YouTube的
toy_story = media.Movie("玩具总动员", "A story of a boy and his toys that come to life",
                        "http://imgsrc.baidu.com/forum/w%3D580/sign=dd1286663a292df597c3ac1d8c305ce2/1c250bd162d9f2d31ed067a6a9ec8a136127cc83.jpg",
                        "https://www.youtube.com/watch?v=xMKrirZaPNw")
# print(toy_story.storyline)
# toy_story.show_trailer()
avatar = media.Movie("阿凡达", "A marine on an alien planet",
                     "http://www.uua.cn/uploadfile/2014/1104/20141104012230917.jpg",
                     "https://www.youtube.com/watch?v=xCjPMKU1pI8&list=PL194EFA9317B18289")
# print(avatar.storyline)
duckweed = media.Movie("乘风破浪", "讲述了不被父亲理解的赛车手阿浪意外经历一场奇妙冒险的故事",
                       "http://a.hiphotos.baidu.com/baike/s%3D500/sign=767a528c21381f309a198da999004c67/0b46f21fbe096b631e713ee405338744ebf8ac1e.jpg",
                       "https://www.youtube.com/watch?v=hPhrBqnHxBU")
initial_d = media.Movie("头文字D",
                        "影片讲述拓海代替父亲每天运送豆腐而无意中成长为一个“飘移”高手并打败了中里毅、须藤京一等赛车高手。而这时，拓海的恋爱出现了危机。最终拓海决定加入赛车队，开始一个真正赛车手的生活。",
                        "https://imgsa.baidu.com/baike/c0%3Dbaike180%2C5%2C5%2C180%2C60/sign=f8038dcbb5de9c82b268f1dd0de8eb6f/c9fcc3cec3fdfc03f81e8a4ad23f8794a5c226d9.jpg",
                        "https://www.youtube.com/watch?v=QM8hYVfMzww")
tiny_times = media.Movie("小时代",
                         "该片根据郭敬明同名小说《小时代》改编，影片以上海为背景，讲述四个从小感情深厚、有着不同价值观和人生观的女生，经历了友情、爱情、亲情的巨大转变。在一个宿舍朝夕相处的四个女生，开始找工作实习的忙碌生活，面对巨大压力，在看似平静的校园相继发生着让她们措手不及的故事。",
                         "https://imgsa.baidu.com/baike/c0%3Dbaike220%2C5%2C5%2C220%2C73/sign=015bdded64d0f703f2bf9d8e69933a58/1b4c510fd9f9d72aeb119be7d22a2834359bbbd7.jpg",
                         "https://www.youtube.com/watch?v=ine6LhdCm0I")
sherlock = media.Movie("神探夏洛克",
                       "该剧改编自阿瑟·柯南·道尔创作的侦探小说《福尔摩斯探案集》，将原著的时间背景从19世纪搬到了21世纪，讲述在繁华热闹的伦敦大都市中，时尚的大侦探夏洛克·福尔摩斯和他的朋友约翰·H·华生经受的一系列危险的、不同寻常的历险。",
                       "https://imgsa.baidu.com/baike/c0%3Dbaike220%2C5%2C5%2C220%2C73/sign=11979261b0de9c82b268f1dd0de8eb6f/738b4710b912c8fc40018095ff039245d78821f3.jpg",
                       "https://www.youtube.com/watch?v=0Dr99aKk8pA")

movies = [toy_story, avatar, duckweed, initial_d, tiny_times, sherlock]
fresh_tomatoes.open_movies_page(movies)

print(media.Movie.VALID_RATINGS)
