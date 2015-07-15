FROM ubuntu
RUN apt-get update
RUN apt-get install -qqy x11-apps
RUN apt-get install -qqy build-essential
RUN apt-get install -qqy cmake libgtk-3-dev pkg-config
RUN apt-get install -qqy libgtkmm-3.0-dev
RUN apt-get install -qqy libxml++2.6-dev
RUN apt-get install -qqy glade
RUN apt-get install -qqy git
RUN apt-get install -qqy libavcodec-dev libavformat-dev libswscale-dev
ADD	build_opencv.sh	/build_opencv.sh
RUN	/bin/sh /build_opencv.sh
RUN	rm -rf /build_opencv.sh
ENV DISPLAY :0
