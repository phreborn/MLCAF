FROM atlas/analysisbase:21.2.39
ADD . /hww/BSMtautauCAF
WORKDIR /hww/build
RUN source ~/release_setup.sh &&  \
    sudo chown -R atlas /hww && \
    cmake ../BSMtautauCAF && \
    make -j4

