import time

current = time.time()
while True:
    if time.time() - current > 1:
        current = time.time()
        print(current)
   
