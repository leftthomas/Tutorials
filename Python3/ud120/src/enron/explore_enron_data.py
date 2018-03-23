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

enron_data = pickle.load(open("../../resources/enron/enron_dataset.pkl", "rb"))
# number of people
print('number of people:', len(enron_data))

# number of features
print('number of features:', len(enron_data['SKILLING JEFFREY K']))

# number of poi(from enron_dataset)
num = 0
for value in enron_data.values():
    if value['poi'] == 1:
        num += 1
print('number of poi(from enron_dataset):', num)

# number of poi(from poi_names)
num = 0
# number of poi which haven't salary(from poi_names)
num_nan = 0
f = open("../../resources/enron/poi_names.txt")
line = f.readline()
while line:
    # 调用文件的readline()方法
    num += line.count('(')
    num_nan += line.count('(n)')
    line = f.readline()
f.close()
print('number of poi(from poi_names):', num)
print('number of poi which haven\'t salary(from poi_names):', num_nan)
print('the percent that haven\'t salary of all poi:', num_nan / num)

# total stock value of James Prentice
print('total stock value of James Prentice:', enron_data['PRENTICE JAMES']['total_stock_value'])

# number of emails from Wesley Colwell to poi
print('number of emails from Wesley Colwell to poi:', enron_data['COLWELL WESLEY']['from_this_person_to_poi'])

# exercised stock options of Jeffrey K Skilling
print('exercised stock options of Jeffrey K Skilling:', enron_data['SKILLING JEFFREY K']['exercised_stock_options'])

# total payments of Jeffrey K Skilling
print('total payments of Jeffrey K Skilling:', enron_data['SKILLING JEFFREY K']['total_payments'])
# total payments of Kenneth Lay
print('total payments of Kenneth Lay:', enron_data['LAY KENNETH L']['total_payments'])
# total payments of Andrew Fastow
print('total payments of Andrew Fastow:', enron_data['FASTOW ANDREW S']['total_payments'])

# number of folks(have salary,have email address from enron_dataset)
num_salary = 0
num_email = 0
for value in enron_data.values():
    if value['salary'] != 'NaN':
        num_salary += 1
    if value['email_address'] != 'NaN':
        num_email += 1
print('number of folks(have salary from enron_dataset):', num_salary)
print('number of folks(have email address from enron_dataset):', num_email)
print('the percent that haven\'t salary of all people:', 1 - num_salary / len(enron_data.values()))
