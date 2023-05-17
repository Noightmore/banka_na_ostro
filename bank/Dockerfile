FROM debian:latest

# Install any necessary dependencies or packages
RUN apt-get update && apt-get install -y \
    libpthread-stubs0-dev \
    libxml2  \
    wget  \
    apache2 \
    msmtp

RUN ls -la

# Set the working directory to /app
WORKDIR /bankApp

# Copy the entire repository into the container at /app
COPY . /bankApp

RUN ls -la

#install bank as a webapp
RUN a2enmod cgi \
    mkdir -p /usr/lib/cgi-bin/ \
    mkdir -p /usr/lib/db \
    cp db/*.xml /usr/lib/db \
    cp ./build/BankApp.cgi /usr/lib/cgi-bin/ \
    chmod 755 /usr/lib/cgi-b \
    chmod -R 755 /usr/lib/db \
    mkdir -p /etc/apache2/conf.d/ \
    cp ./configs/ubuntu_apache.conf /etc/apache2/conf.d/ \
    cp ./configs/msmtprc /etc/ \
    systemctl restart apache2 \

# Define any additional configuration or settings
EXPOSE 80

# Start the application or execute any other final command
CMD ["/bin/bash"]
