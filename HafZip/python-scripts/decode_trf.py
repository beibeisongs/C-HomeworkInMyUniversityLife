# encoding=utf-8

import docx
import sys


def transfer(ded_doc):

    text_name = "D:\\USBei\\C++Projects\\Zip_Tool\\Zip_Tool\\1_doc.txt"
    f_txt = open(text_name, mode='r')

    # 获取文档对象

    doc = docx.Document()
    for line in f_txt.readlines():
        doc.add_paragraph(line, style=None)

    doc.save(ded_doc)

transfer(sys.argv[1])
