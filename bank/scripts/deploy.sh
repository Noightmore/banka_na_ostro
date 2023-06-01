#!/bin/bash

echo "deploying"
mkdir -p /home/azureuser/bank_update
tar –xzf bank.tar -C /home/azureuser/bank_update
ls -al
sudo mkdir -p ~/usr/lib/cgi-bin/
sudo mkdir -p ~/usr/lib/db
sudo cp bank_update/bank/db/*.xml ~/usr/lib/db
sudo cp ~/BankApp.cgi ~/usr/lib/cgi-bin/
sudo chmod 755 ~/usr/lib/cgi-bin/BankApp.cgi
sudo mkdir -p ~/etc/apache2/conf.d/
sudo mkdir -p ~/etc/apache2/conf.d/
sudo cp bank_update/bank/configs/ubuntu_apache.conf ~/etc/apache2/conf.d/
sudo cp bank_update/bank/configs/msmtprc ~/etc/