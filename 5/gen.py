#coding=utf8
import os
import re
import zipfile
import sys
R = re.compile(r"(\d+)")

_, fileName = os.path.split(os.getcwd())
myName = sys.argv[0]
Rm = R.match(fileName)
num = Rm.group(1)

fileList = []

for root, dirs, files in os.walk("."):
    for file in files:
        name, ext = os.path.splitext(file)
        if (ext == ".py" and name+ext != myName or ext == ".cpp" or ext == ".c" or ext == ".pdf" or ext == ".docx"):
            fileList.append(os.path.join(root, file))
            
zf = zipfile.ZipFile("1652270-冯舜-算法作业%s.zip".decode("utf-8") % num, "w", zipfile.zlib.DEFLATED)
for file in fileList:
    _, fileName = os.path.split(file)
    zf.write(file, fileName)
zf.close()