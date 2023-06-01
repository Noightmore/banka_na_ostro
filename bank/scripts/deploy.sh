#!/bin/bash

echo "deploying"
mkdir -p /home/azureuser/db_update
tar –xzf db.tar -C /home/azureuser/bank_update/db_update
ls -al
sudo mkdir -p ~/usr/lib/cgi-bin/
sudo mkdir -p ~/usr/lib/db
sudo cp bank_na_ostro/bank/db/*.xml ~/usr/lib/db
sudo cp ~/BankApp.cgi ~/usr/lib/cgi-bin/
sudo chmod 755 ~/usr/lib/cgi-bin/BankApp.cgi
sudo mkdir -p ~/etc/apache2/conf.d/
sudo mkdir -p ~/etc/apache2/conf.d/
sudo cp bank_na_ostro/bank/configs/ubuntu_apache.conf ~/etc/apache2/conf.d/
sudo cp bank_una_ostro/bank/configs/msmtprc ~/etc/