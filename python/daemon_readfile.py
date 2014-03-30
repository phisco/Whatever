import sys
import time
import matplotlib.pyplot as plt


def watch_file_mods(file=sys.argv[1]):
    file_history = []
    try:
        while True:
            try:
                with open(sys.argv[1]) as file:
                    line = tuple(file.readlines())
                    try:
                        if line != file_history[-1][0]:
                            file_history.append((line, "".join(time.ctime().split(" ")[-2].split(":"))))
                            print(file_history[-1][0])
                    except IndexError:
                        file_history.append((line, "".join(time.ctime().split(" ")[-2].split(":"))))
                        print(file_history[-1][0])
            except IOError:
                pass
    except KeyboardInterrupt:
        return file_history

if __name__ == "__main__":
    file_history = watch_file_mods(sys.argv[1])
    y = [len(y[0]) for y in file_history]
    x = [int(x[1]) for x in file_history]
    x = map(lambda el: el - x[0], x)
    plt.plot(x, y, "o")
    plt.plot(x, y)
    plt.show()
