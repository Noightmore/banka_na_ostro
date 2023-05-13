#!/bin/bash

test_send_email()
{
  echo "Testing send email"
  touch error.log.txt
  echo -e "Subject: Regards\n\nTest Passed!" | msmtp -a outlook bitcoin.tul.cz@outlook.com 2> error.log.txt
  cat error.log.txt
}

main()
{
  test_send_email
}

main