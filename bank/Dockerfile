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

# Define any additional configuration or settings
EXPOSE 80

# Start the application or execute any other final command
CMD ["/bin/bash"]
