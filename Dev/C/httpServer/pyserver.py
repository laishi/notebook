import ctypes

# 加载共享库
server_lib = ctypes.CDLL('./server.so')

# 调用共享库中的函数
# 这里假设共享库中有一个名为 start_server 的函数
server_lib.start_server()

