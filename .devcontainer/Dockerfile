FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04

# [Optional] Uncomment this section to install additional vcpkg ports.
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install <your-port-name-here>"

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    wget

# Install Cosmopolitan toolchain
RUN mkdir -p /cosmocc
RUN cd /cosmocc
RUN wget https://cosmo.zip/pub/cosmocc/cosmocc.zip
RUN unzip cosmocc.zip -d /cosmocc
# RUN rm /cosmocc/cosmocc.zip

# Add cosmocc to PATH
ENV PATH="/cosmocc/bin:/comsocc/lib:/comsocc/include:${PATH}"
