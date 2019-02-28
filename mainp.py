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

# class slide:
#     def __init__(self)

class hslide:
    def __init__(self, ori, tags, id):
        self.ori = ori
        self.tags = tags
        self.id = id
        self.flag = True

class vslide:
    def __init__(self, ori, tags, ids):
        self.ori = ori
        self.tags = tags
        self.ids = ids
        self.flag = True

class photo:
    def __init__(self, ori, tags, id):
        self.ori = ori
        self.tags = tags
        self.id = id

def score(list1, list2):
    t1 = len(list1)
    t2 = len(list2)
    t = len(list(set(list1).intersection(list2)))
    return min(t1-t, t, t2-t)

from random import shuffle

N = get_number()
h = []
photos = []
v = []
hs = []
for i in range(N):
    ori = get_word()
    num = get_number()
    tags = []
    for _ in range(num):
        tags.append(get_word())
    photos.append(photo(ori, tags, i))
    if (ori == 'H'):
        h.append(photo(ori, tags, i))
        hs.append(hslide(ori, tags, i))
    else:
        v.append(photo(ori, tags, i))
        # isos i+1
    # print(photos[i].ori, photos[i].num, photos[i].tags, photos[i].id )

shuffle(v)

vs = []
for i in range(0, len(v), 2):
    tags = list(set(v[i].tags+v[i+1].tags))
    ids = []
    ids.append(v[i].id)
    ids.append(v[i+1].id)
    s = vslide('V', tags, ids)
    vs.append(s)
import sys
slides = hs + vs
shuffle(slides)
file1 = 'e'
file2 = '_output'
out = open(file1 + file2 + ".txt", 'w')
out.write(str(len(slides)) + '\n')
for i in range(len(slides)):
    if (slides[i].ori == 'H'):
        out.write(str(slides[i].id) + '\n')
    else:
        out.write(str(slides[i].ids[0]) + ' ' + str(slides[i].ids[1]) + '\n')
out.close()


# print(score(['a','b'],['b','c','d']))
# print(list(set(['a','b']+['b','c'])))


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
