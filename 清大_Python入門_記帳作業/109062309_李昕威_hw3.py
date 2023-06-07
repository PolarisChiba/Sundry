import sys

class Categories:
    """Maintain the category list and provide some methods."""

    def __init__(self):
        """Initialize Categories"""
        self._categories = ['expense', ['food', ['meal', 'snack', 'drink'], 'transportation', ['bus', 'railway']], 'income', ['salary', 'bonus']]

    def view(self):
        """Show Categories with ident being multiple of 2"""
        def _view(categories, ident):
            if type(categories) == list:
                for sub_categories in categories:
                    _view(sub_categories, ident + 2)
            else:
                print(f"{' ' * ident}- {categories}")
        _view(self._categories, -2)
    
    def is_category_valid(self, category):
        """check given category is in categories list or not"""
        return category in list(self.find_subcategories(category))
    
    def find_subcategories(self, category):
        """find all all categories under given category"""
        def find_subcategories_gen(category, categories, found):
            if type(categories) == list:
                for id, sub_categories in enumerate(categories):
                    yield from find_subcategories_gen(category, sub_categories, found)
                    if sub_categories == category and id + 1 < len(categories) and type(categories[id + 1]) == list:
                        yield from find_subcategories_gen(category, categories[id + 1], True)
            else:
                if categories == category or found == True:
                    yield categories
        
        return find_subcategories_gen(category, self._categories, False)

class Record:
    """Represent a record."""

    def __init__(self, category, description, amount):
        "initialize Record with given category, description, and amount"
        self._category = category
        self._description = description
        self._amount = amount
    
    @property
    def category(self):
        """get category"""
        return self._category
    
    @property
    def description(self):
        """get description"""
        return self._description
    
    @property
    def amount(self):
        """get amount"""
        return self._amount

class Records:
    """Maintain a list of all the 'Record's and the initial amount of money."""

    @classmethod
    def input_initial_money(records, trial = 3):
        """input initial money with default trial times = 3"""
        while True:
            try:
                if trial == 0:
                    sys.stderr.write("Too much error. Initial money set to 0 by default.\n")
                    records._initial_money = 0
                else:
                    records._initial_money = int(input("How much money do you have? "))
                break
            except ValueError:
                sys.stderr.write("Invalid value for money. Please input again.\n\n")
            finally:
                trial = trial - 1
        records._records = []

    def __init__(self):
        """initialize Records (read file or input)"""

        self._intial_money = 0
        self._records = []

        try:
            with open("records.txt", "r") as fh:
                self._initial_money = int(fh.readline()[0 : -1])
                for item in fh.readlines():
                    item = item.split(' ')
                    assert(len(item) == 3)
                    self._records.append(Record(item[0], item[1], int(item[2])))
                print("Welcome back!")
        except FileNotFoundError:
            self.input_initial_money(3)
        except:
            sys.stderr.write("The data has been broken.\n")
            self.input_initial_money(3)

    def add(self, items, categories):
        """Add new items to records. The format should be 'cat1 desc1 amt1, cat2 desc2 amt2, cat3 desc3 amt3, ...'"""
        try:
            items = items.split(',')
            items = list(map(lambda x: x.split(), items))
            try:
                items = list(map(lambda x: x[0 : -1] + [int(x[-1])], items))
            except ValueError:
                sys.stderr.write("Invalid value for money.\nFail to add record.\n")
                items = []
            for item in items:
                assert(len(item) == 3)
            try:
                for category, description, amount in items:
                    assert(categories.is_category_valid(category))
            except:
                sys.stderr.write('The specified category is not in the category list.\nYou can check the category list by command "view categories".\nFail to add a record.')
                items = []

        except:
            sys.stderr.write("The format of a record should be like this: breakfast -50.\nFail to add record.\n")
            items = []
        finally:
            for category, description, amount in items:
                self._records.append(Record(category, description, amount))

    def view(self):
        """Show all record in records"""
        print("Here's your expense and income records:")
        print(f"{'Number':10} {'Category':20} {'Description':20} {'Amount':10}")
        print(f"{'=' * 10} {'=' * 20} {'=' * 20} {'=' * 10}")
        sum = self._initial_money
        for number, record in enumerate(self._records):
            print(f"{number + 1:<10} {record.category:<20} {record.description:<20} {record.amount:<10}")
            sum += record.amount
        print(f"{'=' * 10} {'=' * 20} {'=' * 20} {'=' * 10}")
        print(f"Now you have {sum} dollars.")

    def delete(self, numbers):
        """Delete the records with given id. Ids should be seperated with space."""
        try:
            numbers = list(map(int, numbers.split()))
        except:
            sys.stderr.write("Some input is not integer.\n")
            return
        
        for i in numbers:
            if (1 <= i and i <= len(self._records) == False):
                sys.stderr.write("Some input is out of records range.\n")
                return
        
        numbers.sort()
        for i in reversed(numbers):
            del self._records[i - 1]
        
    def find(self, categories):
        """List all record with category under given one."""
        categories = list(categories)

        if len(categories) == 0:
            sys.stderr.write(f"Category not found.")
            return

        print(f'Here\'s your expense and income records under category "{categories[0]}":')
        print(f"{'Number':10} {'Category':20} {'Description':20} {'Amount':10}")
        print(f"{'=' * 10} {'=' * 20} {'=' * 20} {'=' * 10}")
        sum = 0
        for number, record in enumerate(self._records):
            if record.category in categories:
                print(f"{number + 1:<10} {record.category:<20} {record.description:<20} {record.amount:<10}")
                sum += record.amount
        print(f"{'=' * 10} {'=' * 20} {'=' * 20} {'=' * 10}")
        print(f"Total amount of above is {sum}.")

    def save(self):
        """save initial_money, records to the file."""
        try:
            with open('records.txt', 'w') as fh:
                fh.write(str(self._initial_money) + "\n")
                fh.writelines(list(map(lambda x: "".join([x.category, " ", x.description, " ", str(x.amount), "\n"]), self._records)))
        except Exception as e:
            sys.stderr.write(f"Unknown error msg: {e}.\nExit unexpectedly and there may be data lost.\n")

categories = Categories()
records = Records()


while True:
    command = input("\nWhat do you want to do (add / view / delete / view categories / find / exit)? ")
    if command == 'add':
        record = input('Add some expense or income records with category, description, and amount (separate by spaces):\ncat1 desc1 amt1, cat2 desc2 amt2, cat3 desc3 amt3, ...\n')
        records.add(record, categories)
    elif command == 'view':
        records.view()
    elif command == 'delete':
        delete_record = input("Which record do you want to delete? ")
        records.delete(delete_record)
    elif command == 'view categories':
        categories.view()
    elif command == 'find':
        category = input('Which category do you want to find? ')
        target_categories = categories.find_subcategories(category)
        records.find(target_categories)
    elif command == 'exit':
        records.save()
        break
    else:
        sys.stderr.write('Invalid command. Try again.\n')
