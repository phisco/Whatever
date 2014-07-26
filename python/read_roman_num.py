#!/usr/bin/env python
import os


def read_roman_num(char_num):
    """
    Given a string, both upper or lowercase, containing a roman number
    returns the correspondent number as an int
    """
    reference_dict = {"I": 1, "V": 5, "X": 10, "L": 50}
    buffer = 0
    final_value = 0
    char_num_buff = char_num.upper()
    for el in char_num_buff:
        if buffer > reference_dict[el]:
            final_value += buffer
            buffer = 0
        if buffer != 0 and buffer < reference_dict[el]:
            buffer = reference_dict[el]-buffer
        else:
            buffer += reference_dict[el]
    else:
        return final_value + buffer


def convert_roman_titles(dir="."):
    """
    Given a directory it renames the files that has a roman number as name to
    the correspondent number, keeping the same extension.
    """
    for el in os.listdir(dir):
        try:
            new_name = str(read_roman_num(el[:-4]))
            print el, "-->", new_name
            os.rename(el, ".".join([new_name, el.split(".")[-1]]))
        except:
            pass


if __name__ == "__main__":
    convert_roman_titles(".")
