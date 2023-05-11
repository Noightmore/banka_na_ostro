#!/bin/bash

function ubuntu_install_deps()
{
  # install dependencies
  echo "Installing dependencies"
  sudo apt update
  # essential tools - missing obvious ones like c++ compiler and cmake
  sudo apt install -y zip unzip build-essential pkg-config libpthread-stubs0-dev lcov libxml2 gcc cmake curl libcurl4 libcurl-dev libcurlpp-dev libcurl4-gnutls-dev


  # download and unpack vcpkg
  wget -qO vcpkg.tar.gz https://github.com/microsoft/vcpkg/archive/master.tar.gz
  sudo mkdir /opt/vcpkg
  sudo tar xf vcpkg.tar.gz --strip-components=1 -C /opt/vcpkg
  # install vcpkg
  sudo /opt/vcpkg/bootstrap-vcpkg.sh
  sudo ln -s /opt/vcpkg/vcpkg /usr/local/bin/vcpkg
  # link the vcpkg folder libraries to /usr/local/share/vcpkg (default vcpkg folder on ubuntu)
  #

#  # install cppcms (compilation included)
#  # this takes insane amount of time
#  # installation process taken from the official website: http://cppcms.com/wikipp/en/page/cppcms_1x_build
#  # only working solution
#  git clone git clone https://github.com/artyom-beilis/cppcms.git cppcms
#  cd cppcms
#  mkdir build
#  cd build
#  cmake .. -DCMAKE_BUILD_TYPE=Release -DDISABLE_SHARED=ON -DCMAKE_CXX_FLAGS="-Wno-deprecated-declarations"
#  make -j "$(nproc)"
#  sudo make install
#
#  # update ld indexing
#  sudo ldconfig

  # verify whether dependencies are installed
  ubuntu_verify_deps
  ubuntu_clean_up

  # where lib folder?
  # vcpkg integrate install

  # install vcpkg libraries
  ubuntu_install_vcpkg_libs
}

function ubuntu_verify_deps()
{
  # verify dependencies
  echo "Verifying dependencies"
  # check if vcpkg is installed
  if ! command -v /usr/local/bin/vcpkg &> /dev/null
  then
      echo "vcpkg could not be found"
      exit
  fi
  echo "vcpkg ok"
}

function ubuntu_clean_up()
{
  # clean up
  echo "Cleaning up"
  sudo rm -rf vcpkg.tar.gz
}

function ubuntu_install_vcpkg_libs()
{
  # install vcpkg libraries
  echo "Configuring vcpkg"
  /usr/local/bin/vcpkg update
  # libxml2
  /usr/local/bin/vcpkg install gtest
}

function main()
{
  # Install dependencies for the project
  if [[ "$OSTYPE" == "linux-gnu"* ]]; then
      # shellcheck disable=SC2002
      os_id=$(cat /etc/os-release | grep ^ID= | cut -d '=' -f 2)
      if [[ "$os_id" == "ubuntu" ]]; then
        echo "we are in ubuntu yay"
        ubuntu_install_deps
      else
        echo "Your distro - $os_id - is sadly not supported and we are very sorry :("
      fi
  elif [[ "$OSTYPE" == "win32"* ]]; then
      echo "Windows is not supported"
  fi
}

main
