import os
import re
import requests
from zipfile import ZipFile

# these values can be extracted from the cookies tab in your browser
COOKIES = {
    'hwsid': 'my_hwsid',
    'hwtoken': 'my_hwtoken'
}

#dante shits itself when all active lol
task_html = 1
report_html = 1
source_zip = 0
more_files = 0


def getSubjects():
    url = 'https://dante.iis.p.lodz.pl/api/Student/SubjectBrowser/GetSubjects'
    return requests.get(url, cookies=COOKIES).json()['Entries']


def getTopics(subject_id):
    url = 'https://dante.iis.p.lodz.pl/api/student/topicbrowser/getTopics'
    return requests.get(url, cookies=COOKIES, params={'subjectid': str(subject_id)}).json()['Entries']


def getTasks(subject_id, topic_id):
    url = 'https://dante.iis.p.lodz.pl/api/student/taskbrowser/getTasks'
    return requests.get(url, cookies=COOKIES, params={'subjectid': str(subject_id), 'topicid': str(topic_id)}).json()['Entries']


def getTaskContent(subject_id, topic_id, task_id):
    url = 'https://dante.iis.p.lodz.pl/api/student/taskviewer/getTaskContent'
    return requests.get(url, cookies=COOKIES, params={'subjectid': str(subject_id), 'topicid': str(topic_id), 'taskid': str(task_id)}).json()['Text']


def WriteTaskContent(task_content, path):
    if not os.path.exists(path):
        os.makedirs(path)
    file = open(path + '/task.html', 'w', encoding="utf-8")
    file.writelines(task_content)
    file.close()


def getTaskReply(subject_id, topic_id, task_id):
    url = 'https://dante.iis.p.lodz.pl/api/student/taskviewer/getTaskInfo'
    return requests.get(url, cookies=COOKIES, params={'subjectid': str(subject_id), 'topicid': str(topic_id), 'taskid': str(task_id)}).json()['ReplyStatus']


def scrapeReport(url, path):
    if not os.path.exists(path):
        os.makedirs(path)
    if not os.path.exists(path + "/cmake-build-debug"):
        os.makedirs(path + "/cmake-build-debug")
    report = requests.get(url, cookies=COOKIES).text

    if report_html:
        file = open(path + '/report.html', 'w', encoding="utf-8")
        file.writelines(report)
        file.close()

    if source_zip:
        zip_files = requests.get(url.replace('index.html', 'source.zip'))

        file = open(path + '/source.zip', 'wb')
        file.write(zip_files.content)
        file.close()
        ZipFile(path + '/source.zip').extractall(path=path)

    if more_files:
        more_dante_files = re.findall('Pobierz wygenerowany plik: <a href="(.*)">', report)

        for entry in more_dante_files:
            fileToSave = requests.get(url.replace('index.html', entry))
            with open(path + '/' + entry[4:], 'wb') as file
                file.write(fileToSave.content)
            with open(path + '/cmake-build-debug/' + entry[4:], 'wb') as file
                file.write(fileToSave.content)


def nameSanitize(name):
    return name.translate({ord(i): None for i in '<>:"/\\|?*'}).strip()


subjects = getSubjects()

for subject in subjects:
    subject_id = subject['SubjectID']
    topics = getTopics(subject_id)
    for topic in topics:
        topic_id = topic['TopicID']
        tasks = getTasks(subject_id, topic_id)

        for task in tasks:
            task_id = task['TaskID']

            task_content = getTaskContent(subject_id, topic_id, task_id)
            path = 'dante/' + nameSanitize(subject['SubjectName']) + '/' + str(task['TopicNumber'] + ' ').zfill(3) + nameSanitize(topic['Title']) + '/' + str(task['TaskNumber'] + ' ').zfill(3) + nameSanitize(task['TaskTitle'])
            if task_html:
                WriteTaskContent(task_content, path)

            print(str(task['TopicNumber'] + ' ').zfill(3), str(task['TaskNumber'] + ' ').zfill(3))

            task_reply = getTaskReply(subject_id, topic_id, task_id)
            if not task_reply['MachineReport']:
                continue
            scrapeReport(task_reply['MachineReport'], path)
