FROM atlas/analysisbase:21.2.34
ADD . /hww/CAFExample
WORKDIR /hww/build
RUN source ~/release_setup.sh &&  \
    sudo chown -R atlas /hww && \
    cmake ../CAFExample && \
    make -j4

