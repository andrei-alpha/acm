import string
import random

def id_generator(size=6, chars=string.ascii_uppercase + string.digits):
  return ''.join(random.choice(chars) for _ in range(size))

f = open("big", "w")

for i in xrange(0, 20):
  f.write("<text>\n")
  for j in xrange(0, 2000):
    f.write(id_generator(20, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") + " ") 
  f.write("</text>\n")
  f.write("<top 20/>\n")
