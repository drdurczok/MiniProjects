# Virtual Env Installation

Step 1: Update your repositories

```sudo apt-get update```

Step 2: Install pip for Python 3

```sudo apt-get install build-essential libssl-dev libffi-dev python-dev```

```sudo apt install python3-pip```

Step 3: Use pip to install virtualenv

```sudo pip3 install virtualenv```

Step 4: Launch your Python 3 virtual environment, here the name of my virtual environment will be env3

```virtualenv -p python3 env3```

Step 5: Activate your new Python 3 environment. There are two ways to do this

```. env3/bin/activate``` or ```source env3/bin/activate```

Step 6: To leave the virtual environment

```deactivate```

# Ursina Installation

```pip install ursina```
