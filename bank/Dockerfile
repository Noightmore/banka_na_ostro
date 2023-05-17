FROM ubuntu:latest

# Install any necessary dependencies or packages
#RUN apt-get update && apt-get install -y \
    # Package1 \
    # Package2 \
    # ...
RUN ls -la

# Set the working directory to /app
WORKDIR /bankApp

# Copy the entire repository into the container at /app
COPY . /bankApp

RUN ls -la

# Run your scripts or commands inside the container
RUN chmod +x scripts/install_dependencies.sh  # Make the scripts executable
RUN scripts/install_dependencies.sh  # Replace with your script/command
#RUN ./script2.sh  # Replace with your script/command

# Define any additional configuration or settings
EXPOSE 80

# Start the application or execute any other final command
CMD ["/bin/bash"]
