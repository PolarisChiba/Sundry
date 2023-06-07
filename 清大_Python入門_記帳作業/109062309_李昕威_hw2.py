import sys

def initialize():
    # read the initial_money, records from the file, or input the inital_money if file is not existed or broken
    def input_initial_money(dep):
        # input initial money, there will be 3 times to try
        if dep >= 3:
            sys.stderr.write("Too much error. Initial money set to 0 by default.\n")
            return 0
        try:
            initial_money = int(input("How much money do you have? "))
            return initial_money
        except ValueError:
            sys.stderr.write("Invalid value for money. Please input again.\n\n")
            return input_initial_money(dep + 1)

    try:
        with open('records.txt', 'r') as fh:
            initial_money = int(fh.readline()[0 : -1])
            records = list(map(lambda x: x.split(' '), fh.readlines()))
            records = list(map(lambda x: (" ".join(x[0 : -1]), int(x[-1])), records))
            print("Welcome back!")
            return initial_money, records
    except FileNotFoundError:
        return input_initial_money(0), []
    except:
        sys.stderr.write("The data has been broken.\n")
        return input_initial_money(0), []

def add(records):
    # append a new record to the back of records, the input should contain description and money, space is allowed in description, money should be integer
    try:
        expense = input("Add some expense or income records with description and amount:\ndesc1 amt1, desc2 amt2, desc3 amt3, ...\n").split(',')
        expense = list(map(lambda x: x.split(), expense))
        try:
            expense = list(map(lambda x: (" ".join(x[0 : -1]), int(x[-1])), expense))
        except ValueError:
            sys.stderr.write("Invalid value for money.\nFail to add record.\n")
            expense = []
        
        for item, value in expense:
            if len(item) == 0:
                sys.stderr.write("Some record's description is empty.\nFail to add record.\n");
                expense = []
            if len(item) > 20:
                sys.stderr.write("Some record's description is too long.\nFail to add record.\n")
                expense = []
    except:
        sys.stderr.write("The format of a record should be like this: breakfast -50.\nFail to add record.\n")
        expense = []
    finally:
        records.extend(expense)
        return records

def view(initial_money, records):
    # show the records
    column1_size, column2_size, column3_size = 10, 20, 10
    print("Here's your expense and income records:")
    print(f"{'Number':{column1_size}} {'Description':{column2_size}} {'Amount':{column3_size}}")
    print(f"{'=' * column1_size:{column1_size}} {'=' * column2_size:{column2_size}} {'=' * column3_size:{column3_size}}")
    sum = initial_money
    for number, expense in enumerate(records):
        item, value = expense
        print(f"{number + 1:<{column1_size}} {item:<{column2_size}} {value:<{column3_size}}")
        sum += value
    print(f"{'=' * column1_size:{column1_size}} {'=' * column2_size:{column2_size}} {'=' * column3_size:{column3_size}}")
    print(f"Now you have {sum} dollars.")

def delete(records):
    # delete the record by their number
    try:
        del_record_number = list(map(int, input("Which records do you want to delete?\nEnter their number to delete.\nnum1 num2 ...\n").split()))
    except:
        sys.stderr.write("Some input is not integer.\n")
        return records
    
    for i in del_record_number: 
        if (1 <= i and i <= len(records)) == False:
            sys.stderr.write("Some input is out of records range.\n")
            return records

    del_record_number.sort()
    for i in reversed(del_record_number):
        del records[i - 1]
    return records

def save(initial_money, records):
    # save initial_money, records to the file
    try:
        with open('records.txt', 'w') as fh:
            fh.write(str(initial_money) + "\n")
            fh.writelines(list(map(lambda x: "".join([x[0], " ", str(x[1]), "\n"]), records)))
    except Exception as e:
        sys.stderr.write(f"Unknown error msg: {e}.\nExit unexpectedly and there may be data lost.\n")

initial_money, records = initialize()
while True:
    command = input('\nWhat do you want to do (add / view / delete / exit)? ')
    if command == 'add':
        records = add(records)
    elif command == 'view':
        view(initial_money, records)
    elif command == 'delete':
        records = delete(records)
    elif command == 'exit':
        save(initial_money, records)
        break
    else:
        sys.stderr.write('Invalid command. Try again.\n')