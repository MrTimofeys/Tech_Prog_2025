FROM ubuntu:22.04

ENV TZ=Europe/Moscow
RUN ln -fs /usr/share/zoneinfo/$TZ /etc/localtime

RUN apt-get update && apt-get install -y \
    git \
    qtbase5-dev \
    qttools5-dev-tools \
    build-essential \
    libqt5websockets5-dev \
    libqt5sql5-sqlite \
    libx11-xcb1 \          # Для работы с X11
    libgl1-mesa-glx \      # OpenGL
    xauth \                # Авторизация X11
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
RUN git clone --branch main https://github.com/MrTimofeys/Tech_Prog_2025.git .
WORKDIR /app
RUN qmake && make

ENV DISPLAY=:0
ENV QT_X11_NO_MITSHM=1

EXPOSE 33333

CMD ["./echoServer"]