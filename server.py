import socketserver
import socket

HOST = "0.0.0.0"
PORT = 44344

class MyTCPHandler(socketserver.BaseRequestHandler):
    def handle(self):
        while True:
            self.data = self.request.recv(1024).strip()
            self.request.sendall(self.data[::-1])

if __name__ == "__main__":
    server = socketserver.ThreadingTCPServer((HOST, PORT), MyTCPHandler)
    server.socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
    server.socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_QUICKACK, 1)

    # Activate the server; this will keep running until you
    # interrupt the program with Ctrl-C
    server.serve_forever()
