# Install Docker on debian

```
sudo apt-get -y remove docker docker-engine docker.io
sudo apt-get update
sudo apt-get install -y apt-transport-https ca-certificates wget software-properties-common
wget https://download.docker.com/linux/debian/gpg 
sudo apt-key add gpg
echo "deb [arch=amd64] https://download.docker.com/linux/debian $(lsb_release -cs) stable" | sudo tee -a /etc/apt/sources.list.d/docker.list
sudo apt-get update
sudo apt-cache policy docker-ce
sudo apt-get -y install docker-ce
sudo systemctl start docker
```

# allow non-root to run docker

```
sudo groupadd docker
sudo usermod -aG docker thedevilsvoice
```

# Start arduino IDE

```
sudo docker build -t "nola_con_2018_badge" .
sudo ./arduino.sh

```

