import socket

HOST = "0.0.0.0"
PORT = 44344

while True:
    print("Accepting connections...")
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
        s.setsockopt(socket.IPPROTO_TCP, socket.TCP_QUICKACK, 1)
        s.bind((HOST, PORT))
        s.listen()
        conn, addr = s.accept()
        with conn:
            print(f"Connected by {addr}.")
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                data = data.decode("utf-8").rstrip()
                print(f"{addr} --> {data}")
                print(f"{(HOST, PORT)} --> {data[::-1]}")
                conn.sendall((data[::-1] + "\n").encode())