#!/bin/bash

echo "deploying"
sudo mkdir -p ~/usr/lib/cgi-bin/
sudo mkdir -p ~/usr/lib/db
sudo cp db/*.xml ~/usr/lib/db
sudo cp ./build/BankApp.cgi ~/usr/lib/cgi-bin/
sudo chmod 755 ~/usr/lib/cgi-bin/BankApp.cgi
sudo mkdir -p ~/etc/apache2/conf.d/
sudo mkdir -p ~/etc/apache2/conf.d/
sudo cp ./configs/ubuntu_apache.conf ~/etc/apache2/conf.d/
sudo cp ./configs/msmtprc ~/etc/