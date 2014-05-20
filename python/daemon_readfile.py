import sys
import time
import matplotlib.pyplot as plt


def watch_file_mods(file_to_watch):
    file_history = []
    try:
        while True:
            try:
                with open(file_to_watch) as opened_file:
                    line = tuple(opened_file.readlines())
                    try:
                        if line != file_history[-1][0]:
                            file_history.append((line, "".join(time.ctime().split(" ")[-2].split(":"))))
                            print(file_history[-1][0])
                    except IndexError:
                        file_history.append((line, "".join(time.ctime().split(" ")[-2].split(":"))))
                        print(file_history[-1][0])
            except IOError:
                pass
            time.sleep(1)
    except KeyboardInterrupt:
        return file_history


# def main(file_to_read):
if __name__ == "__main__":
    file_history = watch_file_mods("test.txt")
    plt.ion()
    y = [len(y[0]) for y in file_history]
    x = [int(x[1]) for x in file_history]
    x = [el - x[0] for el in x]
    plt.plot(x, y, "o")
    plt.plot(x, y)
    plt.show()
