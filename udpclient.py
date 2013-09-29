import socket
clisocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
while 1:
      data = "data"
          if data:
                    clisocket.sendto(data, ("131.204.14.189", 10024))
