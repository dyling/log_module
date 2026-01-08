# 基础镜像
FROM ubuntu:20.04

# 维护者信息（可选）
LABEL maintainer="dyling@cisaitech.com"

# 设置默认工作目录
WORKDIR /app

COPY ./sources.list.20.04 /etc/apt/sources.list

# sources.list 中的地址为http而不是https时
RUN apt update --allow-unauthenticated \
    && apt install --reinstall ca-certificates -y \
    && update-ca-certificates --fresh

# 避免交互弹窗
ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && \
    apt clean && apt update --fix-missing && \
    apt install -y --no-install-recommends   \
    vim   \
    wget \
    curl \
    build-essential   \
    cmake   \
    git \
    net-tools   \
    libcurl4-openssl-dev libssl-dev libz-dev libncurses5-dev   \
    libpthread-stubs0-dev   \
    libtool autoconf automake   \
    python3 python3-pip \
    libbz2-dev \
    liblzma-dev \
    zlib1g-dev \
    tar && \
    apt clean && \
    rm -rf /var/lib/apt/lists/*

RUN apt update  \
    && apt install -y --no-install-recommends   \
    openssh-server \
    && apt clean  \
    && rm -rf /var/lib/apt/lists/*

RUN cat <<-EOF >> /etc/ssh/sshd_config
PermitRootLogin yes
PubkeyAuthentication yes
EOF

################################################################################
# # download boost
# # RUN cd /tmp/ \
# #     && wget https://sourceforge.net/projects/boost/files/boost/1.81.0/boost_1_81_0.tar.gz \
# #     && tar -xvzf boost_1_81_0.tar.gz 
# COPY ./boost_1_81_0 /tmp/

# # install boost
# RUN cd /tmp/boost_1_81_0 \
#     && ./bootstrap.sh --prefix=/usr/local \
#     && ./b2 install --with-chrono  \
#     && cd -

# # install qt-dev
# RUN apt install -y qtbase5-dev libqt5serialbus5-dev libqt5serialport5-dev 

##################################################################################

# 恢复环境变量
ENV DEBIAN_FRONTEND=dialog


# 设置容器启动默认命令
CMD ["service ssh start"]