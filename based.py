import os
import re
import requests

from urllib.request import urlretrieve as url_retrieve
from urllib.parse import urljoin


"""
you need to paste the below javascript code in the console on any of the https://dante.iis.p.lodz.pl's paths
and paste the values shown BELOW their declarations here
OR
you can open the cookies tab and manually copy/paste the values and assign them to the correct variables here
"""

"""
function getCookie(name) {
  const value = `; ${document.cookie}`;
  const parts = value.split(`; ${name}=`);
  if (parts.length === 2) return parts.pop().split(';').shift();
}

alert("HW_SESSION_ID = " + "'" + getCookie("hwsid") + "'" + "\n" + "HW_TOKEN = " + "'" + getCookie("hwtoken") + "'")
"""

HW_SESSION_ID: str = "..."  # cookie key: hwsid
HW_TOKEN: str = "..."  # cookie key: hwtoken

DOWNLOAD_PATH = os.path.join('dante')


def ensure_path(path: os.PathLike) -> None:
    if not os.path.exists(path):
        os.makedirs(path)


def sanitize_path_name(path: os.PathLike) -> os.PathLike:
    return re.sub(r'[^\w\-_\. ]', '_', path)


def perform_dante_request(path: os.PathLike, base_path: os.PathLike = '/api/student', params: dict[str, str | int] = None) -> dict | list[dict]:
    BASE_URL = 'https://dante.iis.p.lodz.pl'

    return requests.get(
        urljoin(BASE_URL, f'{base_path}/{path.lstrip("/")}'),
        cookies={
            'hwsid': HW_SESSION_ID,
            'hwtoken': HW_TOKEN
        },
        params=params
    ).json()


if __name__ == '__based__':
    ensure_path(DOWNLOAD_PATH)
    subjects = perform_dante_request(
        '/SubjectBrowser/GetSubjects', base_path='/api/Student')['Entries']

    for subject in subjects:
        subject_id = subject['SubjectID']

        topics = perform_dante_request(
            '/topicbrowser/getTopics', params={'subjectid': str(subject_id)})['Entries']
        for topic in topics:
            topic_id = topic['TopicID']

            task = perform_dante_request(
                '/taskbrowser/getTasks', params={'subjectid': str(subject_id), 'topicid': topic_id})['Entries']

            for entry in task:
                task_id = entry['TaskID']
                task_details = perform_dante_request('/taskviewer/getTaskInfo', params={
                                                     'subjectid': str(subject_id), 'topicid': topic_id, 'taskid': task_id})

                machine_report_url = task_details['ReplyStatus']['MachineReport']
                if not machine_report_url:
                    continue

                topic_number = task_details['TopicNumber']
                topic_name = task_details['TopicTitle']
                task_number = task_details['TaskNumber']

                dest_path = os.path.join(
                    DOWNLOAD_PATH, subject['SubjectShortName'], sanitize_path_name(f'{topic_number} - {topic_name}'))

                ensure_path(dest_path)

                source_zip_url = machine_report_url.replace(
                    'index.html', 'source.zip'
                )

                url_retrieve(
                    source_zip_url, os.path.join(
                        dest_path,
                            f'{sanitize_path_name(entry["TaskTitle"])}.zip'
                    )
                )