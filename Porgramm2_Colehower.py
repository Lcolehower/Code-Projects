import datetime

def date2string(date, type):
    if type == "short" or type == "s" or type == "S":
        dname = date.strftime("%a, %B %d, %Y")
    elif type == "long" or type == "l" or type == "L":
        dname = date.strftime("%A, %B %d, %Y")
    else:
        dname = "Invalid format choice."
    return dname

if __name__ == '__main__':
    choice = input("Please enter your preferred date format (s)hort/(l)ong: ")
    print(date2string(datetime.datetime.now(), choice))