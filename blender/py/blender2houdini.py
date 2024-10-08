import bpy
import json
import threading
import socket

def get_gp_data():
    gp = bpy.data.objects["GPStroke"].data
    gp_frame = gp.layers[0].frames[0]
    gp_strokes = gp_frame.strokes

    stroke_data = {
        'status': '',
        'co': [],
        'pressure': [],
    }

    for stroke in gp_strokes:
        stroke_data['co'].append([list(point.co) for point in stroke.points])
        stroke_data['pressure'].append([point.pressure for point in stroke.points])
    return stroke_data


def get_last_stroke_data():
    gp_data = get_gp_data()
    num_strokes = len(gp_data['co'])
    
    if num_strokes == 0:
        return None
    
    last_stroke_data = {
        'status': '',
        'co': gp_data['co'][-1],
        'pressure': gp_data['pressure'][-1],

    }

    return last_stroke_data


strokesNum = 0
def send_data(scene, depsgraph):
    global strokesNum   
    strokes_len = len(bpy.data.objects["GPStroke"].data.layers[0].frames[0].strokes)
        
    if strokes_len > strokesNum or strokes_len == 1:
        end_stroke_data = get_last_stroke_data()
        end_stroke_data['status'] = 'new'
        message = json.dumps(end_stroke_data).encode('utf-8')
        print(message)
        send_message(message)
    if strokes_len <= strokesNum:
        stroke_data = get_gp_data()
        stroke_data['status'] = 'remove'
        message = json.dumps(stroke_data).encode('utf-8')
        print(message)
        send_message(message)
    
    strokesNum = strokes_len


def send_message(message):
    HOST = '127.0.0.1'
    PORT = 9001
    
    print(f"send data server at:{HOST}:{PORT}")
    
    def send_message_thread():
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.connect((HOST, PORT))
                s.sendall(message)
        except Exception as e:
            print(f"Failed to send message: {e}")
    
    thread = threading.Thread(target=send_message_thread, name='houdiniStroke')
    thread.setDaemon(True) 
    thread.start()


# 清除depsgraph_update_post的所有注册函数
bpy.app.handlers.depsgraph_update_post.clear()
# 注册绘制回调函数
bpy.app.handlers.depsgraph_update_post.append(send_data)

