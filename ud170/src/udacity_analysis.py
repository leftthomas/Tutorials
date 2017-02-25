import csv
from collections import defaultdict
from datetime import datetime as dt

import matplotlib.pyplot as plt
import numpy as np


# 读取csv文件
def read_csv(filename):
    with open(filename) as f:
        reader = csv.DictReader(f)
        return list(reader)


# 将字符串转成日期格式数据
def parse_date(date):
    if date == '':
        return None
    else:
        return dt.strptime(date, '%Y-%m-%d')


# 将字符串转成int格式数据
def parse_maybe_int(i):
    if i == '':
        return None
    else:
        return int(i)


enrollments_filename = "/Users/left/workspace/python/learn/ud170/resources/udacity_students/enrollments.csv"
engagement_filename = "/Users/left/workspace/python/learn/ud170/resources/udacity_students/daily_engagement.csv"
submissions_filename = "/Users/left/workspace/python/learn/ud170/resources/udacity_students/project_submissions.csv"

enrollments = list(read_csv(enrollments_filename))
daily_engagement = list(read_csv(engagement_filename))
project_submissions = list(read_csv(submissions_filename))

# 以下属于数据清洗环节，将数据转成正确的格式
for enrollment in enrollments:
    enrollment['join_date'] = parse_date(enrollment['join_date'])
    enrollment['cancel_date'] = parse_date(enrollment['cancel_date'])
    enrollment['days_to_cancel'] = parse_maybe_int(enrollment['days_to_cancel'])
    enrollment['is_udacity'] = enrollment['is_udacity'] == 'True'
    enrollment['is_canceled'] = enrollment['is_canceled'] == 'True'

for engagement_record in daily_engagement:
    engagement_record['utc_date'] = parse_date(engagement_record['utc_date'])
    engagement_record['num_courses_visited'] = int(float(engagement_record['num_courses_visited']))
    engagement_record['total_minutes_visited'] = int(float(engagement_record['total_minutes_visited']))
    engagement_record['lessons_completed'] = int(float(engagement_record['lessons_completed']))
    engagement_record['projects_completed'] = int(float(engagement_record['projects_completed']))

for project_submission in project_submissions:
    project_submission['creation_date'] = parse_date(project_submission['creation_date'])
    project_submission['completion_date'] = parse_date(project_submission['completion_date'])

# print(enrollments[0])
# print(daily_engagement[0])
# print(project_submissions[0])

# 将daily_engagement数据表中的acct列名转成统一的account_key
for engagement_record in daily_engagement:
    engagement_record['account_key'] = engagement_record['acct']
    del engagement_record['acct']


# 提取出用户的id号
def get_unique_students(data):
    unique_students = set()
    for data_point in data:
        unique_students.add(data_point['account_key'])
    return unique_students

# print(len(enrollments))
unique_enrolled_students = get_unique_students(enrollments)
# print(len(unique_enrolled_students))

# print(len(daily_engagement))
unique_engagement_students = get_unique_students(daily_engagement)
# print(len(unique_engagement_students))

# print(len(project_submissions))
unique_project_submitters = get_unique_students(project_submissions)
# print(len(unique_project_submitters))

# 检查问题数据：一是udacity测试账号，一是第一天就注销的账号
# for enrollment in enrollments:
#     student = enrollment['account_key']
#     if student not in unique_engagement_students:
#         print(enrollment)

# num_problem_students = 0
# for enrollment in enrollments:
#     student = enrollment['account_key']
#     if (student not in unique_engagement_students and
#             enrollment['join_date'] != enrollment['cancel_date']):
#         print(enrollment)
#         num_problem_students += 1
# print(num_problem_students)

udacity_test_accounts = set()
for enrollment in enrollments:
    if enrollment['is_udacity']:
        udacity_test_accounts.add(enrollment['account_key'])


# 删除测试账号
def remove_udacity_accounts(data):
    non_udacity_data = []
    for data_point in data:
        if data_point['account_key'] not in udacity_test_accounts:
            non_udacity_data.append(data_point)
    return non_udacity_data

non_udacity_enrollments = remove_udacity_accounts(enrollments)
non_udacity_engagement = remove_udacity_accounts(daily_engagement)
non_udacity_submissions = remove_udacity_accounts(project_submissions)
# print(len(non_udacity_enrollments))
# print(len(non_udacity_engagement))
# print(len(non_udacity_submissions))

