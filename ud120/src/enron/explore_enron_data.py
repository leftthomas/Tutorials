"""
    Starter code for exploring the Enron dataset (emails + finances);
    loads up the dataset (pickled dict of dicts).
    The dataset has the form:
    enron_data["LASTNAME FIRSTNAME MIDDLEINITIAL"] = { features_dict }

    {features_dict} is a dictionary of features associated with that person.
    You should explore features_dict as part of the mini-project,
    but here's an example to get you started:

    enron_data["SKILLING JEFFREY K"]["bonus"] = 5600000
"""

import pickle

enron_data = pickle.load(open("../../resources/enron_dataset.pkl", "rb"))
# number of people
print(len(enron_data))

# number of features
print(len(enron_data['SKILLING JEFFREY K']))

# number of poi(from enron_dataset)
num = 0
for value in enron_data.values():
    if value['poi'] == 1:
        num += 1
print(num)

# number of poi(from poi_names)
num = 0
f = open("../../resources/poi_names.txt")
line = f.readline()
while line:
    # 调用文件的readline()方法
    num += line.count('(')
    line = f.readline()
f.close()
print(num)

# total stock value of James Prentice
print(enron_data['PRENTICE JAMES']['total_stock_value'])

# number of emails from Wesley Colwell to poi
print(enron_data['COLWELL WESLEY']['from_this_person_to_poi'])

# exercised stock options of Jeffrey K Skilling
print(enron_data['SKILLING JEFFREY K']['exercised_stock_options'])
