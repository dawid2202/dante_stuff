import requests
import re
import os
from zipfile import ZipFile

url = input("gimme link: ")

path="files/"

dante = requests.get(url)

danteFiles = re.findall('Pobierz wygenerowany plik: <a href="(.*)">', dante.text)

if not os.path.exists(path):
    os.makedirs(path)
if not os.path.exists(path + "/cmake-build-debug"):
    os.makedirs(path + "/cmake-build-debug")

zip_files = requests.get(url.replace('index.html', 'source.zip'))
file = open(path + '/source.zip', 'wb')
file.write(zip_files.content)
file.close()
ZipFile(path + '/source.zip').extractall(path=path)

for file in danteFiles:
    if os.path.isfile(path+file[4:]):
        continue
    fileToSave = requests.get(url.replace('index.html', file))
    with open(path+file[4:], "wb") as f:
        f.write(fileToSave.content)
    with open(path+"/cmake-build-debug"+file[4:], "wb") as f:
        f.write(fileToSave.content)
