from sys import argv
from csv import DictReader
from cs50 import SQL

if len(argv) != 2:
    print("Usage: python import.py file.csv")
    exit(1)

db = SQL("sqlite:///students.db")

with open(argv[1],"r") as file:
    reader = DictReader(file)
    for row in reader:
        names = row["name"].split(" ")
        if len(names) == 2:
            names.append(names[1])
            names[1] = "NULL"
        a = names[0]
        b = names[1]
        c = names[2]
        d = row["house"]
        e = row["birth"]
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",a,b,c,d,e)