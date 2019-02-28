# a simple parser for python. use get_number() and get_word() to read
def parser():
    while 1:
        data = list(input().split(' '))
        for number in data:
            if len(number) > 0:
                yield(number)

input_parser = parser()

def get_word():
    global input_parser
    return next(input_parser)

def get_number():
    data = get_word()
    try:
        return int(data)
    except ValueError:
        return float(data)

class photo:
    def __init__(self, ori, num, tags):
        self.ori = ori
        self.num = num
        self.tags = tags

N = get_number()
h = []
photos = []
v = []
for i in range(N):
    ori = get_word()
    num = get_number()
    tags = []
    for _ in range(num):
        tags.append(get_word())
    photos.append(photo(ori, num, tags))
    print(photos[i].ori, photos[i].num, photos[i].tags)
    i


# if (get_word() == 'H'):
#     m = get_number()
#     tags = []
#     for _ in range(m):
#         tags.append(get_word())
#         h.append(tags)
# else:
#     m = get_number()
#     tags = []
#     for _ in range(m):
#         tags.append(get_word())
#         v.append(tags)
#
# print(h)
# print(v)
