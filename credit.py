from cs50 import get_string

def main():
    number = get_string("Number: ")
    add = 0
    n = len(number) - 1
    while n > 0:
        if int(number[n-1]) * 2 > 9:
            temp = str(int(number[n-1]) * 2)
            for i in [0, 1]:
                add += int(temp[i])
        else:
            add += int(number[n-1]) * 2
        n -= 2
    n = len(number) - 1
    while n >= 0:
        add += int(number[n])
        n -= 2

    if checkAME(number) and add % 10 == 0:
        print("AMEX")
    elif checkMASTER(number) and add % 10 == 0:
        print("MASTERCARD")
    elif checkVISA(number) and add % 10 == 0:
        print("VISA")
    else:
        print("INVALID")

def checkAME(number):
    if int(number[0]) == 3 and (int(number[1]) == 4 or int(number[1]) == 7) and len(number) == 15:
        return True
    return False

def checkMASTER(number):
    if int(number[0]) == 5 and len(number) == 16:
        for i in [1, 2, 3, 4, 5]:
            if int(number[1]) == i:
                return True
    return False

def checkVISA(number):
    if int(number[0]) == 4 and (len(number) == 13 or len(number) == 16):
        return True
    return False

main()