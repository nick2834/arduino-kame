# -*- coding: UTF-8 -*-

import socket
import sys

c = socket.socket()  # 创建socket对象
c.connect(('192.168.1.101', 8266))  # 建立连接
while True:
    ab = input('客户端发出：')
    if ab == 'quit':
        c.close()  # 关闭客户端连接
        sys.exit(0)
    else:
        c.send(ab.encode('utf-8'))  # 发送数据
        data = c.recv(1024)  # 接收一个1024字节的数据
        print('收到：', data.decode('utf-8'))
