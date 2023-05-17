FROM ubuntu:latest

# Install any necessary dependencies or packages
RUN apt-get update && apt-get install -y \
    zip  \
    unzip  \
    build-essential  \
    pkg-config  \
    libpthread-stubs0-dev \
    libxml2  \
    gcc  \
    cmake  \
    wget  \
    msmtp \

# install vcpkg
RUN  wget -qO vcpkg.tar.gz https://github.com/microsoft/vcpkg/archive/master.tar.gz \
      mkdir /opt/vcpkg \
      tar xf vcpkg.tar.gz --strip-components=1 -C /opt/vcpkg \
      /opt/vcpkg/bootstrap-vcpkg.sh \
      ln -s /opt/vcpkg/vcpkg /usr/local/bin/vcpkg


# VERIFY VCPKG

RUN  echo "Verifying dependencies" \
  # check if vcpkg is installed
  if ! command -v /usr/local/bin/vcpkg &> /dev/null \
  then \
      echo "vcpkg could not be found" \
      exit \
  fi \
  echo "vcpkg ok" \

RUN ls -la

# Set the working directory to /app
WORKDIR /bankApp

# Copy the entire repository into the container at /app
COPY . /bankApp

RUN ls -la



# Define any additional configuration or settings
EXPOSE 80

# Start the application or execute any other final command
CMD ["/bin/bash"]
