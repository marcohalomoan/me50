from sys import argv

from cs50 import SQL

if len(argv) != 2:
    print("Usage: python roster.py housename")
    exit(1)

db = SQL("sqlite:///students.db")

namelist = db.execute(f"SELECT * FROM students WHERE house = '{argv[1]}'")
print(namelist)
   # print(,",""born",)
for i in range(len(namelist)):
    dictname = namelist[i]
    if (dictname['middle'] == "NULL"):
        print(f"{dictname['first']} {dictname['last']}, born {dictname['birth']}")
    else:
        print(f"{dictname['first']} {dictname['middle']} {dictname['last']}, born {dictname['birth']}")