#!/bin/bash

function ubuntu_install_web_server()
{

  echo "Configuring apache"
  sudo apt install -y apache2 libapache2-mod-fcgid msmtprc
  sudo a2enmod cgi
  sudo a2enmod fcgid
  sudo mkdir -p /usr/lib/cgi-bin/
  sudo mkdir -p /usr/lib/db
  sudo cp db/*.xml /usr/lib/db
  sudo cp ./build/BankApp.cgi /usr/lib/cgi-bin/
  sudo chmod 755 /usr/lib/cgi-bin/BankApp.cgi
  sudo mkdir -p /etc/apache2/conf.d/
  sudo cp ./configs/ubuntu_apache.conf /etc/apache2/conf.d/
  sudo cp ./configs/msmtprc /etc/
  #sudo service apache2 restart
  sudo systemctl restart apache2

  # web server
#  sudo apt install -y apache2 libapache2-mod-fcgid
#  sudo systemctl start apache2
#  sudo systemctl enable apache2
#  sudo a2enmod fcgid
#
#  sudo mkdir -p /var/www/html
#  sudo mkdir -p /var/www/db
#  sudo cp configs/ubuntu_apache.conf /etc/apache2/conf.d/bank.conf
#  sudo a2ensite bank.conf
#  sudo mv build/BankApp.fcgi /var/www/html/BankApp.fcgi
#  sudo chmod -R 755 /var/www/html/BankApp.fcgi
#  ls -l /var/www/html/BankApp.fcgi
#  sudo chmod -R 755 db/*.xml
#  sudo cp db/*.xml /var/www/db
#  sudo systemctl restart apache2
#  sudo systemctl reload apache2

  # nginx
#  sudo apt update
#  sudo apt install -y nginx libfcgi-dev g++ make
#  sudo hostnamectl set-hostname example.com
#  sudo mkdir /var/www/bank.com
#  sudo mkdir -p /var/www/db
#  sudo cp configs/ubuntu_nginx.com /etc/nginx/sites-available/bank.conf
#  sudo cp build/BankApp.fcgi /var/www/bank/index.fcgi
#  sudo systemctl enable fcgiwrap
#  sudo systemctl start fcgiwrap
#  sudo systemctl enable nginx
#  sudo systemctl start nginx
#
#  sudo ln -s /etc/nginx/sites-available/bank.conf /etc/nginx/sites-enabled/
#
#  sudo systemctl restart nginx
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