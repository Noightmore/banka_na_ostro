#!/bin/bash

function ubuntu_install_web_server()
{
  # web server
  sudo apt install -y apache2 libapache2-mod-fcgid
  sudo systemctl start apache2
  sudo systemctl enable apache2
  sudo a2enmod fcgid

  sudo mkdir -p /var/www/bank
  sudo mkdir -p /var/www/db
  sudo cp configs/ubuntu_apache.conf /etc/apache2/sites-available/bank.conf
  sudo a2ensite bank.conf
  sudo chmod ugo+x build/BankApp.fcgi
  sudo cp build/BankApp.fcgi /var/www/bank/BankApp.fcgi
  sudo chmod ugo+rw db/*.xml
  sudo cp db/*.xml /var/www/db
  sudo systemctl restart apache2
  sudo systemctl reload apache2
}

function main()
{
  # Install webserver application
  if [[ "$OSTYPE" == "linux-gnu"* ]]; then
      # shellcheck disable=SC2002
      os_id=$(cat /etc/os-release | grep ^ID= | cut -d '=' -f 2)
      if [[ "$os_id" == "ubuntu" ]]; then
        echo "we are in ubuntu yay"
        ubuntu_install_web_server
      else
        echo "Your distro - $os_id - is sadly not supported and we are very sorry :("
      fi
  elif [[ "$OSTYPE" == "win32"* ]]; then
      echo "Windows is not supported"
  fi
}

main