# 提取出付费用户
paid_students = {}
for enrollment in non_udacity_enrollments:
    if (not enrollment['is_canceled'] or
                enrollment['days_to_cancel'] > 7):
        account_key = enrollment['account_key']
        enrollment_date = enrollment['join_date']
        if (account_key not in paid_students or
                    enrollment_date > paid_students[account_key]):
            paid_students[account_key] = enrollment_date

# print(len(paid_students))


def within_one_week(join_date, engagement_date):
    time_delta = engagement_date - join_date
    return time_delta.days >= 0 and time_delta.days < 7


def remove_free_trial_cancels(data):
    new_data = []
    for data_point in data:
        if data_point['account_key'] in paid_students:
            new_data.append(data_point)
    return new_data


paid_enrollments = remove_free_trial_cancels(non_udacity_enrollments)
paid_engagement = remove_free_trial_cancels(non_udacity_engagement)
paid_submissions = remove_free_trial_cancels(non_udacity_submissions)

# print(len(paid_enrollments))
# print(len(paid_engagement))
# print(len(paid_submissions))

paid_engagement_in_first_week = []
for engagement_record in paid_engagement:
    account_key = engagement_record['account_key']
    join_date = paid_students[account_key]
    engagement_record_date = engagement_record['utc_date']

    if within_one_week(join_date, engagement_record_date):
        paid_engagement_in_first_week.append(engagement_record)
        # print(len(paid_engagement_in_first_week))


def group_data(data, key_name):
    grouped_data = defaultdict(list)
    for data_point in data:
        key = data_point[key_name]
        grouped_data[key].append(data_point)
    return grouped_data

engagement_by_account = group_data(paid_engagement_in_first_week, 'account_key')


def sum_grouped_items(grouped_data, field_name):
    summed_data = {}
    for key, data_points in grouped_data.items():
        total = 0
        for data_point in data_points:
            total += data_point[field_name]
        summed_data[key] = total
    return summed_data

total_minutes_by_account = sum_grouped_items(engagement_by_account, 'total_minutes_visited')


def describe_data(data):
    print('Mean:', np.mean(data))
    print('Standard deviation:', np.std(data))
    print('Minimum:', np.min(data))
    print('Maximum:', np.max(data))
    plt.hist(data)
    plt.show()

# print(total_minutes_by_account.values())
describe_data(list(total_minutes_by_account.values()))
lessons_completed_by_account = sum_grouped_items(engagement_by_account, 'lessons_completed')
describe_data(list(lessons_completed_by_account.values()))

for engagement_record in paid_engagement:
    if engagement_record['num_courses_visited'] > 0:
        engagement_record['has_visited'] = 1
    else:
        engagement_record['has_visited'] = 0

days_visited_by_account = sum_grouped_items(engagement_by_account, 'has_visited')
describe_data(list(days_visited_by_account.values()))

subway_project_lesson_keys = ['746169184', '3176718735']

pass_subway_project = set()

for submission in paid_submissions:
    project = submission['lesson_key']
    rating = submission['assigned_rating']

    if ((project in subway_project_lesson_keys) and
            (rating == 'PASSED' or rating == 'DISTINCTION')):
        pass_subway_project.add(submission['account_key'])

# print(len(pass_subway_project))

passing_engagement = []
non_passing_engagement = []

for engagement_record in paid_engagement_in_first_week:
    if engagement_record['account_key'] in pass_subway_project:
        passing_engagement.append(engagement_record)
    else:
        non_passing_engagement.append(engagement_record)

# print(len(passing_engagement))
# print(len(non_passing_engagement))

passing_engagement_by_account = group_data(passing_engagement, 'account_key')
non_passing_engagement_by_account = group_data(non_passing_engagement, 'account_key')

print('non-passing students:')
non_passing_minutes = sum_grouped_items(non_passing_engagement_by_account, 'total_minutes_visited')
describe_data(list(non_passing_minutes.values()))

print('passing students:')
passing_minutes = sum_grouped_items(passing_engagement_by_account, 'total_minutes_visited')
describe_data(list(passing_minutes.values()))

print('non-passing students:')
non_passing_lessons = sum_grouped_items(non_passing_engagement_by_account, 'lessons_completed')
describe_data(list(non_passing_lessons.values()))

print('passing students:')
passing_lessons = sum_grouped_items(passing_engagement_by_account, 'lessons_completed')
describe_data(list(passing_lessons.values()))

print('non-passing students:')
non_passing_visits = sum_grouped_items(non_passing_engagement_by_account, 'has_visited')
describe_data(list(non_passing_visits.values()))

print('passing students:')
passing_visits = sum_grouped_items(passing_engagement_by_account, 'has_visited')
describe_data(list(passing_visits.values()))

