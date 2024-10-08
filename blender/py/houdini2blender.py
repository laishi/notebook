
import socket
import threading
import json


node = hou.pwd()
geo = node.geometry()

strokesSession = hou.session.strokes = {"status": "", "co": [], "time": [], "pressure": [], "strength": [], "uv_rotation": [], "vertex_color": []}

def receive_data(socket, houModule, jsonModule):
    HOST = '127.0.0.1'  # Houdini的IP地址
    PORT = 9001
    thisNode = houModule.node('/obj/Strokes/pythonStroke')

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen(1)
        
        while True:
            conn, addr = s.accept()
            
            with conn:
                data = b''
                while True:
                    chunk = conn.recv(1024)  # 每次接收的数据块大小
                    if not chunk:
                        break
                    data += chunk
                
                # 对接收到的完整数据进行处理
                if data:
                    dataString = data.decode('utf-8')
                    thisNode.parm('data').set(dataString)
                    
                    dataJson = jsonModule.loads(dataString)
                    
                    status = dataJson['status']
                    
                    # print(status)
                    
                    if status == "new":
                        co = dataJson['co'] 
                        pressure = dataJson['pressure']
                        
                        houModule.session.strokes['status']="new"
                        houModule.session.strokes['co'].append(co)
                        houModule.session.strokes['pressure'].append(pressure)
                                        
                    if status == "remove":
                        houModule.session.strokes = dataJson
             
                    
def get_stroke():
    receive_thread = threading.Thread(target=receive_data,  args=(socket, hou, json,), name='houdiniReceive')
    receive_thread.start()

get_stroke()

